/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2009 Stanford University and the Authors.           *
 * Authors: Scott Le Grand, Peter Eastman                                     *
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

#include "cudaKernels.h"
#include "amoebaCudaKernels.h"

static __constant__ cudaGmxSimulation cSim;
static __constant__ cudaAmoebaGmxSimulation cAmoebaSim;

void SetCalculateAmoebaGrycukSim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status         = cudaMemcpyToSymbol(cSim, &gpu->sim, sizeof(cudaGmxSimulation));
    RTERROR(status, "SetCalculateAmoebaGrycukSim: cudaMemcpyToSymbol: SetSim copy to cSim failed");
    status         = cudaMemcpyToSymbol(cAmoebaSim, &amoebaGpu->amoebaSim, sizeof(cudaAmoebaGmxSimulation));
    RTERROR(status, "SetCalculateAmoebaGrycukSim: cudaMemcpyToSymbol: SetSim copy to cAmoebaSim failed");
}

void GetCalculateAmoebaGrycukSim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status = cudaMemcpyFromSymbol(&gpu->sim, cSim, sizeof(cudaGmxSimulation));
    RTERROR(status, "GetCalculateAmoebaGrycukSim: cudaMemcpyFromSymbol: SetSim copy from cSim failed");
    status = cudaMemcpyFromSymbol(&amoebaGpu->amoebaSim, cAmoebaSim, sizeof(cudaAmoebaGmxSimulation));
    RTERROR(status, "GetCalculateAmoebaGrycukSim: cudaMemcpyFromSymbol: SetSim copy from cAmoebaSim failed");
}

struct GrycukParticle {

    float x;
    float y;
    float z;

    float radius;
    float scaledRadius;

    float bornSum;
};

__device__ void loadGrycukShared( struct GrycukParticle* sA, unsigned int atomI )
{
    // coordinates, radii and scaled radii

    sA->x                        = cSim.pPosq[atomI].x;
    sA->y                        = cSim.pPosq[atomI].y;
    sA->z                        = cSim.pPosq[atomI].z;

    sA->radius                   = cSim.pObcData[atomI].x;
    sA->scaledRadius             = cSim.pObcData[atomI].y;

}

__device__ void calculateGrycukBornRadiiPairIxn_kernel( GrycukParticle& atomI, GrycukParticle& atomJ, float*  bornSum ){

    /*
     * radius:       radius (TINKER rsolv)
     * scaledRadius: radius*overlap scale factor (TINKER rsolv*shct)
     *
     */

    float xr,yr,zr;
    float r,r2;
    
    float sk, sk2;
    float lik, uik;
    float lik3, uik3;
    float l2, l4, lr, l4r;
    float u2, u4, ur, u4r;
    float term;

    // decide whether to compute the current interaction;

    *bornSum = 0.0f;
    if( atomI.radius <= 0.0f ){
        return;
    }

    xr           = atomJ.x - atomI.x;
    yr           = atomJ.y - atomI.y;
    zr           = atomJ.z - atomI.z;

    r2           = xr*xr + yr*yr + zr*zr;
    r            = sqrtf(r2);

    sk           = atomJ.scaledRadius;
    sk2          = sk*sk;

    if( (atomI.radius + r) < sk ){
        lik       = atomI.radius;
        uik       = sk - r; 
        lik3      = lik*lik*lik;
        uik3      = uik*uik*uik;
        *bornSum -= (1.0f/uik3 - 1.0f/lik3);
    }

    uik = r + sk;
    if( (atomI.radius + r) < sk ){
        lik = sk - r; 
    } else if( r < (atomI.radius + sk) ){
        lik = atomI.radius;
    } else {
        lik = r - sk;
    }

    l2          = lik*lik; 
    l4          = l2*l2;
    lr          = lik*r;
    l4r         = l4*r; 

    u2          = uik*uik;
    u4          = u2*u2;
    ur          = uik*r; 
    u4r         = u4*r;

   term         = (3.0f*(r2-sk2)+6.0f*u2-8.0f*ur)/u4r - (3.0f*(r2-sk2)+6.0f*l2-8.0f*lr)/l4r;
  *bornSum     += term/16.0f;

}

__device__ void zeroGrycukParticleSharedField( struct GrycukParticle* sA )
{
    sA->bornSum               = 0.0f;
}

__global__ 
__launch_bounds__(384, 1)
void kReduceGrycukGbsaBornSum_kernel()
{
    unsigned int pos = (blockIdx.x * blockDim.x + threadIdx.x);
    
    while (pos < cSim.atoms)
    {   
        float sum   = 0.0f;
        float* pSt  = cSim.pBornSum + pos;
    
        // Get summed Born data
        for (int i = 0; i < cSim.nonbondOutputBuffers; i++)
        {   
            sum += *pSt;
            pSt += cSim.stride;
        }   
    
        // Now calculate Born radius

        float radius              = cSim.pObcData[pos].x;
        radius                    = 1.0f/(radius*radius*radius);
        sum                       = radius - sum;
        sum                       = sum <= 0.0f ? 1000.0f : powf( sum, -1.0f/3.0f );
        cSim.pBornRadii[pos]      = sum;

        pos                      += gridDim.x * blockDim.x;
    }   
}

