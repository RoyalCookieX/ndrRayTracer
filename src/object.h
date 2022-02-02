#pragma once
#include "defines.h"

#define NDR_MAKE_MATERIAL(type, color, modifier)            (ndrMaterial){ NDR_MATERIAL_TYPE_##type, color, modifier }
#define NDR_MAKE_MATERIAL_LAMBERT(color)                    (ndrMaterial){ NDR_MATERIAL_TYPE_LAMBERT, color, 1.0f }
#define NDR_MAKE_MATERIAL_METAL(color, roughness)           (ndrMaterial){ NDR_MATERIAL_TYPE_METAL, color, roughness }
#define NDR_MAKE_MATERIAL_DIELECTRIC(indexOfRefraction)     (ndrMaterial){ NDR_MATERIAL_TYPE_DIELECTRIC, NDR_COLOR_CLEAR, indexOfRefraction }

#define NDR_MAKE_OBJECT(type, position, scale, material)    (ndrObject){ NDR_OBJECT_TYPE_##type, position, scale, material }
#define NDR_MAKE_OBJECT_SPHERE(position, scale, material)   (ndrObject){ NDR_OBJECT_TYPE_SPHERE, position, scale, material }

typedef struct ndrObject ndrObject;
typedef struct ndrRaycastResult ndrRaycastResult;

// The type of an object.
typedef enum ndrObjectType {
    NDR_OBJECT_TYPE_SPHERE
} ndrObjectType;

// The type of material.
typedef enum ndrMaterialType {
    NDR_MATERIAL_TYPE_LAMBERT,
    NDR_MATERIAL_TYPE_METAL,
    NDR_MATERIAL_TYPE_DIELECTRIC
} ndrMaterialType;

// The surface of an object.
typedef struct ndrMaterial {
    ndrMaterialType type;
    ndrColor color;
    union {
        float roughness;
        float indexOfRefraction;
    };
} ndrMaterial;

// Interacts with the world.
typedef struct ndrObject {
    ndrObjectType type;
    vec3 position;
    float scale;
    ndrMaterial material;
} ndrObject;

// Describes what a ray has hit.
typedef struct ndrRaycastResult {
    float distance;
    vec3 point;
    vec3 normal;
    bool frontFace;
    ndrMaterial material;
} ndrRaycastResult;

// Casts a ray at an object, and returns its results.
bool ndrRaycastObject(ndrObject object, ray3 ray, float minDistance, float maxDistance, ndrRaycastResult* result);
// Scatters an incoming ray.
bool ndrScatter(ray3 in, ndrRaycastResult raycast, ndrColor* outColor, ray3* outRay);
