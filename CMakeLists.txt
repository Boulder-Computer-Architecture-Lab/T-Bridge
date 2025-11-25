# ==============================================================================
# Project:     CacheSimulator
# Author:      Victor Jimenez (victor.jimenez@colorado.edu)
# Institution: Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
# Date:        2025-11-25
# ==============================================================================

cmake_minimum_required(VERSION 3.10)
project(CacheSimulator VERSION 1.0.0 LANGUAGES CXX)

# Set C++17 as the required standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE DEBUG)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Common compiler flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror=return-type)

# Add debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")
    
# Add release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Define source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define header files
file(GLOB_RECURSE HEADERS "include/*.h")

# Define main executable
add_executable(cachesimulator ${SOURCES})

# Print configuration summary
message(STATUS "")
message(STATUS "Cache Simulator Build Configuration:")
message(STATUS "  Version:           ${PROJECT_VERSION}")
message(STATUS "  Build type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Compiler:      ${CMAKE_CXX_COMPILER}")
message(STATUS "  C++ Standard:      C++${CMAKE_CXX_STANDARD}")
message(STATUS "")