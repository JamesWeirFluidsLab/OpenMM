#ifndef CUDATYPES_H
#define CUDATYPES_H

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
#include "openmm/OpenMMException.h"

#define RTERROR(status, s) \
    if (status != cudaSuccess) { \
        throw OpenMM::OpenMMException(std::string(s) + " " + cudaGetErrorString(status)); \
    }

#define LAUNCHERROR(s) \
    { \
        cudaError_t status = cudaGetLastError(); \
        if (status != cudaSuccess) { \
            throw OpenMM::OpenMMException(std::string("Error: ") + cudaGetErrorString(status) + " launching kernel " + s); \
        } \
    }

// Pure virtual class to define an interface for objects resident both on GPU and CPU
struct SoADeviceObject {
    virtual void Allocate() = 0;
    virtual void Deallocate() = 0;
    virtual void Upload() = 0;
    virtual void Download() = 0;
};

template <typename T>
struct CUDAStream : public SoADeviceObject
{
    unsigned int    _length;
    unsigned int    _subStreams;
    unsigned int    _stride;
    T**             _pSysStream;
    T**             _pDevStream;
    T*              _pSysData;
    T*              _pDevData;
    std::string     _name;
    CUDAStream(int length, int subStreams = 1, std::string name="");
    CUDAStream(unsigned int length, unsigned int subStreams = 1, std::string name="");
    CUDAStream(unsigned int length, int subStreams = 1, std::string name="");
    CUDAStream(int length, unsigned int subStreams = 1, std::string name="");
    virtual ~CUDAStream();
    void Allocate();
    void Deallocate();
    void Upload();
    void Download();
    void CopyFrom(const CUDAStream<T>& src);
    void Collapse(unsigned int newstreams = 1, unsigned int interleave = 1);
    T& operator[](int index);
};

float CompareStreams(CUDAStream<float>& s1, CUDAStream<float>& s2, float tolerance, unsigned int maxindex = 0);

template <typename T>
CUDAStream<T>::CUDAStream(int length, unsigned int subStreams, std::string name) : _length(length), _subStreams(subStreams), _stride((length + 0xf) & 0xfffffff0), _name(name)
{
    Allocate();   
}

template <typename T>
CUDAStream<T>::CUDAStream(unsigned int length, int subStreams, std::string name) : _length(length), _subStreams(subStreams), _stride((length + 0xf) & 0xfffffff0), _name(name)
{
    Allocate();   
}

template <typename T>
CUDAStream<T>::CUDAStream(unsigned int length, unsigned int subStreams, std::string name) : _length(length), _subStreams(subStreams), _stride((length + 0xf) & 0xfffffff0), _name(name)
{
    Allocate();   
}

template <typename T>
CUDAStream<T>::CUDAStream(int length, int subStreams, std::string name) : _length(length), _subStreams(subStreams), _stride((length + 0xf) & 0xfffffff0), _name(name)
{
    Allocate();   
}

template <typename T>
CUDAStream<T>::~CUDAStream()
{
    Deallocate();
}

template <typename T>
void CUDAStream<T>::Allocate()
{
    cudaError_t status;
    _pSysStream =   new T*[_subStreams];
    _pDevStream =   new T*[_subStreams];
    _pSysData =     new T[_subStreams * _stride];

    status = cudaMalloc((void **) &_pDevData, _stride * _subStreams * sizeof(T));
    RTERROR(status, (_name+": cudaMalloc in CUDAStream::Allocate failed").c_str());

    for (unsigned int i = 0; i < _subStreams; i++)
    {
        _pSysStream[i] = _pSysData + i * _stride;
        _pDevStream[i] = _pDevData + i * _stride;
    }
}

template <typename T>
void CUDAStream<T>::Deallocate()
{
    cudaError_t status;
    delete[] _pSysStream;
    _pSysStream = NULL;
    delete[] _pDevStream;
    _pDevStream = NULL;
    delete[] _pSysData;
    _pSysData = NULL;
    status = cudaFree(_pDevData);
    RTERROR(status, (_name+": cudaFree in CUDAStream::Deallocate failed").c_str());
}

template <typename T>
void CUDAStream<T>::Upload()
{
    cudaError_t status;
    status = cudaMemcpy(_pDevData, _pSysData, _stride * _subStreams * sizeof(T), cudaMemcpyHostToDevice);
    RTERROR(status, (_name+": cudaMemcpy in CUDAStream::Upload failed").c_str());
}

