# ndrRayTracer
This is my attempt at the "Ray Tracing in One Weekend" book. It is written in C, and implements basic Ray Tracing, as well as multithreading.

# Supported Platforms:
## OS:
- Windows
## Compilers:
- Clang

# How to Build:
## Windows:
### Clang:
- Run `scripts\build_ray_tracer.bat`.
- By default, It will output to `bin\ndrRayTracer\ndrRayTracer.exe`.

# TODO:
- [ ] Compiler Support:
    - [X] Clang
    - [ ] MSVC
- [ ] Implement Ray Tracer
    - [X] Write Ray Tracer Data to Image
    - [X] World, Objects(Spheres), Materials
    - [X] Camera
    - [ ] Lights
    - [ ] More Objects (Boxes)
- [ ] Implement Multithreading
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