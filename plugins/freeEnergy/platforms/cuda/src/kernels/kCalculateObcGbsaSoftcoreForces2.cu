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

#include "openmm/OpenMMException.h"
#include "gputypes.h"
#include "freeEnergyGpuTypes.h"

#include <stdio.h>
#include <cuda.h>
#include <vector_functions.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Atom {
    float x;
    float y;
    float z;
    float r;
    float sr;
    float npScale;
    float fx;
    float fy;
    float fz;
    float fb;
};

static __constant__ cudaGmxSimulation cSim;
static __constant__ cudaFreeEnergyGmxSimulation feSimDev;

extern "C"
void SetCalculateObcGbsaSoftcoreForces2Sim( freeEnergyGpuContext freeEnergyGpu )
{
    cudaError_t status;
    status = cudaMemcpyToSymbol(cSim, &freeEnergyGpu->gpuContext->sim, sizeof(cudaGmxSimulation));
    RTERROR(status, "cudaMemcpyToSymbol: SetCalculateObcGbsaSoftcoreForces2Sim copy to cSim failed");

    status = cudaMemcpyToSymbol( feSimDev, &freeEnergyGpu->freeEnergySim, sizeof(cudaFreeEnergyGmxSimulation));
    RTERROR(status, "cudaMemcpyToSymbol: SetCalculateObcGbsaSoftcoreForces2Sim copy to feSimDev failed");

}

// Include versions of the kernels for N^2 calculations.

#define METHOD_NAME(a, b) a##N2##b
#include "kCalculateObcGbsaSoftcoreForces2.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##N2ByWarp##b
#include "kCalculateObcGbsaSoftcoreForces2.h"

// Include versions of the kernels with cutoffs.

#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP
#define USE_CUTOFF
#define METHOD_NAME(a, b) a##Cutoff##b
#include "kCalculateObcGbsaSoftcoreForces2.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##CutoffByWarp##b
#include "kCalculateObcGbsaSoftcoreForces2.h"

// Include versions of the kernels with periodic boundary conditions.

#undef METHOD_NAME
#undef USE_OUTPUT_BUFFER_PER_WARP
#define USE_PERIODIC
#define METHOD_NAME(a, b) a##Periodic##b
#include "kCalculateObcGbsaSoftcoreForces2.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##PeriodicByWarp##b
#include "kCalculateObcGbsaSoftcoreForces2.h"

void kCalculateObcGbsaSoftcoreForces2( freeEnergyGpuContext freeEnergyGpu )
{
    unsigned int threadsPerBlock;
    static unsigned int threadsPerBlockPerMethod[3] = { 0, 0, 0 };
    static unsigned int natoms[3]                   = { 0, 0, 0 };
    gpuContext gpu                                  = freeEnergyGpu->gpuContext;
    unsigned int methodIndex                        = static_cast<unsigned int>(freeEnergyGpu->freeEnergySim.nonbondedMethod);

    if( methodIndex > 2 ){
        throw OpenMM::OpenMMException( "kCalculateObcGbsaSoftcoreForces2 method index invalid." );
    }   

    if( natoms[methodIndex] != gpu->natoms ){
        unsigned int extra                    = methodIndex == 0 ? 0 : sizeof(float3);
        threadsPerBlockPerMethod[methodIndex] = std::min(getThreadsPerBlockFEP( freeEnergyGpu, (sizeof(Atom) + extra), gpu->sharedMemoryPerBlock ), gpu->sim.nonbond_threads_per_block );
        natoms[methodIndex]                   = gpu->natoms;
    }
    threadsPerBlock                                 = threadsPerBlockPerMethod[methodIndex];

    switch (freeEnergyGpu->freeEnergySim.nonbondedMethod)
    {
        case FREE_ENERGY_NO_CUTOFF:

            if (gpu->bOutputBufferPerWarp)
                kCalculateObcGbsaSoftcoreN2ByWarpForces2_kernel<<<gpu->sim.bornForce2_blocks, threadsPerBlock,
                        sizeof(Atom)*threadsPerBlock>>>(gpu->sim.pWorkUnit);
            else
                kCalculateObcGbsaSoftcoreN2Forces2_kernel<<<gpu->sim.bornForce2_blocks, threadsPerBlock,
                        sizeof(Atom)*threadsPerBlock>>>(gpu->sim.pWorkUnit);
            break;

        case FREE_ENERGY_CUTOFF:

            if (gpu->bOutputBufferPerWarp)
                kCalculateObcGbsaSoftcoreCutoffByWarpForces2_kernel<<<gpu->sim.bornForce2_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float3))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);
            else
                kCalculateObcGbsaSoftcoreCutoffForces2_kernel<<<gpu->sim.bornForce2_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float3))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);
            break;

        case FREE_ENERGY_PERIODIC:

            if (gpu->bOutputBufferPerWarp)
                kCalculateObcGbsaSoftcorePeriodicByWarpForces2_kernel<<<gpu->sim.bornForce2_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float3))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);
            else
                kCalculateObcGbsaSoftcorePeriodicForces2_kernel<<<gpu->sim.bornForce2_blocks, threadsPerBlock,
                        (sizeof(Atom)+sizeof(float3))*threadsPerBlock>>>(gpu->sim.pInteractingWorkUnit);
            break;
    }
    LAUNCHERROR("kCalculateObcGbsaSoftcoreForces2");
}
