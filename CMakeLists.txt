cmake_minimum_required(VERSION 3.31)
project(syncnode CXX)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Configure with -DCMAKE_CXX_COMPILER=clang++")
endif()

# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Release)
# endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# generic target
add_library(build_options INTERFACE)

target_compile_options(build_options INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)

# utils
add_library(utils src/utils/utils.cpp)
target_include_directories(utils PUBLIC src/utils)
target_link_libraries(utils PRIVATE build_options)

# core
add_library(core src/core/core.cpp)
target_include_directories(core PUBLIC src/core)
target_link_libraries(core PRIVATE build_options)

# main
add_executable(syncnode src/app/main.cpp)

target_link_libraries(syncnode
    PRIVATE
    core
    utils
)
