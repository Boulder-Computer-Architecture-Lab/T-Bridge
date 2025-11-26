/**
 * @file      config_reader.cpp
 * @brief     Config reader class implementation.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <utils/config_reader.h>

#include <typedefs.h>
#include <iostream>

#include <tomlplusplus/include/toml++/toml.h>

// Define the static config member.
Config ConfigReader::m_config;

void ConfigReader::Load(std::string const& config_file)
{
    auto config_data = toml::parse_file(config_file);

    // Load the cache parameters.
    m_config.m_sets      = config_data["CACHE"]["sets"].value_or(0);
    m_config.m_ways      = config_data["CACHE"]["ways"].value_or(0);
    m_config.m_line_size = config_data["CACHE"]["line_size"].value_or(0);

    // Load the input and output trace file paths.
    m_config.m_input_trace_file  = config_data["IO"]["input_trace_file"].value_or("");
    m_config.m_output_trace_file = config_data["IO"]["output_trace_file"].value_or("");

    ValidateConfig();
}

void ConfigReader::PrintConfig()
{
    std::cout << "Loaded Configuration:" << std::endl;
    std::cout << std::endl;
    std::cout << "Cache:" << std::endl;
    std::cout << "  Sets: " << m_config.m_sets << std::endl;
    std::cout << "  Ways: " << m_config.m_ways << std::endl;
    std::cout << "  Line Size: " << m_config.m_line_size << " bytes" << std::endl;
    std::cout << std::endl;
    std::cout << "Input Trace File: " << m_config.m_input_trace_file << std::endl;
    std::cout << "Output Trace File: " << m_config.m_output_trace_file << std::endl;
    std::cout << "---------------------" << std::endl << std::endl;
}

Config const& ConfigReader::GetConfig()
{
    return m_config;
}

void ConfigReader::ValidateConfig()
{
    // Validate that cache parameters are powers of two and greater than zero.
    if (m_config.m_sets == 0)
        throw std::runtime_error("Invalid configuration: Cache sets must be greater than 0.");

    if (!IsPow2(m_config.m_sets))
        throw std::runtime_error("Invalid configuration: Cache sets must be a power of 2.");

    if (m_config.m_ways == 0)
        throw std::runtime_error("Invalid configuration: Cache ways must be greater than 0.");

    if (!IsPow2(m_config.m_ways))
        throw std::runtime_error("Invalid configuration: Cache ways must be a power of 2.");
        
    if (m_config.m_line_size == 0)
        throw std::runtime_error("Invalid configuration: Cache line size must be greater than 0.");

    if (!IsPow2(m_config.m_line_size))
        throw std::runtime_error("Invalid configuration: Cache line size must be a power of 2.");

    // Validate that trace file paths are not empty.
    if (m_config.m_input_trace_file.empty())
        throw std::runtime_error("Invalid configuration: Input trace file path is empty.");

    if (m_config.m_output_trace_file.empty())
        throw std::runtime_error("Invalid configuration: Output trace file path is empty.");
}