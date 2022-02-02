@echo off

set _NAME=test
set _PROJECT_DIR=..\
set _BIN_DIR=bin\%_NAME%\

set _INCLUDE_DIRS=src\ ext\stb_image\
set _SOURCE_DIRS=src\
@REM Debug
set _DEFINES=_DEBUG
set _CONFIG_FLAGS=-Werror -g
@REM Release
@REM set _DEFINES=NDEBUG
@REM set _CONFIG_FLAGS=-Werror -O2

set _LIB_DIRS=
set _LIBS=libucrt

call build_project.bat