template <typename T>
void CUDAStream<T>::Download()
{
    cudaError_t status;
    status = cudaMemcpy(_pSysData, _pDevData, _stride * _subStreams * sizeof(T), cudaMemcpyDeviceToHost);
    RTERROR(status, (_name+": cudaMemcpy in CUDAStream::Download failed").c_str());
}

template <typename T>
void CUDAStream<T>::CopyFrom(const CUDAStream<T>& src)
{
    cudaError_t status;
    status = cudaMemcpy(_pDevData, src._pDevData, _stride * _subStreams * sizeof(T), cudaMemcpyDeviceToDevice);
    RTERROR(status, (_name+": cudaMemcpy in CUDAStream::Copy failed").c_str());
}

template <typename T>
void CUDAStream<T>::Collapse(unsigned int newstreams, unsigned int interleave)
{
    T* pTemp = new T[_subStreams * _stride];
    unsigned int stream = 0;
    unsigned int pos = 0;
    unsigned int newstride = _stride * _subStreams / newstreams;
    unsigned int newlength = _length * _subStreams / newstreams;

    // Copy data into new format
    for (unsigned int i = 0; i < _length; i++)
    {
        for (unsigned int j = 0; j < _subStreams; j++)
        {
            pTemp[stream * newstride + pos] = _pSysStream[j][i];
            stream++;
            if (stream == newstreams)
            {
                stream = 0;
                pos++;
            }
        }
    }

    // Remap stream pointers;
    for (unsigned int i = 0; i < newstreams; i++)
    {
        _pSysStream[i] = _pSysData + i * newstride;
        _pDevStream[i] = _pDevData + i * newstride;
    }

    // Copy data back intro original stream
    for (unsigned int i = 0; i < newlength; i++)
        for (unsigned int j = 0; j < newstreams; j++)
            _pSysStream[j][i] = pTemp[j * newstride + i];
    
    _stride = newstride;
    _length = newlength;
    _subStreams = newstreams;
    delete[] pTemp;
}

template <typename T>
T& CUDAStream<T>::operator[](int index)
{
    return _pSysData[index];
}

static const unsigned int GRID = 32;
static const unsigned int GRIDBITS = 5;
static const int G8X_BLOCKS_PER_SM                      = 1;
static const int GT2XX_BLOCKS_PER_SM                    = 1;
static const int GF1XX_BLOCKS_PER_SM                    = 1;

static const int G8X_NONBOND_THREADS_PER_BLOCK          = 256;
static const int GT2XX_NONBOND_THREADS_PER_BLOCK        = 320;
static const int GF1XX_NONBOND_THREADS_PER_BLOCK        = 768;
//static const int GF1XX_NONBOND_THREADS_PER_BLOCK        = 768;

static const int G8X_BORNFORCE2_THREADS_PER_BLOCK       = 256;
static const int GT2XX_BORNFORCE2_THREADS_PER_BLOCK     = 320;
static const int GF1XX_BORNFORCE2_THREADS_PER_BLOCK     = 768;
//static const int GF1XX_BORNFORCE2_THREADS_PER_BLOCK     = 768;

static const int G8X_SHAKE_THREADS_PER_BLOCK            = 128;
static const int GT2XX_SHAKE_THREADS_PER_BLOCK          = 256;
static const int GF1XX_SHAKE_THREADS_PER_BLOCK          = 512;

static const int G8X_UPDATE_THREADS_PER_BLOCK           = 192;
static const int GT2XX_UPDATE_THREADS_PER_BLOCK         = 384;
static const int GF1XX_UPDATE_THREADS_PER_BLOCK         = 768;

static const int G8X_LOCALFORCES_THREADS_PER_BLOCK      = 192;
static const int GT2XX_LOCALFORCES_THREADS_PER_BLOCK    = 384;
static const int GF1XX_LOCALFORCES_THREADS_PER_BLOCK    = 768;

static const int G8X_THREADS_PER_BLOCK                  = 256;
static const int GT2XX_THREADS_PER_BLOCK                = 256;
static const int GF1XX_THREADS_PER_BLOCK                = 512;

static const int G8X_RANDOM_THREADS_PER_BLOCK           = 256;
static const int GT2XX_RANDOM_THREADS_PER_BLOCK         = 384;
static const int GF1XX_RANDOM_THREADS_PER_BLOCK         = 768;

