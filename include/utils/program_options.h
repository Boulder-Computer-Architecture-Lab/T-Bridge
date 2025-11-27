/**
 * @file      program_options.h
 * @brief     Program options class definition. Handles parsing command-line arguments.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H

#include <string>

class ProgramOptions
{
public:
    // Constructor that parses command-line arguments.
    ProgramOptions(int argc, char* argv[]);

    
    // Configuration file path.
    std::string m_config_file;

    // Flag indicating whether the program should exit after displaying help or version info.
    bool m_should_exit;
private:
    // Prints usage information to the console.
    void PrintUsage() const;
};

#endif // PROGRAM_OPTIONS_H