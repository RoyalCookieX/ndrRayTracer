# ndrRayTracer
This is my attempt at the "Ray Tracing in One Weekend" book. It is written in C, and implements basic Ray Tracing, as well as multithreading.

# Supported Platforms:
## OS:
- Windows
## Build Targets
- Visual Studio 2022
- GNU Makefile

# How to Build:
## Windows:
- Clone this repository using ``git clone https://github.com/RoyalCookieX/ndrRayTracer.git``.
- From the repository directory, open a terminal and run ``scripts/premake5 <ACTION>``. This will create a ``build/<ACTION>`` folder containing the build files. Replace ``<ACTION>`` with either:
    - ``vs2022`` for Visual Studio 2022
    - ``gmake2`` for GNU Makefile
- The following steps are build target specific:
### Visual Studio:
- Open the solution file in the ``build/vs2022`` folder.
### GNU Makefile
- From the repository directory, run ``make -C build/gmake2 config=<CONFIG>``. This will create a ``bin/gmake2/<PROJECT_NAME>/<CONFIG>`` folder containing all the binaries. Replace ``<CONFIG>`` with either:
    - ``debug`` for debug build
    - ``release`` for release build

# TODO:
- [ ] Implement Ray Tracer
    - [X] Write Ray Tracer Data to Image
    - [X] World, Objects(Spheres), Materials
    - [X] Camera
    - [ ] Lights
    - [ ] More Objects (Boxes)
- [X] Implement Multithreading
    - [X] Mutex
    - [X] Condition Variables
    - [X] Threads
    - [X] Thread Pools
- [ ] Implement Window
    - [ ] Create and Destroy Window
    - [ ] Display Ray Tracer Data to Window

# Libraries:
- Writing Images: [_stb_image_write.h_](https://github.com/nothings/stb/blob/master/stb_image_write.h)

# Sources:
- Inspired by: [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- Thread Pool Implementation: [_Thread Pool In C_](https://nachtimwald.com/2019/04/12/thread-pool-in-c/)
