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

add_executable(syncnode src/utils/utils.cpp src/core/core.cpp src/app/main.cpp)

target_include_directories(syncnode PRIVATE src)

target_compile_options(syncnode
   PRIVATE
   -Wall -Wextra -Wpedantic -Wshadow -Wconversion
   $<$<CONFIG:Debug>:-g>
   $<$<CONFIG:Release>:-O3>)