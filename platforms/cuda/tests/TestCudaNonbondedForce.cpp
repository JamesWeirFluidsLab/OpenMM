/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2010 Stanford University and the Authors.      *
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

/**
 * This tests all the different force terms in the reference implementation of NonbondedForce.
 */

#include "openmm/internal/AssertionUtilities.h"
#include "openmm/Context.h"
#include "CudaPlatform.h"
#include "ReferencePlatform.h"
#include "openmm/HarmonicBondForce.h"
#include "openmm/NonbondedForce.h"
#include "openmm/System.h"
#include "openmm/LangevinIntegrator.h"
#include "openmm/VerletIntegrator.h"
#include "openmm/internal/ContextImpl.h"
#include "kernels/gputypes.h"
#include "../src/SimTKUtilities/SimTKOpenMMRealType.h"
#include "sfmt/SFMT.h"
#include <iostream>
#include <vector>

using namespace OpenMM;
using namespace std;

const double TOL = 1e-5;

void testCoulomb() {
    CudaPlatform platform;
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    LangevinIntegrator integrator(0.0, 0.1, 0.01);
    NonbondedForce* forceField = new NonbondedForce();
    forceField->addParticle(0.5, 1, 0);
    forceField->addParticle(-1.5, 1, 0);
    system.addForce(forceField);
    Context context(system, integrator, platform);
    vector<Vec3> positions(2);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(2, 0, 0);
    context.setPositions(positions);
    State state = context.getState(State::Forces | State::Energy);
    const vector<Vec3>& forces = state.getForces();
    double force = ONE_4PI_EPS0*(-0.75)/4.0;
    ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces[0], TOL);
    ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces[1], TOL);
    ASSERT_EQUAL_TOL(ONE_4PI_EPS0*(-0.75)/2.0, state.getPotentialEnergy(), TOL);
}

void testLJ() {
    CudaPlatform platform;
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    LangevinIntegrator integrator(0.0, 0.1, 0.01);
    NonbondedForce* forceField = new NonbondedForce();
    forceField->addParticle(0, 1.2, 1);
    forceField->addParticle(0, 1.4, 2);
    system.addForce(forceField);
    Context context(system, integrator, platform);
    vector<Vec3> positions(2);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(2, 0, 0);
    context.setPositions(positions);
    State state = context.getState(State::Forces | State::Energy);
    const vector<Vec3>& forces = state.getForces();
    double x = 1.3/2.0;
    double eps = SQRT_TWO;
    double force = 4.0*eps*(12*std::pow(x, 12.0)-6*std::pow(x, 6.0))/2.0;
    ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces[0], TOL);
    ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces[1], TOL);
    ASSERT_EQUAL_TOL(4.0*eps*(std::pow(x, 12.0)-std::pow(x, 6.0)), state.getPotentialEnergy(), TOL);
}

