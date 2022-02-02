#pragma once
#include "defines.h"

#define NDR_PI 3.14158
#define NDR_RAD_TO_DEG (180.0/NDR_PI)
#define NDR_DEG_TO_RAD (NDR_PI/180.0)

float ndrAbsF(float value);
float ndrSqrtF(float value);
float ndrMinF(float a, float b);
float ndrMaxF(float a, float b);
float ndrClampF(float value, float min, float max);
float ndrLerpF(float a, float b, float t);
float ndrSinF(float angle);
float ndrCosF(float angle);
float ndrTanF(float angle);
float ndrRandomF01();
float ndrRandomF(float min, float max);

bool ndrIsZeroMagnitude(vec3 vec);
void ndrNormalizeVec3(vec3* vec);
float ndrSqrMagnitudeVec3(vec3 vec);
float ndrMagnitudeVec3(vec3 vec);
float ndrDotVec3(vec3 a, vec3 b);
vec3 ndrNormalizedVec3(vec3 vec);
vec3 ndrNegateVec3(vec3 vec);
vec3 ndrAddVec3(vec3 a, vec3 b);
vec3 ndrSubVec3(vec3 a, vec3 b);
vec3 ndrMulScalarVec3(vec3 a, float b);
vec3 ndrMulVec3(vec3 a, vec3 b);
vec3 ndrDivScalarVec3(vec3 a, float b);
vec3 ndrDivVec3(vec3 a, vec3 b);
vec3 ndrCrossVec3(vec3 a, vec3 b);
vec3 ndrReflectVec3(vec3 vec, vec3 normal);
vec3 ndrRefractVec3(vec3 uv, vec3 normal, float etaiOverEtat);
vec3 ndrRandomOnUnitSphere();
vec3 ndrRandomOnUnitHemisphere(vec3 normal);

void ndrNormalizeRay3(ray3* ray);
ray3 ndrNormalizedRay3(ray3 ray);
vec3 ndrAtRay3(ray3 ray, float value);

ndrPixel ndrColorToPixel(ndrColor color);

ndrColor ndrLerpColor(ndrColor a, ndrColor b, float t);
ndrColor ndrClampColor(ndrColor color);
ndrColor ndrGammaCorrect(ndrColor color, uint32_t samples);
ndrColor ndrAddColor(ndrColor a, ndrColor b);
ndrColor ndrMulScalarColor(ndrColor a, float b);
ndrColor ndrMulColor(ndrColor a, ndrColor b);