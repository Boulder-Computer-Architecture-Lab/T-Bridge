/**
 * @file      main.cpp
 * @brief     Main program to demonstrate cache operations and trace engine usage.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <iostream>
#include <stdint.h>
#include <stdio.h>

#include <utils/trace_reader.h>
#include <utils/config_reader.h>
#include <utils/trace_engine.h>
#include <core/cache.h>

int main(int argc, char* argv[])
{
    ConfigReader::Load("sim.conf");
    ConfigReader::PrintConfig();

    Config config = ConfigReader::GetConfig();
    TraceEngine::Initialize(config.m_output_trace_file);

    TraceReader trace_reader(config.m_input_trace_file);

    Cache cache(/* Sets */ config.m_sets, /* Ways */ config.m_ways, /* Line size */ config.m_line_size);

    Operation op_type;
    address_t address;

    while (trace_reader.GetNextAccess(op_type, address))
        cache.PerformOperation(op_type, address);

    cache.Flush();
    TraceEngine::Shutdown();
    return 0;
}
