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

#include "amoebaGpuTypes.h"
#include "amoebaCudaKernels.h"
#include "cudaKernels.h"
#include "kCalculateAmoebaCudaUtilities.h"
#include "kCalculateAmoebaCudaVdwParticle.h"
#include "amoebaScaleFactors.h"

#include <stdio.h>

extern int isNanOrInfinity( double number );

using namespace std;

static __constant__ cudaGmxSimulation cSim;
static __constant__ cudaAmoebaGmxSimulation cAmoebaSim;

void SetCalculateAmoebaCudaVdw14_7Sim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status         = cudaMemcpyToSymbol(cSim, &gpu->sim, sizeof(cudaGmxSimulation));    
    RTERROR(status, "SetCalculateAmoebaCudaVdw14_7Sim: cudaMemcpyToSymbol: SetSim copy to cSim failed");
    status         = cudaMemcpyToSymbol(cAmoebaSim, &amoebaGpu->amoebaSim, sizeof(cudaAmoebaGmxSimulation));    
    RTERROR(status, "SetCalculateAmoebaCudaVdw14_7FieldSim: cudaMemcpyToSymbol: SetSim copy to cAmoebaSim failed");
}

void GetCalculateAmoebaCudaVdw14_7Sim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status = cudaMemcpyFromSymbol(&gpu->sim, cSim, sizeof(cudaGmxSimulation));    
    RTERROR(status, "GetCalculateAmoebaCudaVdw14_7Sim: cudaMemcpyFromSymbol: SetSim copy from cSim failed");
    status = cudaMemcpyFromSymbol(&amoebaGpu->amoebaSim, cAmoebaSim, sizeof(cudaAmoebaGmxSimulation));    
    RTERROR(status, "GetCalculateAmoebaCudaVdw14_7Sim: cudaMemcpyFromSymbol: SetSim copy from cAmoebaSim failed");
}

__device__ void zeroVdw14_7SharedForce( struct Vdw14_7Particle* sA ) 
{
    // zero shared fields

    sA->force[0]              = 0.0f;
    sA->force[1]              = 0.0f;
    sA->force[2]              = 0.0f;

    sA->tempForce[0]          = 0.0f;
    sA->tempForce[1]          = 0.0f;
    sA->tempForce[2]          = 0.0f;

}

__device__ void loadVdw14_7Shared( struct Vdw14_7Particle* sA, unsigned int atomI,
                                   float4* atomCoord, float2* vdwParameters )
{
    // coordinates, sigma, epsilon

    sA->x                        = atomCoord[atomI].x;
    sA->y                        = atomCoord[atomI].y;
    sA->z                        = atomCoord[atomI].z;

    sA->sigma                    = vdwParameters[atomI].x;
    sA->epsilon                  = vdwParameters[atomI].y;

}

__device__ void getVdw14_7CombindedSigmaEpsilon_kernel( int sigmaCombiningRule, float iSigma, float jSigma, float* combindedSigma,
                                                        int epsilonCombiningRule, float iEpsilon, float jEpsilon, float* combindedEpsilon )
{
    if( sigmaCombiningRule == 1 ){
        *combindedSigma      = iSigma + jSigma;
    } else if( sigmaCombiningRule == 2 ){
        *combindedSigma      = 2.0f*sqrtf( iSigma*jSigma );
    } else {
        float iSigma2        = iSigma*iSigma;
        float jSigma2        = jSigma*jSigma;
        *combindedSigma      = 2.0f*( iSigma2*iSigma + jSigma2*jSigma )/( iSigma2 + jSigma2 );
    }

    if( epsilonCombiningRule == 1 ){
        *combindedEpsilon    = iEpsilon + jEpsilon;
    } else if( epsilonCombiningRule == 2 ){
        *combindedEpsilon    = 2.0f*sqrtf( iEpsilon*jEpsilon );
    } else if( epsilonCombiningRule == 3 ){
        float iEpsilon2      = iEpsilon*iEpsilon;
        float jEpsilon2      = jEpsilon*jEpsilon;
        *combindedEpsilon    = 2.0f*( iEpsilon2*iEpsilon + jEpsilon2*jEpsilon )/( iEpsilon2 + jEpsilon2 );
    } else {
        float epsilonS       = sqrtf( iEpsilon ) + sqrtf( jEpsilon );
        *combindedEpsilon    = 4.0f*( iEpsilon*jEpsilon )/( epsilonS*epsilonS );
    }   

}

