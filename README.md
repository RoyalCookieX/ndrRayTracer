# ndrRayTracer
This is my attempt at the "Ray Tracing in One Weekend" book. It is written in C, and implements basic Ray Tracing, as well as multithreading.

# Benchmark:
## System:
- CPU: AMD Ryzen 5 4600G
- RAM: 12 GB
## Ray Tracer Settings:
- Spheres: 50
- Samples: 50
- Max Samples: 100
- Max Threads (multithreaded): 8
- Max Tasks (multithreaded): 16

![](https://github.com/RoyalCookieX/ndrRayTracer/blob/main/benchmark/singlethreaded/n50-s50-b100.png?raw=true)*Singlethreaded (Release): 00:01:30 - 00:02:10*

![](https://github.com/RoyalCookieX/ndrRayTracer/blob/main/benchmark/multithreaded/n50-s50-b100.png?raw=true)
*Multithreaded (Release): 00:00:12 - 00:00:13*

# Supported Platforms:
## OS:
- Windows
## Build Targets
- Visual Studio (2022, 2019, ...)

# How to Build:
## Windows:
- Clone this repository using ``git clone https://github.com/RoyalCookieX/ndrRayTracer.git``.
- From the repository directory, open a terminal and run ``scripts/premake5 <ACTION>``. This will create a ``build/<ACTION>`` folder containing the build files. Replace ``<ACTION>`` with either:
    - ``vs2022`` for Visual Studio 2022
    - ``vs2019`` for Visual Studio 2019, etc...
- The following steps are build target specific:
### Visual Studio:
- Open the solution file in the ``build/<ACTION>`` folder.
- Select a ``<CONFIGURATION>``:
    - ``debug`` for debug singlethreaded build
    - ``debug-multithreaded`` for debug multithreaded build
    - ``release`` for release singlethreaded build
    - ``release-multithreaded`` for release multithreaded build
- Run the project with ``F5``, which will eventually output ``bin/<ACTION>/sandbox/<CONFIGURATION>/sandbox.png``.

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
