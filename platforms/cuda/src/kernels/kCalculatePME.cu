/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2009-2010 Stanford University and the Authors.      *
 * Authors: Erik Lindahl, Rossen Apostolov, Szilard Pall, Peter Eastman       *
 * Contributors:                                                              *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU Lesser General Public License as published   *
 * by the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 * -------------------------------------------------------------------------- */

#include "gputypes.h"
#include "bbsort.h"
#include <cuda.h>

using namespace std;

static __constant__ cudaGmxSimulation cSim;

/* Cuda compiler on Windows does not recognized "static const float" values */
#define LOCAL_HACK_PI 3.1415926535897932384626433832795

void SetCalculatePMESim(gpuContext gpu)
{
    cudaError_t status;
    status = cudaMemcpyToSymbol(cSim, &gpu->sim, sizeof(cudaGmxSimulation));
    RTERROR(status, "cudaMemcpyToSymbol: SetSim copy to cSim failed");
}

void GetCalculatePMESim(gpuContext gpu)
{
    cudaError_t status;
    status = cudaMemcpyFromSymbol(&gpu->sim, cSim, sizeof(cudaGmxSimulation));
    RTERROR(status, "cudaMemcpyFromSymbol: SetSim copy from cSim failed");
}

texture<float4, 1, cudaReadModeElementType> bsplineThetaRef;

