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
#include "cudaKernels.h"
#include "amoebaCudaKernels.h"
#include "kCalculateAmoebaCudaUtilities.h"

static __constant__ cudaGmxSimulation cSim;
static __constant__ cudaAmoebaGmxSimulation cAmoebaSim;

void SetCalculateAmoebaPmeDirectElectrostaticSim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status         = cudaMemcpyToSymbol(cSim, &gpu->sim, sizeof(cudaGmxSimulation));
    RTERROR(status, "SetCalculateAmoebaPmeDirectElectrostaticSim: cudaMemcpyToSymbol: SetSim copy to cSim failed");
    status         = cudaMemcpyToSymbol(cAmoebaSim, &amoebaGpu->amoebaSim, sizeof(cudaAmoebaGmxSimulation));
    RTERROR(status, "SetCalculateAmoebaPmeDirectElectrostaticSim: cudaMemcpyToSymbol: SetSim copy to cAmoebaSim failed");
}

void GetCalculateAmoebaPmeDirectElectrostaticSim(amoebaGpuContext amoebaGpu)
{
    cudaError_t status;
    gpuContext gpu = amoebaGpu->gpuContext;
    status = cudaMemcpyFromSymbol(&gpu->sim, cSim, sizeof(cudaGmxSimulation));
    RTERROR(status, "GetCalculateAmoebaPmeDirectElectrostaticSim: cudaMemcpyFromSymbol: SetSim copy from cSim failed");
    status = cudaMemcpyFromSymbol(&amoebaGpu->amoebaSim, cAmoebaSim, sizeof(cudaAmoebaGmxSimulation));
    RTERROR(status, "GetCalculateAmoebaPmeDirectElectrostaticSim: cudaMemcpyFromSymbol: SetSim copy from cAmoebaSim failed");
}

static int const PScaleIndex            =  0;
static int const DScaleIndex            =  1;
static int const UScaleIndex            =  2;
static int const MScaleIndex            =  3;
static int const LastScalingIndex       =  4;

#define CALCULATE_FULL_TILE

struct PmeDirectElectrostaticParticle {

    // coordinates charge

    float x;
    float y;
    float z;
    float q;

    // lab frame dipole

    float labFrameDipole[3];

    // lab frame quadrupole
    float labFrameQuadrupole[5];

    // induced dipole

    float inducedDipole[3];
    float inducedDipoleP[3];

    // scaling factors

    float thole;
    float damp;

    float force[3];
    float torque[3];
    float padding;

#ifndef CALCULATE_FULL_TILE
    float tempForce[3];
    float tempTorque[3];
#endif
};

#ifndef CALCULATE_FULL_TILE
__device__ void sumTempBuffer( PmeDirectElectrostaticParticle& atomI, PmeDirectElectrostaticParticle& atomJ ){

    atomI.tempForce[0]  += atomJ.tempForce[0];
    atomI.tempForce[1]  += atomJ.tempForce[1];
    atomI.tempForce[2]  += atomJ.tempForce[2];

    atomI.tempTorque[0] += atomJ.tempTorque[0];
    atomI.tempTorque[1] += atomJ.tempTorque[1];
    atomI.tempTorque[2] += atomJ.tempTorque[2];
}
#endif

/*
__device__ static void debugSetup( unsigned int atomI, unsigned int atomJ,
                                   float4* debugArray, float4* pullBack )
{
    unsigned int index                 = atomI + atomJ*cSim.paddedNumberOfAtoms;
    float blockId                      = 111.0f;

    debugArray[index].x                = (float) atomI;
    debugArray[index].y                = (float) atomJ;
    debugArray[index].z                = 0.0f;
    debugArray[index].w                = blockId;

    for( int pullIndex = 0; pullIndex < 1; pullIndex++ ){
        index                             += cSim.paddedNumberOfAtoms;
        debugArray[index].x                = pullBack[pullIndex].x;
        debugArray[index].y                = pullBack[pullIndex].y;
        debugArray[index].z                = pullBack[pullIndex].z;
        debugArray[index].w                = pullBack[pullIndex].w;
    }
}
*/

// self-energy for PME

__device__ static void calculatePmeSelfEnergyElectrostaticPairIxn_kernel( PmeDirectElectrostaticParticle& atomI, float* totalEnergy)
{
    float term      = 2.0f*cSim.alphaEwald*cSim.alphaEwald;
    float fterm     = -cSim.alphaEwald/cAmoebaSim.sqrtPi;

    float cii       = atomI.q*atomI.q;

    float dii       = atomI.labFrameDipole[0]*atomI.labFrameDipole[0] +
                      atomI.labFrameDipole[1]*atomI.labFrameDipole[1] +
                      atomI.labFrameDipole[2]*atomI.labFrameDipole[2];
/*
    float qii       = atomI.labFrameQuadrupole[0]*atomI.labFrameQuadrupole[0] +
                      atomI.labFrameQuadrupole[3]*atomI.labFrameQuadrupole[3] +
                      atomI.labFrameQuadrupole[5]*atomI.labFrameQuadrupole[5] + 2.0f*(
                      atomI.labFrameQuadrupole[1]*atomI.labFrameQuadrupole[1] +
                      atomI.labFrameQuadrupole[2]*atomI.labFrameQuadrupole[2] +
                      atomI.labFrameQuadrupole[4]*atomI.labFrameQuadrupole[4]);
*/

    float qii       = atomI.labFrameQuadrupole[0]*atomI.labFrameQuadrupole[0] +
                      atomI.labFrameQuadrupole[3]*atomI.labFrameQuadrupole[3] +
                      atomI.labFrameQuadrupole[0]*atomI.labFrameQuadrupole[3] +
                      atomI.labFrameQuadrupole[1]*atomI.labFrameQuadrupole[1] +
                      atomI.labFrameQuadrupole[2]*atomI.labFrameQuadrupole[2] +
                      atomI.labFrameQuadrupole[4]*atomI.labFrameQuadrupole[4];

    qii            *= 2.0f;

    float uii       = atomI.labFrameDipole[0]*atomI.inducedDipole[0] + atomI.labFrameDipole[1]*atomI.inducedDipole[1] + atomI.labFrameDipole[2]*atomI.inducedDipole[2];

    float energy    = (cii + term*(dii/3.0f + 2.0f*term*qii/5.0f));
     energy        += term*uii/3.0f;
     energy        *= fterm;
    *totalEnergy   += energy;
}

// self-torque for PME

__device__ static void calculatePmeSelfTorqueElectrostaticPairIxn_kernel( PmeDirectElectrostaticParticle& atomI )
{
    float term       = (2.0f/3.0f)*(cSim.alphaEwald*cSim.alphaEwald*cSim.alphaEwald)/cAmoebaSim.sqrtPi;

    float uix         = (atomI.inducedDipole[0] + atomI.inducedDipoleP[0]);
    float uiy         = (atomI.inducedDipole[1] + atomI.inducedDipoleP[1]);
    float uiz         = (atomI.inducedDipole[2] + atomI.inducedDipoleP[2]);

    atomI.torque[0]  += term*(atomI.labFrameDipole[1]*uiz - atomI.labFrameDipole[2]*uiy);
    atomI.torque[1]  += term*(atomI.labFrameDipole[2]*uix - atomI.labFrameDipole[0]*uiz);
    atomI.torque[2]  += term*(atomI.labFrameDipole[0]*uiy - atomI.labFrameDipole[1]*uix);
}

