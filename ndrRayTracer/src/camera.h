#pragma once
#include "defines.h"

// Represents the view of a world.
typedef struct ndrCamera {
    vec2 viewport;
    vec3 position;
    vec3 bottomLeft;
    vec3 right;
    vec3 up;
    vec3 forward;
} ndrCamera;

// Sets the viewport of the camera.
void ndrSetViewport(ndrCamera* camera, float fovDeg, float aspect);
// Sets the camera's position, and where it's facing.
void ndrLookAt(ndrCamera* camera, vec3 position, vec3 target, vec3 up);
// Casts a ray from the camera's position to the specified UV coordinates of its viewport.
ray3 ndrViewportRay(ndrCamera camera, float u, float v);