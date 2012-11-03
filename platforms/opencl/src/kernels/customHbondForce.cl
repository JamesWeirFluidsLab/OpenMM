/**
 * Compute the difference between two vectors, setting the fourth component to the squared magnitude.
 */
float4 delta(float4 vec1, float4 vec2) {
    float4 result = (float4) (vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z, 0.0f);
    result.w = result.x*result.x + result.y*result.y + result.z*result.z;
    return result;
}

/**
 * Compute the difference between two vectors, taking periodic boundary conditions into account
 * and setting the fourth component to the squared magnitude.
 */
float4 deltaPeriodic(float4 vec1, float4 vec2, float4 periodicBoxSize, float4 invPeriodicBoxSize) {
    float4 result = (float4) (vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z, 0.0f);
#ifdef USE_PERIODIC
    result.x -= floor(result.x*invPeriodicBoxSize.x+0.5f)*periodicBoxSize.x;
    result.y -= floor(result.y*invPeriodicBoxSize.y+0.5f)*periodicBoxSize.y;
    result.z -= floor(result.z*invPeriodicBoxSize.z+0.5f)*periodicBoxSize.z;
#endif
    result.w = result.x*result.x + result.y*result.y + result.z*result.z;
    return result;
}

/**
 * Compute the angle between two vectors.  The w component of each vector should contain the squared magnitude.
 */
float computeAngle(float4 vec1, float4 vec2) {
    float dotProduct = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    float cosine = dotProduct*RSQRT(vec1.w*vec2.w);
    float angle;
    if (cosine > 0.99f || cosine < -0.99f) {
        // We're close to the singularity in acos(), so take the cross product and use asin() instead.

        float4 crossProduct = cross(vec1, vec2);
        float scale = vec1.w*vec2.w;
        angle = asin(SQRT(dot(crossProduct, crossProduct)/scale));
        if (cosine < 0.0f)
            angle = M_PI-angle;
    }
    else
       angle = acos(cosine);
    return angle;
}

/**
 * Compute the cross product of two vectors, setting the fourth component to the squared magnitude.
 */
float4 computeCross(float4 vec1, float4 vec2) {
    float4 result = cross(vec1, vec2);
    result.w = result.x*result.x + result.y*result.y + result.z*result.z;
    return result;
}

/**
 * Compute forces on donors.
 */
__kernel void computeDonorForces(__global float4* restrict forceBuffers, __global float* restrict energyBuffer, __global const float4* restrict posq, __global const int4* restrict exclusions,
        __global const int4* restrict donorAtoms, __global const int4* restrict acceptorAtoms, __global const int4* restrict donorBufferIndices, __local float4* posBuffer, float4 periodicBoxSize, float4 invPeriodicBoxSize
        PARAMETER_ARGUMENTS) {
    float energy = 0.0f;
    float4 f1 = (float4) 0;
    float4 f2 = (float4) 0;
    float4 f3 = (float4) 0;
    for (int donorStart = 0; donorStart < NUM_DONORS; donorStart += get_global_size(0)) {
        // Load information about the donor this thread will compute forces on.

        int donorIndex = donorStart+get_global_id(0);
        int4 atoms, exclusionIndices;
        float4 d1, d2, d3;
        if (donorIndex < NUM_DONORS) {
            atoms = donorAtoms[donorIndex];
            d1 = (atoms.x > -1 ? posq[atoms.x] : (float4) 0);
            d2 = (atoms.y > -1 ? posq[atoms.y] : (float4) 0);
            d3 = (atoms.z > -1 ? posq[atoms.z] : (float4) 0);
#ifdef USE_EXCLUSIONS
            exclusionIndices = exclusions[donorIndex];
#endif
        }
        else
            atoms = (int4) (-1, -1, -1, -1);
        for (int acceptorStart = 0; acceptorStart < NUM_ACCEPTORS; acceptorStart += get_local_size(0)) {
            // Load the next block of acceptors into local memory.

            int blockSize = min((int) get_local_size(0), NUM_ACCEPTORS-acceptorStart);
            if (get_local_id(0) < blockSize) {
                int4 atoms2 = acceptorAtoms[acceptorStart+get_local_id(0)];
                posBuffer[3*get_local_id(0)] = (atoms2.x > -1 ? posq[atoms2.x] : (float4) 0);
                posBuffer[3*get_local_id(0)+1] = (atoms2.y > -1 ? posq[atoms2.y] : (float4) 0);
                posBuffer[3*get_local_id(0)+2] = (atoms2.z > -1 ? posq[atoms2.z] : (float4) 0);
            }
            barrier(CLK_LOCAL_MEM_FENCE);
            if (donorIndex < NUM_DONORS) {
                for (int index = 0; index < blockSize; index++) {
#ifdef USE_EXCLUSIONS
                    int acceptorIndex = acceptorStart+index;
                    if (acceptorIndex == exclusionIndices.x || acceptorIndex == exclusionIndices.y || acceptorIndex == exclusionIndices.z || acceptorIndex == exclusionIndices.w)
                        continue;
#endif
                    // Compute the interaction between a donor and an acceptor.

                    float4 a1 = posBuffer[3*index];
                    float4 a2 = posBuffer[3*index+1];
                    float4 a3 = posBuffer[3*index+2];
                    float4 deltaD1A1 = deltaPeriodic(d1, a1, periodicBoxSize, invPeriodicBoxSize);
#ifdef USE_CUTOFF
                    if (deltaD1A1.w < CUTOFF_SQUARED) {
#endif
                        COMPUTE_DONOR_FORCE
#ifdef USE_CUTOFF
                    }
#endif
                }
            }
        }

        // Write results

        if (donorIndex < NUM_DONORS) {
            int4 bufferIndices = donorBufferIndices[donorIndex];
            if (atoms.x > -1) {
                unsigned int offset = atoms.x+bufferIndices.x*PADDED_NUM_ATOMS;
                float4 force = forceBuffers[offset];
                force.xyz += f1.xyz;
                forceBuffers[offset] = force;
            }
            if (atoms.y > -1) {
                unsigned int offset = atoms.y+bufferIndices.y*PADDED_NUM_ATOMS;
                float4 force = forceBuffers[offset];
                force.xyz += f2.xyz;
                forceBuffers[offset] = force;
            }
            if (atoms.z > -1) {
                unsigned int offset = atoms.z+bufferIndices.z*PADDED_NUM_ATOMS;
                float4 force = forceBuffers[offset];
                force.xyz += f3.xyz;
                forceBuffers[offset] = force;
            }
        }
    }
    energyBuffer[get_global_id(0)] += energy;
}
/**
 * Compute forces on acceptors.
 */
