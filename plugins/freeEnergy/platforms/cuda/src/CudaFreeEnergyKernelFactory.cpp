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

#include "CudaFreeEnergyKernelFactory.h"
#include "CudaFreeEnergyKernels.h"
#include "openmm/freeEnergyKernels.h"
#include "FreeEnergyCudaData.h"
#include "openmm/internal/ContextImpl.h"
#include "openmm/OpenMMException.h"
#include "kernels/GpuFreeEnergyCudaKernels.h"

using namespace OpenMM;

extern "C" void registerPlatforms() {
}

extern "C" void registerKernelFactories() {
    // (void) fprintf( stderr, "initOpenMMCudaFreeEnergyPlugin called\n");
    if ( gpuIsAvailableSoftcore() ){
        for( int ii = 0; ii < Platform::getNumPlatforms(); ii++ ){
            Platform& platform = Platform::getPlatform(ii);
            if( platform.getName().compare( "Cuda" ) == 0 ){
                 CudaFreeEnergyKernelFactory* factory = new CudaFreeEnergyKernelFactory();
                 platform.registerKernelFactory(CalcNonbondedSoftcoreForceKernel::Name(), factory);
                 platform.registerKernelFactory(CalcGBSAOBCSoftcoreForceKernel::Name(), factory);
                 platform.registerKernelFactory(CalcGBVISoftcoreForceKernel::Name(), factory);
            }
        }
    }   
}

extern "C" OPENMMCUDA_EXPORT void registerFreeEnergyCudaKernelFactories( void ) { 
    int hasCudaPlatform = 0;
    for( int ii = 0; ii < Platform::getNumPlatforms() && hasCudaPlatform == 0; ii++ ){
        Platform& platform = Platform::getPlatform(ii);
        if( platform.getName() == "Cuda" ){
            hasCudaPlatform = 1;
        }   
    }   
    if( hasCudaPlatform == 0 ){
        if (gpuIsAvailable() ){
            Platform::registerPlatform(new CudaPlatform());
        }   
    }   
    registerKernelFactories();
}

static std::map<ContextImpl*, FreeEnergyCudaData*> contextToFreeEnergyDataMap;

// look up FreeEnergyCudaData for input contextImpl in contextToFreeEnergyDataMap

extern "C" void* getFreeEnergyCudaData( ContextImpl& context ) { 
    std::map<ContextImpl*, FreeEnergyCudaData*>::const_iterator mapIterator  = contextToFreeEnergyDataMap.find(&context);
    if( mapIterator == contextToFreeEnergyDataMap.end() ){
        return NULL;
    } else {
        return static_cast<void*>(mapIterator->second);
    }   
}

// remove FreeEnergyCudaData from contextToFreeEnergyDataMap

extern "C" void removeFreeEnergyCudaDataFromContextMap( void* inputContext ) { 
    ContextImpl* context = static_cast<ContextImpl*>(inputContext);
    contextToFreeEnergyDataMap.erase( context );
    return;
}

KernelImpl* CudaFreeEnergyKernelFactory::createKernelImpl(std::string name, const Platform& platform, ContextImpl& context) const {

    // create FreeEnergyCudaData object if contextToFreeEnergyDataMap does not contain
    // key equal to current context

    FreeEnergyCudaData* freeEnergyCudaData;
    std::map<ContextImpl*, FreeEnergyCudaData*>::const_iterator mapIterator  = contextToFreeEnergyDataMap.find(&context);

    if( mapIterator == contextToFreeEnergyDataMap.end() ){
        CudaPlatform::PlatformData& cudaPlatformData = *static_cast<CudaPlatform::PlatformData*>(context.getPlatformData());
        freeEnergyCudaData                           = new FreeEnergyCudaData( cudaPlatformData );
        contextToFreeEnergyDataMap[&context]         = freeEnergyCudaData;
        //freeEnergyCudaData->setLog( stderr );
        freeEnergyCudaData->setContextImpl( static_cast<void*>(&context) );
    } else {
        freeEnergyCudaData                           = mapIterator->second;
    }

    if (name == CalcNonbondedSoftcoreForceKernel::Name())
        return new CudaFreeEnergyCalcNonbondedSoftcoreForceKernel(name, platform, *freeEnergyCudaData, context.getSystem());

    if (name == CalcGBSAOBCSoftcoreForceKernel::Name())
        return new CudaFreeEnergyCalcGBSAOBCSoftcoreForceKernel(name, platform, *freeEnergyCudaData);

    if (name == CalcGBVISoftcoreForceKernel::Name())
        return new CudaFreeEnergyCalcGBVISoftcoreForceKernel(name, platform, *freeEnergyCudaData);

    throw OpenMMException( (std::string("Tried to create kernel with illegal kernel name '") + name + "'").c_str() );
}
