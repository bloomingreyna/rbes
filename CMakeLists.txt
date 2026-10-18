cmake_minimum_required(VERSION 3.19)

project(RBES VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "src/*.cpp", "src/*.c",
    "include/*.h"
)

add_executable(rbes_emu ${SRC_FILES})
target_include_directories(rbes_emu PRIVATE include/)
