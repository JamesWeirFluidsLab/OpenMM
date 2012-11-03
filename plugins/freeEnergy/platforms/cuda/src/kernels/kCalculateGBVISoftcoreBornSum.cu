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
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "GpuFreeEnergyCudaKernels.h"
#include "freeEnergyGpuTypes.h"

#include "openmm/OpenMMException.h"
#include <cuda.h>
#include <iostream>
#include <sstream>

#define PARAMETER_PRINT 0
#define MAX_PARAMETER_PRINT 10

static __constant__ cudaGmxSimulation cSim;
static __constant__ cudaFreeEnergyGmxSimulation gbviSimDev;

void SetCalculateGBVISoftcoreBornSumGpuSim( freeEnergyGpuContext freeEnergyGpu)
{
    cudaError_t status;
    status = cudaMemcpyToSymbol( cSim, &freeEnergyGpu->gpuContext->sim, sizeof(cudaGmxSimulation));    
    RTERROR(status, "cudaMemcpyToSymbol: SetCalculateGBVISoftcoreBornSumGpuSim copy to cSim failed");

    status = cudaMemcpyToSymbol( gbviSimDev, &freeEnergyGpu->freeEnergySim, sizeof(cudaFreeEnergyGmxSimulation));    
    RTERROR(status, "cudaMemcpyToSymbol: SetCalculateGBVISoftcoreBornSumGpuSim copy to feSim failed");
}

// create, initialize and enter BornRadiusScaleFactors values (used to scale contribution of atoms to Born sum of other atoms)

