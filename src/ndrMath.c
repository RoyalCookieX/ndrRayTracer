#include "ndrMath.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

static bool seedRandom = false;

float ndrAbsF(float value) { return fabsf(value); }
float ndrSqrtF(float value) { return sqrtf(value); }
float ndrMinF(float a, float b) { return fminf(a, b); }
float ndrMaxF(float a, float b) { return fmaxf(a, b); }
float ndrClampF(float value, float min, float max) { return ndrMinF(ndrMaxF(value, min), max); }
float ndrLerpF(float a, float b, float t) { return a * (1.0f - t) + b * t; }
float ndrSinF(float angle) { return sinf(angle); }
float ndrCosF(float angle) { return cosf(angle); }
float ndrTanF(float angle) { return tanf(angle); }
float ndrRandomF01()
{
    if(!seedRandom)
    {
        srand(time(NULL));
        seedRandom = true;
    }
    return (float)rand() / (float)RAND_MAX;
}
float ndrRandomF(float min, float max)
{
    float rng = ndrRandomF01();
    return min * (1.0f - rng) + max * rng;
}

bool ndrIsZeroMagnitude(vec3 vec)
{
    float sqrEpsilon = 0.0000001f;
    return ndrSqrMagnitudeVec3(vec) < sqrEpsilon;
}
void ndrNormalizeVec3(vec3* vec)
{
    float magnitude = ndrMagnitudeVec3(*vec);
    vec->x /= magnitude;
    vec->y /= magnitude;
    vec->z /= magnitude;
};
float ndrSqrMagnitudeVec3(vec3 vec) { return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z; }
float ndrMagnitudeVec3(vec3 vec) { return sqrtf(ndrSqrMagnitudeVec3(vec)); }
float ndrDotVec3(vec3 a, vec3 b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
vec3 ndrNormalizedVec3(vec3 vec) 
{ 
    ndrNormalizeVec3(&vec);
    return vec; 
}
vec3 ndrNegateVec3(vec3 vec) { return ndrMulScalarVec3(vec, -1.0f); }
vec3 ndrAddVec3(vec3 a, vec3 b)
{
    return (vec3){
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}
vec3 ndrSubVec3(vec3 a, vec3 b)
{
    return (vec3){
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}
vec3 ndrMulScalarVec3(vec3 a, float b)
{
    return (vec3){
        a.x * b,
        a.y * b,
        a.z * b
    };
}
vec3 ndrMulVec3(vec3 a, vec3 b)
{
    return (vec3){
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    };
}
vec3 ndrDivScalarVec3(vec3 a, float b)
{
    return (vec3){
        a.x / b,
        a.y / b,
        a.z / b
    };
}
vec3 ndrDivVec3(vec3 a, vec3 b)
{
    return (vec3){
        a.x / b.x,
        a.y / b.y,
        a.z / b.z
    };
}
vec3 ndrCrossVec3(vec3 a, vec3 b)
{
    return (vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
vec3 ndrReflectVec3(vec3 vec, vec3 normal) { return ndrSubVec3(vec, ndrMulScalarVec3(normal, 2.0f * ndrDotVec3(vec, normal))); }
vec3 ndrRefractVec3(vec3 uv, vec3 normal, float etaiOverEtat)
{
    float cosTheta = ndrMinF(ndrDotVec3(ndrNegateVec3(uv), normal), 1.0f);
    vec3 rPerp = ndrMulScalarVec3(ndrAddVec3(uv, ndrMulScalarVec3(normal, cosTheta)), etaiOverEtat);
    vec3 rPara = ndrMulScalarVec3(normal, -ndrSqrtF(ndrAbsF(1.0f - ndrSqrMagnitudeVec3(rPerp))));
    return ndrAddVec3(rPerp, rPara);
}
vec3 ndrRandomOnUnitSphere()
{
    vec3 rng = {
        ndrRandomF(-1.0f, 1.0f),
        ndrRandomF(-1.0f, 1.0f),
        ndrRandomF(-1.0f, 1.0f)
    };
    ndrNormalizeVec3(&rng);
    return rng;
}
vec3 ndrRandomOnUnitHemisphere(vec3 normal)
{
    vec3 rng = ndrRandomOnUnitSphere();
    return ndrDotVec3(rng, normal) > 0.0f ? rng : ndrNegateVec3(rng);
}

void ndrNormalizeRay3(ray3* ray) { ndrNormalizeVec3(&ray->direction); }
ray3 ndrNormalzedRay3(ray3 ray) 
{ 
    ndrNormalizeRay3(&ray);
    return ray;
}
vec3 ndrAtRay3(ray3 ray, float value) 
{
    ndrNormalizeRay3(&ray);
    return ndrAddVec3(ray.origin, ndrMulScalarVec3(ray.direction, value));
}

ndrPixel ndrColorToPixel(ndrColor color)
{
    return (ndrPixel){
        (uint8_t)(color.r * 255.0f),
        (uint8_t)(color.g * 255.0f),
        (uint8_t)(color.b * 255.0f)
    };
};

ndrColor ndrLerpColor(ndrColor a, ndrColor b, float t) 
{
    return (ndrColor){
        ndrLerpF(a.r, b.r, t),
        ndrLerpF(a.g, b.g, t),
        ndrLerpF(a.b, b.b, t),
        ndrLerpF(a.a, b.a, t)
    };
}
ndrColor ndrClampColor(ndrColor color)
{
    return (ndrColor){
        ndrClampF(color.r, 0.0f, 1.0f),
        ndrClampF(color.g, 0.0f, 1.0f),
        ndrClampF(color.b, 0.0f, 1.0f),
        ndrClampF(color.a, 0.0f, 1.0f)
    };
};
ndrColor ndrGammaCorrect(ndrColor color, uint32_t samples)
{
    if(samples == 0)
        return color;
    
    float scale = 1.0f / samples;
    return (ndrColor){
        ndrSqrtF(scale * color.r),
        ndrSqrtF(scale * color.g),
        ndrSqrtF(scale * color.b),
        1.0f
    };
}
ndrColor ndrAddColor(ndrColor a, ndrColor b)
{
    return (ndrColor){
        a.r + b.r,
        a.g + b.g,
        a.b + b.b,
        a.a + b.a
    };
}
ndrColor ndrMulScalarColor(ndrColor a, float b)
{
    return (ndrColor){
        a.r * b,
        a.g * b,
        a.b * b,
        a.a * b
    };
}
ndrColor ndrMulColor(ndrColor a, ndrColor b)
{
    return (ndrColor){
        a.r * b.r,
        a.g * b.g,
        a.b * b.b,
        a.a * b.a
    };
}