void testExclusionsAnd14() {
    CudaPlatform platform;
    System system;
    NonbondedForce* nonbonded = new NonbondedForce();
    for (int i = 0; i < 5; ++i) {
        system.addParticle(1.0);
        nonbonded->addParticle(0, 1.5, 0);
    }
    vector<pair<int, int> > bonds;
    bonds.push_back(pair<int, int>(0, 1));
    bonds.push_back(pair<int, int>(1, 2));
    bonds.push_back(pair<int, int>(2, 3));
    bonds.push_back(pair<int, int>(3, 4));
    nonbonded->createExceptionsFromBonds(bonds, 0.0, 0.0);
    int first14, second14;
    for (int i = 0; i < nonbonded->getNumExceptions(); i++) {
        int particle1, particle2;
        double chargeProd, sigma, epsilon;
        nonbonded->getExceptionParameters(i, particle1, particle2, chargeProd, sigma, epsilon);
        if ((particle1 == 0 && particle2 == 3) || (particle1 == 3 && particle2 == 0))
            first14 = i;
        if ((particle1 == 1 && particle2 == 4) || (particle1 == 4 && particle2 == 1))
            second14 = i;
    }
    system.addForce(nonbonded);
    for (int i = 1; i < 5; ++i) {
 
        // Test LJ forces

        vector<Vec3> positions(5);
        const double r = 1.0;
        for (int j = 0; j < 5; ++j) {
            nonbonded->setParticleParameters(j, 0, 1.5, 0);
            positions[j] = Vec3(0, j, 0);
        }
        nonbonded->setParticleParameters(0, 0, 1.5, 1);
        nonbonded->setParticleParameters(i, 0, 1.5, 1);
        nonbonded->setExceptionParameters(first14, 0, 3, 0, 1.5, i == 3 ? 0.5 : 0.0);
        nonbonded->setExceptionParameters(second14, 1, 4, 0, 1.5, 0.0);
        positions[i] = Vec3(r, 0, 0);
        // The following is in its own block, because CUDA can't deal with multiple Contexts
        // existing on the same thread at the same time.
        {
            LangevinIntegrator integrator(0.0, 0.1, 0.01);
            Context context(system, integrator, platform);
            context.setPositions(positions);
            State state = context.getState(State::Forces | State::Energy);
            const vector<Vec3>& forces = state.getForces();
            double x = 1.5/r;
            double eps = 1.0;
            double force = 4.0*eps*(12*std::pow(x, 12.0)-6*std::pow(x, 6.0))/r;
            double energy = 4.0*eps*(std::pow(x, 12.0)-std::pow(x, 6.0));
            if (i == 3) {
                force *= 0.5;
                energy *= 0.5;
            }
            if (i < 3) {
                force = 0;
                energy = 0;
            }
            ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces[0], TOL);
            ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces[i], TOL);
            ASSERT_EQUAL_TOL(energy, state.getPotentialEnergy(), TOL);
        }

        // Test Coulomb forces

        {
            nonbonded->setParticleParameters(0, 2, 1.5, 0);
            nonbonded->setParticleParameters(i, 2, 1.5, 0);
            nonbonded->setExceptionParameters(first14, 0, 3, i == 3 ? 4/1.2 : 0, 1.5, 0);
            nonbonded->setExceptionParameters(second14, 1, 4, 0, 1.5, 0);
            LangevinIntegrator integrator(0.0, 0.1, 0.01);
            Context context(system, integrator, platform);
            context.setPositions(positions);
            State state = context.getState(State::Forces | State::Energy);
            const vector<Vec3>& forces2 = state.getForces();
            double force = ONE_4PI_EPS0*4/(r*r);
            double energy = ONE_4PI_EPS0*4/r;
            if (i == 3) {
                force /= 1.2;
                energy /= 1.2;
            }
            if (i < 3) {
                force = 0;
                energy = 0;
            }
            ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces2[0], TOL);
            ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces2[i], TOL);
            ASSERT_EQUAL_TOL(energy, state.getPotentialEnergy(), TOL);
        }
    }
}

void testCutoff() {
    CudaPlatform platform;
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    system.addParticle(1.0);
    LangevinIntegrator integrator(0.0, 0.1, 0.01);
    NonbondedForce* forceField = new NonbondedForce();
    forceField->addParticle(1.0, 1, 0);
    forceField->addParticle(1.0, 1, 0);
    forceField->addParticle(1.0, 1, 0);
    forceField->setNonbondedMethod(NonbondedForce::CutoffNonPeriodic);
    const double cutoff = 2.9;
    forceField->setCutoffDistance(cutoff);
    const double eps = 50.0;
    forceField->setReactionFieldDielectric(eps);
    system.addForce(forceField);
    Context context(system, integrator, platform);
    vector<Vec3> positions(3);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(0, 2, 0);
    positions[2] = Vec3(0, 3, 0);
    context.setPositions(positions);
    State state = context.getState(State::Forces | State::Energy);
    const vector<Vec3>& forces = state.getForces();
    const double krf = (1.0/(cutoff*cutoff*cutoff))*(eps-1.0)/(2.0*eps+1.0);
    const double crf = (1.0/cutoff)*(3.0*eps)/(2.0*eps+1.0);
    const double force1 = ONE_4PI_EPS0*(1.0)*(0.25-2.0*krf*2.0);
    const double force2 = ONE_4PI_EPS0*(1.0)*(1.0-2.0*krf*1.0);
    ASSERT_EQUAL_VEC(Vec3(0, -force1, 0), forces[0], TOL);
    ASSERT_EQUAL_VEC(Vec3(0, force1-force2, 0), forces[1], TOL);
    ASSERT_EQUAL_VEC(Vec3(0, force2, 0), forces[2], TOL);
    const double energy1 = ONE_4PI_EPS0*(1.0)*(0.5+krf*4.0-crf);
    const double energy2 = ONE_4PI_EPS0*(1.0)*(1.0+krf*1.0-crf);
    ASSERT_EQUAL_TOL(energy1+energy2, state.getPotentialEnergy(), TOL);
}

