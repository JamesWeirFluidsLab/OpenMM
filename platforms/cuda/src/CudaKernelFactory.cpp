/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008 Stanford University and the Authors.           *
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

#include "CudaKernelFactory.h"
#include "CudaKernels.h"
#include "openmm/internal/ContextImpl.h"
#include "openmm/OpenMMException.h"

using namespace OpenMM;

OPENMMCUDA_EXPORT KernelImpl* CudaKernelFactory::createKernelImpl(std::string name, const Platform& platform, ContextImpl& context) const {
    CudaPlatform::PlatformData& data = *static_cast<CudaPlatform::PlatformData*>(context.getPlatformData());
    if (name == CalcForcesAndEnergyKernel::Name())
        return new CudaCalcForcesAndEnergyKernel(name, platform, data);
    if (name == UpdateStateDataKernel::Name())
        return new CudaUpdateStateDataKernel(name, platform, data);
    if (name == ApplyConstraintsKernel::Name())
        return new CudaApplyConstraintsKernel(name, platform, data);
    if (name == VirtualSitesKernel::Name())
        return new CudaVirtualSitesKernel(name, platform);
    if (name == CalcHarmonicBondForceKernel::Name())
        return new CudaCalcHarmonicBondForceKernel(name, platform, data, context.getSystem());
    if (name == CalcCustomBondForceKernel::Name())
        return new CudaCalcCustomBondForceKernel(name, platform, data, context.getSystem());
    if (name == CalcHarmonicAngleForceKernel::Name())
        return new CudaCalcHarmonicAngleForceKernel(name, platform, data, context.getSystem());
    if (name == CalcCustomAngleForceKernel::Name())
        return new CudaCalcCustomAngleForceKernel(name, platform, data, context.getSystem());
    if (name == CalcPeriodicTorsionForceKernel::Name())
        return new CudaCalcPeriodicTorsionForceKernel(name, platform, data, context.getSystem());
    if (name == CalcRBTorsionForceKernel::Name())
        return new CudaCalcRBTorsionForceKernel(name, platform, data, context.getSystem());
    if (name == CalcCMAPTorsionForceKernel::Name())
        return new CudaCalcCMAPTorsionForceKernel(name, platform, data, context.getSystem());
    if (name == CalcCustomTorsionForceKernel::Name())
        return new CudaCalcCustomTorsionForceKernel(name, platform, data, context.getSystem());
    if (name == CalcNonbondedForceKernel::Name())
        return new CudaCalcNonbondedForceKernel(name, platform, data, context.getSystem());
    if (name == CalcCustomNonbondedForceKernel::Name())
        return new CudaCalcCustomNonbondedForceKernel(name, platform, data, context.getSystem());
    if (name == CalcGBSAOBCForceKernel::Name())
        return new CudaCalcGBSAOBCForceKernel(name, platform, data);
    if (name == CalcGBVIForceKernel::Name())
        return new CudaCalcGBVIForceKernel(name, platform, data);
    if (name == CalcCustomExternalForceKernel::Name())
        return new CudaCalcCustomExternalForceKernel(name, platform, data, context.getSystem());
    if (name == IntegrateVerletStepKernel::Name())
        return new CudaIntegrateVerletStepKernel(name, platform, data);
    if (name == IntegrateLangevinStepKernel::Name())
        return new CudaIntegrateLangevinStepKernel(name, platform, data);
    if (name == IntegrateBrownianStepKernel::Name())
        return new CudaIntegrateBrownianStepKernel(name, platform, data);
    if (name == IntegrateVariableVerletStepKernel::Name())
        return new CudaIntegrateVariableVerletStepKernel(name, platform, data);
    if (name == IntegrateVariableLangevinStepKernel::Name())
        return new CudaIntegrateVariableLangevinStepKernel(name, platform, data);
    if (name == ApplyAndersenThermostatKernel::Name())
        return new CudaApplyAndersenThermostatKernel(name, platform, data);
    if (name == ApplyMonteCarloBarostatKernel::Name())
        return new CudaApplyMonteCarloBarostatKernel(name, platform, data);
    if (name == CalcKineticEnergyKernel::Name())
        return new CudaCalcKineticEnergyKernel(name, platform, data);
    if (name == RemoveCMMotionKernel::Name())
        return new CudaRemoveCMMotionKernel(name, platform, data);
    throw OpenMMException((std::string("Tried to create kernel with illegal kernel name '")+name+"'").c_str());
}
