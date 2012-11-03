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
#include "kCalculateAmoebaCudaUtilities.h"
#include "kCalculateAmoebaCudaWcaDispersionParticle.h"
#include "amoebaScaleFactors.h"

#include <stdio.h>

using namespace std;

static __constant__ cudaGmxSimulation cSim;
static __constant__ cudaAmoebaGmxSimulation cAmoebaSim;

void SetCalculateAmoebaCudaWcaDispersionSim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status         = cudaMemcpyToSymbol(cSim, &gpu->sim, sizeof(cudaGmxSimulation));    
    RTERROR(status, "SetCalculateAmoebaCudaWcaDispersionSim: cudaMemcpyToSymbol: SetSim copy to cSim failed");
    status         = cudaMemcpyToSymbol(cAmoebaSim, &amoebaGpu->amoebaSim, sizeof(cudaAmoebaGmxSimulation));    
    RTERROR(status, "SetCalculateAmoebaCudaWcaDispersionFieldSim: cudaMemcpyToSymbol: SetSim copy to cAmoebaSim failed");
}

void GetCalculateAmoebaCudaWcaDispersionSim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status = cudaMemcpyFromSymbol(&gpu->sim, cSim, sizeof(cudaGmxSimulation));    
    RTERROR(status, "GetCalculateAmoebaCudaWcaDispersionSim: cudaMemcpyFromSymbol: SetSim copy from cSim failed");
    status = cudaMemcpyFromSymbol(&amoebaGpu->amoebaSim, cAmoebaSim, sizeof(cudaAmoebaGmxSimulation));    
    RTERROR(status, "GetCalculateAmoebaCudaWcaDispersionSim: cudaMemcpyFromSymbol: SetSim copy from cAmoebaSim failed");
}

__device__ void zeroWcaDispersionSharedForce( struct WcaDispersionParticle* sA ) 
{
    // zero shared fields

    sA->force[0]              = 0.0f;
    sA->force[1]              = 0.0f;
    sA->force[2]              = 0.0f;

}

__device__ void loadWcaDispersionShared( struct WcaDispersionParticle* sA, unsigned int atomI,
                                         float4* atomCoord, float2* wcaParameters )
{
    // coordinates, radius, epsilon

    sA->x                        = atomCoord[atomI].x;
    sA->y                        = atomCoord[atomI].y;
    sA->z                        = atomCoord[atomI].z;

    sA->radius                   = wcaParameters[atomI].x;
    sA->epsilon                  = wcaParameters[atomI].y;

}

// load struct and arrays w/ shared data in sA

__device__ void loadWcaDispersionData( struct WcaDispersionParticle* sA,
                                       float4* jCoord, float* jRadius, float* jEpsilon )
{

    // load coordinates, radius, epsilon

    jCoord->x               = sA->x;
    jCoord->y               = sA->y;
    jCoord->z               = sA->z;

    *jRadius                = sA->radius;
    *jEpsilon               = sA->epsilon;
}

__device__ void calculateWcaDispersionInit_kernel( float iRadius,   float iEpsilon,
                                                   float* rmixo,    float* rmixh,
                                                   float* emixo,    float* emixh

 )
{

    float sqrtEps                   = sqrtf(iEpsilon);
    float denominator               = sqrtf(cAmoebaSim.epso) + sqrtEps;
         *emixo                     = 4.0f*cAmoebaSim.epso*iEpsilon / (denominator*denominator);

          denominator               = sqrtf(cAmoebaSim.epsh) + sqrtEps;
         *emixh                     = 4.0f*cAmoebaSim.epsh*iEpsilon / (denominator*denominator);

    float iRadius2                  = iRadius*iRadius;
    float rmino2                    = cAmoebaSim.rmino*cAmoebaSim.rmino; 
         *rmixo                     = 2.0f*(rmino2*cAmoebaSim.rmino + iRadius2*iRadius) / (rmino2 + iRadius2);

    float rminh2                    = cAmoebaSim.rminh*cAmoebaSim.rminh;
         *rmixh                     = 2.0f*(rminh2*cAmoebaSim.rminh + iRadius2*iRadius) / (rminh2+iRadius2);

}