void testCutoff14() {
    CudaPlatform platform;
    System system;
    LangevinIntegrator integrator(0.0, 0.1, 0.01);
    NonbondedForce* nonbonded = new NonbondedForce();
    nonbonded->setNonbondedMethod(NonbondedForce::CutoffNonPeriodic);
    for (int i = 0; i < 5; ++i) {
        system.addParticle(1.0);
        nonbonded->addParticle(0, 1.5, 0);
    }
    const double cutoff = 3.5;
    nonbonded->setCutoffDistance(cutoff);
    const double eps = 30.0;
    nonbonded->setReactionFieldDielectric(eps);
    vector<pair<int, int> > bonds;
    bonds.push_back(pair<int, int>(0, 1));
    bonds.push_back(pair<int, int>(1, 2));
    bonds.push_back(pair<int, int>(2, 3));
    bonds.push_back(pair<int, int>(3, 4));
    nonbonded->createExceptionsFromBonds(bonds, 0.0, 0.0);
    int first14, second14;
    for (int i = 0; i < nonbonded->getNumExceptions(); i++) {
        int particle1, particle2;
        double chargeProd, sigma, epsilon;
        nonbonded->getExceptionParameters(i, particle1, particle2, chargeProd, sigma, epsilon);
        if ((particle1 == 0 && particle2 == 3) || (particle1 == 3 && particle2 == 0))
            first14 = i;
        if ((particle1 == 1 && particle2 == 4) || (particle1 == 4 && particle2 == 1))
            second14 = i;
    }
    system.addForce(nonbonded);
    Context context(system, integrator, platform);
    vector<Vec3> positions(5);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(1, 0, 0);
    positions[2] = Vec3(2, 0, 0);
    positions[3] = Vec3(3, 0, 0);
    positions[4] = Vec3(4, 0, 0);
    for (int i = 1; i < 5; ++i) {
 
        // Test LJ forces
        
        nonbonded->setParticleParameters(0, 0, 1.5, 1);
        for (int j = 1; j < 5; ++j)
            nonbonded->setParticleParameters(j, 0, 1.5, 0);
        nonbonded->setParticleParameters(i, 0, 1.5, 1);
        nonbonded->setExceptionParameters(first14, 0, 3, 0, 1.5, i == 3 ? 0.5 : 0.0);
        nonbonded->setExceptionParameters(second14, 1, 4, 0, 1.5, 0.0);
        context.reinitialize();
        context.setPositions(positions);
        State state = context.getState(State::Forces | State::Energy);
        const vector<Vec3>& forces = state.getForces();
        double r = positions[i][0];
        double x = 1.5/r;
        double e = 1.0;
        double force = 4.0*e*(12*std::pow(x, 12.0)-6*std::pow(x, 6.0))/r;
        double energy = 4.0*e*(std::pow(x, 12.0)-std::pow(x, 6.0));
        if (i == 3) {
            force *= 0.5;
            energy *= 0.5;
        }
        if (i < 3 || r > cutoff) {
            force = 0;
            energy = 0;
        }
        ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces[0], TOL);
        ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces[i], TOL);
        ASSERT_EQUAL_TOL(energy, state.getPotentialEnergy(), TOL);

        // Test Coulomb forces
        
        const double q = 0.7;
        nonbonded->setParticleParameters(0, q, 1.5, 0);
        nonbonded->setParticleParameters(i, q, 1.5, 0);
        nonbonded->setExceptionParameters(first14, 0, 3, i == 3 ? q*q/1.2 : 0, 1.5, 0);
        nonbonded->setExceptionParameters(second14, 1, 4, 0, 1.5, 0);
        context.reinitialize();
        context.setPositions(positions);
        state = context.getState(State::Forces | State::Energy);
        const vector<Vec3>& forces2 = state.getForces();
        force = ONE_4PI_EPS0*q*q/(r*r);
        energy = ONE_4PI_EPS0*q*q/r;
        if (i == 3) {
            force /= 1.2;
            energy /= 1.2;
        }
        if (i < 3 || r > cutoff) {
            force = 0;
            energy = 0;
        }
        ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces2[0], TOL);
        ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces2[i], TOL);
        ASSERT_EQUAL_TOL(energy, state.getPotentialEnergy(), TOL);
    }
}

