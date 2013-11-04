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

#include "openmm/serialization/PeriodicTorsionForceProxy.h"
#include "openmm/serialization/SerializationNode.h"
#include "openmm/Force.h"
#include "openmm/PeriodicTorsionForce.h"
#include <sstream>

using namespace OpenMM;
using namespace std;

PeriodicTorsionForceProxy::PeriodicTorsionForceProxy() : SerializationProxy("PeriodicTorsionForce") {
}

void PeriodicTorsionForceProxy::serialize(const void* object, SerializationNode& node) const {
    node.setIntProperty("version", 1);
    const PeriodicTorsionForce& force = *reinterpret_cast<const PeriodicTorsionForce*>(object);
    SerializationNode& torsions = node.createChildNode("Torsions");
    for (int i = 0; i < force.getNumTorsions(); i++) {
        int particle1, particle2, particle3, particle4, periodicity;
        double phase, k;
        force.getTorsionParameters(i, particle1, particle2, particle3, particle4, periodicity, phase, k);
        torsions.createChildNode("Torsion").setIntProperty("p1", particle1).setIntProperty("p2", particle2).setIntProperty("p3", particle3).setIntProperty("p4", particle4).setIntProperty("periodicity", periodicity).setDoubleProperty("phase", phase).setDoubleProperty("k", k);
    }
}

void* PeriodicTorsionForceProxy::deserialize(const SerializationNode& node) const {
    if (node.getIntProperty("version") != 1)
        throw OpenMMException("Unsupported version number");
    PeriodicTorsionForce* force = new PeriodicTorsionForce();
    try {
        const SerializationNode& torsions = node.getChildNode("Torsions");
        for (int i = 0; i < (int) torsions.getChildren().size(); i++) {
            const SerializationNode& torsion = torsions.getChildren()[i];
            force->addTorsion(torsion.getIntProperty("p1"), torsion.getIntProperty("p2"), torsion.getIntProperty("p3"), torsion.getIntProperty("p4"),
                    torsion.getIntProperty("periodicity"), torsion.getDoubleProperty("phase"), torsion.getDoubleProperty("k"));
        }
    }
    catch (...) {
        delete force;
        throw;
    }
    return force;
}