// lookup table w/ linear interpolation

__device__ void lookupLinearVdwTaper( float r, float* taper, float* dtaper )
{
    if( r > (cAmoebaSim.vdwCutoff - cAmoebaSim.vdwTaperDelta) ){
        *taper = *dtaper = 0.0f;
    } else {

        int index        = (int) (floor( (r - cAmoebaSim.vdwTaperCutoff)/cAmoebaSim.vdwTaperDelta));
//        int index        = (int) round( (r - cAmoebaSim.vdwTaperCutoff)/cAmoebaSim.vdwTaperDelta);
        float slope      = (cAmoebaSim.vdwTaperTable[index+1] - cAmoebaSim.vdwTaperTable[index])/cAmoebaSim.vdwTaperDelta;
        float intercept  =  cAmoebaSim.vdwTaperTable[index+1] - slope*(cAmoebaSim.vdwTaperDelta*static_cast<float>(index+1));
        *taper           = slope*(r-cAmoebaSim.vdwTaperCutoff) + intercept; 

        slope            = (cAmoebaSim.vdw_dTaperTable[index+1] - cAmoebaSim.vdw_dTaperTable[index])/cAmoebaSim.vdwTaperDelta;
        intercept        =  cAmoebaSim.vdw_dTaperTable[index+1]  - slope*(cAmoebaSim.vdwTaperDelta*static_cast<float>(index+1));
        *dtaper          = slope*(r-cAmoebaSim.vdwTaperCutoff) + intercept; 
    }
}

// lookup table w/ quadratic interpolation

__device__ void lookupVdwTaper( float r, float* taper, float* dtaper )
{
    if( r > (cAmoebaSim.vdwCutoff - 2.0f*cAmoebaSim.vdwTaperDelta) ){
        *taper = *dtaper = 0.0f;
    } else {

        float x          = r - cAmoebaSim.vdwTaperCutoff;
//        int index        = (int) (floor(x)/cAmoebaSim.vdwTaperDelta);
        int index        = (int) round(x/cAmoebaSim.vdwTaperDelta);
        if( index ){

            float x0         = cAmoebaSim.vdwTaperDelta*static_cast<float>(index-1);
            float y0         = cAmoebaSim.vdwTaperTable[index-1];
    
            float x1         = x0 + cAmoebaSim.vdwTaperDelta;
            float y1         = cAmoebaSim.vdwTaperTable[index];
    
            float x2         = x1 + cAmoebaSim.vdwTaperDelta;
            float y2         = cAmoebaSim.vdwTaperTable[index+1];
    
            *taper           = y0*( (x-x1)*(x-x2)/((x0-x1)*(x0-x2))) + 
                               y1*( (x-x0)*(x-x2)/((x1-x0)*(x1-x2))) + 
                               y2*( (x-x0)*(x-x1)/((x2-x0)*(x2-x1)));
    
                  y0         = cAmoebaSim.vdw_dTaperTable[index-1];
                  y1         = cAmoebaSim.vdw_dTaperTable[index];
                  y2         = cAmoebaSim.vdw_dTaperTable[index+1];
    
            *dtaper          = y0*( (x-x1)*(x-x2)/((x0-x1)*(x0-x2))) + 
                               y1*( (x-x0)*(x-x2)/((x1-x0)*(x1-x2))) + 
                               y2*( (x-x0)*(x-x1)/((x2-x0)*(x2-x1)));
    
        } else {
            *taper  = 1.0f;
            *dtaper = 0.0f;
        }
    }
}

