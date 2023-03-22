#include <rayTracer.h>
#include <ndrMath.h>
#include <ndrTime.h>

#define MULTITHREADED 1

// world
#define GROUND_MATERIAL NDR_MAKE_MATERIAL_LAMBERT(NDR_MAKE_COLOR(0.5f, 0.6f, 0.3f, 1.0f))
#define MAX_OBJECTS 25

// camera
#define FOV_DEGREES 90.0f
#define CAMERA_POSITION NDR_MAKE_VEC3(0.0f, 5.0f, 7.0f)
#define CAMERA_TARGET NDR_VEC3_ZERO

// ray tracer
#define SAMPLE_COUNT 50
#define MAX_BOUNCES 100
#if MULTITHREADED
#define MAX_THREADS 8
#define MAX_TASKS 16
#else
#define MAX_THREADS 0
#define MAX_TASKS 0
#endif

#define IMAGE_SIZE NDR_MAKE_UVEC2(400, 300)
#if MULTITHREADED
#define IMAGE_NAME "ray_tracer_mt.png"
#else
#define IMAGE_NAME "ray_tracer.png"
#endif

ndrMaterial randomMaterial();
ndrObject randomObject();

int main()
{
    ndrMaterial mat = randomMaterial();
    uvec2 screenSize = IMAGE_SIZE;
    float aspect = (float)screenSize.x / (float)screenSize.y;

    ndrMaterial ground = GROUND_MATERIAL;
    ndrWorld world;
    ndrCreateWorld(MAX_OBJECTS, &world);
    ndrAddObject(world, NDR_MAKE_OBJECT_SPHERE(NDR_MAKE_VEC3(0.0f, -101.0f, 0.0f), 100.0f, ground));
    for(uint32_t i = 1; i < world->maxObjects; i++)
        ndrAddObject(world, randomObject());

    ndrCamera camera;
    ndrSetViewport(&camera, FOV_DEGREES, aspect);
    ndrLookAt(&camera, CAMERA_POSITION, CAMERA_TARGET, NDR_VEC3_UP);

    ndrScreenBuffer screenBuffer;
    ndrCreateScreenBuffer(screenSize, NDR_PIXEL_BLACK, &screenBuffer);

    ndrRenderSettings settings;
    settings.sampleCount = SAMPLE_COUNT;
    settings.maxBounces = MAX_BOUNCES;
    settings.maxThreads = MAX_THREADS;
    settings.maxTasks = MAX_TASKS;

    ndrTime start, end;
    ndrGetTime(&start);
    printf("Rendering %s...\n", IMAGE_NAME);
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

ndrMaterial randomMaterial()
{
    ndrMaterialType type = (ndrMaterialType)ndrRandomF(0, 3);
    ndrMaterial result;
    switch(type)
    {
        case NDR_MATERIAL_TYPE_LAMBERT: result = NDR_MAKE_MATERIAL_LAMBERT(ndrRandomColor()); break;
        case NDR_MATERIAL_TYPE_METAL: result =  NDR_MAKE_MATERIAL_METAL(ndrRandomColor(), ndrRandomF01()); break;
        case NDR_MATERIAL_TYPE_DIELECTRIC: result = NDR_MAKE_MATERIAL_DIELECTRIC(ndrRandomF(1.2f, 2.4f)); break;
        default: break; 
    }
    return result;
}

ndrObject randomObject()
{
    return NDR_MAKE_OBJECT_SPHERE(
        ndrMulScalarVec3(NDR_MAKE_VEC3(
            ndrRandomF(-5.0f, 5.0f),
            0.5f,
            ndrRandomF(-5.0f, 1.0f)), 
        ndrRandomF(0.1f, 3.0f)), 
        ndrRandomF(0.3f, 1.5f), 
        randomMaterial());
}