void testPeriodic() {
    CudaPlatform platform;
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    system.addParticle(1.0);
    LangevinIntegrator integrator(0.0, 0.1, 0.01);
    NonbondedForce* nonbonded = new NonbondedForce();
    nonbonded->addParticle(1.0, 1, 0);
    nonbonded->addParticle(1.0, 1, 0);
    nonbonded->addParticle(1.0, 1, 0);
    nonbonded->addException(0, 1, 0.0, 1.0, 0.0);
    nonbonded->setNonbondedMethod(NonbondedForce::CutoffPeriodic);
    const double cutoff = 2.0;
    nonbonded->setCutoffDistance(cutoff);
    system.setDefaultPeriodicBoxVectors(Vec3(4, 0, 0), Vec3(0, 4, 0), Vec3(0, 0, 4));
    system.addForce(nonbonded);
    Context context(system, integrator, platform);
    vector<Vec3> positions(3);
    positions[0] = Vec3(0, 0, 0);
    positions[1] = Vec3(2, 0, 0);
    positions[2] = Vec3(3, 0, 0);
    context.setPositions(positions);
    State state = context.getState(State::Forces | State::Energy);
    const vector<Vec3>& forces = state.getForces();
    const double eps = 78.3;
    const double krf = (1.0/(cutoff*cutoff*cutoff))*(eps-1.0)/(2.0*eps+1.0);
    const double crf = (1.0/cutoff)*(3.0*eps)/(2.0*eps+1.0);
    const double force = ONE_4PI_EPS0*(1.0)*(1.0-2.0*krf*1.0);
    ASSERT_EQUAL_VEC(Vec3(force, 0, 0), forces[0], TOL);
    ASSERT_EQUAL_VEC(Vec3(-force, 0, 0), forces[1], TOL);
    ASSERT_EQUAL_VEC(Vec3(0, 0, 0), forces[2], TOL);
    ASSERT_EQUAL_TOL(2*ONE_4PI_EPS0*(1.0)*(1.0+krf*1.0-crf), state.getPotentialEnergy(), TOL);
}