__device__ void calculateBn_kernel( float r, float4* bn, float* bn0, float *bn5 ){

    float ralpha                = cSim.alphaEwald*r;
    float alsq2                 = 2.0f*cSim.alphaEwald*cSim.alphaEwald;
    float alsq2n                = 0.0f;
    if( cSim.alphaEwald > 0.0f ){
        alsq2n                  = 1.0f/(cAmoebaSim.sqrtPi*cSim.alphaEwald);
    }   
    float exp2a                 = expf(-(ralpha*ralpha));

    float rr1                   = 1.0f/r;
    *bn0                        = erfcf(ralpha)*rr1;
    float rr2                   = rr1*rr1;
    alsq2n                     *= alsq2;

    bn->x                       = (*bn0+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn->y                       = (3.0f*bn->x+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn->z                       = (5.0f*bn->y+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn->w                       = (7.0f*bn->z+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    *bn5                        = (9.0f*bn->w+alsq2n*exp2a)*rr2;

}

#define SUB_METHOD_NAME(a, b) a##Scale##b
#define APPLY_SCALE
#include "kCalculateAmoebaCudaPmeDirectElectrostaticF1.h"
#include "kCalculateAmoebaCudaPmeDirectElectrostaticF2P.h"
#include "kCalculateAmoebaCudaPmeDirectElectrostaticT1.h"
#include "kCalculateAmoebaCudaPmeDirectElectrostaticT2.h"
//#include "kCalculateAmoebaCudaPmeDirectElectrostaticDriver.h"
#undef APPLY_SCALE
#undef SUB_METHOD_NAME
#define SUB_METHOD_NAME(a, b) a##NoScale##b
#include "kCalculateAmoebaCudaPmeDirectElectrostaticF1.h"
#include "kCalculateAmoebaCudaPmeDirectElectrostaticF2P.h"
//#include "kCalculateAmoebaCudaPmeDirectElectrostaticT1.h"
//#include "kCalculateAmoebaCudaPmeDirectElectrostaticT2.h"
//#include "kCalculateAmoebaCudaPmeDirectElectrostaticDriver.h"
#undef SUB_METHOD_NAME

__device__ void calculatePmeDirectElectrostaticPairIxnOrig_kernel( const PmeDirectElectrostaticParticle& atomI, const   PmeDirectElectrostaticParticle& atomJ,
                                                                   const float* scalingFactors, float4 forceTorqueEnergy[3]){

    float xr    = atomJ.x - atomI.x;
    float yr    = atomJ.y - atomI.y;
    float zr    = atomJ.z - atomI.z;

    // periodic box

    xr         -= floorf(xr*cSim.invPeriodicBoxSizeX+0.5f)*cSim.periodicBoxSizeX;
    yr         -= floorf(yr*cSim.invPeriodicBoxSizeY+0.5f)*cSim.periodicBoxSizeY;
    zr         -= floorf(zr*cSim.invPeriodicBoxSizeZ+0.5f)*cSim.periodicBoxSizeZ;

    float r2    = xr*xr + yr*yr + zr*zr;
    if( r2 <= cSim.nonbondedCutoffSqr ){

        float r      = sqrtf(r2);
        float ck     = atomJ.q;

        // set the permanent multipole and induced dipole values;

        float ci    = atomI.q;

        float di1   = atomI.labFrameDipole[0];
        float di2   = atomI.labFrameDipole[1];
        float di3   = atomI.labFrameDipole[2];

        float qi1   = atomI.labFrameQuadrupole[0];
        float qi2   = atomI.labFrameQuadrupole[1];
        float qi3   = atomI.labFrameQuadrupole[2];
        float qi5   = atomI.labFrameQuadrupole[3];
        float qi6   = atomI.labFrameQuadrupole[4];
        //float qi9   = atomI.labFrameQuadrupole[5];
        float qi9   = -(atomI.labFrameQuadrupole[0] + atomI.labFrameQuadrupole[3]);

        float dk1  = atomJ.labFrameDipole[0];
        float dk2  = atomJ.labFrameDipole[1];
        float dk3  = atomJ.labFrameDipole[2];

        float qk1  = atomJ.labFrameQuadrupole[0];
        float qk2  = atomJ.labFrameQuadrupole[1];
        float qk3  = atomJ.labFrameQuadrupole[2];
        float qk5  = atomJ.labFrameQuadrupole[3];
        float qk6  = atomJ.labFrameQuadrupole[4];
        //float qk9  = atomJ.labFrameQuadrupole[5];
        float qk9   = -(atomI.labFrameQuadrupole[0] + atomJ.labFrameQuadrupole[3]);

        // calculate the real space error function terms

        float ralpha = cSim.alphaEwald*r;
        float bn0    = erfcf(ralpha)/r;

        float alsq2  = 2.0f*cSim.alphaEwald*cSim.alphaEwald;
        float alsq2n = 0.0f;
        if( cSim.alphaEwald > 0.0f ){
            alsq2n = 1.0f/(cAmoebaSim.sqrtPi*cSim.alphaEwald);
        }
        float exp2a  = expf(-(ralpha*ralpha));

        alsq2n      *= alsq2;
        float bn1    = (bn0+alsq2n*exp2a)/r2;

        alsq2n      *= alsq2;
        float bn2    = (3.0f*bn1+alsq2n*exp2a)/r2;

        alsq2n      *= alsq2;
        float bn3    = (5.0f*bn2+alsq2n*exp2a)/r2;

        alsq2n      *= alsq2;
        float bn4    = (7.0f*bn3+alsq2n*exp2a)/r2;

        alsq2n      *= alsq2;
        float bn5    = (9.0f*bn4+alsq2n*exp2a)/r2;

        // apply Thole polarization damping to scale factors

        float rr1    = 1.0f/r;
        float rr3    = rr1 / r2;
        float rr5    = 3.0f * rr3 / r2;
        float rr7    = 5.0f * rr5 / r2;
        float rr9    = 7.0f * rr7 / r2;
        float rr11   = 9.0f * rr9 / r2;
        float scale3 = 1.0f;
        float scale5 = 1.0f;
        float scale7 = 1.0f;

        float ddsc31 = 0.0f;
        float ddsc32 = 0.0f;
        float ddsc33 = 0.0f;

        float ddsc51 = 0.0f;
        float ddsc52 = 0.0f;
        float ddsc53 = 0.0f;

        float ddsc71 = 0.0f;
        float ddsc72 = 0.0f;
        float ddsc73 = 0.0f;

        float damp   = atomI.damp*atomJ.damp;
        if( damp != 0.0f ){
            float pgamma = atomI.thole < atomJ.thole ? atomI.thole : atomJ.thole;
            float ratio  = r/damp;
                damp     = -pgamma*ratio*ratio*ratio;
            if( damp > -50.0f ){
                float expdamp  = expf(damp);
                scale3         = 1.0f - expdamp;
                   scale5      = 1.0f - (1.0f-damp)*expdamp;
                   scale7      = 1.0f - (1.0f-damp+0.6f*damp*damp)*expdamp;
                float temp3    = -3.0f * damp * expdamp / r2;
                float temp5    = -damp;
                float temp7    = -0.2f - 0.6f*damp;

                ddsc31         = temp3 * xr;
                ddsc32         = temp3 * yr;
                ddsc33         = temp3 * zr;

                ddsc51         = temp5 * ddsc31;
                ddsc52         = temp5 * ddsc32;
                ddsc53         = temp5 * ddsc33;

                ddsc71         = temp7 * ddsc51;
                ddsc72         = temp7 * ddsc52;
                ddsc73         = temp7 * ddsc53;
            }
        }

        float dsc3 = 1.0f - scale3*scalingFactors[DScaleIndex];
        float dsc5 = 1.0f - scale5*scalingFactors[DScaleIndex];
        float dsc7 = 1.0f - scale7*scalingFactors[DScaleIndex];

        float psc3 = 1.0f - scale3*scalingFactors[PScaleIndex];
        float psc5 = 1.0f - scale5*scalingFactors[PScaleIndex];
        float psc7 = 1.0f - scale7*scalingFactors[PScaleIndex];

        float usc3 = 1.0f - scale3*scalingFactors[UScaleIndex];
        float usc5 = 1.0f - scale5*scalingFactors[UScaleIndex];

        // construct necessary auxiliary vectors

        float dixdk1       = di2*dk3 - di3*dk2;
        float dixdk2       = di3*dk1 - di1*dk3;
        float dixdk3       = di1*dk2 - di2*dk1;

        float dixuk1       = di2*atomJ.inducedDipole[2]  - di3*atomJ.inducedDipole[1];
        float dixuk2       = di3*atomJ.inducedDipole[0]  - di1*atomJ.inducedDipole[2];
        float dixuk3       = di1*atomJ.inducedDipole[1]  - di2*atomJ.inducedDipole[0];
        float dkxui1       = dk2*atomI.inducedDipole[2]  - dk3*atomI.inducedDipole[1];
        float dkxui2       = dk3*atomI.inducedDipole[0]  - dk1*atomI.inducedDipole[2];
        float dkxui3       = dk1*atomI.inducedDipole[1]  - dk2*atomI.inducedDipole[0];

        float dixukp1      = di2*atomJ.inducedDipoleP[2] - di3*atomJ.inducedDipoleP[1];
        float dixukp2      = di3*atomJ.inducedDipoleP[0] - di1*atomJ.inducedDipoleP[2];
        float dixukp3      = di1*atomJ.inducedDipoleP[1] - di2*atomJ.inducedDipoleP[0];
        float dkxuip1      = dk2*atomI.inducedDipoleP[2] - dk3*atomI.inducedDipoleP[1];
        float dkxuip2      = dk3*atomI.inducedDipoleP[0] - dk1*atomI.inducedDipoleP[2];
        float dkxuip3      = dk1*atomI.inducedDipoleP[1] - dk2*atomI.inducedDipoleP[0];

        float dixr1        = di2*zr - di3*yr;
        float dixr2        = di3*xr - di1*zr;
        float dixr3        = di1*yr - di2*xr;

        float dkxr1        = dk2*zr - dk3*yr;
        float dkxr2        = dk3*xr - dk1*zr;
        float dkxr3        = dk1*yr - dk2*xr;

        float qir1         = qi1*xr + qi2*yr + qi3*zr;
        float qir2         = qi2*xr + qi5*yr + qi6*zr;
        float qir3         = qi3*xr + qi6*yr + qi9*zr;

        float qkr1         = qk1*xr + qk2*yr + qk3*zr;
        float qkr2         = qk2*xr + qk5*yr + qk6*zr;
        float qkr3         = qk3*xr + qk6*yr + qk9*zr;

        float qiqkr1       = qi1*qkr1 + qi2*qkr2 + qi3*qkr3;
        float qiqkr2       = qi2*qkr1 + qi5*qkr2 + qi6*qkr3;
        float qiqkr3       = qi3*qkr1 + qi6*qkr2 + qi9*qkr3;

        float qkqir1       = qk1*qir1 + qk2*qir2 + qk3*qir3;
        float qkqir2       = qk2*qir1 + qk5*qir2 + qk6*qir3;
        float qkqir3       = qk3*qir1 + qk6*qir2 + qk9*qir3;

        float qixqk1       = qi2*qk3 + qi5*qk6 + qi6*qk9 - qi3*qk2 - qi6*qk5 - qi9*qk6;
        float qixqk2       = qi3*qk1 + qi6*qk2 + qi9*qk3 - qi1*qk3 - qi2*qk6 - qi3*qk9;
        float qixqk3       = qi1*qk2 + qi2*qk5 + qi3*qk6 - qi2*qk1 - qi5*qk2 - qi6*qk3;

        float rxqir1       = yr*qir3 - zr*qir2;
        float rxqir2       = zr*qir1 - xr*qir3;
        float rxqir3       = xr*qir2 - yr*qir1;

        float rxqkr1       = yr*qkr3 - zr*qkr2;
        float rxqkr2       = zr*qkr1 - xr*qkr3;
        float rxqkr3       = xr*qkr2 - yr*qkr1;

        float rxqikr1      = yr*qiqkr3 - zr*qiqkr2;
        float rxqikr2      = zr*qiqkr1 - xr*qiqkr3;
        float rxqikr3      = xr*qiqkr2 - yr*qiqkr1;

        float rxqkir1      = yr*qkqir3 - zr*qkqir2;
        float rxqkir2      = zr*qkqir1 - xr*qkqir3;
        float rxqkir3      = xr*qkqir2 - yr*qkqir1;

        float qkrxqir1     = qkr2*qir3 - qkr3*qir2;
        float qkrxqir2     = qkr3*qir1 - qkr1*qir3;
        float qkrxqir3     = qkr1*qir2 - qkr2*qir1;

        float qidk1        = qi1*dk1 + qi2*dk2 + qi3*dk3;
        float qidk2        = qi2*dk1 + qi5*dk2 + qi6*dk3;
        float qidk3        = qi3*dk1 + qi6*dk2 + qi9*dk3;

        float qkdi1        = qk1*di1 + qk2*di2 + qk3*di3;
        float qkdi2        = qk2*di1 + qk5*di2 + qk6*di3;
        float qkdi3        = qk3*di1 + qk6*di2 + qk9*di3;

        float qiuk1        = qi1*atomJ.inducedDipole[0]  + qi2*atomJ.inducedDipole[1]  + qi3*atomJ.inducedDipole[2];
        float qiuk2        = qi2*atomJ.inducedDipole[0]  + qi5*atomJ.inducedDipole[1]  + qi6*atomJ.inducedDipole[2];
        float qiuk3        = qi3*atomJ.inducedDipole[0]  + qi6*atomJ.inducedDipole[1]  + qi9*atomJ.inducedDipole[2];

        float qkui1        = qk1*atomI.inducedDipole[0]  + qk2*atomI.inducedDipole[1]  + qk3*atomI.inducedDipole[2];
        float qkui2        = qk2*atomI.inducedDipole[0]  + qk5*atomI.inducedDipole[1]  + qk6*atomI.inducedDipole[2];
        float qkui3        = qk3*atomI.inducedDipole[0]  + qk6*atomI.inducedDipole[1]  + qk9*atomI.inducedDipole[2];

        float qiukp1       = qi1*atomJ.inducedDipoleP[0] + qi2*atomJ.inducedDipoleP[1] + qi3*atomJ.inducedDipoleP[2];
        float qiukp2       = qi2*atomJ.inducedDipoleP[0] + qi5*atomJ.inducedDipoleP[1] + qi6*atomJ.inducedDipoleP[2];
        float qiukp3       = qi3*atomJ.inducedDipoleP[0] + qi6*atomJ.inducedDipoleP[1] + qi9*atomJ.inducedDipoleP[2];

        float qkuip1       = qk1*atomI.inducedDipoleP[0] + qk2*atomI.inducedDipoleP[1] + qk3*atomI.inducedDipoleP[2];
        float qkuip2       = qk2*atomI.inducedDipoleP[0] + qk5*atomI.inducedDipoleP[1] + qk6*atomI.inducedDipoleP[2];
        float qkuip3       = qk3*atomI.inducedDipoleP[0] + qk6*atomI.inducedDipoleP[1] + qk9*atomI.inducedDipoleP[2];

        float dixqkr1      = di2*qkr3 - di3*qkr2;
        float dixqkr2      = di3*qkr1 - di1*qkr3;
        float dixqkr3      = di1*qkr2 - di2*qkr1;

        float dkxqir1      = dk2*qir3 - dk3*qir2;
        float dkxqir2      = dk3*qir1 - dk1*qir3;
        float dkxqir3      = dk1*qir2 - dk2*qir1;

        float uixqkr1      = atomI.inducedDipole[1]*qkr3 - atomI.inducedDipole[2]*qkr2;
        float uixqkr2      = atomI.inducedDipole[2]*qkr1 - atomI.inducedDipole[0]*qkr3;
        float uixqkr3      = atomI.inducedDipole[0]*qkr2 - atomI.inducedDipole[1]*qkr1;

        float ukxqir1      = atomJ.inducedDipole[1]*qir3 - atomJ.inducedDipole[2]*qir2;
        float ukxqir2      = atomJ.inducedDipole[2]*qir1 - atomJ.inducedDipole[0]*qir3;
        float ukxqir3      = atomJ.inducedDipole[0]*qir2 - atomJ.inducedDipole[1]*qir1;

        float uixqkrp1     = atomI.inducedDipoleP[1]*qkr3 - atomI.inducedDipoleP[2]*qkr2;
        float uixqkrp2     = atomI.inducedDipoleP[2]*qkr1 - atomI.inducedDipoleP[0]*qkr3;
        float uixqkrp3     = atomI.inducedDipoleP[0]*qkr2 - atomI.inducedDipoleP[1]*qkr1;

        float ukxqirp1     = atomJ.inducedDipoleP[1]*qir3 - atomJ.inducedDipoleP[2]*qir2;
        float ukxqirp2     = atomJ.inducedDipoleP[2]*qir1 - atomJ.inducedDipoleP[0]*qir3;
        float ukxqirp3     = atomJ.inducedDipoleP[0]*qir2 - atomJ.inducedDipoleP[1]*qir1;

        float rxqidk1      = yr*qidk3 - zr*qidk2;
        float rxqidk2      = zr*qidk1 - xr*qidk3;
        float rxqidk3      = xr*qidk2 - yr*qidk1;

        float rxqkdi1      = yr*qkdi3 - zr*qkdi2;
        float rxqkdi2      = zr*qkdi1 - xr*qkdi3;
        float rxqkdi3      = xr*qkdi2 - yr*qkdi1;

        float rxqiuk1      = yr*qiuk3 - zr*qiuk2;
        float rxqiuk2      = zr*qiuk1 - xr*qiuk3;
        float rxqiuk3      = xr*qiuk2 - yr*qiuk1;

        float rxqkui1      = yr*qkui3 - zr*qkui2;
        float rxqkui2      = zr*qkui1 - xr*qkui3;
        float rxqkui3      = xr*qkui2 - yr*qkui1;

        float rxqiukp1     = yr*qiukp3 - zr*qiukp2;
        float rxqiukp2     = zr*qiukp1 - xr*qiukp3;
        float rxqiukp3     = xr*qiukp2 - yr*qiukp1;

        float rxqkuip1     = yr*qkuip3 - zr*qkuip2;
        float rxqkuip2     = zr*qkuip1 - xr*qkuip3;
        float rxqkuip3     = xr*qkuip2 - yr*qkuip1;

        // calculate the scalar products for permanent components

        float sc2          = di1*dk1 + di2*dk2 + di3*dk3;
        float sc3          = di1*xr + di2*yr + di3*zr;
        float sc4          = dk1*xr + dk2*yr + dk3*zr;
        float sc5          = qir1*xr + qir2*yr + qir3*zr;
        float sc6          = qkr1*xr + qkr2*yr + qkr3*zr;
        float sc7          = qir1*dk1 + qir2*dk2 + qir3*dk3;
        float sc8          = qkr1*di1 + qkr2*di2 + qkr3*di3;
        float sc9          = qir1*qkr1 + qir2*qkr2 + qir3*qkr3;
        float sc10         = qi1*qk1 + qi2*qk2 + qi3*qk3
                             + qi2*qk2 + qi5*qk5 + qi6*qk6
                             + qi3*qk3 + qi6*qk6 + qi9*qk9;

        // calculate the scalar products for induced components

        float sci1         = atomI.inducedDipole[0]*dk1 + atomI.inducedDipole[1]*dk2
                             + atomI.inducedDipole[2]*dk3 + di1*atomJ.inducedDipole[0]
                             + di2*atomJ.inducedDipole[1] + di3*atomJ.inducedDipole[2];

        float sci3         = atomI.inducedDipole[0]*xr + atomI.inducedDipole[1]*yr + atomI.inducedDipole[2]*zr;
        float sci4         = atomJ.inducedDipole[0]*xr + atomJ.inducedDipole[1]*yr + atomJ.inducedDipole[2]*zr;
        float sci7         = qir1*atomJ.inducedDipole[0] + qir2*atomJ.inducedDipole[1] + qir3*atomJ.inducedDipole[2];
        float sci8         = qkr1*atomI.inducedDipole[0] + qkr2*atomI.inducedDipole[1] + qkr3*atomI.inducedDipole[2];
        float scip1        = atomI.inducedDipoleP[0]*dk1 + atomI.inducedDipoleP[1]*dk2 + atomI.inducedDipoleP[2]*dk3 + di1*atomJ.inducedDipoleP[0] + di2*atomJ.inducedDipoleP[1] + di3*atomJ.inducedDipoleP[2];
        float scip2        = atomI.inducedDipole[0]*atomJ.inducedDipoleP[0]+atomI.inducedDipole[1]*atomJ.inducedDipoleP[1]
                              + atomI.inducedDipole[2]*atomJ.inducedDipoleP[2]+atomI.inducedDipoleP[0]*atomJ.inducedDipole[0]
                              + atomI.inducedDipoleP[1]*atomJ.inducedDipole[1]+atomI.inducedDipoleP[2]*atomJ.inducedDipole[2];

        float scip3        = atomI.inducedDipoleP[0]*xr + atomI.inducedDipoleP[1]*yr + atomI.inducedDipoleP[2]*zr;
        float scip4        = atomJ.inducedDipoleP[0]*xr + atomJ.inducedDipoleP[1]*yr + atomJ.inducedDipoleP[2]*zr;

        float scip7        = qir1*atomJ.inducedDipoleP[0] + qir2*atomJ.inducedDipoleP[1] + qir3*atomJ.inducedDipoleP[2];
        float scip8        = qkr1*atomI.inducedDipoleP[0] + qkr2*atomI.inducedDipoleP[1] + qkr3*atomI.inducedDipoleP[2];

        // calculate the gl functions for permanent components

        float gl0           = ci*ck;
        float gl1           = ck*sc3 - ci*sc4;
        float gl2           = ci*sc6 + ck*sc5 - sc3*sc4;
        float gl3           = sc3*sc6 - sc4*sc5;
        float gl4           = sc5*sc6;
        float gl5           = -4.0f * sc9;
        float gl6           = sc2;
        float gl7           = 2.0f * (sc7-sc8);
        float gl8           = 2.0f * sc10;

        // calculate the gl functions for induced components

        float gli1          = ck*sci3 - ci*sci4;
        float gli2          = -sc3*sci4 - sci3*sc4;
        float gli3          = sci3*sc6 - sci4*sc5;
        float gli6          = sci1;
        float gli7          = 2.0f * (sci7-sci8);
        float glip1         = ck*scip3 - ci*scip4;
        float glip2         = -sc3*scip4 - scip3*sc4;
        float glip3         = scip3*sc6 - scip4*sc5;
        float glip6         = scip1;
        float glip7         = 2.0f * (scip7-scip8);

        // compute the energy contributions for this interaction

        float e             = bn0*gl0 + bn1*(gl1+gl6) + bn2*(gl2+gl7+gl8) + bn3*(gl3+gl5) + bn4*gl4;
        float ei            = 0.5f * (bn1*(gli1+gli6) + bn2*(gli2+gli7) + bn3*gli3); 

        // get the real energy without any screening function

        float erl           = rr1*gl0 + rr3*(gl1+gl6) + rr5*(gl2+gl7+gl8) + rr7*(gl3+gl5) + rr9*gl4;
        float erli          = 0.5f*(rr3*(gli1+gli6)*psc3 + rr5*(gli2+gli7)*psc5 + rr7*gli3*psc7);
        e                   = e - (1.0f-scalingFactors[MScaleIndex])*erl;
        ei                  = ei - erli;

        forceTorqueEnergy[0].w = (e + ei);

        // increment the total intramolecular energy; assumes;
        // intramolecular distances are less than half of cell;
        // length and less than the ewald cutoff;
/*
        if (molcule(ii) .eq. molcule(kk)) {
           eintra = eintra + mscale(kk)*erl*f;
           eintra = eintra + 0.5f*pscale(kk);
&                        * (rr3*(gli1+gli6)*scale3;
&                              + rr5*(gli2+gli7)*scale5;
&                              + rr7*gli3*scale7);
        }
*/

        // intermediate variables for permanent force terms

        float gf1 = bn1*gl0 + bn2*(gl1+gl6)
                     + bn3*(gl2+gl7+gl8)
                     + bn4*(gl3+gl5) + bn5*gl4;
        float gf2 = -ck*bn1 + sc4*bn2 - sc6*bn3;
        float gf3 = ci*bn1 + sc3*bn2 + sc5*bn3;
        float gf4 = 2.0f * bn2;
        float gf5 = 2.0f * (-ck*bn2+sc4*bn3-sc6*bn4);
        float gf6 = 2.0f * (-ci*bn2-sc3*bn3-sc5*bn4);
        float gf7 = 4.0f * bn3;
        float gfr1 = rr3*gl0 + rr5*(gl1+gl6)
                      + rr7*(gl2+gl7+gl8)
                      + rr9*(gl3+gl5) + rr11*gl4;
        float gfr2 = -ck*rr3 + sc4*rr5 - sc6*rr7;
        float gfr3 = ci*rr3 + sc3*rr5 + sc5*rr7;
        float gfr4 = 2.0f * rr5;
        float gfr5 = 2.0f * (-ck*rr5+sc4*rr7-sc6*rr9);
        float gfr6 = 2.0f * (-ci*rr5-sc3*rr7-sc5*rr9);
        float gfr7 = 4.0f * rr7;

        // intermediate variables for induced force terms

        float gfi1 = 0.5f*(bn2*(gli1+glip1+gli6+glip6)
                      + bn2*scip2
                      + bn3*(gli2+glip2+gli7+glip7)
                      - bn3*(sci3*scip4+scip3*sci4)
                      + bn4*(gli3+glip3));
        float gfi2 = -ck*bn1 + sc4*bn2 - sc6*bn3;
        float gfi3 = ci*bn1 + sc3*bn2 + sc5*bn3;
        float gfi4 = 2.0f * bn2;
        float gfi5 = bn3 * (sci4+scip4);
        float gfi6 = -bn3 * (sci3+scip3);
        float gfri1 = 0.5f*(rr5*((gli1+gli6)*psc3
                             + (glip1+glip6)*dsc3
                             + scip2*usc3)
                  + rr7*((gli7+gli2)*psc5
                             + (glip7+glip2)*dsc5
                      - (sci3*scip4+scip3*sci4)*usc5)
                  + rr9*(gli3*psc7+glip3*dsc7));
        float gfri4 = 2.0f * rr5;
        float gfri5 = rr7 * (sci4*psc7+scip4*dsc7);
        float gfri6 = -rr7 * (sci3*psc7+scip3*dsc7);

        // get the permanent force with screening

        float ftm21 = gf1*xr + gf2*di1 + gf3*dk1
                       + gf4*(qkdi1-qidk1) + gf5*qir1
                       + gf6*qkr1 + gf7*(qiqkr1+qkqir1);
        float ftm22 = gf1*yr + gf2*di2 + gf3*dk2
                       + gf4*(qkdi2-qidk2) + gf5*qir2
                       + gf6*qkr2 + gf7*(qiqkr2+qkqir2);
        float ftm23 = gf1*zr + gf2*di3 + gf3*dk3
                       + gf4*(qkdi3-qidk3) + gf5*qir3
                       + gf6*qkr3 + gf7*(qiqkr3+qkqir3);

        // get the permanent force without screening

        float ftm2r1 = gfr1*xr + gfr2*di1 + gfr3*dk1
                       + gfr4*(qkdi1-qidk1) + gfr5*qir1
                       + gfr6*qkr1 + gfr7*(qiqkr1+qkqir1);
        float ftm2r2 = gfr1*yr + gfr2*di2 + gfr3*dk2
                       + gfr4*(qkdi2-qidk2) + gfr5*qir2
                       + gfr6*qkr2 + gfr7*(qiqkr2+qkqir2);
        float ftm2r3 = gfr1*zr + gfr2*di3 + gfr3*dk3
                       + gfr4*(qkdi3-qidk3) + gfr5*qir3
                       + gfr6*qkr3 + gfr7*(qiqkr3+qkqir3);

        // get the induced force with screening

        float ftm2i1 = gfi1*xr + 0.5f*
              (gfi2*(atomI.inducedDipole[0]+atomI.inducedDipoleP[0])
             + bn2*(sci4*atomI.inducedDipoleP[0]+scip4*atomI.inducedDipole[0])
             + gfi3*(atomJ.inducedDipole[0]+atomJ.inducedDipoleP[0])
             + bn2*(sci3*atomJ.inducedDipoleP[0]+scip3*atomJ.inducedDipole[0])
             + (sci4+scip4)*bn2*di1
             + (sci3+scip3)*bn2*dk1
             + gfi4*(qkui1+qkuip1-qiuk1-qiukp1))
             + gfi5*qir1 + gfi6*qkr1;

        float ftm2i2 = gfi1*yr + 0.5f*
              (gfi2*(atomI.inducedDipole[1]+atomI.inducedDipoleP[1])
             + bn2*(sci4*atomI.inducedDipoleP[1]+scip4*atomI.inducedDipole[1])
             + gfi3*(atomJ.inducedDipole[1]+atomJ.inducedDipoleP[1])
             + bn2*(sci3*atomJ.inducedDipoleP[1]+scip3*atomJ.inducedDipole[1])
             + (sci4+scip4)*bn2*di2
             + (sci3+scip3)*bn2*dk2
             + gfi4*(qkui2+qkuip2-qiuk2-qiukp2))
             + gfi5*qir2 + gfi6*qkr2;

        float ftm2i3 = gfi1*zr + 0.5f*
              (gfi2*(atomI.inducedDipole[2]+atomI.inducedDipoleP[2])
             + bn2*(sci4*atomI.inducedDipoleP[2]+scip4*atomI.inducedDipole[2])
             + gfi3*(atomJ.inducedDipole[2]+atomJ.inducedDipoleP[2])
             + bn2*(sci3*atomJ.inducedDipoleP[2]+scip3*atomJ.inducedDipole[2])
             + (sci4+scip4)*bn2*di3
             + (sci3+scip3)*bn2*dk3
             + gfi4*(qkui3+qkuip3-qiuk3-qiukp3))
             + gfi5*qir3 + gfi6*qkr3;

        // get the induced force without screening

        float ftm2ri1 = gfri1*xr + 0.5f*
            (- rr3*ck*(atomI.inducedDipole[0]*psc3+atomI.inducedDipoleP[0]*dsc3)
             + rr5*sc4*(atomI.inducedDipole[0]*psc5+atomI.inducedDipoleP[0]*dsc5)
             - rr7*sc6*(atomI.inducedDipole[0]*psc7+atomI.inducedDipoleP[0]*dsc7))
             + (rr3*ci*(atomJ.inducedDipole[0]*psc3+atomJ.inducedDipoleP[0]*dsc3)
             + rr5*sc3*(atomJ.inducedDipole[0]*psc5+atomJ.inducedDipoleP[0]*dsc5)
             + rr7*sc5*(atomJ.inducedDipole[0]*psc7+atomJ.inducedDipoleP[0]*dsc7))*0.5f
             + rr5*usc5*(sci4*atomI.inducedDipoleP[0]+scip4*atomI.inducedDipole[0]
             + sci3*atomJ.inducedDipoleP[0]+scip3*atomJ.inducedDipole[0])*0.5f
             + 0.5f*(sci4*psc5+scip4*dsc5)*rr5*di1
             + 0.5f*(sci3*psc5+scip3*dsc5)*rr5*dk1
             + 0.5f*gfri4*((qkui1-qiuk1)*psc5
             + (qkuip1-qiukp1)*dsc5)
             + gfri5*qir1 + gfri6*qkr1;

        float ftm2ri2 = gfri1*yr + 0.5f*
            (- rr3*ck*(atomI.inducedDipole[1]*psc3+atomI.inducedDipoleP[1]*dsc3)
             + rr5*sc4*(atomI.inducedDipole[1]*psc5+atomI.inducedDipoleP[1]*dsc5)
             - rr7*sc6*(atomI.inducedDipole[1]*psc7+atomI.inducedDipoleP[1]*dsc7))
             + (rr3*ci*(atomJ.inducedDipole[1]*psc3+atomJ.inducedDipoleP[1]*dsc3)
             + rr5*sc3*(atomJ.inducedDipole[1]*psc5+atomJ.inducedDipoleP[1]*dsc5)
             + rr7*sc5*(atomJ.inducedDipole[1]*psc7+atomJ.inducedDipoleP[1]*dsc7))*0.5f
             + rr5*usc5*(sci4*atomI.inducedDipoleP[1]+scip4*atomI.inducedDipole[1]
             + sci3*atomJ.inducedDipoleP[1]+scip3*atomJ.inducedDipole[1])*0.5f
             + 0.5f*(sci4*psc5+scip4*dsc5)*rr5*di2
             + 0.5f*(sci3*psc5+scip3*dsc5)*rr5*dk2
             + 0.5f*gfri4*((qkui2-qiuk2)*psc5
             + (qkuip2-qiukp2)*dsc5)
             + gfri5*qir2 + gfri6*qkr2;

        float ftm2ri3 = gfri1*zr + 0.5f*
            (- rr3*ck*(atomI.inducedDipole[2]*psc3+atomI.inducedDipoleP[2]*dsc3)
             + rr5*sc4*(atomI.inducedDipole[2]*psc5+atomI.inducedDipoleP[2]*dsc5)
             - rr7*sc6*(atomI.inducedDipole[2]*psc7+atomI.inducedDipoleP[2]*dsc7))
             + (rr3*ci*(atomJ.inducedDipole[2]*psc3+atomJ.inducedDipoleP[2]*dsc3)
             + rr5*sc3*(atomJ.inducedDipole[2]*psc5+atomJ.inducedDipoleP[2]*dsc5)
             + rr7*sc5*(atomJ.inducedDipole[2]*psc7+atomJ.inducedDipoleP[2]*dsc7))*0.5f
             + rr5*usc5*(sci4*atomI.inducedDipoleP[2]+scip4*atomI.inducedDipole[2]
             + sci3*atomJ.inducedDipoleP[2]+scip3*atomJ.inducedDipole[2])*0.5f
             + 0.5f*(sci4*psc5+scip4*dsc5)*rr5*di3
             + 0.5f*(sci3*psc5+scip3*dsc5)*rr5*dk3
             + 0.5f*gfri4*((qkui3-qiuk3)*psc5
             + (qkuip3-qiukp3)*dsc5)
             + gfri5*qir3 + gfri6*qkr3;

        // account for partially excluded induced interactions

        float temp3 = 0.5f * rr3 * ((gli1+gli6)*scalingFactors[PScaleIndex]
                                   +(glip1+glip6)*scalingFactors[DScaleIndex]);

        float temp5 = 0.5f * rr5 * ((gli2+gli7)*scalingFactors[PScaleIndex]
                                   +(glip2+glip7)*scalingFactors[DScaleIndex]);

        float temp7 = 0.5f * rr7 * (gli3*scalingFactors[PScaleIndex]
                                   +glip3*scalingFactors[DScaleIndex]);

        float fridmp1 = temp3*ddsc31 + temp5*ddsc51 + temp7*ddsc71;
        float fridmp2 = temp3*ddsc32 + temp5*ddsc52 + temp7*ddsc72;
        float fridmp3 = temp3*ddsc33 + temp5*ddsc53 + temp7*ddsc73;

        // find some scaling terms for induced-induced force

        temp3         = 0.5f * rr3 * scalingFactors[UScaleIndex] * scip2;
        temp5         = -0.5f * rr5 * scalingFactors[UScaleIndex] * (sci3*scip4+scip3*sci4);
        float findmp1 = temp3*ddsc31 + temp5*ddsc51;
        float findmp2 = temp3*ddsc32 + temp5*ddsc52;
        float findmp3 = temp3*ddsc33 + temp5*ddsc53;

        // modify the forces for partially excluded interactions

        ftm2i1       -= (fridmp1 + findmp1);
        ftm2i2       -= (fridmp2 + findmp2);
        ftm2i3       -= (fridmp3 + findmp3);

        // correction to convert mutual to direct polarization force

        if( cAmoebaSim.polarizationType ){

           float gfd     = 0.5f * (bn2*scip2 - bn3*(scip3*sci4+sci3*scip4));
           ftm2i1       -= gfd*xr + 0.5f*bn2*(sci4*atomI.inducedDipoleP[0]+scip4*atomI.inducedDipole[0]+sci3*atomJ.inducedDipoleP[0]+scip3*atomJ.inducedDipole[0]);
           ftm2i2       -= gfd*yr + 0.5f*bn2*(sci4*atomI.inducedDipoleP[1]+scip4*atomI.inducedDipole[1]+sci3*atomJ.inducedDipoleP[1]+scip3*atomJ.inducedDipole[1]);
           ftm2i3       -= gfd*zr + 0.5f*bn2*(sci4*atomI.inducedDipoleP[2]+scip4*atomI.inducedDipole[2]+sci3*atomJ.inducedDipoleP[2]+scip3*atomJ.inducedDipole[2]);

           float gfdr    = 0.5f * (rr5*scip2*usc3 - rr7*(scip3*sci4 +sci3*scip4)*usc5);
           float fdir1   = gfdr*xr + 0.5f*usc5*rr5*(sci4*atomI.inducedDipoleP[0]+scip4*atomI.inducedDipole[0] + sci3*atomJ.inducedDipoleP[0]+scip3*atomJ.inducedDipole[0]);
           float fdir2   = gfdr*yr + 0.5f*usc5*rr5*(sci4*atomI.inducedDipoleP[1]+scip4*atomI.inducedDipole[1] + sci3*atomJ.inducedDipoleP[1]+scip3*atomJ.inducedDipole[1]);
           float fdir3   = gfdr*zr + 0.5f*usc5*rr5*(sci4*atomI.inducedDipoleP[2]+scip4*atomI.inducedDipole[2] + sci3*atomJ.inducedDipoleP[2]+scip3*atomJ.inducedDipole[2]);

           ftm2i1       += fdir1 + findmp1;
           ftm2i2       += fdir2 + findmp2;
           ftm2i3       += fdir3 + findmp3;
        }

        // intermediate variables for induced torque terms

        float gti2  = 0.5f * bn2 * (sci4+scip4);
        float gti3  = 0.5f * bn2 * (sci3+scip3);
        float gti4  = gfi4;
        float gti5  = gfi5;
        float gti6  = gfi6;
        float gtri2 = 0.5f * rr5 * (sci4*psc5+scip4*dsc5);
        float gtri3 = 0.5f * rr5 * (sci3*psc5+scip3*dsc5);
        float gtri4 = gfri4;
        float gtri5 = gfri5;
        float gtri6 = gfri6;

        // get the permanent torque with screening

        float ttm21 = -bn1*dixdk1 + gf2*dixr1
            + gf4*(dixqkr1+dkxqir1+rxqidk1-2.0f*qixqk1)
            - gf5*rxqir1 - gf7*(rxqikr1+qkrxqir1);
        float ttm22 = -bn1*dixdk2 + gf2*dixr2
            + gf4*(dixqkr2+dkxqir2+rxqidk2-2.0f*qixqk2)
            - gf5*rxqir2 - gf7*(rxqikr2+qkrxqir2);
        float ttm23 = -bn1*dixdk3 + gf2*dixr3
            + gf4*(dixqkr3+dkxqir3+rxqidk3-2.0f*qixqk3)
            - gf5*rxqir3 - gf7*(rxqikr3+qkrxqir3);
        float ttm31 = bn1*dixdk1 + gf3*dkxr1
            - gf4*(dixqkr1+dkxqir1+rxqkdi1-2.0f*qixqk1)
            - gf6*rxqkr1 - gf7*(rxqkir1-qkrxqir1);
        float ttm32 = bn1*dixdk2 + gf3*dkxr2
            - gf4*(dixqkr2+dkxqir2+rxqkdi2-2.0f*qixqk2)
            - gf6*rxqkr2 - gf7*(rxqkir2-qkrxqir2);
        float ttm33 = bn1*dixdk3 + gf3*dkxr3
            - gf4*(dixqkr3+dkxqir3+rxqkdi3-2.0f*qixqk3)
            - gf6*rxqkr3 - gf7*(rxqkir3-qkrxqir3);

        // get the permanent torque without screening

        float ttm2r1 = -rr3*dixdk1 + gfr2*dixr1-gfr5*rxqir1
            + gfr4*(dixqkr1+dkxqir1+rxqidk1-2.0f*qixqk1)
            - gfr7*(rxqikr1+qkrxqir1);
        float ttm2r2 = -rr3*dixdk2 + gfr2*dixr2-gfr5*rxqir2
            + gfr4*(dixqkr2+dkxqir2+rxqidk2-2.0f*qixqk2)
            - gfr7*(rxqikr2+qkrxqir2);
        float ttm2r3 = -rr3*dixdk3 + gfr2*dixr3-gfr5*rxqir3
            + gfr4*(dixqkr3+dkxqir3+rxqidk3-2.0f*qixqk3)
            - gfr7*(rxqikr3+qkrxqir3);
        float ttm3r1 = rr3*dixdk1 + gfr3*dkxr1 -gfr6*rxqkr1
            - gfr4*(dixqkr1+dkxqir1+rxqkdi1-2.0f*qixqk1)
            - gfr7*(rxqkir1-qkrxqir1);
        float ttm3r2 = rr3*dixdk2 + gfr3*dkxr2 -gfr6*rxqkr2
            - gfr4*(dixqkr2+dkxqir2+rxqkdi2-2.0f*qixqk2)
            - gfr7*(rxqkir2-qkrxqir2);
        float ttm3r3 = rr3*dixdk3 + gfr3*dkxr3 -gfr6*rxqkr3
            - gfr4*(dixqkr3+dkxqir3+rxqkdi3-2.0f*qixqk3)
            - gfr7*(rxqkir3-qkrxqir3);

        // get the induced torque with screening

        float ttm2i1 = -bn1*(dixuk1+dixukp1)*0.5f
            + gti2*dixr1 + gti4*(ukxqir1+rxqiuk1
            + ukxqirp1+rxqiukp1)*0.5f - gti5*rxqir1;
        float ttm2i2 = -bn1*(dixuk2+dixukp2)*0.5f
            + gti2*dixr2 + gti4*(ukxqir2+rxqiuk2
            + ukxqirp2+rxqiukp2)*0.5f - gti5*rxqir2;
        float ttm2i3 = -bn1*(dixuk3+dixukp3)*0.5f
            + gti2*dixr3 + gti4*(ukxqir3+rxqiuk3
            + ukxqirp3+rxqiukp3)*0.5f - gti5*rxqir3;
        float ttm3i1 = -bn1*(dkxui1+dkxuip1)*0.5f
            + gti3*dkxr1 - gti4*(uixqkr1+rxqkui1
            + uixqkrp1+rxqkuip1)*0.5f - gti6*rxqkr1;
        float ttm3i2 = -bn1*(dkxui2+dkxuip2)*0.5f
            + gti3*dkxr2 - gti4*(uixqkr2+rxqkui2
            + uixqkrp2+rxqkuip2)*0.5f - gti6*rxqkr2;
        float ttm3i3 = -bn1*(dkxui3+dkxuip3)*0.5f
            + gti3*dkxr3 - gti4*(uixqkr3+rxqkui3
            + uixqkrp3+rxqkuip3)*0.5f - gti6*rxqkr3;

        // get the induced torque without screening

        float ttm2ri1 = -rr3*(dixuk1*psc3+dixukp1*dsc3)*0.5f
            + gtri2*dixr1 + gtri4*((ukxqir1+rxqiuk1)*psc5
            +(ukxqirp1+rxqiukp1)*dsc5)*0.5f - gtri5*rxqir1;
        float ttm2ri2 = -rr3*(dixuk2*psc3+dixukp2*dsc3)*0.5f
            + gtri2*dixr2 + gtri4*((ukxqir2+rxqiuk2)*psc5
            +(ukxqirp2+rxqiukp2)*dsc5)*0.5f - gtri5*rxqir2;
        float ttm2ri3 = -rr3*(dixuk3*psc3+dixukp3*dsc3)*0.5f
            + gtri2*dixr3 + gtri4*((ukxqir3+rxqiuk3)*psc5
            +(ukxqirp3+rxqiukp3)*dsc5)*0.5f - gtri5*rxqir3;
        float ttm3ri1 = -rr3*(dkxui1*psc3+dkxuip1*dsc3)*0.5f
            + gtri3*dkxr1 - gtri4*((uixqkr1+rxqkui1)*psc5
            +(uixqkrp1+rxqkuip1)*dsc5)*0.5f - gtri6*rxqkr1;
        float ttm3ri2 = -rr3*(dkxui2*psc3+dkxuip2*dsc3)*0.5f
            + gtri3*dkxr2 - gtri4*((uixqkr2+rxqkui2)*psc5
            +(uixqkrp2+rxqkuip2)*dsc5)*0.5f - gtri6*rxqkr2;
        float ttm3ri3 = -rr3*(dkxui3*psc3+dkxuip3*dsc3)*0.5f
            + gtri3*dkxr3 - gtri4*((uixqkr3+rxqkui3)*psc5
            +(uixqkrp3+rxqkuip3)*dsc5)*0.5f - gtri6*rxqkr3;

        // handle the case where scaling is used

        ftm21  = (ftm21-(1.0f-scalingFactors[MScaleIndex])*ftm2r1);
        ftm2i1 = (ftm2i1-ftm2ri1);
        ttm21  = (ttm21-(1.0f-scalingFactors[MScaleIndex])*ttm2r1);
        ttm2i1 = (ttm2i1-ttm2ri1);
        ttm31  = (ttm31-(1.0f-scalingFactors[MScaleIndex])*ttm3r1);
        ttm3i1 = (ttm3i1-ttm3ri1);

        ftm22  = (ftm22-(1.0f-scalingFactors[MScaleIndex])*ftm2r2);
        ftm2i2 = (ftm2i2-ftm2ri2);
        ttm22  = (ttm22-(1.0f-scalingFactors[MScaleIndex])*ttm2r2);
        ttm2i2 = (ttm2i2-ttm2ri2);
        ttm32  = (ttm32-(1.0f-scalingFactors[MScaleIndex])*ttm3r2);
        ttm3i2 = (ttm3i2-ttm3ri2);

        ftm23  = (ftm23-(1.0f-scalingFactors[MScaleIndex])*ftm2r3);
        ftm2i3 = (ftm2i3-ftm2ri3);
        ttm23  = (ttm23-(1.0f-scalingFactors[MScaleIndex])*ttm2r3);
        ttm2i3 = (ttm2i3-ttm2ri3);
        ttm33  = (ttm33-(1.0f-scalingFactors[MScaleIndex])*ttm3r3);
        ttm3i3 = (ttm3i3-ttm3ri3);

        // increment gradient due to force and torque on first site;

        forceTorqueEnergy[0].x       = (ftm21 + ftm2i1);
        forceTorqueEnergy[0].y       = (ftm22 + ftm2i2);
        forceTorqueEnergy[0].z       = (ftm23 + ftm2i3);

        forceTorqueEnergy[1].x       =  (ttm21 + ttm2i1);
        forceTorqueEnergy[1].y       =  (ttm22 + ttm2i2);
        forceTorqueEnergy[1].z       =  (ttm23 + ttm2i3);

        forceTorqueEnergy[2].x       =  (ttm31 + ttm3i1);
        forceTorqueEnergy[2].y       =  (ttm32 + ttm3i2);
        forceTorqueEnergy[2].z       =  (ttm33 + ttm3i3);

    } else {

        forceTorqueEnergy[0].x  = 0.0f;
        forceTorqueEnergy[0].y  = 0.0f;
        forceTorqueEnergy[0].z  = 0.0f;

        forceTorqueEnergy[1].x  = 0.0f;
        forceTorqueEnergy[1].y  = 0.0f;
        forceTorqueEnergy[1].z  = 0.0f;

        forceTorqueEnergy[2].x  = 0.0f;
        forceTorqueEnergy[2].y  = 0.0f;
        forceTorqueEnergy[2].z  = 0.0f;

        forceTorqueEnergy[0].w  = 0.0f;

    }

    return;

}

__device__ void calculatePmeDirectElectrostaticPairIxn_kernel( PmeDirectElectrostaticParticle& atomI, PmeDirectElectrostaticParticle& atomJ,
                                                               bool bExclusionFlag, const float* scalingFactors, float forceFactor, float* energy ){

    float4 delta;
    delta.x          = atomJ.x - atomI.x;
    delta.y          = atomJ.y - atomI.y;
    delta.z          = atomJ.z - atomI.z;

    // periodic box

    delta.x         -= floorf(delta.x*cSim.invPeriodicBoxSizeX+0.5f)*cSim.periodicBoxSizeX;
    delta.y         -= floorf(delta.y*cSim.invPeriodicBoxSizeY+0.5f)*cSim.periodicBoxSizeY;
    delta.z         -= floorf(delta.z*cSim.invPeriodicBoxSizeZ+0.5f)*cSim.periodicBoxSizeZ;

    delta.w          = delta.x*delta.x + delta.y*delta.y + delta.z*delta.z;
    if( delta.w > cSim.nonbondedCutoffSqr ){
        return;
    }   

    float r                     = sqrtf(delta.w);
    float ralpha                = cSim.alphaEwald*r;

    float alsq2                 = 2.0f*cSim.alphaEwald*cSim.alphaEwald;
    float alsq2n                = 0.0f;
    if( cSim.alphaEwald > 0.0f ){
        alsq2n                  = 1.0f/(cAmoebaSim.sqrtPi*cSim.alphaEwald);
    }   
    float exp2a                 = expf(-(ralpha*ralpha));

    float rr1                   = 1.0f/r;
    delta.w                     = rr1;
    float bn0                   = erfcf(ralpha)*rr1;
    *energy                    += forceFactor*atomI.q*atomJ.q*bn0;
    float rr2                   = rr1*rr1;
    alsq2n                     *= alsq2;

    float4 bn;
    bn.x                        = (bn0+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn.y                        = (3.0f*bn.x+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn.z                        = (5.0f*bn.y+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn.w                        = (7.0f*bn.z+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    float bn5                   = (9.0f*bn.w+alsq2n*exp2a)*rr2;
/*
    float  bn0, bn5;
    float4 bn;
    calculateBn_kernel( r, &bn, &bn0, &bn5 );
    *energy                    += forceFactor*atomI.q*atomJ.q*bn0;
    delta.w                     = 1.0f/r;
*/

    float force[3];

    //calculatePmeDirectElectrostaticPairIxnF1Scale_kernel( atomI, atomJ, delta, bn, bn5, forceFactor, scalingFactors, force, energy );
    if( bExclusionFlag ){

        calculatePmeDirectElectrostaticPairIxnF1Scale_kernel( atomI, atomJ, delta, bn, bn5, forceFactor, scalingFactors, force, energy );
        calculatePmeDirectElectrostaticPairIxnF2Scale_kernel( atomI, atomJ, delta, bn, forceFactor, scalingFactors, force, energy );
    } else {
        calculatePmeDirectElectrostaticPairIxnF1NoScale_kernel( atomI, atomJ, delta, bn, bn5, forceFactor, force, energy );
        calculatePmeDirectElectrostaticPairIxnF2NoScale_kernel( atomI, atomJ, delta, bn, forceFactor, force, energy );
    }

    atomI.force[0] += force[0];
    atomI.force[1] += force[1];
    atomI.force[2] += force[2];

    if( forceFactor == 1.0f ){
        atomJ.force[0] -= force[0];
        atomJ.force[1] -= force[1];
        atomJ.force[2] -= force[2];
    }
    
    calculatePmeDirectElectrostaticPairIxnT1Scale_kernel( atomI, atomJ, delta, bn, scalingFactors );
    calculatePmeDirectElectrostaticPairIxnT2Scale_kernel( atomI, atomJ, delta, bn, scalingFactors );

    if( forceFactor == 1.0f ){

        // T3 == T1 w/ particles I and J reversed
        // T4 == T2 w/ particles I and J reversed

        delta.x *= -1.0f;
        delta.y *= -1.0f;
        delta.z *= -1.0f;

        calculatePmeDirectElectrostaticPairIxnT1Scale_kernel( atomJ, atomI, delta, bn, scalingFactors );
        calculatePmeDirectElectrostaticPairIxnT2Scale_kernel( atomJ, atomI, delta, bn, scalingFactors );

    }

    return;
}

#ifdef OLD
__device__ void calculatePmeDirectElectrostaticPairIxnOrigg_kernel( PmeDirectElectrostaticParticle& atomI, PmeDirectElectrostaticParticle& atomJ,
                                                               bool bExclusionFlag, const float* scalingFactors, float forceFactor, float* energy ){

    float4 delta;
    delta.x          = atomJ.x - atomI.x;
    delta.y          = atomJ.y - atomI.y;
    delta.z          = atomJ.z - atomI.z;

    // periodic box

    delta.x         -= floorf(delta.x*cSim.invPeriodicBoxSizeX+0.5f)*cSim.periodicBoxSizeX;
    delta.y         -= floorf(delta.y*cSim.invPeriodicBoxSizeY+0.5f)*cSim.periodicBoxSizeY;
    delta.z         -= floorf(delta.z*cSim.invPeriodicBoxSizeZ+0.5f)*cSim.periodicBoxSizeZ;

    delta.w          = delta.x*delta.x + delta.y*delta.y + delta.z*delta.z;
    if( delta.w > cSim.nonbondedCutoffSqr ){
        return;
    }   

    float r                     = sqrtf(delta.w);
    float ralpha                = cSim.alphaEwald*r;

    float alsq2                 = 2.0f*cSim.alphaEwald*cSim.alphaEwald;
    float alsq2n                = 0.0f;
    if( cSim.alphaEwald > 0.0f ){
        alsq2n                  = 1.0f/(cAmoebaSim.sqrtPi*cSim.alphaEwald);
    }   
    float exp2a                 = expf(-(ralpha*ralpha));

    float rr1                   = 1.0f/r;
    delta.w                     = rr1;
    float bn0                   = erfcf(ralpha)*rr1;
    *energy                    += forceFactor*atomI.q*atomJ.q*bn0;
    float rr2                   = rr1*rr1;
    alsq2n                     *= alsq2;

    float4 bn;
    bn.x                        = (bn0+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn.y                        = (3.0f*bn.x+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn.z                        = (5.0f*bn.y+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    bn.w                        = (7.0f*bn.z+alsq2n*exp2a)*rr2;

    alsq2n                     *= alsq2;
    float bn5                   = (9.0f*bn.w+alsq2n*exp2a)*rr2;

    float force[3];

    //calculatePmeDirectElectrostaticPairIxnF1Scale_kernel( atomI, atomJ, delta, bn, bn5, forceFactor, scalingFactors, force, energy );
    if( bExclusionFlag ){

        calculatePmeDirectElectrostaticPairIxnF1Scale_kernel( atomI, atomJ, delta, bn, bn5, forceFactor, scalingFactors, force, energy );
        calculatePmeDirectElectrostaticPairIxnF2Scale_kernel( atomI, atomJ, delta, bn, forceFactor, scalingFactors, force, energy );
    } else {
        calculatePmeDirectElectrostaticPairIxnF1NoScale_kernel( atomI, atomJ, delta, bn, bn5, forceFactor, force, energy );
        calculatePmeDirectElectrostaticPairIxnF2NoScale_kernel( atomI, atomJ, delta, bn, forceFactor, force, energy );
    }

    atomI.force[0] += force[0];
    atomI.force[1] += force[1];
    atomI.force[2] += force[2];

    if( forceFactor == 1.0f ){
        atomJ.force[0] -= force[0];
        atomJ.force[1] -= force[1];
        atomJ.force[2] -= force[2];
    }
    
    calculatePmeDirectElectrostaticPairIxnT1Scale_kernel( atomI, atomJ, delta, bn, scalingFactors );
    calculatePmeDirectElectrostaticPairIxnT2Scale_kernel( atomI, atomJ, delta, bn, scalingFactors );

    if( forceFactor == 1.0f ){

        // T3 == T1 w/ particles I and J reversed
        // T4 == T2 w/ particles I and J reversed

        delta.x *= -1.0f;
        delta.y *= -1.0f;
        delta.z *= -1.0f;

        calculatePmeDirectElectrostaticPairIxnT1Scale_kernel( atomJ, atomI, delta, bn, scalingFactors );
        calculatePmeDirectElectrostaticPairIxnT2Scale_kernel( atomJ, atomI, delta, bn, scalingFactors );
    }

    return;
}
#endif

__device__ void loadPmeDirectElectrostaticParticle( unsigned int atomI,  struct PmeDirectElectrostaticParticle* sA )
{
    // coordinates & charge
    float4 posq                  = cSim.pPosq[atomI];
    sA->x                        = posq.x;
    sA->y                        = posq.y;
    sA->z                        = posq.z;
    sA->q                        = posq.w;

    // lab dipole

    sA->labFrameDipole[0]        = cAmoebaSim.pLabFrameDipole[atomI*3];
    sA->labFrameDipole[1]        = cAmoebaSim.pLabFrameDipole[atomI*3+1];
    sA->labFrameDipole[2]        = cAmoebaSim.pLabFrameDipole[atomI*3+2];

    // lab quadrupole

    sA->labFrameQuadrupole[0]    = cAmoebaSim.pLabFrameQuadrupole[atomI*9];
    sA->labFrameQuadrupole[1]    = cAmoebaSim.pLabFrameQuadrupole[atomI*9+1];
    sA->labFrameQuadrupole[2]    = cAmoebaSim.pLabFrameQuadrupole[atomI*9+2];
    sA->labFrameQuadrupole[3]    = cAmoebaSim.pLabFrameQuadrupole[atomI*9+4];
    sA->labFrameQuadrupole[4]    = cAmoebaSim.pLabFrameQuadrupole[atomI*9+5];

    // traceless tensor
    
    //sA->labFrameQuadrupole[5]    = cAmoebaSim.pLabFrameQuadrupole[atomI*9+8];
    //sA->labFrameQuadrupole[5]    = -(sA->labFrameQuadrupole[0] + sA->labFrameQuadrupole[3]);

    // induced dipole

    sA->inducedDipole[0]         =  cAmoebaSim.pInducedDipole[atomI*3];
    sA->inducedDipole[1]         =  cAmoebaSim.pInducedDipole[atomI*3+1];
    sA->inducedDipole[2]         =  cAmoebaSim.pInducedDipole[atomI*3+2];

    // induced dipole polar

    sA->inducedDipoleP[0]        =  cAmoebaSim.pInducedDipolePolar[atomI*3];
    sA->inducedDipoleP[1]        =  cAmoebaSim.pInducedDipolePolar[atomI*3+1];
    sA->inducedDipoleP[2]        =  cAmoebaSim.pInducedDipolePolar[atomI*3+2];

    float2 dampingFactorAndThole = cAmoebaSim.pDampingFactorAndThole[atomI];
    sA->damp                     = dampingFactorAndThole.x;
    sA->thole                    = dampingFactorAndThole.y;

}

__device__ void zeroPmeDirectElectrostaticParticle( struct PmeDirectElectrostaticParticle* sA )
{

    sA->force[0]                 = 0.0f;
    sA->force[1]                 = 0.0f;
    sA->force[2]                 = 0.0f;

    sA->torque[0]                = 0.0f;
    sA->torque[1]                = 0.0f;
    sA->torque[2]                = 0.0f;

}

// Include versions of the kernels for N^2 calculations.

#undef USE_OUTPUT_BUFFER_PER_WARP
#define METHOD_NAME(a, b) a##Cutoff##b
#include "kCalculateAmoebaCudaPmeDirectElectrostatic.h"
#define USE_OUTPUT_BUFFER_PER_WARP
#undef METHOD_NAME
#define METHOD_NAME(a, b) a##CutoffByWarp##b
#include "kCalculateAmoebaCudaPmeDirectElectrostatic.h"

// reduce psWorkArray_3_1 -> torque

static void kReduceTorque(amoebaGpuContext amoebaGpu )
{
    gpuContext gpu = amoebaGpu->gpuContext;
    kReduceFields_kernel<<<gpu->sim.nonbond_blocks, gpu->sim.bsf_reduce_threads_per_block>>>(
                           gpu->sim.paddedNumberOfAtoms*3, gpu->sim.outputBuffers,
                           amoebaGpu->psWorkArray_3_1->_pDevData, amoebaGpu->psTorque->_pDevData, 1 );
    LAUNCHERROR("kReducePmeDirectElectrostaticTorque");
}

/**---------------------------------------------------------------------------------------

   Compute Amoeba dirrect space portion of electrostatic force & torque

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */

void cudaComputeAmoebaPmeDirectElectrostatic( amoebaGpuContext amoebaGpu )
{

    // ---------------------------------------------------------------------------------------

    gpuContext gpu = amoebaGpu->gpuContext;

    // apparently debug array can take up nontrivial no. registers
    // on first pass, set threads/block

    static unsigned int threadsPerBlock = 0;
    static const int maxL1              = 0; 
    if( threadsPerBlock == 0 ){
        unsigned int sharedMemoryPerBlock = gpu->sharedMemoryPerBlock;
        unsigned int maxThreads;
        if (gpu->sm_version >= SM_20){
            maxThreads = 384;
            if( maxL1 ){
                sharedMemoryPerBlock = 16384;
                cudaFuncSetCacheConfig(kCalculateAmoebaPmeDirectElectrostaticCutoffForces_kernel, cudaFuncCachePreferL1 );
            }
        } else if (gpu->sm_version >= SM_12){
            maxThreads = 128;
        } else {
            maxThreads = 64;
        }
        threadsPerBlock = std::min(getThreadsPerBlock(amoebaGpu, sizeof(PmeDirectElectrostaticParticle), sharedMemoryPerBlock), maxThreads);
    }

    kClearFields_3( amoebaGpu, 1 );

    if (gpu->bOutputBufferPerWarp){

        kCalculateAmoebaPmeDirectElectrostaticCutoffByWarpForces_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(PmeDirectElectrostaticParticle)*threadsPerBlock>>>(
                                                                          gpu->sim.pInteractingWorkUnit,
                                                                          amoebaGpu->psWorkArray_3_1->_pDevData );
    } else {

        kCalculateAmoebaPmeDirectElectrostaticCutoffForces_kernel<<<gpu->sim.nonbond_blocks, threadsPerBlock, sizeof(PmeDirectElectrostaticParticle)*threadsPerBlock>>>(
                                                                    gpu->sim.pInteractingWorkUnit,
                                                                    amoebaGpu->psWorkArray_3_1->_pDevData );
    }
    LAUNCHERROR("kCalculateAmoebaPmeDirectElectrostaticCutoffForces");

    kReduceTorque( amoebaGpu );

}

/**---------------------------------------------------------------------------------------

   Compute Amoeba electrostatic force & torque using PME

   @param amoebaGpu        amoebaGpu context

   --------------------------------------------------------------------------------------- */

void cudaComputeAmoebaPmeElectrostatic( amoebaGpuContext amoebaGpu )
{
    cudaComputeAmoebaPmeDirectElectrostatic( amoebaGpu );
    kCalculateAmoebaPMEInducedDipoleForces( amoebaGpu );
    cudaComputeAmoebaMapTorqueAndAddToForce( amoebaGpu, amoebaGpu->psTorque );
}

