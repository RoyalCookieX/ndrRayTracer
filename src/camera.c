#include "camera.h"
#include "ndrMath.h"

void ndrSetBottomLeft(ndrCamera* camera);

void ndrSetViewport(ndrCamera* camera, float fovDeg, float aspect)
{
    float theta = fovDeg * NDR_DEG_TO_RAD;
    float h = ndrTanF(theta / 2.0f);
    float viewportHeight = 2.0f * h;
    float viewportWidth = aspect * viewportHeight;
    camera->viewport.x = viewportWidth;
    camera->viewport.y = viewportHeight;
    ndrSetBottomLeft(camera);
}

void ndrLookAt(ndrCamera* camera, vec3 position, vec3 target, vec3 up)
{
    camera->position = position;

    camera->forward = ndrNormalizedVec3(ndrSubVec3(camera->position, target));
    camera->right = ndrNormalizedVec3(ndrCrossVec3(up, camera->forward));
    camera->up = ndrNormalizedVec3(ndrCrossVec3(camera->forward, camera->right));
    ndrSetBottomLeft(camera);
}

ray3 ndrViewportRay(ndrCamera camera, float u, float v)
{
    u = ndrClampF(u, 0.0f, camera.viewport.x);
    v = ndrClampF(v, 0.0f, camera.viewport.y);
    vec3 rayDirection = ndrSubVec3(ndrAddVec3(ndrAddVec3(camera.bottomLeft,
        ndrMulScalarVec3(camera.right, u * camera.viewport.x)),
        ndrMulScalarVec3(camera.up, v * camera.viewport.y)),
        camera.position);
    return (ray3){
        camera.position,
        ndrNormalizedVec3(rayDirection)
    };
}

void ndrSetBottomLeft(ndrCamera* camera)
{
    camera->bottomLeft = ndrSubVec3(ndrSubVec3(ndrSubVec3(camera->position, 
    ndrMulScalarVec3(camera->right, camera->viewport.x / 2.0f)), 
    ndrMulScalarVec3(camera->up, camera->viewport.y / 2.0f)),
    camera->forward);
}