void testLargeSystem() {
    const int numMolecules = 600;
    const int numParticles = numMolecules*2;
    const double cutoff = 2.0;
    const double boxSize = 20.0;
    const double tol = 2e-3;
    CudaPlatform cuda;
    ReferencePlatform reference;
    System system;
    for (int i = 0; i < numParticles; i++)
        system.addParticle(1.0);
    NonbondedForce* nonbonded = new NonbondedForce();
    HarmonicBondForce* bonds = new HarmonicBondForce();
    vector<Vec3> positions(numParticles);
    vector<Vec3> velocities(numParticles);
    OpenMM_SFMT::SFMT sfmt;
    init_gen_rand(0, sfmt);

    for (int i = 0; i < numMolecules; i++) {
        if (i < numMolecules/2) {
            nonbonded->addParticle(-1.0, 0.2, 0.1);
            nonbonded->addParticle(1.0, 0.1, 0.1);
        }
        else {
            nonbonded->addParticle(-1.0, 0.2, 0.2);
            nonbonded->addParticle(1.0, 0.1, 0.2);
        }
        positions[2*i] = Vec3(boxSize*genrand_real2(sfmt), boxSize*genrand_real2(sfmt), boxSize*genrand_real2(sfmt));
        positions[2*i+1] = Vec3(positions[2*i][0]+1.0, positions[2*i][1], positions[2*i][2]);
        velocities[2*i] = Vec3(genrand_real2(sfmt), genrand_real2(sfmt), genrand_real2(sfmt));
        velocities[2*i+1] = Vec3(genrand_real2(sfmt), genrand_real2(sfmt), genrand_real2(sfmt));
        bonds->addBond(2*i, 2*i+1, 1.0, 0.1);
        nonbonded->addException(2*i, 2*i+1, 0.0, 0.15, 0.0);
    }

    // Try with cutoffs but not periodic boundary conditions, and make sure the Cuda and Reference
    // platforms agree.

    nonbonded->setNonbondedMethod(NonbondedForce::CutoffNonPeriodic);
    nonbonded->setCutoffDistance(cutoff);
    system.addForce(nonbonded);
    system.addForce(bonds);
    VerletIntegrator integrator1(0.01);
    VerletIntegrator integrator2(0.01);
    Context cudaContext(system, integrator1, cuda);
    Context referenceContext(system, integrator2, reference);
    cudaContext.setPositions(positions);
    cudaContext.setVelocities(velocities);
    referenceContext.setPositions(positions);
    referenceContext.setVelocities(velocities);
    State cudaState = cudaContext.getState(State::Positions | State::Velocities | State::Forces | State::Energy);
    State referenceState = referenceContext.getState(State::Positions | State::Velocities | State::Forces | State::Energy);
    for (int i = 0; i < numParticles; i++) {
        ASSERT_EQUAL_VEC(cudaState.getPositions()[i], referenceState.getPositions()[i], tol);
        ASSERT_EQUAL_VEC(cudaState.getVelocities()[i], referenceState.getVelocities()[i], tol);
        ASSERT_EQUAL_VEC(cudaState.getForces()[i], referenceState.getForces()[i], tol);
    }
    ASSERT_EQUAL_TOL(cudaState.getPotentialEnergy(), referenceState.getPotentialEnergy(), tol);

    // Now do the same thing with periodic boundary conditions.

    nonbonded->setNonbondedMethod(NonbondedForce::CutoffPeriodic);
    system.setDefaultPeriodicBoxVectors(Vec3(boxSize, 0, 0), Vec3(0, boxSize, 0), Vec3(0, 0, boxSize));
    cudaContext.reinitialize();
    referenceContext.reinitialize();
    cudaContext.setPositions(positions);
    cudaContext.setVelocities(velocities);
    referenceContext.setPositions(positions);
    referenceContext.setVelocities(velocities);
    cudaState = cudaContext.getState(State::Positions | State::Velocities | State::Forces | State::Energy);
    referenceState = referenceContext.getState(State::Positions | State::Velocities | State::Forces | State::Energy);
    for (int i = 0; i < numParticles; i++) {
        ASSERT_EQUAL_TOL(fmod(cudaState.getPositions()[i][0]-referenceState.getPositions()[i][0], boxSize), 0, tol);
        ASSERT_EQUAL_TOL(fmod(cudaState.getPositions()[i][1]-referenceState.getPositions()[i][1], boxSize), 0, tol);
        ASSERT_EQUAL_TOL(fmod(cudaState.getPositions()[i][2]-referenceState.getPositions()[i][2], boxSize), 0, tol);
        ASSERT_EQUAL_VEC(cudaState.getVelocities()[i], referenceState.getVelocities()[i], tol);
        ASSERT_EQUAL_VEC(cudaState.getForces()[i], referenceState.getForces()[i], tol);
    }
    ASSERT_EQUAL_TOL(cudaState.getPotentialEnergy(), referenceState.getPotentialEnergy(), tol);
}

