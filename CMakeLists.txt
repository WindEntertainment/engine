cmake_minimum_required(VERSION 3.22)

project(wind)

message("Building with CMake version: ${CMAKE_VERSION}")
message("WASM: ${BUILD_WASM}")
message("Output type: ${OUTPUT_TYPE}")

include(${CMAKE_SOURCE_DIR}/cmake/wind.cmake)

###===================================================================================##

import(compiler ON)
message(STATUS "C Compiler: ${CMAKE_C_COMPILER} (${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION})")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER} (${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION})")

###===================================================================================##

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

###===================================================================================##

add_subdirectory(./game/)
add_subdirectory(./engine/)
add_subdirectory(./editor/)
add_subdirectory(./asset-bundler/)
add_subdirectory(./wi/)

###===================================================================================##

import(tests OFF)
import(cpack ON)
