@echo off

set _NAME=ndrRayTracer
set _PROJECT_DIR=..\
set _BIN_DIR=bin\%_NAME%\

set _INCLUDE_DIRS=src\ ext\stb_image\
set _SOURCE_DIRS=src\ test\%_NAME%\
@REM Debug
set _DEFINES=_DEBUG
@REM Release
@REM set _DEFINES=NDEBUG

set _LIB_DIRS=

if %1==clang (
    set _LIBS=libucrt
    set _CONFIG_FLAGS=-Werror -g
    call build_clang_project.bat
) else if %1==msvc (
    set _CONFIG_FLAGS=/EHsc /Zi /MTd
    call build_msvc_project.bat
) else (
    echo Usage: %~nx0 ^<clang^|msvc^>
    exit /b 1
)