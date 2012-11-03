#ifndef AMOEBA_CUDATYPES_H
#define AMOEBA_CUDATYPES_H

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

#include <kernels/cudatypes.h>

#include <stdarg.h>
#include <limits>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cufft.h>
#include <builtin_types.h>
#include <vector_functions.h>

enum CudaAmoebaNonbondedMethod
{
    AMOEBA_NO_CUTOFF,
    AMOEBA_PARTICLE_MESH_EWALD
};

static const int AMOEBA_PME_ORDER = 5;
static const int AMOEBA_MAX_TORSION_TORSION_GRIDS = 12;

struct cudaAmoebaGmxSimulation {

    // Constants

    unsigned int    amoebaBonds;                    // Number of bonds
    int4*           pAmoebaBondID;                  // Bond atom and output buffer IDs
    float2*         pAmoebaBondParameter;           // Bond parameters
    float           amoebaBondCubicParameter;       // cubic bond parameters
    float           amoebaBondQuarticicParameter;   // quartic bond parameters
    unsigned int    amoebaBond_offset;              // Offset to end of bonds


    unsigned int    amoebaAngles;                   // Number of bond angles
    int4*           pAmoebaAngleID1;                // Bond angle atom and first output buffer IDs
    int2*           pAmoebaAngleID2;                // Bond angle output buffer IDs
    float2*         pAmoebaAngleParameter;          // Bond angle parameters
    unsigned int    amoebaAngle_offset;             // Offset to end of bond angles

    float amoebaAngleCubicK;                        // cubic factor
    float amoebaAngleQuarticK;                      // quartic factor
    float amoebaAnglePenticK;                       // pentic factor
    float amoebaAngleSexticK;                       // sextic factor

    unsigned int    amoebaInPlaneAngles;            // Number of in-plane angles
    int4*           pAmoebaInPlaneAngleID1;         // Bond angle atom and first output buffer IDs
    int4*           pAmoebaInPlaneAngleID2;         // Bond angle output buffer IDs
    float2*         pAmoebaInPlaneAngleParameter;   // Bond angle parameters
    unsigned int    amoebaInPlaneAngle_offset;      // Offset to end of bond angles

    float amoebaInPlaneAngleCubicK;                 // cubic factor
    float amoebaInPlaneAngleQuarticK;               // quartic factor
    float amoebaInPlaneAnglePenticK;                // pentic factor
    float amoebaInPlaneAngleSexticK;                // sextic factor

    unsigned int    amoebaTorsions;                 // Number of torsions
    int4*           pAmoebaTorsionID1;              // Torsion atom and first output buffer IDs
    int4*           pAmoebaTorsionID2;              // Torsion output buffer IDs
    float4*         pAmoebaTorsionParameter1;       // Torsion parameters
    float2*         pAmoebaTorsionParameter2;       // Torsion parameters
    unsigned int    amoebaTorsion_offset;           // Offset to end of torsions

    unsigned int    amoebaPiTorsions;               // Number of torsions
    int4*           pAmoebaPiTorsionID1;            // PiTorsion atom and first output buffer IDs
    int4*           pAmoebaPiTorsionID2;            // PiTorsion output buffer IDs
    int4*           pAmoebaPiTorsionID3;            // PiTorsion output buffer IDs
    float*          pAmoebaPiTorsionParameter;      // PiTorsion parameters
    unsigned int    amoebaPiTorsion_offset;         // Offset to end of torsions

    unsigned int    amoebaStretchBends;             // Number of stretch bends
    int4*           pAmoebaStretchBendID1;          // stretch bend atoms and first output buffer IDs
    int2*           pAmoebaStretchBendID2;          // stretch bend output buffer IDs
    float4*         pAmoebaStretchBendParameter;    // stretch bend parameters
    unsigned int    amoebaStretchBend_offset;       // Offset to end of stretch bends

    unsigned int    amoebaOutOfPlaneBends;          // Number of stretch bends
    int4*           pAmoebaOutOfPlaneBendID1;       // stretch bend atoms and first output buffer IDs
    int4*           pAmoebaOutOfPlaneBendID2;       // stretch bend output buffer IDs
    float*          pAmoebaOutOfPlaneBendParameter; // stretch bend parameters
    unsigned int    amoebaOutOfPlaneBend_offset;    // Offset to end of stretch bends
    float amoebaOutOfPlaneBendCubicK;               // cubic factor
    float amoebaOutOfPlaneBendQuarticK;             // quartic factor
    float amoebaOutOfPlaneBendPenticK;              // pentic factor
    float amoebaOutOfPlaneBendSexticK;              // sextic factor