/**---------------------------------------------------------------------------------------

   Reduce Born radii

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */

void kReduceGrycukGbsaBornSum( amoebaGpuContext amoebaGpu )
{

    kReduceGrycukGbsaBornSum_kernel<<<amoebaGpu->gpuContext->sim.blocks, 384>>>();
    LAUNCHERROR("kReduceGrycukGbsaBornSum");

    if( 0 ){
        static int callId                    = 0;
        gpuContext gpu                       = amoebaGpu->gpuContext;
        std::vector<int> fileId;
        fileId.push_back( callId++ );
        VectorOfDoubleVectors outputVector;
        cudaLoadCudaFloatArray( gpu->natoms,  1, gpu->psBornRadii, outputVector, gpu->psAtomIndex->_pSysData, 1.0f ); 
        cudaWriteVectorOfDoubleVectorsToFile( "BornRGry", fileId, outputVector );
    }   
}

// Include versions of the kernels for N^2 calculations.

#undef USE_OUTPUT_BUFFER_PER_WARP
#define METHOD_NAME(a, b) a##N2##b
#include "kCalculateAmoebaCudaGrycukBornRadii.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##N2ByWarp##b
#include "kCalculateAmoebaCudaGrycukBornRadii.h"

/**---------------------------------------------------------------------------------------

   Compute Born radii using Grycuk algorithm

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */


void kCalculateAmoebaGrycukBornRadii( amoebaGpuContext amoebaGpu )
{

    // ---------------------------------------------------------------------------------------

    gpuContext gpu = amoebaGpu->gpuContext;

    // apparently debug array can take up nontrivial no. registers

    // on first pass, set threads/block and based on that setting the energy buffer array

    static unsigned int threadsPerBlock = 0;
    if( threadsPerBlock == 0 ){
        unsigned int maxThreads;
        if (gpu->sm_version >= SM_20)
            //maxThreads = 384;
            maxThreads = 512;
        else if (gpu->sm_version >= SM_12)
            maxThreads = 128;
        else
            maxThreads = 64;
        threadsPerBlock = std::min(getThreadsPerBlock(amoebaGpu, sizeof(GrycukParticle), gpu->sharedMemoryPerBlock ), maxThreads);
    }

    if (gpu->bOutputBufferPerWarp){
        kCalculateAmoebaGrycukBornRadiiN2ByWarp_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(GrycukParticle)*threadsPerBlock>>>( gpu->psWorkUnit->_pDevData);
    } else {
       kCalculateAmoebaGrycukBornRadiiN2_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(GrycukParticle)*threadsPerBlock>>>( gpu->psWorkUnit->_pDevData);
    }
    LAUNCHERROR("kCalculateAmoebaCudaGrycukN2Forces");

   // ---------------------------------------------------------------------------------------
}

// Born radius chain rule component for Grycuk

struct GrycukChainRuleParticle {

    float x;
    float y;
    float z;

    float radius;
    float scaledRadius;

    float bornRadius;
    float bornForce;

    float force[3];
};

__device__ void loadGrycukChainRuleParticleShared( struct GrycukChainRuleParticle* sA, unsigned int atomI )
{
    // coordinates, radii and scaled radii

    sA->x                        = cSim.pPosq[atomI].x;
    sA->y                        = cSim.pPosq[atomI].y;
    sA->z                        = cSim.pPosq[atomI].z;

    sA->radius                   = cSim.pObcData[atomI].x;
    sA->scaledRadius             = cSim.pObcData[atomI].y;
    sA->bornRadius               = cSim.pBornRadii[atomI];
    sA->bornForce                = cSim.pBornForce[atomI];

}

__device__ void zeroGrycukChainRuleParticleSharedField( struct GrycukChainRuleParticle* sA )
{
    // zero force

    sA->force[0]                 = 0.0f;
    sA->force[1]                 = 0.0f;
    sA->force[2]                 = 0.0f;

}

