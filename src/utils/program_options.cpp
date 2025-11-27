/**
 * @file      program_options.cpp
 * @brief     Program options class implementation.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <utils/program_options.h>

#include <typedefs.h>

#include <stdexcept>
#include <iostream>
#include <filesystem>

ProgramOptions::ProgramOptions(int argc, char* argv[]) : m_config_file(DEFAULT_CONFIG_FILE), m_should_exit(false)
{
    // Parse command-line arguments.
    for (int i = 1; i < argc; ++i)
    {
        std::string argument = argv[i];
        
        if (argument == "-h" || argument == "--help")
        {
            PrintUsage();
            m_should_exit = true;
            return;
        } 
        else if (argument == "-f")
        {
            // Sanity Check: Is there a next argument?
            if (i + 1 < argc)
                m_config_file = argv[++i];
            else
                throw std::invalid_argument("The -f option requires a filename argument.");
        } 
        else if (argument == "-v")
        {
            std::cout << SIMULATOR_NAME << " version " << SIMULATOR_VERSION << std::endl;
            m_should_exit = true;
            return;
        } 
        else
        {
            
            std::cerr << "Error: Unknown option '" << argument << "'.\n";
            PrintUsage();
            m_should_exit = true;
            return;
        }
    }

    // Verify if the configuration file exists.
    if (!std::filesystem::exists(m_config_file))
        throw std::invalid_argument("Configuration file not found: " + m_config_file);
}

void ProgramOptions::PrintUsage() const
{
    std::cout << SIMULATOR_NAME << " version " << SIMULATOR_VERSION << std::endl
              << "Usage: " << SIMULATOR_NAME << " [options]" << std::endl
              << "Options: " << std::endl
              << "  -f <file>   Specify configuration file (Default: " << DEFAULT_CONFIG_FILE << ")" << std::endl
              << "  -v          Show version information" << std::endl
              << "  -h, --help  Show this help message" << std::endl;
}