__device__ void calculateWcaDispersionPairIxn_kernel( float4 atomCoordinatesI, float4 atomCoordinatesJ,
                                                      float radiusI,  float radiusJ,
                                                      float rmixo,    float rmixh,
                                                      float emixo,    float emixh,
                                                      float force[3], float* energy ) {

    const float pi         = 3.1415926535897f;
    const float shctd      = cAmoebaSim.shctd;
    const float awater     = cAmoebaSim.awater;

    // ---------------------------------------------------------------------------------------
    
    // get deltaR, and r between 2 atoms
    
    force[0]                                     = atomCoordinatesJ.x - atomCoordinatesI.x;
    force[1]                                     = atomCoordinatesJ.y - atomCoordinatesI.y;
    force[2]                                     = atomCoordinatesJ.z - atomCoordinatesI.z;

    float r2                                     = force[0]*force[0] + force[1]*force[1] + force[2]*force[2];
    if( r2 <= 0.0f ){
        force[0] = force[1] = force[2] = *energy = 0.0f;
        return;
    }
    float rI                                     = rsqrtf( r2 );
    float r                                      = 1.0f/rI;

    float sk                                     = radiusJ*shctd;
    float sk2                                    = sk*sk;
    if( radiusI >= (r+sk) ){
        force[0] = force[1] = force[2] = *energy = 0.0f;
        return;
    }

    float rmax                                   = radiusI > (r - sk) ? radiusI : (r - sk);
    float lik                                    = rmax;
    float lik2                                   = lik*lik;
    float lik3                                   = lik2*lik;
    float lik4                                   = lik2*lik2;
 
    float uik                                    = (r+sk) < rmixo ? (r+sk) : rmixo;
    float uik2                                   = uik*uik;
    float uik3                                   = uik2*uik;
    float uik4                                   = uik2*uik2;

    // 3453
    float term                                   = 4.0f*pi/(48.f*r)*(3.0f*(lik4-uik4) - 8.0f*r*(lik3-uik3) + 6.0f*(r2-sk2)*(lik2-uik2));

    float r3                                     = r2*r;
    float dl1                                    = lik2*(-lik2 + 2.0f*(r2 + sk2) );
    float dl2                                    = lik*(-lik3 + 4.0f*lik2*r - 6.0f*lik*r2 + 2.0f*lik*sk2 + 4.0f*r3 - 4.0f*r*sk2);
    float dl                                     = radiusI > (r-sk)? dl1 : dl2;

    // 3464

    float du1                                    = uik2*(-uik2 + 2.0f*(r2 + sk2) );
    float du2                                    = uik*(-uik3 + 4.0f*uik2*r - 2.0f*uik*(3.0f*r2 - sk2) + 4.0f*r*(r2 - sk2) );
    //float du2                                    = uik*(uik*( -uik2 + 4.0f*uik*r - 2.0f*(3.0f*r2 - sk2)) + 4.0f*r*(r2 - sk2) );
    float du                                     = (r+sk) > rmixo ? du1 : du2;
          du                                    *= -1.0f;

    float mask2                                  = lik < rmixo ? 1.0f : 0.0f;
    float sum                                    = -mask2*(emixo*term);
    float de                                     = -mask2*emixo*pi*(dl+du)/(4.0f*r2);

    // block at 3476

    uik                                          = (r+sk) < rmixh ? (r+sk) : rmixh;
    uik2                                         = uik*uik;
    uik3                                         = uik2*uik;
    uik4                                         = uik2*uik2;

    // 3481

    term                                         = (pi)/ (12.0f*r) * (3.0f*(lik4-uik4) - 8.0f*r*(lik3-uik3) + 6.0f*(r2-sk2)*(lik2-uik2));

    dl1                                          = lik2*(-lik2 + 2.0f*r2 + 2.0f*sk2);
    dl2                                          = lik*(-lik3 + 4.0f*lik2*r - 6.0f*lik*r2 + 2.0f*lik*sk2 + 4.0f*r3 - 4.0f*r*sk2);
    dl                                           = radiusI > (r-sk) ? dl1 : dl2;

    // 3492

    du1                                          = -uik2*(-uik2 + 2.0f*r2 + 2.0f*sk2);
    du2                                          = -uik*(-uik3 + 4.0f*uik2*r - 6.0f*uik*r2 + 2.0f*uik*sk2 + 4.0f*r3 - 4.0f*r*sk2);
    du                                           = (r+sk) > rmixh ? du1 : du2;

    mask2                                        = lik < rmixh ? 1.0f : 0.0f;
    sum                                         -= mask2*(2.0f*emixh*term);
    de                                          -= mask2*(2.0f*emixh*pi*(dl+du)/(4.0f*r2));

    // 3504

    uik                                          = r + sk;
    uik2                                         = uik*uik;
    uik3                                         = uik2*uik;
    uik4                                         = uik2*uik2;
    float uik5                                   = uik4*uik;
    float uik6                                   = uik3*uik3;
    float uik10                                  = uik5*uik5;
    float uik11                                  = uik10*uik;
    float uik12                                  = uik6*uik6;
    float uik13                                  = uik12*uik;

    lik                                          = rmax > rmixo ? rmax : rmixo;
    lik2                                         = lik*lik;
    lik3                                         = lik2*lik;
    lik4                                         = lik2*lik2;
    float lik5                                   = lik4*lik;
    float lik6                                   = lik3*lik3;
    float lik10                                  = lik5*lik5;
    float lik11                                  = lik10*lik;
    float lik12                                  = lik6*lik6;
    float lik13                                  = lik12*lik;

    // 3525

    term                                         = 4.0f*pi/(120.0f*r*lik5*uik5)*(15.0f*uik*lik*r*(uik4-lik4) - 10.0f*uik2*lik2*(uik3-lik3) + 6.0f*(sk2-r2)*(uik5-lik5));
    dl1                                          = (-5.0f*lik2 + 3.0f*r2 + 3.0f*sk2)/lik5;
    dl2                                          = ( 5.0f*lik3 - 33.0f*lik*r2 - 3.0f*lik*sk2 + 15.0f*(lik2*r+r3-r*sk2))/lik6;
    dl                                           = (radiusI > (r-sk)) || (rmax < rmixo) ? -dl1 : dl2;

    du                                           = (-5.0f*uik3 + 33.0f*uik*r2 + 3.0f*uik*sk2 - 15.0f*(uik2*r+r3-r*sk2))/uik6;

    float rmixo7                                 = rmixo*rmixo*rmixo;
          rmixo7                                 = rmixo7*rmixo7*rmixo;
    float ao                                     = emixo*rmixo7;

    // 3540

    float idisp                                  = -2.0f*ao*term;
    mask2                                        = uik > rmixo ? 1.0f : 0.0f;

    // 3541
    de                                          -= mask2*(2.0f*ao*pi*(dl + du)/(15.0f*r2));

    // 3542

    term                                         = 4.0f*pi/(2640.0f*r*lik12*uik12) * (120.0f*uik*lik*r*(uik11-lik11) - 66.0f*uik2*lik2*(uik10-lik10) + 55.0f*(sk2-r2)*(uik12-lik12));

    // 3546

    dl1                                          = (6.0f*lik2 - 5.0f*r2 - 5.0f*sk2)/lik12;
    dl2                                          = (6.0f*lik3 - 125.0f*lik*r2 - 5.0f*lik*sk2 + 60.0f*(lik2*r+r3-r*sk2))/lik13;
    dl                                           = (radiusI > (r-sk)) || (rmax < rmixo) ? dl1 : dl2;

    // 3554

    du                                           = (-6.0f*uik3 + 125.0f*uik*r2 + 5.0f*uik*sk2 - 60.0f*(uik2*r+r3-r*sk2))/uik13;

    de                                          += mask2*(ao*rmixo7*pi*(dl + du)/(60.0f*r2));
    float irep                                   = ao*rmixo7*term;
    sum                                         += mask2*(irep + idisp);

    // 3562

    lik                                          = rmax > rmixh ? rmax : rmixh;
    lik2                                         = lik*lik;
    lik3                                         = lik2*lik;
    lik4                                         = lik2*lik2;
    lik5                                         = lik4*lik;
    lik6                                         = lik3*lik3;
    lik10                                        = lik5*lik5;
    lik11                                        = lik10*lik;
    lik12                                        = lik6*lik6;
    lik13                                        = lik12*lik;

    // 3572

    term                                         = 4.0f * pi / (120.0f*r*lik5*uik5) * (15.0f*uik*lik*r*(uik4-lik4) -
                                                   10.0f*uik2*lik2*(uik3-lik3) + 6.0f*(sk2-r2)*(uik5-lik5));

    dl1                                          = (-5.0f*lik2 + 3.0f*r2 + 3.0f*sk2)/lik5;
    dl2                                          = (5.0f*lik3 - 33.0f*lik*r2 - 3.0f*lik*sk2+ 15.0f*(lik2*r+r3-r*sk2))/lik6;
    dl                                           = (radiusI > (r-sk)) || (rmax < rmixh) ? -dl1 : dl2;

    du                                           = -(5.0f*uik3 - 33.0f*uik*r2 - 3.0f*uik*sk2 + 15.0f*(uik2*r+r3-r*sk2))/uik6;

    float rmixh7                                 = rmixh*rmixh*rmixh;
          rmixh7                                 = rmixh7*rmixh7*rmixh;
    float ah                                     = emixh * rmixh7;

    // 3587
    idisp                                        = -4.0f * ah * term;

    mask2                                        = uik > rmixh ? 1.0f : 0.0f;
    de                                          -= mask2*(4.0f*ah*pi*(dl + du)/(15.0f*r2));

    term                                         = 4.0f * pi / (2640.0f*r*lik12*uik12) * (120.0f*uik*lik*r*(uik11-lik11) -
                                                   66.0f*uik2*lik2*(uik10-lik10) + 55.0f*(sk2-r2)*(uik12-lik12));

    // 3593

    dl1                                          = -(-6.0f*lik2 + 5.0f*r2 + 5.0f*sk2)/lik12;
    dl2                                          =  (6.0f*lik3 - 125.0f*lik*r2 - 5.0f*lik*sk2 + 60.0f*(lik2*r+r3-r*sk2))/lik13;
    dl                                           = ( (radiusI > (r-sk) ) || (rmax < rmixh) ) ? dl1 : dl2;

    // 3603

    du                                           = -(6.0f*uik3 - 125.0f*uik*r2 -5.0f*uik*sk2 + 60.0f*(uik2*r+r3-r*sk2))/uik13;
    irep                                         = 2.0f*ah*rmixh7*term;

    de                                          += mask2*(ah*rmixh7*pi*(dl+du)/(30.0f*r2));
    sum                                         += mask2*(irep + idisp);

    *energy                                      = sum;

    de                                          *= -(awater/r);
    force[0]                                    *= de;
    force[1]                                    *= de;
    force[2]                                    *= de;

}