__device__ void calculateVdw14_7PairIxn_kernel( float combindedSigma,    float combindedEpsilon,
                                                float force[3], float* energy)
{

    const float deltaHalM1 = 0.07f;
    const float deltaHal   = 1.07f;
    const float gammaHal   = 1.12f;
    const float gammaHalM1 = 0.12f;

    // ---------------------------------------------------------------------------------------
    
    // on input force[i] is assummed to contain delta[i] for coordinates of atom I and J 
    
    float r2                                     = force[0]*force[0] + force[1]*force[1] + force[2]*force[2];
    if( r2 > cAmoebaSim.vdwCutoff2 ){
        *energy = force[0] = force[1] = force[2] = 0.0f;
        return;
    }
    float rI                                     =  rsqrtf( r2 );
    float r                                      =  1.0f/rI;
    float r6                                     =  r2*r2*r2;
    float r7                                     =  r6*r;
 
    float combindedSigma7                        = combindedSigma*combindedSigma;
    combindedSigma7                              = combindedSigma7*combindedSigma7*combindedSigma7*combindedSigma;

    float rho                                    = r7 + combindedSigma7*gammaHalM1;
    float rhoInverse                             = 1.0f/rho;
 
    float tau                                    = deltaHal/(r + deltaHalM1*combindedSigma);
    float tau7                                   = tau*tau*tau;
         tau7                                    = tau7*tau7*tau;
    float dTau                                   = tau/deltaHal;
    
    float tmp                                    = combindedSigma7*rhoInverse;
    float gTau                                   = combindedEpsilon*tau7*r6*gammaHal*tmp*tmp;
 
    *energy                                      = combindedEpsilon*combindedSigma7*tau7*( (combindedSigma7*gammaHal*rhoInverse) - 2.0f);
    float deltaE                                 = (-7.0f*(dTau*(*energy) + gTau))*rI;
 
    if( r > cAmoebaSim.vdwTaperCutoff ){ 

        float taper, dtaper;
        lookupVdwTaper( r, &taper, &dtaper );
        //lookupLinearVdwTaper( r, &taper, &dtaper );
        deltaE   = (*energy)*dtaper + deltaE*taper;
        *energy *= taper;
    }

    force[0]                                    *= deltaE;
    force[1]                                    *= deltaE;
    force[2]                                    *= deltaE;


}

// perform reduction of force on H's and add to heavy atom partner
// input force is the Vdw force
// output force is the cumulative force

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_NONBOND_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_NONBOND_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_NONBOND_THREADS_PER_BLOCK, 1)
#endif
void kCalculateAmoebaVdw14_7Reduction_kernel( float* inputForce, float4* outputForce )
{
    unsigned int pos = blockIdx.x * blockDim.x + threadIdx.x;

    while (pos < cAmoebaSim.amoebaVdwReductions )
    {
        int4   atomIndices              = cAmoebaSim.pAmoebaVdwReductionID[pos];
        float4 forceA;
        float4 forceB;
        float4 forceC;
        float4 forceD;

        int index                       = 3*atomIndices.x;
        forceA.x                        = inputForce[index];
        forceA.y                        = inputForce[index+1];
        forceA.z                        = inputForce[index+2];

        index                           = 3*atomIndices.y;
        forceB.x                        = inputForce[index];
        forceB.y                        = inputForce[index+1];
        forceB.z                        = inputForce[index+2];

        index                           = 3*atomIndices.z;
        forceC.x                        = inputForce[index];
        forceC.y                        = inputForce[index+1];
        forceC.z                        = inputForce[index+2];

        index                           = 3*atomIndices.w;
        forceD.x                        = inputForce[index];
        forceD.y                        = inputForce[index+1];
        forceD.z                        = inputForce[index+2];

        float  reductionFactor          = cAmoebaSim.pAmoebaVdwReduction[pos];
        float  reductionFactorM1        = 1.0f - reductionFactor;
        
        float4 forceTemp1;
        forceTemp1.x                    = reductionFactor*forceB.x;
        forceTemp1.y                    = reductionFactor*forceB.y;
        forceTemp1.z                    = reductionFactor*forceB.z;

        forceA.x                       += reductionFactorM1*forceB.x;
        forceA.y                       += reductionFactorM1*forceB.y;
        forceA.z                       += reductionFactorM1*forceB.z;

        outputForce[atomIndices.y].x   += forceTemp1.x;
        outputForce[atomIndices.y].y   += forceTemp1.y;
        outputForce[atomIndices.y].z   += forceTemp1.z;

        reductionFactor                 = atomIndices.x != atomIndices.z ? reductionFactor   : 0.0f;
        reductionFactorM1               = atomIndices.x != atomIndices.z ? reductionFactorM1 : 0.0f;

        forceTemp1.x                    = reductionFactor*forceC.x;
        forceTemp1.y                    = reductionFactor*forceC.y;
        forceTemp1.z                    = reductionFactor*forceC.z;

        forceA.x                       += reductionFactorM1*forceC.x;
        forceA.y                       += reductionFactorM1*forceC.y;
        forceA.z                       += reductionFactorM1*forceC.z;

        outputForce[atomIndices.z].x   += forceTemp1.x;
        outputForce[atomIndices.z].y   += forceTemp1.y;
        outputForce[atomIndices.z].z   += forceTemp1.z;

        reductionFactor                 = atomIndices.x != atomIndices.w ? reductionFactor   : 0.0f;
        reductionFactorM1               = atomIndices.x != atomIndices.w ? reductionFactorM1 : 0.0f;

        forceTemp1.x                    = reductionFactor*forceD.x;
        forceTemp1.y                    = reductionFactor*forceD.y;
        forceTemp1.z                    = reductionFactor*forceD.z;

        forceA.x                       += reductionFactorM1*forceD.x;
        forceA.y                       += reductionFactorM1*forceD.y;
        forceA.z                       += reductionFactorM1*forceD.z;

        outputForce[atomIndices.w].x   += forceTemp1.x;
        outputForce[atomIndices.w].y   += forceTemp1.y;
        outputForce[atomIndices.w].z   += forceTemp1.z;

        outputForce[atomIndices.x].x   += forceA.x;
        outputForce[atomIndices.x].y   += forceA.y;
        outputForce[atomIndices.x].z   += forceA.z;
        
        pos                            += blockDim.x * gridDim.x;
    }
}