extern "C"
void gpuSetGBVISoftcoreParameters( freeEnergyGpuContext freeEnergyGpu, float innerDielectric, float solventDielectric, const std::vector<int>& atom,
                                   const std::vector<float>& radius, const std::vector<float>& gamma,
                                   const std::vector<float>& scaledRadii, const std::vector<float>& bornRadiusScaleFactors,
                                   const std::vector<float>& quinticSplineParameters ){

    unsigned int numberOfParticles                    = radius.size();

    gpuContext gpu                                    = freeEnergyGpu->gpuContext;

    static const float electricConstant               = -166.02691f;
    double tau                                        = ((1.0f/innerDielectric)-(1.0f/solventDielectric)); 
    freeEnergyGpu->psSwitchDerivative                 = new CUDAStream<float>( gpu->sim.paddedNumberOfAtoms, 1, "SwitchDerivative");
    freeEnergyGpu->freeEnergySim.pSwitchDerivative    = freeEnergyGpu->psSwitchDerivative->_pDevData;

    // create gpuGBVISoftcore, load parameters, and track minimum softcore value
    // gpuGBVISoftcore is not really being used (it was in the initial implementation) -- 
    // will be removed in future once confirmed not needed


    // check if quintic scaling to be applied

    if( quinticSplineParameters.size() == 2 ){
       freeEnergyGpu->freeEnergySim.bornRadiiScalingMethod        = 1;
       freeEnergyGpu->freeEnergySim.quinticLowerLimitFactor       = quinticSplineParameters[0];
       freeEnergyGpu->freeEnergySim.quinticUpperLimit             = quinticSplineParameters[1];
    } else {
       freeEnergyGpu->freeEnergySim.bornRadiiScalingMethod        = 0;
       freeEnergyGpu->freeEnergySim.quinticLowerLimitFactor       = 0.8f;
       freeEnergyGpu->freeEnergySim.quinticUpperLimit             = 5.0f;
    }

    for( unsigned int ii = 0; ii < bornRadiusScaleFactors.size(); ii++ ){
            (*gpu->psGBVIData)[ii].x                 = radius[ii];
            (*gpu->psGBVIData)[ii].y                 = scaledRadii[ii];
            (*gpu->psGBVIData)[ii].z                 = tau*gamma[ii];
            (*gpu->psGBVIData)[ii].w                 = bornRadiusScaleFactors[ii];
            (*gpu->psBornRadii)[ii]                  = 0.0f;
            (*freeEnergyGpu->psSwitchDerivative)[ii] = 0.0f;
    }

    // Dummy out extra atom data

    for( unsigned int ii = bornRadiusScaleFactors.size(); ii < gpu->sim.paddedNumberOfAtoms; ii++ ){
        (*gpu->psGBVIData)[ii].x                 = 0.01f;
        (*gpu->psGBVIData)[ii].y                 = 0.01f;
        (*gpu->psGBVIData)[ii].z                 = 0.0f;
        (*gpu->psGBVIData)[ii].w                 = 0.0f;
        (*gpu->psBornRadii)[ii]                  = 0.0f;
        (*freeEnergyGpu->psSwitchDerivative)[ii] = 0.0f;
    }

    gpu->sim.preFactor               = 2.0f*electricConstant*((1.0f/innerDielectric)-(1.0f/solventDielectric))*gpu->sim.forceConversionFactor;

    // diagnostics

    if( freeEnergyGpu->log ){
        (void) fprintf( freeEnergyGpu->log,"GBVISoftcore: part.=%u padded=%u sclMeth=%d\n",
                        static_cast<unsigned int>(bornRadiusScaleFactors.size()), static_cast<unsigned int>(gpu->sim.paddedNumberOfAtoms),
                        freeEnergyGpu->freeEnergySim.bornRadiiScalingMethod );
        if( quinticSplineParameters.size() == 2 ){
            (void) fprintf( freeEnergyGpu->log,"QuinticScaling: LwFct=%8.3f UpLmt=[%12.5e (nm) %12.5e]\n",
                        freeEnergyGpu->freeEnergySim.quinticLowerLimitFactor,
                        powf( freeEnergyGpu->freeEnergySim.quinticUpperLimit, -0.3333333f ), freeEnergyGpu->freeEnergySim.quinticUpperLimit );
        }
        (void) fprintf( freeEnergyGpu->log, "gpuSetGBVISoftcoreParameters: preFactor=%14.6e elecCnstnt=%.4f frcCnvrsnFctr=%.4f tau=%.4f.\n",
                        gpu->sim.preFactor, 2.0f*electricConstant, gpu->sim.forceConversionFactor, ((1.0f/innerDielectric)-(1.0f/solventDielectric)) );
#ifdef PARAMETER_PRINT
        int maxPrint = MAX_PARAMETER_PRINT;
        (void) fprintf( freeEnergyGpu->log, "               radius  scaled radius      tau*gamma         lambda\n" );
        for( unsigned int ii = 0; ii < bornRadiusScaleFactors.size(); ii++ ){
    
            (void) fprintf( freeEnergyGpu->log,"%6u %14.7e %14.7e %14.7e %14.7e\n",
                            ii, (*gpu->psGBVIData)[ii].x, (*gpu->psGBVIData)[ii].y, (*gpu->psGBVIData)[ii].z, (*gpu->psGBVIData)[ii].w ); 
            if( ii == maxPrint ){
                ii = bornRadiusScaleFactors.size() - maxPrint;
                if( ii < maxPrint )ii = maxPrint;
            }
        }
        unsigned int offset = gpu->sim.paddedNumberOfAtoms - MAX_PARAMETER_PRINT;
        if( offset > 0 && gpu->sim.paddedNumberOfAtoms > bornRadiusScaleFactors.size()  ){
            for( unsigned int ii = offset; ii < gpu->sim.paddedNumberOfAtoms; ii++ ){
                (void) fprintf( freeEnergyGpu->log,"%6u %14.7e %14.7e %14.7e %14.7e\n",
                                ii, (*gpu->psGBVIData)[ii].x, (*gpu->psGBVIData)[ii].y, (*gpu->psGBVIData)[ii].z, (*gpu->psGBVIData)[ii].w ); 
            }
        }
#endif
    }

    gpu->psGBVIData->Upload();
    gpu->psBornRadii->Upload();
    freeEnergyGpu->psSwitchDerivative->Upload();

    return;
}

struct Atom {
    float x;
    float y;
    float z;
    float r;
    float sr;
    float sum;
    float gamma;
    float bornRadiusScaleFactor;
};

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kClearGBVISoftcoreBornSum_kernel()
{
    unsigned int pos = blockIdx.x * blockDim.x + threadIdx.x;
    while (pos < cSim.stride * cSim.nonbondOutputBuffers)
    {   
        ((float*)cSim.pBornSum)[pos]  = 0.0f;
        pos                          += gridDim.x * blockDim.x;
    }   
}