static const int G8X_NONBOND_WORKUNITS_PER_SM           = 220;
static const int GT2XX_NONBOND_WORKUNITS_PER_SM         = 256;
static const int GF1XX_NONBOND_WORKUNITS_PER_SM         = 768;

static const unsigned int MAX_STACK_SIZE = 8;
static const unsigned int MAX_TABULATED_FUNCTIONS = 4;

static const float PI = 3.14159265358979323846f;

static const int PME_ORDER = 5;

enum CudaNonbondedMethod
{
    NO_CUTOFF,
    CUTOFF,
    PERIODIC,
    EWALD,
    PARTICLE_MESH_EWALD
};

enum ExpressionOp {
    VARIABLE0 = 0, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8, MULTIPLY, DIVIDE, ADD, SUBTRACT, POWER, MULTIPLY_CONSTANT, POWER_CONSTANT, ADD_CONSTANT,
        GLOBAL, CONSTANT, CUSTOM, CUSTOM_DERIV, NEGATE, RECIPROCAL, SQRT, EXP, LOG, SQUARE, CUBE, STEP, SIN, COS, SEC, CSC, TAN, COT, ASIN, ACOS, ATAN, SINH, COSH, TANH, ERF, ERFC,
        MIN, MAX, ABS
};

template<int SIZE>
struct Expression {
    int op[SIZE];
    float arg[SIZE];
    int length, stackSize;
};

struct cudaGmxSimulation {
    // Constants
    unsigned int    atoms;                          // Number of atoms
    unsigned int    paddedNumberOfAtoms;            // Padded number of atoms
    unsigned int    blocks;                         // Number of blocks to launch across linear kernels
    unsigned int    blocksPerSM;                    // Number of blocks per share memory
    unsigned int    nonbond_blocks;                 // Number of blocks to launch across CDLJ and Born Force Part1
    unsigned int    bornForce2_blocks;              // Number of blocks to launch across Born Force 2
    unsigned int    interaction_blocks;             // Number of blocks to launch when identifying interacting tiles
    unsigned int    threads_per_block;              // Threads per block to launch
    unsigned int    nonbond_threads_per_block;      // Threads per block in nonbond kernel calls
    unsigned int    bornForce2_threads_per_block;   // Threads per block in nonbond kernel calls
    unsigned int    max_update_threads_per_block;   // Maximum threads per block in update kernel calls
    unsigned int    update_threads_per_block;       // Threads per block in update kernel calls
    unsigned int    bf_reduce_threads_per_block;    // Threads per block in Born Force reduction calls
    unsigned int    bsf_reduce_threads_per_block;   // Threads per block in Born Sum And Forces reduction calls
    unsigned int    max_shake_threads_per_block;    // Maximum threads per block in shake kernel calls
    unsigned int    shake_threads_per_block;        // Threads per block in shake kernel calls
    unsigned int    settle_threads_per_block;       // Threads per block in SETTLE kernel calls
    unsigned int    ccma_threads_per_block;         // Threads per block in CCMA kernel calls
    unsigned int    max_localForces_threads_per_block;  // Threads per block in local forces kernel calls
    unsigned int    localForces_threads_per_block;  // Threads per block in local forces kernel calls
    unsigned int    random_threads_per_block;       // Threads per block in RNG kernel calls
    unsigned int    interaction_threads_per_block;  // Threads per block when identifying interacting tiles
    unsigned int    custom_exception_threads_per_block; // Threads per block in custom nonbonded exception kernel calls
    unsigned int    customExpressionStackSize;      // Stack size for evaluating custom nonbonded forces
    unsigned int    workUnits;                      // Number of work units
    unsigned int*   pWorkUnit;                      // Pointer to work units
    unsigned int*   pInteractingWorkUnit;           // Pointer to work units that have interactions
    unsigned int*   pInteractionFlag;               // Flags for which work units have interactions
    float2*         pStepSize;                      // The size of the previous and current time steps
    float*          pLangevinParameters;            // Parameters used for Langevin integration
    float           errorTol;                       // Error tolerance for selecting the step size
    size_t*         pInteractionCount;              // A count of the number of work units which have interactions
    unsigned int    nonbond_workBlock;              // Number of work units running simultaneously per block in CDLJ and Born Force Part 1
    unsigned int    bornForce2_workBlock;           // Number of work units running second half of Born Forces calculation
    unsigned int    workUnitsPerSM;                 // Number of workblocks per SM
    unsigned int    nbWorkUnitsPerBlock;            // Number of work units assigned to each nonbond block
    unsigned int    nbWorkUnitsPerBlockRemainder;   // Remainder of work units to assign across lower numbered nonbond blocks
    unsigned int    bf2WorkUnitsPerBlock;           // Number of work units assigned to each bornForce2 block
    unsigned int    bf2WorkUnitsPerBlockRemainder;  // Remainder of work units to assign across lower numbered bornForce2 blocks


