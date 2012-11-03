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

#include "ReferenceFreeEnergyKernelFactory.h"
#include "ReferenceFreeEnergyKernels.h"
#include "openmm/internal/ContextImpl.h"
#include "openmm/OpenMMException.h"

using namespace OpenMM;

#if defined(WIN32)
    #include <windows.h>
    extern "C" void initFreeEnergyReferenceKernels();
    BOOL WINAPI DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
        if (ul_reason_for_call == DLL_PROCESS_ATTACH)
            initFreeEnergyReferenceKernels();
        return TRUE;
    }
#else
    extern "C" void __attribute__((constructor)) initFreeEnergyReferenceKernels();
#endif

extern "C" void initFreeEnergyReferenceKernels() {
    for( int ii = 0; ii < Platform::getNumPlatforms(); ii++ ){
        Platform& platform = Platform::getPlatform(ii);
        if( platform.getName().compare( "Reference" ) == 0 ){
            ReferenceFreeEnergyKernelFactory* factory  = new ReferenceFreeEnergyKernelFactory();
            platform.registerKernelFactory(CalcNonbondedSoftcoreForceKernel::Name(), factory);
            platform.registerKernelFactory(CalcGBSAOBCSoftcoreForceKernel::Name(), factory);
            platform.registerKernelFactory(CalcGBVISoftcoreForceKernel::Name(), factory);
        }
    }   
}

KernelImpl* ReferenceFreeEnergyKernelFactory::createKernelImpl(std::string name, const Platform& platform, ContextImpl& context) const {
    ReferencePlatform::PlatformData& data = *static_cast<ReferencePlatform::PlatformData*>(context.getPlatformData());

    if (name == CalcNonbondedSoftcoreForceKernel::Name())
        return new ReferenceFreeEnergyCalcNonbondedSoftcoreForceKernel(name, platform);

    if (name == CalcGBSAOBCSoftcoreForceKernel::Name())
        return new ReferenceFreeEnergyCalcGBSAOBCSoftcoreForceKernel(name, platform);

    if (name == CalcGBVISoftcoreForceKernel::Name())
        return new ReferenceFreeEnergyCalcGBVISoftcoreForceKernel(name, platform);

    throw OpenMMException( (std::string("Tried to create kernel with illegal kernel name '") + name + "'").c_str() );
}
