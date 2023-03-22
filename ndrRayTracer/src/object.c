#include "object.h"
#include "ndrMath.h"

bool ndrRaycastSphere(ndrObject object, ray3 ray, float minDistance, float maxDistance, ndrRaycastResult* result);

bool ndrRaycastObject(ndrObject object, ray3 ray, float minDistance, float maxDistance, ndrRaycastResult* result)
{
    switch(object.type)
    {
        case NDR_OBJECT_TYPE_SPHERE: return ndrRaycastSphere(object, ray, minDistance, maxDistance, result);
        default: return false;
    }
}

bool ndrRaycastSphere(ndrObject object, ray3 ray, float minDistance, float maxDistance, ndrRaycastResult* result)
{
    ndrNormalizeRay3(&ray);
    vec3 oc = ndrSubVec3(ray.origin, object.position);
    float a = ndrSqrMagnitudeVec3(ray.direction);
    float hb = ndrDotVec3(oc, ray.direction);
    float c = ndrSqrMagnitudeVec3(oc) - object.scale * object.scale;

    float discriminant = hb * hb - a * c;
    if(discriminant < 0)
        return false;
    float sqrtd = ndrSqrtF(discriminant);

    float root = (-hb - sqrtd) / a;
    if(root < minDistance || root > maxDistance)
    {
        root = (-hb + sqrtd) / a;
        if(root < minDistance || root > maxDistance)
            return false;
    }
    result->distance = root;
    result->point = ndrAtRay3(ray, result->distance);

    vec3 outNormal = ndrDivScalarVec3(ndrSubVec3(result->point, object.position), object.scale);
    result->frontFace = ndrDotVec3(ray.direction, outNormal) < 0.0f;
    result->normal = result->frontFace ? outNormal : ndrMulScalarVec3(outNormal, -1.0f);
    result->material = object.material;
    return true;
}

bool ndrScatter(ray3 in, ndrRaycastResult raycast, ndrColor* outColor, ray3* outRay)
{
    ndrNormalizeRay3(&in);
    switch(raycast.material.type)
    {
        case NDR_MATERIAL_TYPE_LAMBERT:
        {
            vec3 scatterDirection = ndrAddVec3(raycast.normal, ndrRandomOnUnitSphere());
            if(ndrIsZeroMagnitude(scatterDirection))
                scatterDirection = raycast.normal;

            *outColor = raycast.material.color;
            outRay->origin = raycast.point;
            outRay->direction = scatterDirection;
            return true;
        }
        case NDR_MATERIAL_TYPE_METAL:
        {
            vec3 reflectDirection = ndrReflectVec3(in.direction, raycast.normal);
            vec3 scatterDirection = ndrAddVec3(reflectDirection, ndrMulScalarVec3(ndrRandomOnUnitSphere(), raycast.material.roughness));
            *outColor = raycast.material.color;
            outRay->origin = raycast.point;
            outRay->direction = scatterDirection;
            return true;
        }
        case NDR_MATERIAL_TYPE_DIELECTRIC:
        {
            float refractionRatio = raycast.frontFace ? (1.0f / raycast.material.indexOfRefraction) : raycast.material.indexOfRefraction;
            
            float cosTheta = ndrMinF(ndrDotVec3(ndrNegateVec3(in.direction), raycast.normal), 1.0f);
            float sinTheta = ndrSqrtF(1.0f - cosTheta * cosTheta);
            bool cantRefract = refractionRatio * sinTheta > 1.0f;
            vec3 refractDirection = ndrRefractVec3(in.direction, raycast.normal, refractionRatio);
            vec3 reflectDirection = ndrReflectVec3(in.direction, raycast.normal);

            *outColor = (ndrColor){ 1.0f, 1.0f, 1.0f, 1.0f };
            outRay->origin = raycast.point;
            outRay->direction = cantRefract ? reflectDirection : refractDirection;
            return true;
        }
        default: return false;
    }
}