    unsigned int    stride;                         // Atomic attributes stride
    unsigned int    stride2;                        // Atomic attributes stride x 2
    unsigned int    stride3;                        // Atomic attributes stride x 3
    unsigned int    stride4;                        // Atomic attributes stride x 4
    unsigned int    nonbondOutputBuffers;           // Nonbond output buffers per nonbond call
    unsigned int    outputBuffers;                  // Number of output buffers
    unsigned int    energyOutputBuffers;            // Number of energy output buffers
    float           bigFloat;                       // Floating point value used as a flag for Shaken atoms 
    float           epsfac;                         // Epsilon factor for CDLJ calculations
    CudaNonbondedMethod nonbondedMethod;            // How to handle nonbonded interactions
    CudaNonbondedMethod customNonbondedMethod;      // How to handle custom nonbonded interactions
    float           nonbondedCutoff;                // Cutoff distance for nonbonded interactions
    float           nonbondedCutoffSqr;             // Square of the cutoff distance for nonbonded interactions
    float           periodicBoxSizeX;               // The X dimension of the periodic box
    float           periodicBoxSizeY;               // The Y dimension of the periodic box
    float           periodicBoxSizeZ;               // The Z dimension of the periodic box
    float           invPeriodicBoxSizeX;            // The 1 over the X dimension of the periodic box
    float           invPeriodicBoxSizeY;            // The 1 over the Y dimension of the periodic box
    float           invPeriodicBoxSizeZ;            // The 1 over the Z dimension of the periodic box
    float           recipBoxSizeX;                  // The X dimension of the reciprocal box for Ewald summation
    float           recipBoxSizeY;                  // The Y dimension of the reciprocal box for Ewald summation
    float           recipBoxSizeZ;                  // The Z dimension of the reciprocal box for Ewald summation
    float           cellVolume;                     // Ewald parameter alpha (a.k.a. kappa)
    float           alphaEwald;                     // Ewald parameter alpha (a.k.a. kappa)
    float           factorEwald;                    // - 1 ( 4 * alphaEwald * alphaEwald)
    int             kmaxX;                          // Maximum number of reciprocal vectors in the X direction
    int             kmaxY;                          // Maximum number of reciprocal vectors in the Y direction
    int             kmaxZ;                          // Maximum number of reciprocal vectors in the Z direction
    float           reactionFieldK;                 // Constant for reaction field correction
    float           reactionFieldC;                 // Constant for reaction field correction
    float           probeRadius;                    // SASA probe radius
    float           surfaceAreaFactor;              // ACE approximation surface area factor
    float           electricConstant;               // ACE approximation electric constant
    float           forceConversionFactor;          // kJ to kcal force conversion factor
    float           preFactor;                      // Born electrostatic pre-factor
    float           dielectricOffset;               // Born dielectric offset
    float           alphaOBC;                       // OBC alpha factor
    float           betaOBC;                        // OBC beta factor
    float           gammaOBC;                       // OBC gamma factor
    float           deltaT;                         // Molecular dynamics deltaT constant
    float           oneOverDeltaT;                  // 1/deltaT
    float           T;                              // Temperature
    float           kT;                             // Boltzmann's constant times T
    float           noiseAmplitude;                 // The magnitude of the noise for Brownian dynamics
    float           tau;                            // Inverse friction for Langevin or Brownian dynamics
    float           tauDeltaT;                      // tau*deltaT
    float           collisionFrequency;             // Collision frequency for Andersen thermostat
    float2*         pObcData;                       // Pointer to fixed Born data
    int             gbviBornRadiusScalingMethod;    // scaling method for GB/VI Born radii
    float           gbviQuinticLowerLimitFactor;    // Lower limit factor for scaing of GB/VI Born radii using quintic spline
    float           gbviQuinticUpperBornRadiusLimit;// Upper limit for GB/VI Born radii 
    float4*         pGBVIData;                      // Pointer to fixed Born data for GB/VI algorithm
    float*          pGBVISwitchDerivative;          // Pointer to GB/VI Born switch derivatives
    float2*         pAttr;                          // Pointer to additional atom attributes (sig, eps)
    float4*         pCustomParams;                  // Pointer to atom parameters for custom nonbonded force
    unsigned int    customExceptions;               // Number of custom nonbonded exceptions
    unsigned int    customParameters;               // Number of parameters for custom nonbonded interactions
    int4*           pCustomBondID;                  // Atom indices for custom bonds
    float4*         pCustomBondParams;              // Parameters for custom bonds
    unsigned int    customBonds;                    // Number of custom bonds
    unsigned int    customBondParameters;           // Number of parameters for custom bonds
    int4*           pCustomAngleID1;                // Atom indices for custom angles
    int2*           pCustomAngleID2;                // Atom indices for custom angles
    float4*         pCustomAngleParams;             // Parameters for custom angles
    unsigned int    customAngles;                   // Number of custom angles
    unsigned int    customAngleParameters;          // Number of parameters for custom angles
    int4*           pCustomTorsionID1;              // Atom indices for custom torsions
    int4*           pCustomTorsionID2;              // Atom indices for custom torsions
    float4*         pCustomTorsionParams;           // Parameters for custom torsions
    unsigned int    customTorsions;                 // Number of custom torsions
    unsigned int    customTorsionParameters;        // Number of parameters for custom torsions
    int*            pCustomExternalID;              // Atom indices for custom external force
    float4*         pCustomExternalParams;          // Parameters for custom external force
    unsigned int    customExternals;                // Number of particles for custom external force
    unsigned int    customExternalParameters;       // Number of parameters for custom external force
    float4*         pTabulatedFunctionCoefficients[MAX_TABULATED_FUNCTIONS]; // The spline coefficients for each tabulated function
    float4*         pTabulatedFunctionParams;       // The min, max, and spacing for each tabulated function
    float2*         pEwaldCosSinSum;                // Pointer to the cos/sin sums (ewald)
    float*          pTabulatedErfc;                 // Tabulated values for erfc()
    int             tabulatedErfcSize;              // The number of tabulated values for erfc()
    float           tabulatedErfcScale;             // Scale factor for the argument to erfc()
    int3            pmeGridSize;                    // The dimensions of the grid for particle mesh Ewald
    int3            pmeGroupSize;                   // The dimensions of the groups used in charge spreading for PME
    cufftComplex*   pPmeGrid;                       // Grid points for particle mesh Ewald
    float*          pPmeBsplineModuli[3];
    float4*         pPmeBsplineTheta;
    float4*         pPmeBsplineDtheta;
    int*            pPmeAtomRange;                  // The range of sorted atoms at each grid point
    int2*           pPmeAtomGridIndex;              // The grid point each atom is at
    unsigned int    bonds;                          // Number of bonds
    int4*           pBondID;                        // Bond atom and output buffer IDs
    float2*         pBondParameter;                 // Bond parameters
    unsigned int    bond_angles;                    // Number of bond angles
    int4*           pBondAngleID1;                  // Bond angle atom and first output buffer IDs
    int2*           pBondAngleID2;                  // Bond angle output buffer IDs
    float2*         pBondAngleParameter;            // Bond angle parameters
    unsigned int    dihedrals;                      // Number of dihedrals
    int4*           pDihedralID1;                   // Dihedral IDs
    int4*           pDihedralID2;                   // Dihedral output buffer IDs
    float4*         pDihedralParameter;             // Dihedral parameters
    unsigned int    rb_dihedrals;                   // Number of Ryckaert Bellemans dihedrals
    int4*           pRbDihedralID1;                 // Ryckaert Bellemans Dihedral IDs
    int4*           pRbDihedralID2;                 // Ryckaert Bellemans Dihedral output buffer IDs
    float4*         pRbDihedralParameter1;          // Ryckaert Bellemans Dihedral parameters
    float2*         pRbDihedralParameter2;          // Ryckaert Bellemans Dihedral parameters
    unsigned int    LJ14s;                          // Number of Lennard Jones 1-4 interactions
    int4*           pLJ14ID;                        // Lennard Jones 1-4 atom and output buffer IDs
    float4*         pLJ14Parameter;                 // Lennard Jones 1-4 parameters
    float           inverseTotalMass;               // Used in linear momentum removal
    unsigned int    ShakeConstraints;               // Total number of Shake constraints
    unsigned int    settleConstraints;              // Total number of Settle constraints
    unsigned int    ccmaConstraints;                // Total number of CCMA constraints.
    unsigned int    rigidClusters;                  // Total number of rigid clusters
    unsigned int    maxRigidClusterSize;            // The size of the largest rigid cluster
    unsigned int    clusterShakeBlockSize;          // The number of threads to process each rigid cluster
    unsigned int    maxShakeIterations;             // Maximum shake iterations
    unsigned int    degreesOfFreedom;               // Number of degrees of freedom in system
    float           shakeTolerance;                 // Shake tolerance
    float           InvMassJ;                       // Shake inverse mass for hydrogens
    int*            pNonShakeID;                    // Not Shaking atoms
    int4*           pShakeID;                       // Shake atoms and phase
    float4*         pShakeParameter;                // Shake parameters
    int4*           pSettleID;                      // Settle atoms
    float2*         pSettleParameter;               // Settle parameters
    unsigned int*   pExclusion;                     // Nonbond exclusion data
    unsigned int*   pExclusionIndex;                // Index of exclusion data for each work unit
    unsigned int    bond_offset;                    // Offset to end of bonds
    unsigned int    bond_angle_offset;              // Offset to end of bond angles
    unsigned int    dihedral_offset;                // Offset to end of dihedrals
    unsigned int    rb_dihedral_offset;             // Offset to end of Ryckaert Bellemans dihedrals
    unsigned int    LJ14_offset;                    // Offset to end of Lennard Jones 1-4 parameters
    int*            pAtomIndex;                     // The original index of each atom
    float4*         pGridBoundingBox;               // The size of each grid cell
    float4*         pGridCenter;                    // The center of each grid cell
    int2*           pCcmaAtoms;                     // The atoms connected by each CCMA constraint
    float4*         pCcmaDistance;                  // The displacement vector (x, y, z) and constraint distance (w) for each CCMA constraint
    float*          pCcmaDelta1;                    // Workspace for CCMA
    float*          pCcmaDelta2;                    // Workspace for CCMA
    int*            pCcmaAtomConstraints;           // The indices of constraints involving each atom
    int*            pCcmaNumAtomConstraints;        // The number of constraints involving each atom
    int*            ccmaConvergedDeviceMarker;      // Device memory used to communicate that CCMA has converged
    float*          pCcmaReducedMass;               // The reduced mass for each CCMA constraint
    unsigned int*   pConstraintMatrixColumn;        // The column of each element in the constraint matrix.
    float*          pConstraintMatrixValue;         // The value of each element in the constraint matrix.

