/* -------------------------------------------------------------------------- *
 *                                OpenMMAmoeba                                *
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

#include "openmm/serialization/AmoebaOutOfPlaneBendForceProxy.h"
#include "openmm/serialization/SerializationNode.h"
#include "openmm/Force.h"
#include "openmm/AmoebaOutOfPlaneBendForce.h"
#include <sstream>

using namespace OpenMM;
using namespace std;

AmoebaOutOfPlaneBendForceProxy::AmoebaOutOfPlaneBendForceProxy() : SerializationProxy("AmoebaOutOfPlaneBendForce") {
}

void AmoebaOutOfPlaneBendForceProxy::serialize(const void* object, SerializationNode& node) const {
    node.setIntProperty("version", 1);
    const AmoebaOutOfPlaneBendForce& force = *reinterpret_cast<const AmoebaOutOfPlaneBendForce*>(object);
    node.setDoubleProperty("OutOfPlaneBendCubic",   force.getAmoebaGlobalOutOfPlaneBendCubic());
    node.setDoubleProperty("OutOfPlaneBendQuartic", force.getAmoebaGlobalOutOfPlaneBendQuartic());
    node.setDoubleProperty("OutOfPlaneBendPentic",  force.getAmoebaGlobalOutOfPlaneBendPentic());
    node.setDoubleProperty("OutOfPlaneBendSextic",  force.getAmoebaGlobalOutOfPlaneBendSextic());

    SerializationNode& bonds = node.createChildNode("OutOfPlaneBend").setIntProperty( "size", force.getNumOutOfPlaneBends() );
    for (unsigned int ii = 0; ii < static_cast<unsigned int>(force.getNumOutOfPlaneBends()); ii++) {
        int particle1, particle2, particle3, particle4;
        double k;
        force.getOutOfPlaneBendParameters(ii, particle1, particle2, particle3, particle4, k);
        bonds.createChildNode("OutOfPlaneBend").setIntProperty("p1", particle1).setIntProperty("p2", particle2).setIntProperty("p3", particle3).setIntProperty("p4", particle4).setDoubleProperty("k", k);
    }
}

void* AmoebaOutOfPlaneBendForceProxy::deserialize(const SerializationNode& node) const {
    if (node.getIntProperty("version") != 1)
        throw OpenMMException("Unsupported version number");
    AmoebaOutOfPlaneBendForce* force = new AmoebaOutOfPlaneBendForce();
    try {

        force->setAmoebaGlobalOutOfPlaneBendCubic(node.getDoubleProperty(  "OutOfPlaneBendCubic"));
        force->setAmoebaGlobalOutOfPlaneBendQuartic(node.getDoubleProperty("OutOfPlaneBendQuartic"));
        force->setAmoebaGlobalOutOfPlaneBendPentic(node.getDoubleProperty( "OutOfPlaneBendPentic"));
        force->setAmoebaGlobalOutOfPlaneBendSextic(node.getDoubleProperty( "OutOfPlaneBendSextic"));

        const SerializationNode& bonds = node.getChildNode("OutOfPlaneBend");
        for (unsigned int ii = 0; ii < bonds.getChildren().size(); ii++) {
            const SerializationNode& bond = bonds.getChildren()[ii];
            force->addOutOfPlaneBend(bond.getIntProperty("p1"), bond.getIntProperty("p2"), bond.getIntProperty("p3"),  bond.getIntProperty("p4"), bond.getDoubleProperty("k"));
        }
    }
    catch (...) {
        delete force;
        throw;
    }
    return force;
}
