#include "rayTracer.h"
#include "ndrThread.h"
#include "ndrMath.h"
#include <stdlib.h>

typedef struct ndrRenderArgs {
    ndrWorld world;
    ndrCamera camera;
    ndrScreenBuffer screenBuffer;
    ndrRenderSettings settings;
    uvec2 screenPosition;
} ndrRenderArgs;

void ndrRenderWorker(void* args);
ndrColor ndrGetRayColor(ndrWorld world, ray3 ray, uint32_t maxBounces);

bool ndrRenderSingleThreaded(ndrWorld world, ndrCamera camera, ndrScreenBuffer screenBuffer, ndrRenderSettings settings)
{
    if(world == NULL || screenBuffer == NULL)
        return false;

    for(uint32_t y = 0; y < screenBuffer->size.y; y++)
    {
        for(uint32_t x = 0; x < screenBuffer->size.x; x++)
        {
            ndrRenderArgs renderArgs;
            renderArgs.world = world;
            renderArgs.camera = camera;
            renderArgs.screenBuffer = screenBuffer;
            renderArgs.settings = settings;
            renderArgs.screenPosition = NDR_MAKE_UVEC2(x, y);
            ndrRenderWorker(&renderArgs);
        }
    }
    return true;
}

bool ndrRenderMultiThreaded(ndrWorld world, ndrCamera camera, ndrScreenBuffer screenBuffer, ndrRenderSettings settings)
{
    if(world == NULL || screenBuffer == NULL)
        return false;

    ndrThreadPool threadPool;
    ndrCreateThreadPool(settings.maxThreads, settings.maxTasks, &threadPool);
    ndrRenderArgs* renderArgs = malloc(sizeof(ndrRenderArgs) * settings.maxTasks); 
    uint32_t renderArgsIndex = 0;

    for(uint32_t y = 0; y < screenBuffer->size.y; y++)
    {
        for(uint32_t x = 0; x < screenBuffer->size.x; x++)
        {
            renderArgs[renderArgsIndex].world = world;
            renderArgs[renderArgsIndex].camera = camera;
            renderArgs[renderArgsIndex].screenBuffer = screenBuffer;
            renderArgs[renderArgsIndex].settings = settings;
            renderArgs[renderArgsIndex].screenPosition = NDR_MAKE_UVEC2(x, y);
            ndrAddTask(threadPool, ndrRenderWorker, &renderArgs[renderArgsIndex]);
            renderArgsIndex = (renderArgsIndex + 1) % settings.maxTasks;
        }
    }
    ndrWaitThreadPool(threadPool);

    free(renderArgs);
    ndrDestroyThreadPool(threadPool);
    return true;
}

void ndrRenderWorker(void* args)
{
    ndrRenderArgs* renderArgs = args;
    ndrWorld world = renderArgs->world;
    ndrCamera camera = renderArgs->camera;
    ndrScreenBuffer screenBuffer = renderArgs->screenBuffer;
    ndrRenderSettings settings = renderArgs->settings;
    uvec2 screenPosition = renderArgs->screenPosition;

    ndrColor color = NDR_COLOR_CLEAR;
    if(settings.sampleCount == 0)
    {
        float u = (float)(screenPosition.x) / (float)(screenBuffer->size.x);
        float v = (float)(screenPosition.y) / (float)(screenBuffer->size.y);
        ray3 cameraRay = ndrViewportRay(camera, u, v);
        color = ndrGetRayColor(world, cameraRay, settings.maxBounces);
    }
    else
    {
        for(uint32_t s = 0; s < settings.sampleCount; s++)
        {
            float u = (float)(screenPosition.x + (ndrRandomF01() * 2.0f - 1.0f)) / (float)(screenBuffer->size.x);
            float v = (float)(screenPosition.y + (ndrRandomF01() * 2.0f - 1.0f)) / (float)(screenBuffer->size.y);
            ray3 cameraRay = ndrViewportRay(camera, u, v);
            color = ndrAddColor(color, ndrGetRayColor(world, cameraRay, settings.maxBounces));
        }
    }
    color = ndrGammaCorrect(color, settings.sampleCount);
    color = ndrClampColor(color);
    ndrWritePixel(screenBuffer, screenPosition, ndrColorToPixel(color));
}

ndrColor ndrGetRayColor(ndrWorld world, ray3 ray, uint32_t maxBounces)
{
    if(maxBounces < 1)
        return NDR_COLOR_BLACK;

    ndrColor result = NDR_COLOR_CLEAR;
    ndrRaycastResult raycast;
    if (ndrRaycastWorld(world, ray, 0.001f, 100.0f, &raycast))
    {
        ray3 scatterRay;
        if(!ndrScatter(ray, raycast, &result, &scatterRay))
            return NDR_COLOR_BLACK;
        result = ndrMulColor(ndrGetRayColor(world, scatterRay, maxBounces - 1), result);
        result.a = 1.0f;
    }
    else
    {
        float t = (ray.direction.y + 1.0f) / 2.0f;
        result = ndrLerpColor(NDR_COLOR_WHITE, NDR_MAKE_COLOR(0.5f, 0.7f, 1.0f, 1.0f), t);
    }
    return result;
}