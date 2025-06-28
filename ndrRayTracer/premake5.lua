include "../defines"

project "ndrRayTracer"
    kind "StaticLib"
    language "C"
    cdialect "C17"
    targetdir "%{TARGETDIR}"
    objdir "%{OBJDIR}"

    files {
        "src/camera.*",
        "src/defines.*",
        "src/ndrMath.*",
        "src/ndrThread.*",
        "src/ndrTime.*",
        "src/object.*",
        "src/rayTracer.*",
        "src/screenBuffer.*",
        "src/world.*",
    }

    includedirs {
        "src",
    }

    filter "configurations:debug*"
        defines "_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:release*"
        runtime "Release"
        optimize "On"

    filter "system:windows"
        files {
            "src/ndrThread_win32.c",
        }