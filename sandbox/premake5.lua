include "../defines"

project "sandbox"
    kind "ConsoleApp"
    language "C"
    cdialect "C17"
    targetdir "%{TARGETDIR}"
    objdir "%{OBJDIR}"

    files {
        "src/main.*",
    }

    includedirs {
        "%{NDR_RAY_TRACER_INCLUDE}",
    }

    links {
        "ndrRayTracer",
    }

    filter "configurations:debug*"
        runtime "Debug"
        symbols "On"

    filter "configurations:release*"
        runtime "Release"
        optimize "On"

    filter "configurations:*-multithreaded"
        targetname "%{prj.name}-multithreaded"
        defines {
            "MULTITHREADED",
        }

    filter "action:vs*"
        debugdir "%{TARGETDIR}"
        debugargs {
            "ray_tracer.png",
        }

