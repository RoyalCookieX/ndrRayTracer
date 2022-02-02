#include "world.h"
#include "ndrMath.h"
#include <stdlib.h>

bool ndrCreateWorld(uint32_t maxObjects, ndrWorld* result)
{
    if(result == NULL || maxObjects == 0)
        return false;
        
    size_t objectsSize = sizeof(ndrObject) * maxObjects;
    *result = malloc(sizeof(ndrWorld_t) + objectsSize);

    (*result)->maxObjects = maxObjects;
    (*result)->objectCount = 0;
    (*result)->objects = NDR_PTR_OFFSET((*result), sizeof(ndrWorld_t));
    return true;
}

void ndrDestroyWorld(ndrWorld world)
{
    if(world == NULL)
        return;

    free(world);
}

bool ndrAddObject(ndrWorld world, ndrObject object)
{
    if(world == NULL || world->objects == NULL || world->objectCount >= world->maxObjects)
        return false;

    world->objects[world->objectCount] = object;
    world->objectCount++;
    return true;
}

bool ndrRaycastWorld(ndrWorld world, ray3 ray, float minDistance, float maxDistance, ndrRaycastResult* result)
{
    if(world == NULL || world->objects == NULL || result == NULL)
        return false;

    ndrRaycastResult temp;
    bool hit = false;
    float closest = maxDistance;

    for(uint32_t i = 0; i < world->objectCount; i++)
    {
        if(ndrRaycastObject(world->objects[i], ray, minDistance, closest, &temp))
        {
            hit = true;
            closest = temp.distance;
            *result = temp;
        }
    }
    return hit;
}