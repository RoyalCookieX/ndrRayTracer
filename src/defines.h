#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NDR_BIT(b) (1 << b)
#define NDR_PTR_OFFSET(ptr, offset) ((void*)((char*)(ptr) + (size_t)(offset)))

#define NDR_TIME_INFINITE UINT32_MAX

#define NDR_MAKE_VEC2(x, y)              (vec2){ x, y }
#define NDR_MAKE_IVEC2(x, y)             (ivec2){ x, y }
#define NDR_MAKE_UVEC2(x, y)             (uvec2){ x, y }

#define NDR_MAKE_VEC3(x, y, z)          (vec3){ x, y, z }
#define NDR_VEC3_ZERO                   (vec3){  0.0f,  0.0f,  0.0f }
#define NDR_VEC3_RIGHT                  (vec3){  1.0f,  0.0f,  0.0f }
#define NDR_VEC3_LEFT                   (vec3){ -1.0f,  0.0f,  0.0f }
#define NDR_VEC3_UP                     (vec3){  0.0f,  1.0f,  0.0f }
#define NDR_VEC3_DOWN                   (vec3){  0.0f, -1.0f,  0.0f }
#define NDR_VEC3_FORWARD                (vec3){  0.0f,  0.0f,  1.0f }
#define NDR_VEC3_BACK                   (vec3){  0.0f,  0.0f, -1.0f }
#define NDR_VEC3_ONE                    (vec3){  1.0f,  1.0f,  1.0f }

#define NDR_MAKE_COLOR(r, g, b, a)      (ndrColor){ r, g, b, a }
#define NDR_COLOR_CLEAR                 (ndrColor){ 0.0f, 0.0f, 0.0f, 0.0f }
#define NDR_COLOR_BLACK                 (ndrColor){ 0.0f, 0.0f, 0.0f, 1.0f }
#define NDR_COLOR_RED                   (ndrColor){ 1.0f, 0.0f, 0.0f, 1.0f }
#define NDR_COLOR_YELLOW                (ndrColor){ 1.0f, 1.0f, 0.0f, 1.0f }
#define NDR_COLOR_GREEN                 (ndrColor){ 0.0f, 1.0f, 0.0f, 1.0f }
#define NDR_COLOR_CYAN                  (ndrColor){ 0.0f, 1.0f, 1.0f, 1.0f }
#define NDR_COLOR_BLUE                  (ndrColor){ 0.0f, 0.0f, 1.0f, 1.0f }
#define NDR_COLOR_MAGENTA               (ndrColor){ 1.0f, 0.0f, 1.0f, 1.0f }
#define NDR_COLOR_WHITE                 (ndrColor){ 1.0f, 1.0f, 1.0f, 1.0f }

#define NDR_PIXEL_BLACK                 (ndrPixel){   0,   0,   0 }
#define NDR_PIXEL_WHITE                 (ndrPixel){ 255, 255, 255 }

typedef uint64_t ndrTime;

typedef struct vec2 {
    union {
        struct { float x, y; };
        struct { float data[2]; };
    };
} vec2;

typedef struct ivec2 {
    union {
        struct { int32_t x, y; };
        struct { int32_t data[2]; };
    };
} ivec2;

typedef struct uvec2 {
    union {
        struct { uint32_t x, y; };
        struct { uint32_t data[2]; };
    };
} uvec2;

typedef struct vec3 {
    union {
        struct { float x, y, z; };
        struct { float data[3]; };
    };
} vec3;

typedef struct ray3 {
    vec3 origin;
    vec3 direction;
} ray3;

typedef struct vec4 {
    union {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        struct { float data[4]; };
    };
} vec4, ndrColor;

typedef struct ndrPixel {
    uint8_t r, g, b;
} ndrPixel;