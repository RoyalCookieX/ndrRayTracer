@echo off
setlocal EnableDelayedExpansion

if not exist %_PROJECT_DIR% (
    echo Invalid Project Directory '%_PROJECT_DIR%'
    exit /b 1
)
pushd %_PROJECT_DIR%

set _DEFINE_FLAGS=
set _LIB_FLAGS=
set _INCLUDE_DIR_FLAGS=
set _SOURCE_FILES=
set _LIB_DIR_FLAGS=

if not exist %_BIN_DIR% mkdir %_BIN_DIR%

for %%d in (%_DEFINES%) do set _DEFINE_FLAGS=!_DEFINE_FLAGS! -D%%d
for %%l in (%_LIBS%) do set _LIB_FLAGS=!_LIB_FLAGS! -l%%l
for %%i in (%_INCLUDE_DIRS%) do (
    if not exist %%i (
        echo Invalid Include Directory '%%i'
        exit /b 1
    )
    set _INCLUDE_DIR_FLAGS=!_INCLUDE_DIR_FLAGS! -I%%i
)

for %%l in (%_LIB_DIRS%) do (
    if not exist %%l (
        echo Invalid Library Directory '%%l'
        exit /b 1
    )
    set _LIB_DIR_FLAGS=!_LIB_DIR_FLAGS! -L%%l
)

for %%s in (%_SOURCE_DIRS%) do (
    if not exist %%s (
        echo Invalid Source Directory '%%s'
        exit /b 1
    )
    pushd %%s
    for /R %%f in (*.c) do (
        echo %%f
        set _SOURCE_FILES=!_SOURCE_FILES! %%f
    )
    popd
)

echo Building %_NAME%...
clang %_SOURCE_FILES% -o %_BIN_DIR%%_NAME%.exe -std=c17 %_CONFIG_FLAGS% %_INCLUDE_DIR_FLAGS% %_DEFINE_FLAGS% %_LIB_DIR_FLAGS% %_LIB_FLAGS%
echo -^> %_BIN_DIR%%_NAME%.exe
popd