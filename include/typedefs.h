/**
 * @file      typedefs.h
 * @brief     Type definitions for cache simulator.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <cstdint>
#include <type_traits>

// Type definitions
using address_t = uint64_t;
using tag_t = uint64_t;
using set_t = uint32_t;
using way_t = uint32_t;

using timestamp_t = uint64_t;

// Define program name and version to prevent IDE warnings. They will be set during compilation by CMake.
#ifndef SIMULATOR_NAME
    #define SIMULATOR_NAME ""
#endif
#ifndef SIMULATOR_VERSION
    #define SIMULATOR_VERSION ""
#endif

// Constants.
#define DEFAULT_CONFIG_FILE "sim.conf"
#define TIMESTAMP_MAX UINT64_MAX
#define NO_WAY static_cast<way_t>(-1)

// Operation types for cache access.
enum Operation
{
    LOAD,
    STORE
};

// Utility function to check if a number is a power of two.
template <typename T>
constexpr auto IsPow2(T n) -> typename std::enable_if<std::is_integral<T>::value, bool>::type
{
    return n > 0 && (n & (n - 1)) == 0;
}

#endif // TYPEDEFS_H