void testBlockInteractions(bool periodic) {
    const int blockSize = 32;
    const int numBlocks = 100;
    const int numParticles = blockSize*numBlocks;
    const double cutoff = 1.0;
    const double boxSize = (periodic ? 5.1 : 1.1);
    CudaPlatform cuda;
    System system;
    VerletIntegrator integrator(0.01);
    NonbondedForce* nonbonded = new NonbondedForce();
    vector<Vec3> positions(numParticles);
    OpenMM_SFMT::SFMT sfmt;
    init_gen_rand(0, sfmt);

    for (int i = 0; i < numParticles; i++) {
        system.addParticle(1.0);
        nonbonded->addParticle(1.0, 0.2, 0.2);
        positions[i] = Vec3(boxSize*(3*genrand_real2(sfmt)-1), boxSize*(3*genrand_real2(sfmt)-1), boxSize*(3*genrand_real2(sfmt)-1));
    }
    nonbonded->setNonbondedMethod(periodic ? NonbondedForce::CutoffPeriodic : NonbondedForce::CutoffNonPeriodic);
    nonbonded->setCutoffDistance(cutoff);
    system.setDefaultPeriodicBoxVectors(Vec3(boxSize, 0, 0), Vec3(0, boxSize, 0), Vec3(0, 0, boxSize));
    system.addForce(nonbonded);
    Context context(system, integrator, cuda);
    context.setPositions(positions);
    State state = context.getState(State::Positions | State::Velocities | State::Forces);
    ContextImpl* contextImpl = *reinterpret_cast<ContextImpl**>(&context);
    CudaPlatform::PlatformData& data = *static_cast<CudaPlatform::PlatformData*>(contextImpl->getPlatformData());
    
    // Verify that the bounds of each block were calculated correctly.

    data.gpu->psPosq4->Download();
    data.gpu->psGridBoundingBox->Download();
    data.gpu->psGridCenter->Download();
    for (int i = 0; i < numBlocks; i++) {
        float4 gridSize = (*data.gpu->psGridBoundingBox)[i];
        float4 center = (*data.gpu->psGridCenter)[i];
        if (periodic) {
            ASSERT(gridSize.x < 0.5*boxSize);
            ASSERT(gridSize.y < 0.5*boxSize);
            ASSERT(gridSize.z < 0.5*boxSize);
        }
        float minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0, minz = 0.0, maxz = 0.0, radius = 0.0;
        for (int j = 0; j < blockSize; j++) {
            float4 pos = (*data.gpu->psPosq4)[i*blockSize+j];
            float dx = pos.x-center.x;
            float dy = pos.y-center.y;
            float dz = pos.z-center.z;
            if (periodic) {
                dx -= (float)(floor(0.5+dx/boxSize)*boxSize);
                dy -= (float)(floor(0.5+dy/boxSize)*boxSize);
                dz -= (float)(floor(0.5+dz/boxSize)*boxSize);
            }
            ASSERT(abs(dx) < gridSize.x+TOL);
            ASSERT(abs(dy) < gridSize.y+TOL);
            ASSERT(abs(dz) < gridSize.z+TOL);
            minx = min(minx, dx);
            maxx = max(maxx, dx);
            miny = min(miny, dy);
            maxy = max(maxy, dy);
            minz = min(minz, dz);
            maxz = max(maxz, dz);
        }
        ASSERT_EQUAL_TOL(-minx, gridSize.x, TOL);
        ASSERT_EQUAL_TOL(maxx, gridSize.x, TOL);
        ASSERT_EQUAL_TOL(-miny, gridSize.y, TOL);
        ASSERT_EQUAL_TOL(maxy, gridSize.y, TOL);
        ASSERT_EQUAL_TOL(-minz, gridSize.z, TOL);
        ASSERT_EQUAL_TOL(maxz, gridSize.z, TOL);
    }

    // Verify that interactions were identified correctly.

    data.gpu->psInteractionCount->Download();
    int numWithInteractions = (*data.gpu->psInteractionCount)[0];
    vector<bool> hasInteractions(data.gpu->sim.workUnits, false);
    data.gpu->psInteractingWorkUnit->Download();
    data.gpu->psInteractionFlag->Download();
    const unsigned int atoms = data.gpu->sim.paddedNumberOfAtoms;
    const unsigned int grid = data.gpu->grid;
    const unsigned int dim = (atoms+(grid-1))/grid;
    for (int i = 0; i < numWithInteractions; i++) {
        unsigned int workUnit = (*data.gpu->psInteractingWorkUnit)[i];
        unsigned int x = (workUnit >> 17);
        unsigned int y = ((workUnit >> 2) & 0x7fff);
        int tile = (x > y ? x+y*dim-y*(y+1)/2 : y+x*dim-x*(x+1)/2);
        hasInteractions[tile] = true;

        // Make sure this tile really should have been flagged based on bounding volumes.

        float4 gridSize1 = (*data.gpu->psGridBoundingBox)[x];
        float4 gridSize2 = (*data.gpu->psGridBoundingBox)[y];
        float4 center1 = (*data.gpu->psGridCenter)[x];
        float4 center2 = (*data.gpu->psGridCenter)[y];
        float dx = center1.x-center2.x;
        float dy = center1.y-center2.y;
        float dz = center1.z-center2.z;
        if (periodic) {
            dx -= (float)(floor(0.5+dx/boxSize)*boxSize);
            dy -= (float)(floor(0.5+dy/boxSize)*boxSize);
            dz -= (float)(floor(0.5+dz/boxSize)*boxSize);
        }
        dx = max(0.0f, abs(dx)-gridSize1.x-gridSize2.x);
        dy = max(0.0f, abs(dy)-gridSize1.y-gridSize2.y);
        dz = max(0.0f, abs(dz)-gridSize1.z-gridSize2.z);
        ASSERT(sqrt(dx*dx+dy*dy+dz*dz) < cutoff+TOL);

        // Check the interaction flags.

        unsigned int flags = (*data.gpu->psInteractionFlag)[i];
        for (int atom2 = 0; atom2 < 32; atom2++) {
            if ((flags & 1) == 0) {
                float4 pos2 = (*data.gpu->psPosq4)[y*blockSize+atom2];
                for (int atom1 = 0; atom1 < blockSize; ++atom1) {
                    float4 pos1 = (*data.gpu->psPosq4)[x*blockSize+atom1];
                    float dx = pos2.x-pos1.x;
                    float dy = pos2.y-pos1.y;
                    float dz = pos2.z-pos1.z;
                    if (periodic) {
                        dx -= (float)(floor(0.5+dx/boxSize)*boxSize);
                        dy -= (float)(floor(0.5+dy/boxSize)*boxSize);
                        dz -= (float)(floor(0.5+dz/boxSize)*boxSize);
                    }
                    ASSERT(dx*dx+dy*dy+dz*dz > cutoff*cutoff);
                }
            }
            flags >>= 1;
        }
    }

    // Check the tiles that did not have interactions to make sure all atoms are beyond the cutoff.

    data.gpu->psWorkUnit->Download();
    for (int i = 0; i < (int)hasInteractions.size(); i++)
        if (!hasInteractions[i]) {
            unsigned int workUnit = (*data.gpu->psWorkUnit)[i];
            unsigned int x = (workUnit >> 17);
            unsigned int y = ((workUnit >> 2) & 0x7fff);
            for (int atom1 = 0; atom1 < blockSize; ++atom1) {
                float4 pos1 = (*data.gpu->psPosq4)[x*blockSize+atom1];
                for (int atom2 = 0; atom2 < blockSize; ++atom2) {
                    float4 pos2 = (*data.gpu->psPosq4)[y*blockSize+atom2];
                    float dx = pos1.x-pos2.x;
                    float dy = pos1.y-pos2.y;
                    float dz = pos1.z-pos2.z;
                    if (periodic) {
                        dx -= (float)(floor(0.5+dx/boxSize)*boxSize);
                        dy -= (float)(floor(0.5+dy/boxSize)*boxSize);
                        dz -= (float)(floor(0.5+dz/boxSize)*boxSize);
                    }
                    ASSERT(dx*dx+dy*dy+dz*dz > cutoff*cutoff);
                }
            }
        }
}

