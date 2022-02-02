#pragma once
#include "world.h"
#include "camera.h"
#include "screenBuffer.h"

// The settings used by the ray tracer.
typedef struct ndrRenderSettings {
    uint32_t sampleCount;
    uint32_t maxBounces;
    uint32_t maxThreads;
    uint32_t maxTasks;
} ndrRenderSettings;

// Renders the world from the camera, which outputs to the screenBuffer.
bool ndrRenderSingleThreaded(ndrWorld world, ndrCamera camera, ndrScreenBuffer screenBuffer, ndrRenderSettings settings);
// Renders the world from the camera, which outputs to the screenBuffer.
bool ndrRenderMultiThreaded(ndrWorld world, ndrCamera camera, ndrScreenBuffer screenBuffer, ndrRenderSettings settings);