void kClearGBVISoftcoreBornSum(gpuContext gpu) {
    kClearGBVISoftcoreBornSum_kernel<<<gpu->sim.blocks, gpu->sim.threads_per_block>>>();
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kReduceGBVISoftcoreBornForces_kernel()
{
    unsigned int pos = (blockIdx.x * blockDim.x + threadIdx.x);
    float energy     = 0.0f;
    while (pos < cSim.atoms)
    {
        float bornRadius  = cSim.pBornRadii[pos];
        float4 gbviData   = cSim.pGBVIData[pos];
        float totalForce  = 0.0f;
        float* pFt        = cSim.pBornForce + pos;

        int i = cSim.nonbondOutputBuffers;
        while (i >= 4)
        {
            float f1    = *pFt;
            pFt        += cSim.stride;
            float f2    = *pFt;
            pFt        += cSim.stride;
            float f3    = *pFt;
            pFt        += cSim.stride;
            float f4    = *pFt;
            pFt        += cSim.stride;
            totalForce += f1 + f2 + f3 + f4;
            i -= 4;
        }
        if (i >= 2)
        {
            float f1    = *pFt;
            pFt        += cSim.stride;
            float f2    = *pFt;
            pFt        += cSim.stride;
            totalForce += f1 + f2;
            i -= 2;
        }
        if (i > 0)
        {
            totalForce += *pFt;
        }

        float ratio         = (gbviData.x/bornRadius);
        float ratio3        = ratio*ratio*ratio;

        energy             -= gbviData.z*ratio3;                   //  gbviData.z = gamma*tau

        totalForce         += (3.0f*gbviData.z*ratio3)/bornRadius; // 'cavity' term
        float br2           = bornRadius*bornRadius;
        totalForce         *= (1.0f/3.0f)*br2*br2;

        pFt                 = cSim.pBornForce + pos;
        *pFt                = totalForce;
        pos                += gridDim.x * blockDim.x;
    }
    cSim.pEnergy[blockIdx.x * blockDim.x + threadIdx.x] += energy;
}

void kReduceGBVISoftcoreBornForces( freeEnergyGpuContext freeEnergyGpu )
{
    gpuContext gpu = freeEnergyGpu->gpuContext;
    kReduceGBVISoftcoreBornForces_kernel<<<gpu->sim.blocks, gpu->sim.bf_reduce_threads_per_block>>>();
    LAUNCHERROR("kReduceGBVISoftcoreBornForces");

}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kReduceGBVISoftcoreBornSum_kernel()
{
    unsigned int pos = (blockIdx.x * blockDim.x + threadIdx.x);
    
    while (pos < cSim.atoms)
    {
        float sum    = 0.0f;
        float* pSt   = cSim.pBornSum + pos;
        float4 atom  = cSim.pGBVIData[pos];
        
        // Get summed Born data
        for (int i = 0; i < cSim.nonbondOutputBuffers; i++)
        {
            sum += *pSt;
            pSt += cSim.stride;
        }
        
        // Now calculate Born radius

        float Rinv           = 1.0f/atom.x;
        sum                  = Rinv*Rinv*Rinv - sum; 
        cSim.pBornRadii[pos] = pow( sum, (-1.0f/3.0f) ); 
        pos                 += gridDim.x * blockDim.x;
    }   
}

void kReduceGBVISoftcoreBornSum( freeEnergyGpuContext freeEnergyGpu )
{
    gpuContext gpu = freeEnergyGpu->gpuContext;
    kReduceGBVISoftcoreBornSum_kernel<<<gpu->sim.blocks, gpu->sim.threads_per_block>>>();
    LAUNCHERROR("kReduceGBVISoftcoreBornSum");
}

// Include versions of the kernels for N^2 calculations.

#define METHOD_NAME(a, b) a##N2##b
#include "kCalculateGBVISoftcoreBornSum.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##N2ByWarp##b
#include "kCalculateGBVISoftcoreBornSum.h"

// Include versions of the kernels with cutoffs.

#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP
#define USE_CUTOFF
#define METHOD_NAME(a, b) a##Cutoff##b
#include "kCalculateGBVISoftcoreBornSum.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##CutoffByWarp##b
#include "kCalculateGBVISoftcoreBornSum.h"

// Include versions of the kernels with periodic boundary conditions.

#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP
#define USE_PERIODIC
#define METHOD_NAME(a, b) a##Periodic##b
#include "kCalculateGBVISoftcoreBornSum.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##PeriodicByWarp##b
#include "kCalculateGBVISoftcoreBornSum.h"

 __device__ void quinticSpline( float  x, float rl, float ru, float* outValue, float* outDerivative )
{
   float numerator    = x  - rl;
   float denominator  = ru - rl;
   float ratio        = numerator/denominator;
   float ratio2       = ratio*ratio;
   float ratio3       = ratio2*ratio;

   *outValue          =  1.0f + ratio3*(-10.f + 3.0f*ratio*(5.0f - 2.0f*ratio));
   *outDerivative     = -30.0f*ratio2*( 1.0f + ratio*(ratio - 2.0f))/denominator;
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kReduceGBVIBornSumQuinticScaling_kernel()
{
    unsigned int pos = (blockIdx.x * blockDim.x + threadIdx.x);
    
    while (pos < cSim.atoms)
    {
        float sum   = 0.0f;
        float* pSt  = cSim.pBornSum + pos;
        float4 atom = cSim.pGBVIData[pos];
        
        // Get summed Born data
        for (int i = 0; i < cSim.nonbondOutputBuffers; i++)
        {
            sum += *pSt;
            pSt += cSim.stride;
        }
        
        // Now calculate Born radius

        float Rinv           = 1.0f/atom.x;
        float r3             = Rinv*Rinv*Rinv;
        float splineL        = gbviSimDev.quinticLowerLimitFactor*r3;
        float switchDeriviative;
        if( sum > splineL ){
            if( sum < r3 ){
                float splineValue, splineDerivative;
                quinticSpline( sum, splineL, r3, &splineValue, &splineDerivative ); 
                switchDeriviative  = splineValue - (r3 - sum)*splineDerivative;
                sum                = (r3 - sum)*splineValue + gbviSimDev.quinticUpperLimit;
            } else {
                sum                = gbviSimDev.quinticUpperLimit;
                switchDeriviative  = 0.0f;
            }
        } else {
            sum               = r3 - sum;
            switchDeriviative = 1.0f;
        }

        cSim.pBornRadii[pos]               = pow( sum, (-1.0f/3.0f) ); 
        gbviSimDev.pSwitchDerivative[pos]  = switchDeriviative;
        pos                               += gridDim.x * blockDim.x;
    }   
}

void kReduceGBVIBornSumQuinticScaling( freeEnergyGpuContext freeEnergyGpu )
{
    gpuContext gpu = freeEnergyGpu->gpuContext;
    kReduceGBVIBornSumQuinticScaling_kernel<<<gpu->sim.blocks, gpu->sim.threads_per_block>>>();
    LAUNCHERROR("kReduceGBVIBornSumQuinticScaling_kernel");
}

__global__ 
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_THREADS_PER_BLOCK, 1)
#endif
void kReduceGBVIBornForcesQuinticScaling_kernel()
{
    unsigned int pos = (blockIdx.x * blockDim.x + threadIdx.x);
    float energy     = 0.0f;
    while (pos < cSim.atoms)
    {
        float bornRadius    = cSim.pBornRadii[pos];
        float4 gbviData     = cSim.pGBVIData[pos];
        float  switchDeriv  = gbviSimDev.pSwitchDerivative[pos];
        float totalForce    = 0.0f;
        float* pFt          = cSim.pBornForce + pos;

        int i = cSim.nonbondOutputBuffers;
        while (i >= 4)
        {
            float f1    = *pFt;
            pFt        += cSim.stride;
            float f2    = *pFt;
            pFt        += cSim.stride;
            float f3    = *pFt;
            pFt        += cSim.stride;
            float f4    = *pFt;
            pFt        += cSim.stride;
            totalForce += f1 + f2 + f3 + f4;
            i -= 4;
        }
        if (i >= 2)
        {
            float f1    = *pFt;
            pFt        += cSim.stride;
            float f2    = *pFt;
            pFt        += cSim.stride;
            totalForce += f1 + f2;
            i -= 2;
        }
        if (i > 0)
        {
            totalForce += *pFt;
        }

        float ratio         = (gbviData.x/bornRadius);
        float ratio3        = ratio*ratio*ratio;
        energy             -= gbviData.z*ratio3;
        totalForce         += (3.0f*gbviData.z*ratio3)/bornRadius; // 'cavity' term
        float br2           = bornRadius*bornRadius;
        totalForce         *= (1.0f/3.0f)*br2*br2*switchDeriv;

        pFt                 = cSim.pBornForce + pos;
        *pFt                = totalForce;
        pos                += gridDim.x * blockDim.x;
    }
    cSim.pEnergy[blockIdx.x * blockDim.x + threadIdx.x] += energy;
}

void kReduceGBVIBornForcesQuinticScaling( freeEnergyGpuContext freeEnergyGpu )
{
    gpuContext gpu = freeEnergyGpu->gpuContext;

    //(void) fprintf( stderr, "kReduceObcGbsaBornForces %6d blks=%u bsf_reduce_threads_per_block=%5u %5u   %5u %5u %5u\n",
    //                 gpu->natoms, gpu->sim.blocks, gpu->sim.bsf_reduce_threads_per_block, gpu->sim.bf_reduce_threads_per_block,
    //                 GF1XX_THREADS_PER_BLOCK, GT2XX_THREADS_PER_BLOCK, G8X_THREADS_PER_BLOCK); fflush( stderr );
    kReduceGBVIBornForcesQuinticScaling_kernel<<<gpu->sim.blocks, gpu->sim.bsf_reduce_threads_per_block>>>();
    LAUNCHERROR("kReduceGBVIBornForcesQuinticScaling");
}

void kPrintGBVISoftcore( freeEnergyGpuContext freeEnergyGpu, std::string callId, int call, FILE* log)
{
    gpuContext gpu = freeEnergyGpu->gpuContext;
    //int maxPrint   = gpu->natoms;

    gpu->psGBVIData->Download();
    gpu->psBornRadii->Download();
    gpu->psBornForce->Download();
    gpu->psPosq4->Download();

    CUDAStream<float>* switchDeriviative = freeEnergyGpu->psSwitchDerivative;
    CUDAStream<float4>* sigEps4          = freeEnergyGpu->psSigEps4;

    switchDeriviative->Download();
    sigEps4->Download();

    (void) fprintf( log, "kPrintGBVISoftcore Cuda Softcore bR bF swd   prm    sigeps4\n" );
    for( int ii = 0; ii < gpu->sim.paddedNumberOfAtoms; ii++ ){
        (void) fprintf( log, "%6d %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e %15.7e \n",
                        ii, 
                        gpu->psBornRadii->_pSysData[ii],
                        gpu->psBornForce->_pSysData[ii],
                        switchDeriviative->_pSysData[ii],

                        gpu->psGBVIData->_pSysData[ii].x,
                        gpu->psGBVIData->_pSysData[ii].y,
                        gpu->psGBVIData->_pSysData[ii].z,
                        gpu->psGBVIData->_pSysData[ii].w,

                        sigEps4->_pSysData[ii].x,
                        sigEps4->_pSysData[ii].y,
                        sigEps4->_pSysData[ii].z,
                        sigEps4->_pSysData[ii].w );

    }

}

extern __global__ void kFindBlockBoundsCutoff_kernel();
extern __global__ void kFindBlockBoundsPeriodic_kernel();

extern __global__ void kFindBlocksWithInteractionsCutoff_kernel();
extern __global__ void kFindBlocksWithInteractionsPeriodic_kernel();

extern __global__ void kFindInteractionsWithinBlocksCutoff_kernel(unsigned int*);
extern __global__ void kFindInteractionsWithinBlocksPeriodic_kernel(unsigned int*);

void kCalculateGBVISoftcoreBornSum( freeEnergyGpuContext freeEnergyGpu )
{

    unsigned int threadsPerBlock;
    static unsigned int threadsPerBlockPerMethod[3] = { 0, 0, 0 };
    static unsigned int natoms[3]                   = { 0, 0, 0 };
    gpuContext gpu                                  = freeEnergyGpu->gpuContext;
    unsigned int methodIndex                        = static_cast<unsigned int>(freeEnergyGpu->freeEnergySim.nonbondedMethod);

    if( methodIndex > 2 ){
        throw OpenMM::OpenMMException( "kCalculateGBVISoftcoreBornSum method index invalid." );
    }

    if( natoms[methodIndex] != gpu->natoms ){
        unsigned int extra                    = methodIndex == 0 ? 0 : sizeof(float);
        threadsPerBlockPerMethod[methodIndex] = std::min(getThreadsPerBlockFEP( freeEnergyGpu, (sizeof(Atom) + extra), gpu->sharedMemoryPerBlock ), gpu->sim.nonbond_threads_per_block );
        natoms[methodIndex]                   = gpu->natoms;
    }   
    threadsPerBlock = threadsPerBlockPerMethod[methodIndex];

    kClearGBVISoftcoreBornSum( gpu );
    LAUNCHERROR("kClearGBVIBornSum from kCalculateGBVISoftcoreBornSum");

    switch (freeEnergyGpu->freeEnergySim.nonbondedMethod)
    {   
        case FREE_ENERGY_NO_CUTOFF:

            if (gpu->bOutputBufferPerWarp){
                kCalculateGBVISoftcoreN2ByWarpBornSum_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                        sizeof(Atom)*threadsPerBlock>>>(gpu->sim.pWorkUnit);
            } else {
                kCalculateGBVISoftcoreN2BornSum_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                        sizeof(Atom)*threadsPerBlock>>>(gpu->sim.pWorkUnit);
            }
            break;

        case FREE_ENERGY_CUTOFF:

            kFindBlockBoundsCutoff_kernel<<<(gpu->psGridBoundingBox->_length+63)/64, 64>>>();
            LAUNCHERROR("kFindBlockBoundsCutoff");
            kFindBlocksWithInteractionsCutoff_kernel<<<gpu->sim.interaction_blocks, gpu->sim.interaction_threads_per_block>>>();
            LAUNCHERROR("kFindBlocksWithInteractionsCutoff");
            compactStream(gpu->compactPlan, gpu->sim.pInteractingWorkUnit, gpu->sim.pWorkUnit, gpu->sim.pInteractionFlag, gpu->sim.workUnits, gpu->sim.pInteractionCount);
            kFindInteractionsWithinBlocksCutoff_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                    sizeof(unsigned int)*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);

            if (gpu->bOutputBufferPerWarp)
                kCalculateGBVISoftcoreCutoffByWarpBornSum_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);
            else
                kCalculateGBVISoftcoreCutoffBornSum_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit );

            break;

        case FREE_ENERGY_PERIODIC:

            kFindBlockBoundsPeriodic_kernel<<<(gpu->psGridBoundingBox->_length+63)/64, 64>>>();
            LAUNCHERROR("kFindBlockBoundsPeriodic");
            kFindBlocksWithInteractionsPeriodic_kernel<<<gpu->sim.interaction_blocks, gpu->sim.interaction_threads_per_block>>>();
            LAUNCHERROR("kFindBlocksWithInteractionsPeriodic");
            compactStream(gpu->compactPlan, gpu->sim.pInteractingWorkUnit, gpu->sim.pWorkUnit, gpu->sim.pInteractionFlag, gpu->sim.workUnits, gpu->sim.pInteractionCount);
            kFindInteractionsWithinBlocksPeriodic_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                    sizeof(unsigned int)*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);

            if (gpu->bOutputBufferPerWarp)
                kCalculateGBVISoftcorePeriodicByWarpBornSum_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit );
            else
                kCalculateGBVISoftcorePeriodicBornSum_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit );

            break;

        default:
            throw OpenMM::OpenMMException( "Nonbonded softcore method not recognized." );

    }
    LAUNCHERROR("kCalculateGBVISoftcoreBornSum");

}