    // Mutable stuff
    float4*         pPosq;                          // Pointer to atom positions and charges
    float4*         pPosqP;                         // Pointer to mid-integration atom positions
    float4*         pOldPosq;                       // Pointer to old atom positions
    float4*         pVelm4;                         // Pointer to atom velocity and inverse mass
    float4*         pForce4;                        // Pointer to force data
    float*          pEnergy;                        // Pointer to energy output buffer
    float*          pBornForce;                     // Pointer to Born force data
    float*	    pBornSum;                       // Pointer to Born Radii calculation output buffers
    float*	    pBornRadii;                     // Pointer to Born Radii
    float*          pObcChain;                      // Pointer to OBC chain data
    float4*         pLinearMomentum;                // Pointer to linear momentum
    
    // Random numbers
    float4*         pRandom4;                       // Pointer to 4 random numbers
    float2*         pRandom2;                       // Pointer to 2 random numbers
    uint4*          pRandomSeed;                    // Pointer to random seeds
    int*            pRandomPosition;                // Pointer to random number positions
    unsigned int    randoms;                        // Number of randoms
    unsigned int    totalRandoms;                   // Number of randoms plus overflow.
    unsigned int    randomIterations;               // Number of iterations before regenerating randoms
    unsigned int    randomFrames;                   // Number of frames of random numbers
};

struct Vectors {
    float3 v0;
    float3 v1;
    float3 v2;
};

#endif
