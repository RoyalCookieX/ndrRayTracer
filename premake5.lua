workspace "ndrRayTracer"
    location ("build/" .. _ACTION)
    architecture "x86_64"
    startproject "sandbox"
    configurations { "debug", "debug-multithreaded", "release", "release-multithreaded" }

include "ndrRayTracer"
include "sandbox"