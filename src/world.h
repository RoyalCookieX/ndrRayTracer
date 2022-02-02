#pragma once
#include "defines.h"
#include "object.h"

// Represents the space where the objects are contained.
typedef struct ndrWorld_t {
    uint32_t maxObjects;
    uint32_t objectCount;
    ndrObject* objects;
} ndrWorld_t, *ndrWorld;

// Creates a world.
bool ndrCreateWorld(uint32_t maxObjects, ndrWorld* result);
// Destroys a world.
void ndrDestroyWorld(ndrWorld world);
// Adds an object to the world.
bool ndrAddObject(ndrWorld world, ndrObject object);
// Casts a ray into the world, and returns its results.
bool ndrRaycastWorld(ndrWorld world, ray3 ray, float minDistance, float maxDistance, ndrRaycastResult* result);