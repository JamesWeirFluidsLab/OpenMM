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

#include "openmm/serialization/CustomAngleForceProxy.h"
#include "openmm/serialization/SerializationNode.h"
#include "openmm/Force.h"
#include "openmm/CustomAngleForce.h"
#include <sstream>

using namespace OpenMM;
using namespace std;

CustomAngleForceProxy::CustomAngleForceProxy() : SerializationProxy("CustomAngleForce") {
}

void CustomAngleForceProxy::serialize(const void* object, SerializationNode& node) const {
    node.setIntProperty("version", 1);
    const CustomAngleForce& force = *reinterpret_cast<const CustomAngleForce*>(object);
    node.setStringProperty("energy", force.getEnergyFunction());
    SerializationNode& perAngleParams = node.createChildNode("PerAngleParameters");
    for (int i = 0; i < force.getNumPerAngleParameters(); i++) {
        perAngleParams.createChildNode("Parameter").setStringProperty("name", force.getPerAngleParameterName(i));
    }
    SerializationNode& globalParams = node.createChildNode("GlobalParameters");
    for (int i = 0; i < force.getNumGlobalParameters(); i++) {
        globalParams.createChildNode("Parameter").setStringProperty("name", force.getGlobalParameterName(i)).setDoubleProperty("default", force.getGlobalParameterDefaultValue(i));
    }
    SerializationNode& angles = node.createChildNode("Angles");
    for (int i = 0; i < force.getNumAngles(); i++) {
        int p1, p2, p3;
        vector<double> params;
        force.getAngleParameters(i, p1, p2, p3, params);
        SerializationNode& node = angles.createChildNode("Angle").setIntProperty("p1", p1).setIntProperty("p2", p2).setIntProperty("p3", p3);
        for (int j = 0; j < (int) params.size(); j++) {
            stringstream key;
            key << "param";
            key << j+1;
            node.setDoubleProperty(key.str(), params[j]);
        }
    }
}

void* CustomAngleForceProxy::deserialize(const SerializationNode& node) const {
    if (node.getIntProperty("version") != 1)
        throw OpenMMException("Unsupported version number");
    CustomAngleForce* force = NULL;
    try {
        CustomAngleForce* force = new CustomAngleForce(node.getStringProperty("energy"));
        const SerializationNode& perAngleParams = node.getChildNode("PerAngleParameters");
        for (int i = 0; i < (int) perAngleParams.getChildren().size(); i++) {
            const SerializationNode& parameter = perAngleParams.getChildren()[i];
            force->addPerAngleParameter(parameter.getStringProperty("name"));
        }
        const SerializationNode& globalParams = node.getChildNode("GlobalParameters");
        for (int i = 0; i < (int) globalParams.getChildren().size(); i++) {
            const SerializationNode& parameter = globalParams.getChildren()[i];
            force->addGlobalParameter(parameter.getStringProperty("name"), parameter.getDoubleProperty("default"));
        }
        const SerializationNode& angles = node.getChildNode("Angles");
        vector<double> params(force->getNumPerAngleParameters());
        for (int i = 0; i < (int) angles.getChildren().size(); i++) {
            const SerializationNode& angle = angles.getChildren()[i];
            for (int j = 0; j < (int) params.size(); j++) {
                stringstream key;
                key << "param";
                key << j+1;
                params[j] = angle.getDoubleProperty(key.str());
            }
            force->addAngle(angle.getIntProperty("p1"), angle.getIntProperty("p2"), angle.getIntProperty("p3"), params);
        }
        return force;
    }
    catch (...) {
        if (force != NULL)
            delete force;
        throw;
    }
}
