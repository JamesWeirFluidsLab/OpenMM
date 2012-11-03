#ifndef OPENMM_CUDAKERNELS_H_
#define OPENMM_CUDAKERNELS_H_

/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2009 Stanford University and the Authors.      *
 * Authors: Peter Eastman                                                     *
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

#include "CudaPlatform.h"
#include "openmm/kernels.h"
#include "kernels/gputypes.h"
#include "openmm/System.h"

class CudaAndersenThermostat;
class CudaBrownianDynamics;
class CudaStochasticDynamics;
class CudaShakeAlgorithm;
class CudaVerletDynamics;

namespace OpenMM {

// Export internal cudaOpenMMInitializeIntegration() method so it can be used by NML plugin
void OPENMMCUDA_EXPORT cudaOpenMMInitializeIntegration(const System& system, CudaPlatform::PlatformData& data, const Integrator& integrator);

/**
 * This kernel is invoked at the beginning and end of force and energy computations.  It gives the
 * Platform a chance to clear buffers and do other initialization at the beginning, and to do any
 * necessary work at the end to determine the final results.
 */
class CudaCalcForcesAndEnergyKernel : public CalcForcesAndEnergyKernel {
public:
    CudaCalcForcesAndEnergyKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : CalcForcesAndEnergyKernel(name, platform), data(data) {
    }
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     */
    void initialize(const System& system);
    /**
     * This is called at the beginning of each force/energy computation, before calcForcesAndEnergy() has been called on
     * any ForceImpl.
     *
     * @param context       the context in which to execute this kernel
     * @param includeForce  true if forces should be computed
     * @param includeEnergy true if potential energy should be computed
     * @param groups        a set of bit flags for which force groups to include
     */
    void beginComputation(ContextImpl& context, bool includeForce, bool includeEnergy, int groups);
    /**
     * This is called at the end of each force/energy computation, after calcForcesAndEnergy() has been called on
     * every ForceImpl.
     *
     * @param context       the context in which to execute this kernel
     * @param includeForce  true if forces should be computed
     * @param includeEnergy true if potential energy should be computed
     * @param groups        a set of bit flags for which force groups to include
     * @return the potential energy of the system.  This value is added to all values returned by ForceImpls'
     * calcForcesAndEnergy() methods.  That is, each force kernel may <i>either</i> return its contribution to the
     * energy directly, <i>or</i> add it to an internal buffer so that it will be included here.
     */
    double finishComputation(ContextImpl& context, bool includeForce, bool includeEnergy, int groups);
private:
    CudaPlatform::PlatformData& data;
};

/**
 * This kernel provides methods for setting and retrieving various state data: time, positions,
 * velocities, and forces.
 */
class CudaUpdateStateDataKernel : public UpdateStateDataKernel {
public:
    CudaUpdateStateDataKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : UpdateStateDataKernel(name, platform), data(data) {
    }
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     */
    void initialize(const System& system);
    /**
     * Get the current time (in picoseconds).
     *
     * @param context    the context in which to execute this kernel
     */
    double getTime(const ContextImpl& context) const;
    /**
     * Set the current time (in picoseconds).
     *
     * @param context    the context in which to execute this kernel
     */
    void setTime(ContextImpl& context, double time);
    /**
     * Get the positions of all particles.
     *
     * @param positions  on exit, this contains the particle positions
     */
    void getPositions(ContextImpl& context, std::vector<Vec3>& positions);
    /**
     * Set the positions of all particles.
     *
     * @param positions  a vector containg the particle positions
     */
    void setPositions(ContextImpl& context, const std::vector<Vec3>& positions);
    /**
     * Get the velocities of all particles.
     *
     * @param velocities  on exit, this contains the particle velocities
     */
    void getVelocities(ContextImpl& context, std::vector<Vec3>& velocities);
    /**
     * Set the velocities of all particles.
     *
     * @param velocities  a vector containg the particle velocities
     */
    void setVelocities(ContextImpl& context, const std::vector<Vec3>& velocities);
    /**
     * Get the current forces on all particles.
     *
     * @param forces  on exit, this contains the forces
     */
    void getForces(ContextImpl& context, std::vector<Vec3>& forces);
    /**
     * Get the current periodic box vectors.
     *
     * @param a      on exit, this contains the vector defining the first edge of the periodic box
     * @param b      on exit, this contains the vector defining the second edge of the periodic box
     * @param c      on exit, this contains the vector defining the third edge of the periodic box
     */
    void getPeriodicBoxVectors(ContextImpl& context, Vec3& a, Vec3& b, Vec3& c) const;
    /**
     * Set the current periodic box vectors.
     *
     * @param a      the vector defining the first edge of the periodic box
     * @param b      the vector defining the second edge of the periodic box
     * @param c      the vector defining the third edge of the periodic box
     */
    void setPeriodicBoxVectors(ContextImpl& context, const Vec3& a, const Vec3& b, const Vec3& c) const;
private:
    CudaPlatform::PlatformData& data;
};

/**
 * This kernel modifies the positions of particles to enforce distance constraints.
 */
class CudaApplyConstraintsKernel : public ApplyConstraintsKernel {
public:
    CudaApplyConstraintsKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : ApplyConstraintsKernel(name, platform), data(data) {
    }
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     */
    void initialize(const System& system);
    /**
     * Update particle positions to enforce constraints.
     *
     * @param context    the context in which to execute this kernel
     * @param tol        the distance tolerance within which constraints must be satisfied.
     */
    void apply(ContextImpl& context, double tol);
private:
    CudaPlatform::PlatformData& data;
};

/**
 * This kernel recomputes the positions of virtual sites.
 */
class CudaVirtualSitesKernel : public VirtualSitesKernel {
public:
    CudaVirtualSitesKernel(std::string name, const Platform& platform) : VirtualSitesKernel(name, platform) {
    }
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     */
    void initialize(const System& system);
    /**
     * Compute the virtual site locations.
     *
     * @param context    the context in which to execute this kernel
     */
    void computePositions(ContextImpl& context);
};

/**
 * This kernel is invoked by HarmonicBondForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcHarmonicBondForceKernel : public CalcHarmonicBondForceKernel {
public:
    CudaCalcHarmonicBondForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcHarmonicBondForceKernel(name, platform), data(data), system(system) {
    }
    ~CudaCalcHarmonicBondForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the HarmonicBondForce this kernel will be used for
     */
    void initialize(const System& system, const HarmonicBondForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    int numBonds;
    CudaPlatform::PlatformData& data;
    System& system;
};

/**
 * This kernel is invoked by CustomBondForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcCustomBondForceKernel : public CalcCustomBondForceKernel {
public:
    CudaCalcCustomBondForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcCustomBondForceKernel(name, platform),
            data(data), system(system) {
    }
    ~CudaCalcCustomBondForceKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param force      the CustomBondForce this kernel will be used for
     */
    void initialize(const System& system, const CustomBondForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    void updateGlobalParams(ContextImpl& context);
    int numBonds;
    CudaPlatform::PlatformData& data;
    std::vector<std::string> globalParamNames;
    std::vector<float> globalParamValues;
    System& system;
};

/**
 * This kernel is invoked by HarmonicAngleForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcHarmonicAngleForceKernel : public CalcHarmonicAngleForceKernel {
public:
    CudaCalcHarmonicAngleForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcHarmonicAngleForceKernel(name, platform), data(data), system(system) {
    }
    ~CudaCalcHarmonicAngleForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the HarmonicAngleForce this kernel will be used for
     */
    void initialize(const System& system, const HarmonicAngleForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    int numAngles;
    CudaPlatform::PlatformData& data;
    System& system;
};

/**
 * This kernel is invoked by CustomAngleForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcCustomAngleForceKernel : public CalcCustomAngleForceKernel {
public:
    CudaCalcCustomAngleForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcCustomAngleForceKernel(name, platform),
            data(data), system(system) {
    }
    ~CudaCalcCustomAngleForceKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param force      the CustomAngleForce this kernel will be used for
     */
    void initialize(const System& system, const CustomAngleForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    void updateGlobalParams(ContextImpl& context);
    int numAngles;
    CudaPlatform::PlatformData& data;
    std::vector<std::string> globalParamNames;
    std::vector<float> globalParamValues;
    System& system;
};

/**
 * This kernel is invoked by PeriodicTorsionForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcPeriodicTorsionForceKernel : public CalcPeriodicTorsionForceKernel {
public:
    CudaCalcPeriodicTorsionForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcPeriodicTorsionForceKernel(name, platform), data(data), system(system) {
    }
    ~CudaCalcPeriodicTorsionForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the PeriodicTorsionForce this kernel will be used for
     */
    void initialize(const System& system, const PeriodicTorsionForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    int numTorsions;
    CudaPlatform::PlatformData& data;
    System& system;
};

/**
 * This kernel is invoked by RBTorsionForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcRBTorsionForceKernel : public CalcRBTorsionForceKernel {
public:
    CudaCalcRBTorsionForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcRBTorsionForceKernel(name, platform), data(data), system(system) {
    }
    ~CudaCalcRBTorsionForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the RBTorsionForce this kernel will be used for
     */
    void initialize(const System& system, const RBTorsionForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    int numTorsions;
    CudaPlatform::PlatformData& data;
    System& system;
};

/**
 * This kernel is invoked by CMAPTorsionForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcCMAPTorsionForceKernel : public CalcCMAPTorsionForceKernel {
public:
    CudaCalcCMAPTorsionForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) :
            CalcCMAPTorsionForceKernel(name, platform), data(data), system(system), coefficients(NULL), mapPositions(NULL),
            torsionIndices(NULL), torsionMaps(NULL) {
    }
    ~CudaCalcCMAPTorsionForceKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param force      the CMAPTorsionForce this kernel will be used for
     */
    void initialize(const System& system, const CMAPTorsionForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    CudaPlatform::PlatformData& data;
    System& system;
    int numTorsions;
    CUDAStream<float4>* coefficients;
    CUDAStream<int2>* mapPositions;
    CUDAStream<int4>* torsionIndices;
    CUDAStream<int>* torsionMaps;
};

/**
 * This kernel is invoked by CustomTorsionForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcCustomTorsionForceKernel : public CalcCustomTorsionForceKernel {
public:
    CudaCalcCustomTorsionForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcCustomTorsionForceKernel(name, platform),
            data(data), system(system) {
    }
    ~CudaCalcCustomTorsionForceKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param force      the CustomTorsionForce this kernel will be used for
     */
    void initialize(const System& system, const CustomTorsionForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    void updateGlobalParams(ContextImpl& context);
    int numTorsions;
    CudaPlatform::PlatformData& data;
    std::vector<std::string> globalParamNames;
    std::vector<float> globalParamValues;
    System& system;
};

/**
 * This kernel is invoked by NonbondedForce to calculate the forces acting on the system.
 */
class CudaCalcNonbondedForceKernel : public CalcNonbondedForceKernel {
public:
    CudaCalcNonbondedForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcNonbondedForceKernel(name, platform), data(data), system(system) {
    }
    ~CudaCalcNonbondedForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the NonbondedForce this kernel will be used for
     */
    void initialize(const System& system, const NonbondedForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @param includeReciprocal  true if reciprocal space interactions should be included
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy, bool includeDirect, bool includeReciprocal);
private:
    class ForceInfo;
    CudaPlatform::PlatformData& data;
    int numParticles;
    System& system;
};

/**
 * This kernel is invoked by CustomNonbondedForce to calculate the forces acting on the system.
 */
class CudaCalcCustomNonbondedForceKernel : public CalcCustomNonbondedForceKernel {
public:
    CudaCalcCustomNonbondedForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcCustomNonbondedForceKernel(name, platform), data(data), system(system) {
    }
    ~CudaCalcCustomNonbondedForceKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param force      the CustomNonbondedForce this kernel will be used for
     */
    void initialize(const System& system, const CustomNonbondedForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    void updateGlobalParams(ContextImpl& context);
    CudaPlatform::PlatformData& data;
    int numParticles;
    std::vector<std::string> globalParamNames;
    std::vector<float> globalParamValues;
    System& system;
};

/**
 * This kernel is invoked by GBSAOBCForce to calculate the forces acting on the system.
 */
class CudaCalcGBSAOBCForceKernel : public CalcGBSAOBCForceKernel {
public:
    CudaCalcGBSAOBCForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : CalcGBSAOBCForceKernel(name, platform), data(data) {
    }
    ~CudaCalcGBSAOBCForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the GBSAOBCForce this kernel will be used for
     */
    void initialize(const System& system, const GBSAOBCForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    CudaPlatform::PlatformData& data;
};

/**
 * This kernel is invoked by GBVIForce to calculate the forces acting on the system.
 */
class CudaCalcGBVIForceKernel : public CalcGBVIForceKernel {
public:
    CudaCalcGBVIForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : CalcGBVIForceKernel(name, platform), data(data) {
    }
    ~CudaCalcGBVIForceKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system      the System this kernel will be applied to
     * @param force       the GBVIForce this kernel will be used for
     * @param scaledRadii the scaled radii (Eq. 5 of Labute paper)
     */
    void initialize(const System& system, const GBVIForce& force, const std::vector<double> & scaledRadii);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    CudaPlatform::PlatformData& data;
};

/**
 * This kernel is invoked by CustomExternalForce to calculate the forces acting on the system and the energy of the system.
 */
class CudaCalcCustomExternalForceKernel : public CalcCustomExternalForceKernel {
public:
    CudaCalcCustomExternalForceKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data, System& system) : CalcCustomExternalForceKernel(name, platform),
            data(data), system(system) {
    }
    ~CudaCalcCustomExternalForceKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param force      the CustomExternalForce this kernel will be used for
     */
    void initialize(const System& system, const CustomExternalForce& force);
    /**
     * Execute the kernel to calculate the forces and/or energy.
     *
     * @param context        the context in which to execute this kernel
     * @param includeForces  true if forces should be calculated
     * @param includeEnergy  true if the energy should be calculated
     * @return the potential energy due to the force
     */
    double execute(ContextImpl& context, bool includeForces, bool includeEnergy);
private:
    class ForceInfo;
    void updateGlobalParams(ContextImpl& context);
    int numParticles;
    CudaPlatform::PlatformData& data;
    std::vector<std::string> globalParamNames;
    std::vector<float> globalParamValues;
    System& system;
};

/**
 * This kernel is invoked by VerletIntegrator to take one time step.
 */
class CudaIntegrateVerletStepKernel : public IntegrateVerletStepKernel {
public:
    CudaIntegrateVerletStepKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : IntegrateVerletStepKernel(name, platform), data(data) {
    }
    ~CudaIntegrateVerletStepKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param integrator the VerletIntegrator this kernel will be used for
     */
    void initialize(const System& system, const VerletIntegrator& integrator);
    /**
     * Execute the kernel.
     * 
     * @param context    the context in which to execute this kernel
     * @param integrator the VerletIntegrator this kernel is being used for
     */
    void execute(ContextImpl& context, const VerletIntegrator& integrator);
private:
    CudaPlatform::PlatformData& data;
    double prevStepSize;
};

/**
 * This kernel is invoked by LangevinIntegrator to take one time step.
 */
class CudaIntegrateLangevinStepKernel : public IntegrateLangevinStepKernel {
public:
    CudaIntegrateLangevinStepKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : IntegrateLangevinStepKernel(name, platform), data(data) {
    }
    ~CudaIntegrateLangevinStepKernel();
    /**
     * Initialize the kernel, setting up the particle masses.
     * 
     * @param system     the System this kernel will be applied to
     * @param integrator the LangevinIntegrator this kernel will be used for
     */
    void initialize(const System& system, const LangevinIntegrator& integrator);
    /**
     * Execute the kernel.
     * 
     * @param context    the context in which to execute this kernel
     * @param integrator the LangevinIntegrator this kernel is being used for
     */
    void execute(ContextImpl& context, const LangevinIntegrator& integrator);
private:
    CudaPlatform::PlatformData& data;
    double prevTemp, prevFriction, prevStepSize;
};

/**
 * This kernel is invoked by BrownianIntegrator to take one time step.
 */
class CudaIntegrateBrownianStepKernel : public IntegrateBrownianStepKernel {
public:
    CudaIntegrateBrownianStepKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : IntegrateBrownianStepKernel(name, platform), data(data) {
    }
    ~CudaIntegrateBrownianStepKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param integrator the BrownianIntegrator this kernel will be used for
     */
    void initialize(const System& system, const BrownianIntegrator& integrator);
    /**
     * Execute the kernel.
     * 
     * @param context    the context in which to execute this kernel
     * @param integrator the BrownianIntegrator this kernel is being used for
     */
    void execute(ContextImpl& context, const BrownianIntegrator& integrator);
private:
    CudaPlatform::PlatformData& data;
    double prevTemp, prevFriction, prevStepSize;
};

/**
 * This kernel is invoked by VariableVerletIntegrator to take one time step.
 */
class CudaIntegrateVariableVerletStepKernel : public IntegrateVariableVerletStepKernel {
public:
    CudaIntegrateVariableVerletStepKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : IntegrateVariableVerletStepKernel(name, platform), data(data) {
    }
    ~CudaIntegrateVariableVerletStepKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param integrator the VerletIntegrator this kernel will be used for
     */
    void initialize(const System& system, const VariableVerletIntegrator& integrator);
    /**
     * Execute the kernel.
     *
     * @param context    the context in which to execute this kernel
     * @param integrator the VerletIntegrator this kernel is being used for
     * @param maxTime    the maximum time beyond which the simulation should not be advanced
     * @return the size of the step that was taken
     */
    double execute(ContextImpl& context, const VariableVerletIntegrator& integrator, double maxTime);
private:
    CudaPlatform::PlatformData& data;
    double prevErrorTol;
};

/**
 * This kernel is invoked by VariableLangevinIntegrator to take one time step.
 */
class CudaIntegrateVariableLangevinStepKernel : public IntegrateVariableLangevinStepKernel {
public:
    CudaIntegrateVariableLangevinStepKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : IntegrateVariableLangevinStepKernel(name, platform), data(data) {
    }
    ~CudaIntegrateVariableLangevinStepKernel();
    /**
     * Initialize the kernel, setting up the particle masses.
     *
     * @param system     the System this kernel will be applied to
     * @param integrator the VariableLangevinIntegrator this kernel will be used for
     */
    void initialize(const System& system, const VariableLangevinIntegrator& integrator);
    /**
     * Execute the kernel.
     *
     * @param context    the context in which to execute this kernel
     * @param integrator the VariableLangevinIntegrator this kernel is being used for
     * @param maxTime    the maximum time beyond which the simulation should not be advanced
     * @return the size of the step that was taken
     */
    double execute(ContextImpl& context, const VariableLangevinIntegrator& integrator, double maxTime);
private:
    CudaPlatform::PlatformData& data;
    double prevTemp, prevFriction, prevErrorTol;
};

/**
 * This kernel is invoked by AndersenThermostat at the start of each time step to adjust the particle velocities.
 */
class CudaApplyAndersenThermostatKernel : public ApplyAndersenThermostatKernel {
public:
    CudaApplyAndersenThermostatKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : ApplyAndersenThermostatKernel(name, platform),
            data(data), atomGroups(NULL) {
    }
    ~CudaApplyAndersenThermostatKernel();
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     * @param thermostat the AndersenThermostat this kernel will be used for
     */
    void initialize(const System& system, const AndersenThermostat& thermostat);
    /**
     * Execute the kernel.
     * 
     * @param context    the context in which to execute this kernel
     */
    void execute(ContextImpl& context);
private:
    CudaPlatform::PlatformData& data;
    double prevTemp, prevFrequency, prevStepSize;
    CUDAStream<int>* atomGroups;
};

/**
 * This kernel is invoked by MonteCarloBarostat to adjust the periodic box volume
 */
class CudaApplyMonteCarloBarostatKernel : public ApplyMonteCarloBarostatKernel {
public:
    CudaApplyMonteCarloBarostatKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : ApplyMonteCarloBarostatKernel(name, platform), data(data),
            hasInitializedMolecules(false), moleculeAtoms(NULL), moleculeStartIndex(NULL) {
    }
    ~CudaApplyMonteCarloBarostatKernel();
    /**
     * Initialize the kernel.
     *
     * @param system     the System this kernel will be applied to
     * @param barostat   the MonteCarloBarostat this kernel will be used for
     */
    void initialize(const System& system, const MonteCarloBarostat& barostat);
    /**
     * Attempt a Monte Carlo step, scaling particle positions (or cluster centers) by a specified value.
     * This is called BEFORE the periodic box size is modified.  It should begin by translating each particle
     * or cluster into the first periodic box, so that coordinates will still be correct after the box size
     * is changed.
     *
     * @param context    the context in which to execute this kernel
     * @param scale      the scale factor by which to multiply particle positions
     */
    void scaleCoordinates(ContextImpl& context, double scale);
    /**
     * Reject the most recent Monte Carlo step, restoring the particle positions to where they were before
     * scaleCoordinates() was last called.
     *
     * @param context    the context in which to execute this kernel
     */
    void restoreCoordinates(ContextImpl& context);
private:
    CudaPlatform::PlatformData& data;
    bool hasInitializedMolecules;
    int numMolecules;
    CUDAStream<int>* moleculeAtoms;
    CUDAStream<int>* moleculeStartIndex;
};

/**
 * This kernel is invoked to calculate the kinetic energy of the system.
 */
class CudaCalcKineticEnergyKernel : public CalcKineticEnergyKernel {
public:
    CudaCalcKineticEnergyKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : CalcKineticEnergyKernel(name, platform), data(data) {
    }
    /**
     * Initialize the kernel.
     * 
     * @param system     the System this kernel will be applied to
     */
    void initialize(const System& system);
    /**
     * Execute the kernel.
     * 
     * @param context    the context in which to execute this kernel
     */
    double execute(ContextImpl& context);
private:
    CudaPlatform::PlatformData& data;
    std::vector<double> masses;
};

/**
 * This kernel is invoked to remove center of mass motion from the system.
 */
class CudaRemoveCMMotionKernel : public RemoveCMMotionKernel {
public:
    CudaRemoveCMMotionKernel(std::string name, const Platform& platform, CudaPlatform::PlatformData& data) : RemoveCMMotionKernel(name, platform), data(data) {
    }
    /**
     * Initialize the kernel, setting up the particle masses.
     * 
     * @param system     the System this kernel will be applied to
     * @param force      the CMMotionRemover this kernel will be used for
     */
    void initialize(const System& system, const CMMotionRemover& force);
    /**
     * Execute the kernel.
     * 
     * @param context    the context in which to execute this kernel
     */
    void execute(ContextImpl& context);
private:
    CudaPlatform::PlatformData& data;
};

} // namespace OpenMM

#endif /*OPENMM_CUDAKERNELS_H_*/