__device__ void calculateGrycukChainRulePairIxn_kernel( GrycukChainRuleParticle& atomI, GrycukChainRuleParticle& atomJ, float force[3] ){

    const float pi         = 3.1415926535897f;
    float third            = 1.0f/3.0f;
    float pi43             = 4.0f*third*pi;

    float lik, uik;
    float lik4, uik4;
    float factor           = -powf(pi,third)*powf(6.0f,(2.0f*third))/9.0f;
    float term             = pi43/(atomI.bornRadius*atomI.bornRadius*atomI.bornRadius);
          term             = factor/powf( term, (4.0f*third) );

    float xr               = atomJ.x - atomI.x;
    float yr               = atomJ.y - atomI.y;
    float zr               = atomJ.z - atomI.z;

    float sk               = atomJ.scaledRadius;
    float sk2              = sk*sk;
    float r2               = xr*xr + yr*yr + zr*zr;
    float r                = sqrtf(r2);
    float de               = 0.0f;

    if( (atomI.radius + r) < sk ){
        float uik4;
        uik        = sk - r;
        uik4       = uik*uik;
        uik4       = uik4*uik4;
        de         = -4.0f*pi/uik4;
    }

    if( (atomI.radius + r) < sk){
        lik  = sk - r;
        lik4 = lik*lik;
        lik4 = lik4*lik4;
        de  += 0.25f*pi*(sk2-4.0f*sk*r+17.0f*r2)/ (r2*lik4);
    } else if( r < (atomI.radius +sk) ){
        lik  = atomI.radius;
        lik4 = lik*lik;
        lik4 = lik4*lik4;
        de  += 0.25f*pi*(2.0f*atomI.radius*atomI.radius-sk2-r2)/ (r2*lik4);
    } else {
        lik  = r - sk;
        lik4 = lik*lik;
        lik4 = lik4*lik4;
        de  += 0.25f*pi*(sk2-4.0f*sk*r+r2)/ (r2*lik4);
    }
    uik        = r + sk;
    uik4       = uik*uik;
    uik4       = uik4*uik4;
    
    de        -= 0.25f*pi*(sk2+4.0f*sk*r+r2)/ (r2*uik4);
    float dbr  = term * de/r;
          de   = dbr*atomI.bornForce;

    force[0]   = xr*de;
    force[1]   = yr*de;
    force[2]   = zr*de;
}

// Include versions of the kernels for N^2 calculations.

#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP
#define METHOD_NAME(a, b) a##N2##b
#include "kCalculateAmoebaCudaGrycukChainRule.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##N2ByWarp##b
#include "kCalculateAmoebaCudaGrycukChainRule.h"

/**---------------------------------------------------------------------------------------

   Compute Grycuk chain rule contribution to force

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */


void kCalculateGrycukGbsaForces2( amoebaGpuContext amoebaGpu )
{

    // ---------------------------------------------------------------------------------------

    gpuContext gpu = amoebaGpu->gpuContext;

    // apparently debug array can take up nontrivial no. registers

    // on first pass, set threads/block and based on that setting the energy buffer array

    static unsigned int threadsPerBlock = 0;
    if( threadsPerBlock == 0 ){
        unsigned int maxThreads;
        if (gpu->sm_version >= SM_20)
            //maxThreads = 384;
            maxThreads = 512;
        else if (gpu->sm_version >= SM_12)
            maxThreads = 128;
        else
            maxThreads = 64;
        threadsPerBlock = std::min(getThreadsPerBlock(amoebaGpu, sizeof(GrycukChainRuleParticle), gpu->sharedMemoryPerBlock ), maxThreads);
    }

    if (gpu->bOutputBufferPerWarp){
        kCalculateAmoebaGrycukChainRuleN2ByWarp_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(GrycukChainRuleParticle)*threadsPerBlock>>>( gpu->psWorkUnit->_pDevData);
    } else {
        kCalculateAmoebaGrycukChainRuleN2_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(GrycukChainRuleParticle)*threadsPerBlock>>>( gpu->psWorkUnit->_pDevData);
    }
    LAUNCHERROR("kCalculateAmoebaCudaGrycukN2Forces");

   if( 0 ){ 
        static int callId                    = 0;
        gpuContext gpu                       = amoebaGpu->gpuContext;
        std::vector<int> fileId;
        fileId.push_back( callId++ ); 
        VectorOfDoubleVectors outputVector;
        //cudaLoadCudaFloat4Array( gpu->natoms, 3, gpu->psPosq4,              outputVector, gpu->psAtomIndex->_pSysData, 1.0f );
        //cudaLoadCudaFloatArray( gpu->natoms,  3, amoebaGpu->psLabFrameDipole,     outputVector, gpu->psAtomIndex->_pSysData, 1.0f );
        CUDAStream<float>* temp  = new CUDAStream<float>(3*gpu->sim.paddedNumberOfAtoms, 1, "Temp1");

        reduceAndCopyCUDAStreamFloat4( gpu->psForce4, temp, 1.0 );
        cudaLoadCudaFloatArray( gpu->natoms,  3, temp, outputVector, gpu->psAtomIndex->_pSysData, 1.0f/4.184f ); 
        cudaLoadCudaFloatArray( gpu->natoms,  1, gpu->psBornForce, outputVector, gpu->psAtomIndex->_pSysData, 1.0f/4.184f ); 
        cudaLoadCudaFloatArray( gpu->natoms,  1, gpu->psBornRadii, outputVector, gpu->psAtomIndex->_pSysData, 1.0f ); 
        cudaWriteVectorOfDoubleVectorsToFile( "GryF", fileId, outputVector );
        delete temp;
        //exit(0);
    }    

   // ---------------------------------------------------------------------------------------
}