inline __host__ __device__ int fast_mod(int a, int b)
{
    return (b & (b - 1)) ? a % b : a & (b - 1);
}
inline __host__ __device__ float4 make_float4(float s)
{
    return make_float4(s, s, s, s);
}
inline __host__ __device__ float4 operator-(float4 &a)
{
    return make_float4(-a.x, -a.y, -a.z, -a.w);
}
inline __host__ __device__ float4 operator-(float4 a, float4 b)
{
    return make_float4(a.x - b.x, a.y - b.y, a.z - b.z,  a.w - b.w);
}
inline __host__ __device__ float4 operator+(float4 a, float4 b)
{
    return make_float4(a.x + b.x, a.y + b.y, a.z + b.z,  a.w + b.w);
}
inline __host__ __device__ float4 operator+(float4 a, float b)
{
    return make_float4(a.x + b, a.y + b, a.z + b, a.w + b);
}
inline __host__ __device__ float4 operator+(float a, float4 b)
{
    return make_float4(a + b.x, a + b.y, a + b.z,  a + b.w);
}
inline __host__ __device__ float4 operator*(float s, float4 a)
{
    return make_float4(a.x * s, a.y * s, a.z * s, a.w * s);
}
inline __host__ __device__ float4 operator*(float4 a, float4 b)
{
    return make_float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w + b.w);
}
inline __host__ __device__ float4 make_float4(int3 a)
{
    return make_float4((float) a.x, (float) a.y, (float) a.z, 0);
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(1024, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(512, 1)
#else
__launch_bounds__(256, 1)
#endif
void kUpdateBsplines_kernel()
{
    unsigned int    tnb = blockDim.x * gridDim.x;
    unsigned int    tid = blockIdx.x * blockDim.x + threadIdx.x;
    extern __shared__ float4 bsplines_cache[]; // size = 2 * block_size * pme_order

    const float4 div_o   = make_float4(1.0f/(PME_ORDER - 1));

    for (int i = tid; i < cSim.atoms; i += tnb)
    {

        float4* data    = &bsplines_cache[threadIdx.x*PME_ORDER];
        float4* ddata   = &bsplines_cache[threadIdx.x*PME_ORDER + blockDim.x*PME_ORDER];

        for (int j = 0; j < PME_ORDER; j++)
        {
	    data[j] = make_float4(0.0f);
            ddata[j] = make_float4(0.0f);
        }

        float4 posq = cSim.pPosq[i];
        posq.x -= floorf(posq.x*cSim.invPeriodicBoxSizeX)*cSim.periodicBoxSizeX;
        posq.y -= floorf(posq.y*cSim.invPeriodicBoxSizeY)*cSim.periodicBoxSizeY;
        posq.z -= floorf(posq.z*cSim.invPeriodicBoxSizeZ)*cSim.periodicBoxSizeZ;
        float3 t = make_float3((posq.x*cSim.invPeriodicBoxSizeX)*cSim.pmeGridSize.x,
                               (posq.y*cSim.invPeriodicBoxSizeY)*cSim.pmeGridSize.y,
                               (posq.z*cSim.invPeriodicBoxSizeZ)*cSim.pmeGridSize.z);
        float4 dr = make_float4(t.x-(int) t.x, t.y-(int) t.y, t.z-(int) t.z, 0.0f);
        int3 gridIndex = make_int3(((int) t.x) % cSim.pmeGridSize.x,
                              ((int) t.y) % cSim.pmeGridSize.y,
                              ((int) t.z) % cSim.pmeGridSize.z);
        cSim.pPmeAtomGridIndex[i] = make_int2(i, gridIndex.x*cSim.pmeGridSize.y*cSim.pmeGridSize.z+gridIndex.y*cSim.pmeGridSize.z+gridIndex.z);

        data[PME_ORDER - 1] = make_float4(0.0f);
        data[1]            = dr;
        data[0]            = make_float4(1.0f) - dr;

        for (int j = 3; j < PME_ORDER; j++)
        {
            float div = 1.0f / ((float)j - 1.0f);
            data[j - 1] = div * dr * data[j - 2];

            for (int k = 1; k < (j - 1); k++)
            {
                data[j - k - 1] =
                   div * (
                           (dr + float(k))          * data[j - k - 2] +
                           (-dr + ((float)(j - k))) * data[j - k - 1]);
            }
            data[0] = div * (- dr + 1) * data[0];
        }

        ddata[0] = -data[0];

        for (int j = 1; j < PME_ORDER; j++)
            ddata[j] = data[j - 1] - data[j];

        data[PME_ORDER - 1] = div_o * dr * data[PME_ORDER - 2];

        for (int j = 1; j < (PME_ORDER - 1); j++)
        {
            data[PME_ORDER - j - 1] =
                div_o * (
                    (dr + (float)j)                 * data[PME_ORDER - j - 2] +
                    (-dr + ((float)(PME_ORDER - j))) * data[PME_ORDER - j - 1]
                );
        }
        data[0] = div_o * (-dr + 1.0f) * data[0];

        for (int j = 0; j < PME_ORDER; j++)
        {
            data[j].w = posq.w; // Storing the charge here improves cache coherency in the charge spreading kernel
            cSim.pPmeBsplineTheta[i + j*cSim.atoms] =  data[j];
            cSim.pPmeBsplineDtheta[i + j*cSim.atoms] = ddata[j];
        }
    }
}

/**
 * For each grid point, find the range of sorted atoms associated with that point.
 */
__global__
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(1024, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(512, 1)
#else
__launch_bounds__(256, 1)
#endif
void kFindAtomRangeForGrid_kernel()
{
    int thread = blockIdx.x*blockDim.x+threadIdx.x;
    int start = (cSim.atoms*thread)/(blockDim.x*gridDim.x);
    int end = (cSim.atoms*(thread+1))/(blockDim.x*gridDim.x);
    int last = (start == 0 ? -1 : cSim.pPmeAtomGridIndex[start-1].y);
    for (int i = start; i < end; ++i)
    {
        int2 atomData = cSim.pPmeAtomGridIndex[i];
        int gridIndex = atomData.y;
        if (gridIndex != last)
        {
            for (int j = last+1; j <= gridIndex; ++j)
                cSim.pPmeAtomRange[j] = i;
            last = gridIndex;
        }

        // The grid index won't be needed again.  Reuse that component to hold the z index, thus saving
        // some work in the charge spreading kernel.

        float posz = cSim.pPosq[atomData.x].z;
        posz -= floorf(posz*cSim.invPeriodicBoxSizeZ)*cSim.periodicBoxSizeZ;
        int z = ((int) ((posz*cSim.invPeriodicBoxSizeZ)*cSim.pmeGridSize.z)) % cSim.pmeGridSize.z;
        cSim.pPmeAtomGridIndex[i].y = z;
    }

    // Fill in values beyond the last atom.

    if (thread == blockDim.x*gridDim.x-1)
    {
        int gridSize = cSim.pmeGridSize.x*cSim.pmeGridSize.y*cSim.pmeGridSize.z;
        for (int j = last+1; j <= gridSize; ++j)
            cSim.pPmeAtomRange[j] = cSim.atoms;
    }
}

__global__
void kGridSpreadCharge_kernel()
{
    unsigned int numGridPoints = cSim.pmeGridSize.x*cSim.pmeGridSize.y*cSim.pmeGridSize.z;
    unsigned int numThreads = gridDim.x*blockDim.x;
    for (int gridIndex = blockIdx.x*blockDim.x+threadIdx.x; gridIndex < numGridPoints; gridIndex += numThreads)
    {
        int3 gridPoint;
        gridPoint.x = gridIndex/(cSim.pmeGridSize.y*cSim.pmeGridSize.z);
        int remainder = gridIndex-gridPoint.x*cSim.pmeGridSize.y*cSim.pmeGridSize.z;
        gridPoint.y = remainder/cSim.pmeGridSize.z;
        gridPoint.z = remainder-gridPoint.y*cSim.pmeGridSize.z;
        float result = 0.0f;
        for (int ix = 0; ix < PME_ORDER; ++ix)
        {
            int x = gridPoint.x-ix+(gridPoint.x >= ix ? 0 : cSim.pmeGridSize.x);
            for (int iy = 0; iy < PME_ORDER; ++iy)
            {
                int y = gridPoint.y-iy+(gridPoint.y >= iy ? 0 : cSim.pmeGridSize.y);
                int z1 = gridPoint.z-PME_ORDER+1;
                z1 += (z1 >= 0 ? 0 : cSim.pmeGridSize.z);
                int z2 = (z1 < gridPoint.z ? gridPoint.z : cSim.pmeGridSize.z-1);
                int gridIndex1 = x*cSim.pmeGridSize.y*cSim.pmeGridSize.z+y*cSim.pmeGridSize.z+z1;
                int gridIndex2 = x*cSim.pmeGridSize.y*cSim.pmeGridSize.z+y*cSim.pmeGridSize.z+z2;
                int firstAtom = cSim.pPmeAtomRange[gridIndex1];
                int lastAtom = cSim.pPmeAtomRange[gridIndex2+1];
                for (int i = firstAtom; i < lastAtom; ++i)
                {
                    int2 atomData = cSim.pPmeAtomGridIndex[i];
                    int atomIndex = atomData.x;
                    int z = atomData.y;
                    int iz = gridPoint.z-z+(gridPoint.z >= z ? 0 : cSim.pmeGridSize.z);
                    float atomCharge = tex1Dfetch(bsplineThetaRef, atomIndex+ix*cSim.atoms).w;
                    result += atomCharge*tex1Dfetch(bsplineThetaRef, atomIndex+ix*cSim.atoms).x*tex1Dfetch(bsplineThetaRef, atomIndex+iy*cSim.atoms).y*tex1Dfetch(bsplineThetaRef, atomIndex+iz*cSim.atoms).z;
                }
                if (z1 > gridPoint.z)
                {
                    gridIndex1 = x*cSim.pmeGridSize.y*cSim.pmeGridSize.z+y*cSim.pmeGridSize.z;
                    gridIndex2 = x*cSim.pmeGridSize.y*cSim.pmeGridSize.z+y*cSim.pmeGridSize.z+gridPoint.z;
                    firstAtom = cSim.pPmeAtomRange[gridIndex1];
                    lastAtom = cSim.pPmeAtomRange[gridIndex2+1];
                    for (int i = firstAtom; i < lastAtom; ++i)
                    {
                        int2 atomData = cSim.pPmeAtomGridIndex[i];
                        int atomIndex = atomData.x;
                        int z = atomData.y;
                        int iz = gridPoint.z-z+(gridPoint.z >= z ? 0 : cSim.pmeGridSize.z);
                        float atomCharge = tex1Dfetch(bsplineThetaRef, atomIndex+ix*cSim.atoms).w;
                        result += atomCharge*tex1Dfetch(bsplineThetaRef, atomIndex+ix*cSim.atoms).x*tex1Dfetch(bsplineThetaRef, atomIndex+iy*cSim.atoms).y*tex1Dfetch(bsplineThetaRef, atomIndex+iz*cSim.atoms).z;
                    }
                }
            }
        }
        cSim.pPmeGrid[gridIndex] = make_cuComplex(result*sqrtf(cSim.epsfac), 0.0f);
    }
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(1024, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(512, 1)
#else
__launch_bounds__(256, 1)
#endif
void kReciprocalConvolution_kernel()
{
    const unsigned int gridSize = cSim.pmeGridSize.x*cSim.pmeGridSize.y*cSim.pmeGridSize.z;
    float expFactor = LOCAL_HACK_PI*LOCAL_HACK_PI/(cSim.alphaEwald*cSim.alphaEwald);
    float scaleFactor = 1.0/(LOCAL_HACK_PI*cSim.periodicBoxSizeX*cSim.periodicBoxSizeY*cSim.periodicBoxSizeZ);
    float energy = 0.0f;
    for (int index = blockIdx.x*blockDim.x+threadIdx.x; index < gridSize; index += blockDim.x*gridDim.x)
    {
        int kx = index/(cSim.pmeGridSize.y*cSim.pmeGridSize.z);
        int remainder = index-kx*cSim.pmeGridSize.y*cSim.pmeGridSize.z;
        int ky = remainder/cSim.pmeGridSize.z;
        int kz = remainder-ky*cSim.pmeGridSize.z;
        if (kx == 0 && ky == 0 && kz == 0)
            continue;
        int mx = (kx < (cSim.pmeGridSize.x+1)/2) ? kx : (kx-cSim.pmeGridSize.x);
        int my = (ky < (cSim.pmeGridSize.y+1)/2) ? ky : (ky-cSim.pmeGridSize.y);
        int mz = (kz < (cSim.pmeGridSize.z+1)/2) ? kz : (kz-cSim.pmeGridSize.z);
        float mhx = mx*cSim.invPeriodicBoxSizeX;
        float mhy = my*cSim.invPeriodicBoxSizeY;
        float mhz = mz*cSim.invPeriodicBoxSizeZ;
        float bx = cSim.pPmeBsplineModuli[0][kx];
        float by = cSim.pPmeBsplineModuli[1][ky];
        float bz = cSim.pPmeBsplineModuli[2][kz];
        cuComplex grid = cSim.pPmeGrid[index];
        float m2 = mhx*mhx+mhy*mhy+mhz*mhz;
        float denom = m2*bx*by*bz;
        float eterm = scaleFactor*exp(-expFactor*m2)/denom;
        cSim.pPmeGrid[index] = make_cuComplex(grid.x*eterm, grid.y*eterm);
        energy += eterm*(grid.x*grid.x + grid.y*grid.y);
    }
    cSim.pEnergy[blockIdx.x*blockDim.x+threadIdx.x] += 0.5f*energy;
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(1024, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(512, 1)
#else
__launch_bounds__(256, 1)
#endif
void kGridInterpolateForce_kernel()
{
    for (int atom = blockIdx.x*blockDim.x+threadIdx.x; atom < cSim.atoms; atom += blockDim.x*gridDim.x)
    {
        float3 force = make_float3(0.0f, 0.0f, 0.0f);
        float4 posq = cSim.pPosq[atom];
        posq.x -= floorf(posq.x*cSim.invPeriodicBoxSizeX)*cSim.periodicBoxSizeX;
        posq.y -= floorf(posq.y*cSim.invPeriodicBoxSizeY)*cSim.periodicBoxSizeY;
        posq.z -= floorf(posq.z*cSim.invPeriodicBoxSizeZ)*cSim.periodicBoxSizeZ;
        float3 t = make_float3((posq.x*cSim.invPeriodicBoxSizeX)*cSim.pmeGridSize.x,
                               (posq.y*cSim.invPeriodicBoxSizeY)*cSim.pmeGridSize.y,
                               (posq.z*cSim.invPeriodicBoxSizeZ)*cSim.pmeGridSize.z);
        int3 gridIndex = make_int3(((int) t.x) % cSim.pmeGridSize.x,
                              ((int) t.y) % cSim.pmeGridSize.y,
                              ((int) t.z) % cSim.pmeGridSize.z);
        for (int ix = 0; ix < PME_ORDER; ix++)
        {
            int xindex = gridIndex.x+ix;
            xindex -= (xindex >= cSim.pmeGridSize.x ? cSim.pmeGridSize.x : 0);
            float tx = cSim.pPmeBsplineTheta[atom+ix*cSim.atoms].x;
            float dtx = cSim.pPmeBsplineDtheta[atom+ix*cSim.atoms].x;
            for (int iy = 0; iy < PME_ORDER; iy++)
            {
                int yindex = gridIndex.y+iy;
                yindex -= (yindex >= cSim.pmeGridSize.y ? cSim.pmeGridSize.y : 0);
                float ty = cSim.pPmeBsplineTheta[atom+iy*cSim.atoms].y;
                float dty = cSim.pPmeBsplineDtheta[atom+iy*cSim.atoms].y;
                for (int iz = 0; iz < PME_ORDER; iz++)
                {
                    int zindex               = gridIndex.z+iz;
                    zindex -= (zindex >= cSim.pmeGridSize.z ? cSim.pmeGridSize.z : 0);
                    float tz = cSim.pPmeBsplineTheta[atom+iz*cSim.atoms].z;
                    float dtz = cSim.pPmeBsplineDtheta[atom+iz*cSim.atoms].z;
                    int index                = xindex*cSim.pmeGridSize.y*cSim.pmeGridSize.z + yindex*cSim.pmeGridSize.z + zindex;
                    float gridvalue          = cSim.pPmeGrid[index].x;
                    force.x                 += dtx*ty*tz*gridvalue;
                    force.y                 += tx*dty*tz*gridvalue;
                    force.z                 += tx*ty*dtz*gridvalue;
                }
            }
        }
        float4 totalForce = cSim.pForce4[atom];
        float q = posq.w*sqrtf(cSim.epsfac);
        totalForce.x -= q*force.x*cSim.pmeGridSize.x*cSim.invPeriodicBoxSizeX;
        totalForce.y -= q*force.y*cSim.pmeGridSize.y*cSim.invPeriodicBoxSizeY;
        totalForce.z -= q*force.z*cSim.pmeGridSize.z*cSim.invPeriodicBoxSizeZ;
        cSim.pForce4[atom] = totalForce;
    }
}

void kCalculatePME(gpuContext gpu)
{
//    printf("kCalculatePME\n");
    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float4>();
    cudaBindTexture(NULL, &bsplineThetaRef, gpu->psPmeBsplineTheta->_pDevData, &channelDesc, gpu->psPmeBsplineTheta->_length*sizeof(float4));
    unsigned int threads = 16380/(2*PME_ORDER*sizeof(float4));
    kUpdateBsplines_kernel<<<gpu->sim.blocks, threads, 2*threads*PME_ORDER*sizeof(float4)>>>();
    LAUNCHERROR("kUpdateBsplines");
    bbSort(gpu->psPmeAtomGridIndex->_pDevData, gpu->natoms);
    kFindAtomRangeForGrid_kernel<<<gpu->sim.blocks, gpu->sim.update_threads_per_block>>>();
    LAUNCHERROR("kFindAtomRangeForGrid");
    kGridSpreadCharge_kernel<<<16*gpu->sim.blocks, 64>>>();
    LAUNCHERROR("kGridSpreadCharge");
    cufftExecC2C(gpu->fftplan, gpu->psPmeGrid->_pDevData, gpu->psPmeGrid->_pDevData, CUFFT_FORWARD);
    kReciprocalConvolution_kernel<<<gpu->sim.blocks, gpu->sim.nonbond_threads_per_block>>>();
    LAUNCHERROR("kReciprocalConvolution");
    cufftExecC2C(gpu->fftplan, gpu->psPmeGrid->_pDevData, gpu->psPmeGrid->_pDevData, CUFFT_INVERSE);
    kGridInterpolateForce_kernel<<<2*gpu->sim.blocks, gpu->sim.update_threads_per_block>>>();
    LAUNCHERROR("kGridInterpolateForce");
}
