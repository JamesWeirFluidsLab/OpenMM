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

#include "amoebaScaleFactors.h"

__global__
#if (__CUDA_ARCH__ >= 200)
__launch_bounds__(GF1XX_NONBOND_THREADS_PER_BLOCK, 1)
#elif (__CUDA_ARCH__ >= 120)
__launch_bounds__(GT2XX_NONBOND_THREADS_PER_BLOCK, 1)
#else
__launch_bounds__(G8X_NONBOND_THREADS_PER_BLOCK, 1)
#endif
void METHOD_NAME(kCalculateAmoebaMutualInducedField, _kernel)(
                            unsigned int* workUnit,
                            float* outputField, float* outputFieldPolar){

    extern __shared__ MutualInducedParticle sA[];

    unsigned int totalWarps      = gridDim.x*blockDim.x/GRID;
    unsigned int warp            = (blockIdx.x*blockDim.x+threadIdx.x)/GRID;
    unsigned int numWorkUnits    = cSim.pInteractionCount[0];
    unsigned int pos             = warp*numWorkUnits/totalWarps;
    unsigned int end             = (warp+1)*numWorkUnits/totalWarps;
    unsigned int lasty           = 0xFFFFFFFF;

    while (pos < end)
    {

        unsigned int x;
        unsigned int y;
        bool bExclusionFlag;

        // Extract cell coordinates

        decodeCell( workUnit[pos], &x, &y, &bExclusionFlag );

        unsigned int tgx                 = threadIdx.x & (GRID - 1);
        unsigned int tbx                 = threadIdx.x - tgx;
        unsigned int tj                  = tgx;

        MutualInducedParticle*  psA      = &sA[tbx];
        unsigned int atomI               = x + tgx;
        MutualInducedParticle localParticle;
        loadMutualInducedShared( &localParticle, atomI );

        float fieldSum[3];
        float fieldPolarSum[3];

        // 0: field at i due to j
        // 1: field at i due to j polar

        fieldSum[0]                      = 0.0f;
        fieldSum[1]                      = 0.0f;
        fieldSum[2]                      = 0.0f;

        fieldPolarSum[0]                 = 0.0f;
        fieldPolarSum[1]                 = 0.0f;
        fieldPolarSum[2]                 = 0.0f;

        if (x == y) // Handle diagonals uniquely at 50% efficiency
        {

            // load shared data

            loadMutualInducedShared( &(sA[threadIdx.x]), atomI );

            for (unsigned int j = 0; j < GRID; j++)
            {

                float ijField[4][3];

                // load coords, charge, ...

                calculateMutualInducedFieldPairIxn_kernel( localParticle, psA[j], ijField);

                unsigned int mask       =  ( (atomI == (y + j)) || (atomI >= cSim.atoms) || ((y+j) >= cSim.atoms) ) ? 0 : 1;

                // add to field at atomI the field due atomJ's dipole

                fieldSum[0]            += mask ? ijField[0][0] : 0.0f;
                fieldSum[1]            += mask ? ijField[0][1] : 0.0f;
                fieldSum[2]            += mask ? ijField[0][2] : 0.0f;

                fieldPolarSum[0]       += mask ? ijField[1][0] : 0.0f;
                fieldPolarSum[1]       += mask ? ijField[1][1] : 0.0f;
                fieldPolarSum[2]       += mask ? ijField[1][2] : 0.0f;

            }

            // Write results

#ifdef USE_OUTPUT_BUFFER_PER_WARP
            unsigned int offset            = 3*(x + tgx + warp*cSim.paddedNumberOfAtoms);
            load3dArrayBufferPerWarp( offset, fieldSum,      outputField );
            load3dArrayBufferPerWarp( offset, fieldPolarSum, outputFieldPolar);

#else
            unsigned int offset            = 3*(x + tgx + (x >> GRIDBITS) * cSim.paddedNumberOfAtoms);
            load3dArray( offset, fieldSum,      outputField );
            load3dArray( offset, fieldPolarSum, outputFieldPolar);

#endif

        } else {

            // Read fixed atom data into registers and GRF
            if (lasty != y)
            {
                unsigned int atomJ        = y + tgx;

                // load coordinates, charge, ...

                loadMutualInducedShared( &(sA[threadIdx.x]), atomJ );
            }

           // zero shared fields

            zeroMutualInducedParticleSharedField(  &(sA[threadIdx.x]) );

            for (unsigned int j = 0; j < GRID; j++)
            {

                float ijField[4][3];

                // load coords, charge, ...

                calculateMutualInducedFieldPairIxn_kernel( localParticle, psA[tj], ijField);

                unsigned int mask         =  ( (atomI >= cSim.atoms) || ((y+tj) >= cSim.atoms) ) ? 0 : 1;
           
                // add to field at atomI the field due atomJ's dipole

                fieldSum[0]              += mask ? ijField[0][0] : 0.0f;
                fieldSum[1]              += mask ? ijField[0][1] : 0.0f;
                fieldSum[2]              += mask ? ijField[0][2] : 0.0f;
    
                // add to polar field at atomI the field due atomJ's dipole

                fieldPolarSum[0]         += mask ? ijField[1][0] : 0.0f;
                fieldPolarSum[1]         += mask ? ijField[1][1] : 0.0f;
                fieldPolarSum[2]         += mask ? ijField[1][2] : 0.0f;

                // add to field at atomJ the field due atomI's dipole

                psA[tj].field[0]         += mask ? ijField[2][0] : 0.0f;
                psA[tj].field[1]         += mask ? ijField[2][1] : 0.0f;
                psA[tj].field[2]         += mask ? ijField[2][2] : 0.0f;

                // add to polar field at atomJ the field due atomI's dipole

                psA[tj].fieldPolar[0]    += mask ? ijField[3][0] : 0.0f;
                psA[tj].fieldPolar[1]    += mask ? ijField[3][1] : 0.0f;
                psA[tj].fieldPolar[2]    += mask ? ijField[3][2] : 0.0f;


                tj                        = (tj + 1) & (GRID - 1);

            }

            // Write results

#ifdef USE_OUTPUT_BUFFER_PER_WARP
            unsigned int offset     = 3*(x + tgx + warp*cSim.paddedNumberOfAtoms);
            load3dArrayBufferPerWarp( offset, fieldSum,      outputField );
            load3dArrayBufferPerWarp( offset, fieldPolarSum, outputFieldPolar);

            offset                  = 3*(y + tgx + warp*cSim.paddedNumberOfAtoms);

            load3dArrayBufferPerWarp( offset, sA[threadIdx.x].field,      outputField );
            load3dArrayBufferPerWarp( offset, sA[threadIdx.x].fieldPolar, outputFieldPolar);

#else
            unsigned int offset     = 3*(x + tgx + (y >> GRIDBITS) * cSim.paddedNumberOfAtoms);
            load3dArray( offset, fieldSum,      outputField );
            load3dArray( offset, fieldPolarSum, outputFieldPolar);

            offset                  = 3*(y + tgx + (x >> GRIDBITS) * cSim.paddedNumberOfAtoms);
            load3dArray( offset, sA[threadIdx.x].field,      outputField );
            load3dArray( offset, sA[threadIdx.x].fieldPolar, outputFieldPolar);

#endif
            lasty = y;
        }

        pos++;
    }
}