__device__ void sumTempBuffer( Vdw14_7Particle& atomI, Vdw14_7Particle& atomJ ){

    atomI.tempForce[0]  += atomJ.tempForce[0];
    atomI.tempForce[1]  += atomJ.tempForce[1];
    atomI.tempForce[2]  += atomJ.tempForce[2];
}

static void kCalculateAmoebaVdw14_7Reduction(amoebaGpuContext amoebaGpu, CUDAStream<float>* vdwOutputArray, CUDAStream<float4>* forceOutputArray )
{
    unsigned int threadsPerBlock;
    if (amoebaGpu->gpuContext->sm_version >= SM_20)
        threadsPerBlock = GF1XX_NONBOND_THREADS_PER_BLOCK;
    else if (amoebaGpu->gpuContext->sm_version >= SM_12)
        threadsPerBlock = GT2XX_NONBOND_THREADS_PER_BLOCK;
    else
        threadsPerBlock = G8X_NONBOND_THREADS_PER_BLOCK;
    kCalculateAmoebaVdw14_7Reduction_kernel<<<amoebaGpu->gpuContext->sim.blocks, threadsPerBlock>>>(
                               vdwOutputArray->_pDevData, forceOutputArray->_pDevData );
    LAUNCHERROR("kCalculateAmoebaVdw14_7Reduction");
}

