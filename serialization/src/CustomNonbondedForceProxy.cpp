/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2010 Stanford University and the Authors.           *
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

#include "openmm/serialization/CustomNonbondedForceProxy.h"
#include "openmm/serialization/SerializationNode.h"
#include "openmm/Force.h"
#include "openmm/CustomNonbondedForce.h"
#include <sstream>

using namespace OpenMM;
using namespace std;

CustomNonbondedForceProxy::CustomNonbondedForceProxy() : SerializationProxy("CustomNonbondedForce") {
}

void CustomNonbondedForceProxy::serialize(const void* object, SerializationNode& node) const {
    node.setIntProperty("version", 1);
    const CustomNonbondedForce& force = *reinterpret_cast<const CustomNonbondedForce*>(object);
    node.setStringProperty("energy", force.getEnergyFunction());
    node.setIntProperty("method", (int) force.getNonbondedMethod());
    node.setDoubleProperty("cutoff", force.getCutoffDistance());
    SerializationNode& perParticleParams = node.createChildNode("PerParticleParameters");
    for (int i = 0; i < force.getNumPerParticleParameters(); i++) {
        perParticleParams.createChildNode("Parameter").setStringProperty("name", force.getPerParticleParameterName(i));
    }
    SerializationNode& globalParams = node.createChildNode("GlobalParameters");
    for (int i = 0; i < force.getNumGlobalParameters(); i++) {
        globalParams.createChildNode("Parameter").setStringProperty("name", force.getGlobalParameterName(i)).setDoubleProperty("default", force.getGlobalParameterDefaultValue(i));
    }
    SerializationNode& particles = node.createChildNode("Particles");
    for (int i = 0; i < force.getNumParticles(); i++) {
        vector<double> params;
        force.getParticleParameters(i, params);
        SerializationNode& node = particles.createChildNode("Particle");
        for (int j = 0; j < (int) params.size(); j++) {
            stringstream key;
            key << "param";
            key << j+1;
            node.setDoubleProperty(key.str(), params[j]);
        }
    }
    SerializationNode& exclusions = node.createChildNode("Exclusions");
    for (int i = 0; i < force.getNumExclusions(); i++) {
        int particle1, particle2;
        force.getExclusionParticles(i, particle1, particle2);
        exclusions.createChildNode("Exclusion").setIntProperty("p1", particle1).setIntProperty("p2", particle2);
    }
    SerializationNode& functions = node.createChildNode("Functions");
    for (int i = 0; i < force.getNumFunctions(); i++) {
        string name;
        vector<double> values;
        double min, max;
        force.getFunctionParameters(i, name, values, min, max);
        SerializationNode& node = functions.createChildNode("Function").setStringProperty("name", name).setDoubleProperty("min", min).setDoubleProperty("max", max);
        SerializationNode& valuesNode = node.createChildNode("Values");
        for (int j = 0; j < (int) values.size(); j++)
            valuesNode.createChildNode("Value").setDoubleProperty("v", values[j]);
    }
}

void* CustomNonbondedForceProxy::deserialize(const SerializationNode& node) const {
    if (node.getIntProperty("version") != 1)
        throw OpenMMException("Unsupported version number");
    CustomNonbondedForce* force = NULL;
    try {
        CustomNonbondedForce* force = new CustomNonbondedForce(node.getStringProperty("energy"));
        force->setNonbondedMethod((CustomNonbondedForce::NonbondedMethod) node.getIntProperty("method"));
        force->setCutoffDistance(node.getDoubleProperty("cutoff"));
        const SerializationNode& perParticleParams = node.getChildNode("PerParticleParameters");
        for (int i = 0; i < (int) perParticleParams.getChildren().size(); i++) {
            const SerializationNode& parameter = perParticleParams.getChildren()[i];
            force->addPerParticleParameter(parameter.getStringProperty("name"));
        }
        const SerializationNode& globalParams = node.getChildNode("GlobalParameters");
        for (int i = 0; i < (int) globalParams.getChildren().size(); i++) {
            const SerializationNode& parameter = globalParams.getChildren()[i];
            force->addGlobalParameter(parameter.getStringProperty("name"), parameter.getDoubleProperty("default"));
        }
        const SerializationNode& particles = node.getChildNode("Particles");
        vector<double> params(force->getNumPerParticleParameters());
        for (int i = 0; i < (int) particles.getChildren().size(); i++) {
            const SerializationNode& particle = particles.getChildren()[i];
            for (int j = 0; j < (int) params.size(); j++) {
                stringstream key;
                key << "param";
                key << j+1;
                params[j] = particle.getDoubleProperty(key.str());
            }
            force->addParticle(params);
        }
        const SerializationNode& exclusions = node.getChildNode("Exclusions");
        for (int i = 0; i < (int) exclusions.getChildren().size(); i++) {
            const SerializationNode& exclusion = exclusions.getChildren()[i];
            force->addExclusion(exclusion.getIntProperty("p1"), exclusion.getIntProperty("p2"));
        }
        const SerializationNode& functions = node.getChildNode("Functions");
        for (int i = 0; i < (int) functions.getChildren().size(); i++) {
            const SerializationNode& function = functions.getChildren()[i];
            const SerializationNode& valuesNode = function.getChildNode("Values");
            vector<double> values;
            for (int j = 0; j < (int) valuesNode.getChildren().size(); j++)
                values.push_back(valuesNode.getChildren()[j].getDoubleProperty("v"));
            force->addFunction(function.getStringProperty("name"), values, function.getDoubleProperty("min"), function.getDoubleProperty("max"));
        }
        return force;
    }
    catch (...) {
        if (force != NULL)
            delete force;
        throw;
    }
}