// Include versions of the kernels for N^2 calculations.

#define METHOD_NAME(a, b) a##N2##b
#include "kCalculateAmoebaCudaWcaDispersion.h"

#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##N2ByWarp##b
#include "kCalculateAmoebaCudaWcaDispersion.h"

/**---------------------------------------------------------------------------------------

   Compute WCA dispersion

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */

void kCalculateAmoebaWcaDispersionForces( amoebaGpuContext amoebaGpu )
{
  
   // ---------------------------------------------------------------------------------------

    static int threadsPerBlock    = 0;

   // ---------------------------------------------------------------------------------------

     gpuContext gpu    = amoebaGpu->gpuContext;

    // set threads/block first time through

    if( threadsPerBlock == 0 ){
        unsigned int maxThreads;
        if (gpu->sm_version >= SM_20)
            maxThreads = 384;
        else if (gpu->sm_version >= SM_12)
            maxThreads = 192;
        else
            maxThreads = 64;
       threadsPerBlock = std::min(getThreadsPerBlock( amoebaGpu, sizeof(WcaDispersionParticle), gpu->sharedMemoryPerBlock ), maxThreads);
    }

    if (gpu->bOutputBufferPerWarp){

        kCalculateAmoebaWcaDispersionN2ByWarp_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(WcaDispersionParticle)*threadsPerBlock>>>(
                                                            gpu->psWorkUnit->_pDevData );

    } else {

        kCalculateAmoebaWcaDispersionN2_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(WcaDispersionParticle)*threadsPerBlock>>>(
                                                            gpu->psWorkUnit->_pDevData );

    }
    LAUNCHERROR("kCalculateAmoebaWcaDispersion");  

   // ---------------------------------------------------------------------------------------
}