// perform reduction of coordinate on H's and add to heavy atom partner
// input coordinate is the Vdw coordinate
// output coordinate is the cumulative coordinate

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kCalculateAmoebaVdw14_7CoordinateReduction_kernel( float4* inputCoordinate, float4* outputCoordinate )
{
    unsigned int pos = blockIdx.x * blockDim.x + threadIdx.x;

    while (pos < cAmoebaSim.amoebaVdwReductions )
    {
        int4   atomIndices              = cAmoebaSim.pAmoebaVdwReductionID[pos];
        float4 coordinateA;
        float4 coordinateB;
        float4 coordinateC;
        float4 coordinateD;

        int index                             = atomIndices.x;
        coordinateA.x                         = inputCoordinate[index].x;
        coordinateA.y                         = inputCoordinate[index].y;
        coordinateA.z                         = inputCoordinate[index].z;

        index                                 = atomIndices.y;
        coordinateB.x                         = inputCoordinate[index].x;
        coordinateB.y                         = inputCoordinate[index].y;
        coordinateB.z                         = inputCoordinate[index].z;

        index                                 = atomIndices.z;
        coordinateC.x                         = inputCoordinate[index].x;
        coordinateC.y                         = inputCoordinate[index].y;
        coordinateC.z                         = inputCoordinate[index].z;

        index                                 = atomIndices.w;
        coordinateD.x                         = inputCoordinate[index].x;
        coordinateD.y                         = inputCoordinate[index].y;
        coordinateD.z                         = inputCoordinate[index].z;

        float  reductionFactor                = cAmoebaSim.pAmoebaVdwReduction[pos];
        float  reductionFactorM1              = 1.0f - reductionFactor;
        
        float4 coordinateTemp1;
        coordinateTemp1.x                     = reductionFactor*coordinateB.x + reductionFactorM1*coordinateA.x;
        coordinateTemp1.y                     = reductionFactor*coordinateB.y + reductionFactorM1*coordinateA.y;
        coordinateTemp1.z                     = reductionFactor*coordinateB.z + reductionFactorM1*coordinateA.z;

        outputCoordinate[atomIndices.y].x     = coordinateTemp1.x;
        outputCoordinate[atomIndices.y].y     = coordinateTemp1.y;
        outputCoordinate[atomIndices.y].z     = coordinateTemp1.z;

        reductionFactor                       = atomIndices.x != atomIndices.z ? reductionFactor   : 1.0f;
        reductionFactorM1                     = atomIndices.x != atomIndices.z ? reductionFactorM1 : 0.0f;

        coordinateTemp1.x                     = reductionFactor*coordinateC.x + reductionFactorM1*coordinateA.x;
        coordinateTemp1.y                     = reductionFactor*coordinateC.y + reductionFactorM1*coordinateA.y;
        coordinateTemp1.z                     = reductionFactor*coordinateC.z + reductionFactorM1*coordinateA.z;

        outputCoordinate[atomIndices.z].x     = coordinateTemp1.x;
        outputCoordinate[atomIndices.z].y     = coordinateTemp1.y;
        outputCoordinate[atomIndices.z].z     = coordinateTemp1.z;

        reductionFactor                       = atomIndices.x != atomIndices.w ? reductionFactor   : 1.0f;
        reductionFactorM1                     = atomIndices.x != atomIndices.w ? reductionFactorM1 : 0.0f;

        coordinateTemp1.x                     = reductionFactor*coordinateD.x + reductionFactorM1*coordinateA.x;
        coordinateTemp1.y                     = reductionFactor*coordinateD.y + reductionFactorM1*coordinateA.y;
        coordinateTemp1.z                     = reductionFactor*coordinateD.z + reductionFactorM1*coordinateA.z;

        outputCoordinate[atomIndices.w].x     = coordinateTemp1.x;
        outputCoordinate[atomIndices.w].y     = coordinateTemp1.y;
        outputCoordinate[atomIndices.w].z     = coordinateTemp1.z;

        pos                                  += blockDim.x * gridDim.x;
    }
}

static void kCalculateAmoebaVdw14_7CoordinateReduction(amoebaGpuContext amoebaGpu,
                                                       CUDAStream<float4>* coordinateArray,
                                                       CUDAStream<float4>* reducedCoordinateArray)
{
    unsigned int threadsPerBlock;
    if (amoebaGpu->gpuContext->sm_version >= SM_20)
        threadsPerBlock = GF1XX_THREADS_PER_BLOCK;
    else if (amoebaGpu->gpuContext->sm_version >= SM_12)
        threadsPerBlock = GT2XX_THREADS_PER_BLOCK;
    else
        threadsPerBlock = G8X_THREADS_PER_BLOCK;
    kCalculateAmoebaVdw14_7CoordinateReduction_kernel<<<amoebaGpu->gpuContext->sim.blocks, threadsPerBlock>>>(
                               coordinateArray->_pDevData, reducedCoordinateArray->_pDevData );
    LAUNCHERROR("kCalculateAmoebaVdw14_7CoordinateReduction");
}

// perform reduction of force on H's and add to heavy atom partner
// input force is the Vdw force
// output force is the cumulative force

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kCalculateAmoebaVdw14_7NonReduction_kernel( float* inputForce, float4* outputForce )
{
    unsigned int pos = blockIdx.x * blockDim.x + threadIdx.x;

    while (pos < cAmoebaSim.amoebaVdwNonReductions )
    {
        int   atomIndex             = cAmoebaSim.pAmoebaVdwNonReductionID[pos];
        int index                   = 3*atomIndex;
        outputForce[atomIndex].x   += inputForce[index];
        outputForce[atomIndex].y   += inputForce[index+1];
        outputForce[atomIndex].z   += inputForce[index+2];
        
        pos                        += blockDim.x * gridDim.x;
    }
}