__kernel void computeAcceptorForces(__global float4* restrict forceBuffers, __global float* restrict energyBuffer, __global const float4* restrict posq, __global const int4* restrict exclusions,
        __global const int4* restrict donorAtoms, __global const int4* restrict acceptorAtoms, __global const int4* restrict acceptorBufferIndices, __local float4* restrict posBuffer, float4 periodicBoxSize, float4 invPeriodicBoxSize
        PARAMETER_ARGUMENTS) {
    float4 f1 = (float4) 0;
    float4 f2 = (float4) 0;
    float4 f3 = (float4) 0;
    for (int acceptorStart = 0; acceptorStart < NUM_ACCEPTORS; acceptorStart += get_global_size(0)) {
        // Load information about the acceptor this thread will compute forces on.

        int acceptorIndex = acceptorStart+get_global_id(0);
        int4 atoms, exclusionIndices;
        float4 a1, a2, a3;
        if (acceptorIndex < NUM_ACCEPTORS) {
            atoms = acceptorAtoms[acceptorIndex];
            a1 = (atoms.x > -1 ? posq[atoms.x] : (float4) 0);
            a2 = (atoms.y > -1 ? posq[atoms.y] : (float4) 0);
            a3 = (atoms.z > -1 ? posq[atoms.z] : (float4) 0);
#ifdef USE_EXCLUSIONS
            exclusionIndices = exclusions[acceptorIndex];
#endif
        }
        else
            atoms = (int4) (-1, -1, -1, -1);
        for (int donorStart = 0; donorStart < NUM_DONORS; donorStart += get_local_size(0)) {
            // Load the next block of donors into local memory.

            int blockSize = min((int) get_local_size(0), NUM_DONORS-donorStart);
            if (get_local_id(0) < blockSize) {
                int4 atoms2 = donorAtoms[donorStart+get_local_id(0)];
                posBuffer[3*get_local_id(0)] = (atoms2.x > -1 ? posq[atoms2.x] : (float4) 0);
                posBuffer[3*get_local_id(0)+1] = (atoms2.y > -1 ? posq[atoms2.y] : (float4) 0);
                posBuffer[3*get_local_id(0)+2] = (atoms2.z > -1 ? posq[atoms2.z] : (float4) 0);
            }
            barrier(CLK_LOCAL_MEM_FENCE);
            if (acceptorIndex < NUM_ACCEPTORS) {
                for (int index = 0; index < blockSize; index++) {
#ifdef USE_EXCLUSIONS
                    int donorIndex = donorStart+index;
                    if (donorIndex == exclusionIndices.x || donorIndex == exclusionIndices.y || donorIndex == exclusionIndices.z || donorIndex == exclusionIndices.w)
                        continue;
#endif
                    // Compute the interaction between a donor and an acceptor.

                    float4 d1 = posBuffer[3*index];
                    float4 d2 = posBuffer[3*index+1];
                    float4 d3 = posBuffer[3*index+2];
                    float4 deltaD1A1 = deltaPeriodic(d1, a1, periodicBoxSize, invPeriodicBoxSize);
#ifdef USE_CUTOFF
                    if (deltaD1A1.w < CUTOFF_SQUARED) {
#endif
                        COMPUTE_ACCEPTOR_FORCE
#ifdef USE_CUTOFF
                    }
#endif
                }
            }
        }

        // Write results

        if (acceptorIndex < NUM_ACCEPTORS) {
            int4 bufferIndices = acceptorBufferIndices[acceptorIndex];
            if (atoms.x > -1) {
                unsigned int offset = atoms.x+bufferIndices.x*PADDED_NUM_ATOMS;
                float4 force = forceBuffers[offset];
                force.xyz += f1.xyz;
                forceBuffers[offset] = force;
            }
            if (atoms.y > -1) {
                unsigned int offset = atoms.y+bufferIndices.y*PADDED_NUM_ATOMS;
                float4 force = forceBuffers[offset];
                force.xyz += f2.xyz;
                forceBuffers[offset] = force;
            }
            if (atoms.z > -1) {
                unsigned int offset = atoms.z+bufferIndices.z*PADDED_NUM_ATOMS;
                float4 force = forceBuffers[offset];
                force.xyz += f3.xyz;
                forceBuffers[offset] = force;
            }
        }
    }
}
