# ndrRayTracer
This is my attempt at the "Ray Tracing in One Weekend" book. It is written in C, and implements basic Ray Tracing, as well as multithreading.

# Supported Platforms:
## OS:
- Windows
## Compilers:
- Clang

# How to Build:

# TODO:
- [ ] Compiler Support:
    - [x] Clang
    - [ ] MSVC
- [ ] Implement Ray Tracer
    - [ ] Write Ray Tracer Data to Image
    - [ ] World, Objects(Spheres), Materials
    - [ ] Camera
    - [ ] Lights
    - [ ] More Objects (Boxes)
- [ ] Implement Multithreading
    - [ ] Mutex
    - [ ] Condition Variables
    - [ ] Threads
    - [ ] Thread Pools
- [ ] Implement Window
    - [ ] Create and Destroy Window
    - [ ] Display Ray Tracer Data to Window

# Libraries:
- Writing Images: [_stb_image_write.h_](https://github.com/nothings/stb/blob/master/stb_image_write.h)

# Sources:
- Inspired by: [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- Thread Pool Implementation: [_Thread Pool In C_](https://nachtimwald.com/2019/04/12/thread-pool-in-c/)