    unsigned int    amoebaTorsionTorsions;          // Number of torsion torsions
    int4*           pAmoebaTorsionTorsionID1;       // torsion torsion atoms and first output buffer IDs
    int4*           pAmoebaTorsionTorsionID2;       // torsion torsion output buffer IDs
    int4*           pAmoebaTorsionTorsionID3;       // torsion torsion parameters
    unsigned int    amoebaTorsionTorsion_offset;    // Offset to end of torsion torsions

                                                    // grids
    int   amoebaTorTorGridOffset[AMOEBA_MAX_TORSION_TORSION_GRIDS];                // grid offset
    int   amoebaTorTorGridNy[AMOEBA_MAX_TORSION_TORSION_GRIDS];                    // 25
    float amoebaTorTorGridBegin[AMOEBA_MAX_TORSION_TORSION_GRIDS];                 // -180.0
    float amoebaTorTorGridDelta[AMOEBA_MAX_TORSION_TORSION_GRIDS];                 // 15.0
    float4*          pAmoebaTorsionTorsionGrids;    // torsion torsion grids

    unsigned int    amoebaUreyBradleys;             // Number of UB ixns
    int4*           pAmoebaUreyBradleyID;           // UreyBradley atom and output buffer IDs
    float2*         pAmoebaUreyBradleyParameter;    // UreyBradley parameters
    float           amoebaUreyBradleyCubicParameter;// cubic parameter
    float           amoebaUreyBradleyQuarticicParameter; // quartic parameter
    unsigned int    amoebaUreyBradley_offset;       // Offset to end of bonds

    float sqrtPi;                                   // sqrt(PI)
    float scalingDistanceCutoff;                    // scaling cutoff
    float2*         pDampingFactorAndThole;         // Thole & damping factors
    int polarizationType;                           // polarization type (0=Mutual, 1=Direct)

    int4*  pMultipoleParticlesIdsAndAxisType; 
    int4*  pMultipoleParticlesTorqueBufferIndices; 
    int maxTorqueBufferIndex;
    float4* pTorqueMapForce4;

    float* pMolecularDipole; 
    float* pMolecularQuadrupole; 

    float* pLabFrameDipole;
    float* pLabFrameQuadrupole;

    float* pInducedDipole;
    float* pInducedDipolePolar;

    float* pInducedDipoleS;
    float* pInducedDipolePolarS;

    float* pTorque;

    float* pWorkArray_3_1;
    float* pWorkArray_3_2;
    float* pWorkArray_1_1;
    float* pWorkArray_1_2;

    int vdwUsePBC;
    float vdwCutoff;
    float vdwCutoff2;
    float vdwTaperCutoff;
    float vdwTaperCutoff2;
    float vdwTaperDelta;

#define VDW_TAPER_TABLE_SIZE 100
    float vdwTaperTable[VDW_TAPER_TABLE_SIZE+1];
    float vdw_dTaperTable[VDW_TAPER_TABLE_SIZE+1];

    unsigned int amoebaVdwNonReductions;
    int* pAmoebaVdwNonReductionID;
    unsigned int* pVdwWorkUnit;

    unsigned int amoebaVdwReductions;
    int4* pAmoebaVdwReductionID;
    float* pAmoebaVdwReduction;
    int* pVdwExclusionIndicesIndex;
    int* pVdwExclusionIndices;

    // WCA constants

    float epso;
    float epsh;
    float rmino;
    float rminh;
    float awater;
    float shctd;
    float dispoff;
    float totalMaxWcaDispersionEnergy;
    float2* pWcaDispersionRadiusEpsilon;

                    // scaling indices
    int*            pScaleIndicesIndex;
    int*            pD_ScaleIndices;
    int2*           pP_ScaleIndices;
    int2*           pM_ScaleIndices;

    float electric;   // 3.320637090E+02f;
    float gkc;        // 2.455f;

    float dielec;    // 1.0f;
    float dwater;    // 78.3f;
    float fc;        // electric * 1.0f * (1.0f-dwater)/(0.0f+1.0f*dwater);
    float fd;        // electric * 2.0f * (1.0f-dwater)/(1.0f+2.0f*dwater);
    float fq;        // electric * 3.0f * (1.0f-dwater)/(2.0f+3.0f*dwater);

    // PME arrays

    float4* pThetai1;
    float4* pThetai2;
    float4* pThetai3;
    int4* pIgrid;
    float* pPhi;
    float* pPhid;
    float* pPhip;
    float* pPhidp;
};

#endif
