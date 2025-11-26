/**
 * @file      config_reader.h
 * @brief     Config reader class definition. Handles reading configuration files.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <cstdint>
#include <string>

struct Config
{
    // Amount of sets in the cache.
    std::size_t m_sets;

    // Amount of ways in the cache.
    std::size_t m_ways;

    // Size of a line in the cache.
    std::size_t m_line_size;

    // Path to the input trace file.
    std::string m_input_trace_file;

    // Path to the output trace file.
    std::string m_output_trace_file;
};

class ConfigReader
{
public:
    // Loads the configuration file.
    static void Load(std::string const& config_file);

    // Print the loaded configuration.
    static void PrintConfig();

    // Returns the loaded configuration.
    static Config const& GetConfig();
private:
    // Configuration data.
    static Config m_config;


    // Sanity check the loaded configuration.
    static void ValidateConfig();
};

#endif // CONFIG_READER_H