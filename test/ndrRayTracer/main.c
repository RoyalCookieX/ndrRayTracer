#include <rayTracer.h>
#include <ndrTime.h>

#define MULTITHREADED 1
#define IMAGE_SIZE NDR_MAKE_UVEC2(800, 600)
#if MULTITHREADED
#define IMAGE_NAME "ray_tracer_mt.png"
#else
#define IMAGE_NAME "ray_tracer.png"
#endif

int main()
{
    uvec2 screenSize = IMAGE_SIZE;
    float aspect = (float)screenSize.x / (float)screenSize.y;

    ndrMaterial ground = NDR_MAKE_MATERIAL_LAMBERT(NDR_MAKE_COLOR(0.5f, 0.6f, 0.3f, 1.0f));
    ndrWorld world;
    ndrCreateWorld(5, &world);
    ndrAddObject(world, NDR_MAKE_OBJECT_SPHERE(NDR_MAKE_VEC3(0.0f, -101.0f, 0.0f), 100.0f, ground));

    ndrCamera camera;
    ndrSetViewport(&camera, 90.0f, aspect);
    ndrLookAt(&camera, NDR_MAKE_VEC3(0.0f, 2.0f, 2.0f), NDR_VEC3_ZERO, NDR_VEC3_UP);

    ndrScreenBuffer screenBuffer;
    ndrCreateScreenBuffer(screenSize, NDR_PIXEL_BLACK, &screenBuffer);

    ndrRenderSettings settings = {};
    settings.sampleCount = 50;
    settings.maxBounces = 100;
    settings.maxThreads = 8;
    settings.maxTasks = 16;

    ndrTime start, end;
    ndrGetTime(&start);
#if MULTITHREADED
    ndrRenderMultiThreaded(world, camera, screenBuffer, settings);
#else
    ndrRenderSingleThreaded(world, camera, screenBuffer, settings);
#endif
    ndrWriteFile(screenBuffer, IMAGE_NAME);
    ndrGetTime(&end);
    ndrTime elapsed = ndrGetElapsedSeconds(start, end);
    ndrPrintHHMMSS(elapsed);

    ndrDestroyWorld(world);
    ndrDestroyScreenBuffer(screenBuffer);
}