workspace "ndrRayTracer"
    location ("build/" .. _ACTION)
    architecture "x86_64"
    startproject "sandbox"
    configurations { "debug", "release" }

include "ndrRayTracer"
include "sandbox"