void testDispersionCorrection() {
    // Create a box full of identical particles.

    int gridSize = 5;
    int numParticles = gridSize*gridSize*gridSize;
    double boxSize = gridSize*0.5;
    double cutoff = boxSize/3;
    CudaPlatform platform;
    System system;
    VerletIntegrator integrator(0.01);
    NonbondedForce* nonbonded = new NonbondedForce();
    vector<Vec3> positions(numParticles);
    int index = 0;
    for (int i = 0; i < gridSize; i++)
        for (int j = 0; j < gridSize; j++)
            for (int k = 0; k < gridSize; k++) {
                system.addParticle(1.0);
                nonbonded->addParticle(0, 1.1, 0.5);
                positions[index] = Vec3(i*boxSize/gridSize, j*boxSize/gridSize, k*boxSize/gridSize);
                index++;
            }
    nonbonded->setNonbondedMethod(NonbondedForce::CutoffPeriodic);
    nonbonded->setCutoffDistance(cutoff);
    system.setDefaultPeriodicBoxVectors(Vec3(boxSize, 0, 0), Vec3(0, boxSize, 0), Vec3(0, 0, boxSize));
    system.addForce(nonbonded);

    // See if the correction has the correct value.

    Context context(system, integrator, platform);
    context.setPositions(positions);
    double energy1 = context.getState(State::Energy).getPotentialEnergy();
    nonbonded->setUseDispersionCorrection(false);
    context.reinitialize();
    context.setPositions(positions);
    double energy2 = context.getState(State::Energy).getPotentialEnergy();
    double term1 = (0.5*pow(1.1, 12)/pow(cutoff, 9))/9;
    double term2 = (0.5*pow(1.1, 6)/pow(cutoff, 3))/3;
    double expected = 8*M_PI*numParticles*numParticles*(term1-term2)/(boxSize*boxSize*boxSize);
    ASSERT_EQUAL_TOL(expected, energy1-energy2, 1e-4);

    // Now modify half the particles to be different, and see if it is still correct.

    int numType2 = 0;
    for (int i = 0; i < numParticles; i += 2) {
        nonbonded->setParticleParameters(i, 0, 1, 1);
        numType2++;
    }
    int numType1 = numParticles-numType2;
    nonbonded->setUseDispersionCorrection(true);
    context.reinitialize();
    context.setPositions(positions);
    energy1 = context.getState(State::Energy).getPotentialEnergy();
    nonbonded->setUseDispersionCorrection(false);
    context.reinitialize();
    context.setPositions(positions);
    energy2 = context.getState(State::Energy).getPotentialEnergy();
    term1 = ((numType1*(numType1+1))/2)*(0.5*pow(1.1, 12)/pow(cutoff, 9))/9;
    term2 = ((numType1*(numType1+1))/2)*(0.5*pow(1.1, 6)/pow(cutoff, 3))/3;
    term1 += ((numType2*(numType2+1))/2)*(1*pow(1.0, 12)/pow(cutoff, 9))/9;
    term2 += ((numType2*(numType2+1))/2)*(1*pow(1.0, 6)/pow(cutoff, 3))/3;
    double combinedSigma = 0.5*(1+1.1);
    double combinedEpsilon = sqrt(1*0.5);
    term1 += (numType1*numType2)*(combinedEpsilon*pow(combinedSigma, 12)/pow(cutoff, 9))/9;
    term2 += (numType1*numType2)*(combinedEpsilon*pow(combinedSigma, 6)/pow(cutoff, 3))/3;
    term1 /= (numParticles*(numParticles+1))/2;
    term2 /= (numParticles*(numParticles+1))/2;
    expected = 8*M_PI*numParticles*numParticles*(term1-term2)/(boxSize*boxSize*boxSize);
    ASSERT_EQUAL_TOL(expected, energy1-energy2, 1e-4);
}

int main() {
    try {
        testCoulomb();
        testLJ();
        testExclusionsAnd14();
        testCutoff();
        testCutoff14();
        testPeriodic();
        testLargeSystem();
        testBlockInteractions(false);
        testBlockInteractions(true);
        testDispersionCorrection();
    }
    catch(const exception& e) {
        cout << "exception: " << e.what() << endl;
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