static void kCalculateAmoebaVdw14_7NonReduction(amoebaGpuContext amoebaGpu, CUDAStream<float>* vdwOutputArray, CUDAStream<float4>* forceOutputArray )
{
    kCalculateAmoebaVdw14_7NonReduction_kernel<<<amoebaGpu->gpuContext->sim.blocks, amoebaGpu->gpuContext->sim.threads_per_block>>>(
                               vdwOutputArray->_pDevData, forceOutputArray->_pDevData );
    LAUNCHERROR("kCalculateAmoebaVdw14_7MonReduction");
}

// Include versions of the kernels for N^2 calculations.

#define METHOD_NAME(a, b) a##N2##b
#include "kCalculateAmoebaCudaVdw14_7.h"

#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##N2ByWarp##b
#include "kCalculateAmoebaCudaVdw14_7.h"
#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP 

#define USE_CUTOFF
#define METHOD_NAME(a, b) a##Cutoff##b
#include "kCalculateAmoebaCudaVdw14_7.h"
#undef METHOD_NAME

#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##CutoffByWarp##b
#include "kCalculateAmoebaCudaVdw14_7.h"
#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP 
#undef USE_CUTOFF

// reduce psWorkArray_3_1 -> outputArray

static void kReduceVdw14_7(amoebaGpuContext amoebaGpu, CUDAStream<float>* outputArray )
{
    gpuContext gpu = amoebaGpu->gpuContext;
    kReduceFields_kernel<<<gpu->sim.nonbond_blocks, gpu->sim.bsf_reduce_threads_per_block>>>(
                           gpu->sim.paddedNumberOfAtoms*3, gpu->sim.outputBuffers,
                           amoebaGpu->psWorkArray_3_1->_pDevData, outputArray->_pDevData, 0 );
    LAUNCHERROR("kReduceVdw14_7");
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kCalculateAmoebaVdw14_7CopyCoordinates_kernel( unsigned int bufferLength, float4* toCopy, float4* copy )
{
    unsigned int pos = blockIdx.x * blockDim.x + threadIdx.x;
    while (pos < bufferLength )
    {   
        copy[pos].x       = toCopy[pos].x;
        copy[pos].y       = toCopy[pos].y;
        copy[pos].z       = toCopy[pos].z;
        copy[pos].w       = toCopy[pos].w;
        pos              += gridDim.x * blockDim.x;
    }   
}

void kCalculateAmoebaVdw14_7CopyCoordinates( amoebaGpuContext amoebaGpu, CUDAStream<float4>* toCopy, CUDAStream<float4>* copy )
{
    kCalculateAmoebaVdw14_7CopyCoordinates_kernel<<<amoebaGpu->gpuContext->blocksPerSM, amoebaGpu->gpuContext->sim.threads_per_block>>>( amoebaGpu->gpuContext->sim.paddedNumberOfAtoms, 
                      toCopy->_pDevData, copy->_pDevData );
    LAUNCHERROR("kCalculateAmoebaVdw14_7CopyCoordinates");
}

/**---------------------------------------------------------------------------------------

   Compute Vdw 14-7

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */

void kCalculateAmoebaVdw14_7Forces( amoebaGpuContext amoebaGpu, int applyCutoff )
{
  
   // ---------------------------------------------------------------------------------------

    static int threadsPerBlock    = 0;

   // ---------------------------------------------------------------------------------------

     gpuContext gpu    = amoebaGpu->gpuContext;

    // set threads/block first time through

    // on first pass, set threads/block

    if( threadsPerBlock == 0 ){ 
        unsigned int maxThreads;
        if (gpu->sm_version >= SM_20)
            maxThreads = 384; 
        else if (gpu->sm_version >= SM_12)
            maxThreads = 192; 
        else
            maxThreads = 128;
        threadsPerBlock = std::min(getThreadsPerBlock(amoebaGpu, sizeof(Vdw14_7Particle), gpu->sharedMemoryPerBlock ), maxThreads);
    }    


    kCalculateAmoebaVdw14_7CopyCoordinates( amoebaGpu, gpu->psPosq4, amoebaGpu->psAmoebaVdwCoordinates );
    kCalculateAmoebaVdw14_7CoordinateReduction( amoebaGpu, amoebaGpu->psAmoebaVdwCoordinates, amoebaGpu->psAmoebaVdwCoordinates );

    // clear output arrays

    kClearFields_3( amoebaGpu, 1 );

    if( applyCutoff ){

        kFindBlockBoundsPeriodic_kernel<<<(gpu->psGridBoundingBox->_length+63)/64, 64>>>();
        LAUNCHERROR("kFindBlockBoundsVdwPeriodic");
        kFindBlocksWithInteractionsVdwPeriodic_kernel<<<gpu->sim.interaction_blocks, gpu->sim.interaction_threads_per_block>>>();
        LAUNCHERROR("kFindBlocksWithInteractionsVdwPeriodic");
        compactStream(gpu->compactPlan, gpu->sim.pInteractingWorkUnit, amoebaGpu->amoebaSim.pVdwWorkUnit, gpu->sim.pInteractionFlag, gpu->sim.workUnits, gpu->sim.pInteractionCount);
        kFindInteractionsWithinBlocksVdwPeriodic_kernel<<<gpu->sim.nonbond_blocks, gpu->sim.nonbond_threads_per_block,
                    sizeof(unsigned int)*gpu->sim.nonbond_threads_per_block>>>(gpu->sim.pInteractingWorkUnit);
        LAUNCHERROR("kFindInteractionsWithinBlocksVdwPeriodic");

        if (gpu->bOutputBufferPerWarp){
            kCalculateAmoebaVdw14_7CutoffByWarp_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(Vdw14_7Particle)*threadsPerBlock>>>(
                                                                gpu->sim.pInteractingWorkUnit,
                                                                amoebaGpu->psAmoebaVdwCoordinates->_pDevData,
                                                                amoebaGpu->psVdwSigmaEpsilon->_pDevData,
                                                                amoebaGpu->vdwSigmaCombiningRule,
                                                                amoebaGpu->vdwEpsilonCombiningRule,
                                                                amoebaGpu->psWorkArray_3_1->_pDevData );
        } else {

            kCalculateAmoebaVdw14_7Cutoff_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(Vdw14_7Particle)*threadsPerBlock>>>(
                                                                gpu->sim.pInteractingWorkUnit,
                                                                amoebaGpu->psAmoebaVdwCoordinates->_pDevData,
                                                                amoebaGpu->psVdwSigmaEpsilon->_pDevData,
                                                                amoebaGpu->vdwSigmaCombiningRule,
                                                                amoebaGpu->vdwEpsilonCombiningRule,
                                                                amoebaGpu->psWorkArray_3_1->_pDevData );
        }
        LAUNCHERROR("kCalculateAmoebaVdw14_7Cutoff");  

    } else {

        if (gpu->bOutputBufferPerWarp){

            kCalculateAmoebaVdw14_7N2ByWarp_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(Vdw14_7Particle)*threadsPerBlock>>>(
                                                                amoebaGpu->psVdwWorkUnit->_pDevData,
                                                                amoebaGpu->psAmoebaVdwCoordinates->_pDevData,
                                                                amoebaGpu->psVdwSigmaEpsilon->_pDevData,
                                                                amoebaGpu->vdwSigmaCombiningRule,
                                                                amoebaGpu->vdwEpsilonCombiningRule,
                                                                amoebaGpu->psWorkArray_3_1->_pDevData );
        } else {

            kCalculateAmoebaVdw14_7N2_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(Vdw14_7Particle)*threadsPerBlock>>>(
                                                                amoebaGpu->psVdwWorkUnit->_pDevData,
                                                                amoebaGpu->psAmoebaVdwCoordinates->_pDevData,
                                                                amoebaGpu->psVdwSigmaEpsilon->_pDevData,
                                                                amoebaGpu->vdwSigmaCombiningRule,
                                                                amoebaGpu->vdwEpsilonCombiningRule,
                                                                amoebaGpu->psWorkArray_3_1->_pDevData );
    
        }
        LAUNCHERROR("kCalculateAmoebaVdw14_7N2");  
    }

    kReduceVdw14_7( amoebaGpu, amoebaGpu->psWorkArray_3_2 );

    kCalculateAmoebaVdw14_7Reduction( amoebaGpu, amoebaGpu->psWorkArray_3_2, amoebaGpu->gpuContext->psForce4 );
    kCalculateAmoebaVdw14_7NonReduction( amoebaGpu, amoebaGpu->psWorkArray_3_2, amoebaGpu->gpuContext->psForce4 );

}
