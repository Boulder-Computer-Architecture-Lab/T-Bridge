/**
 * @file      trace_engine.cpp
 * @brief     Trace engine class implementation.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <utils/trace_engine.h>

#include <fstream>

// Define the static output file member.
std::ofstream TraceEngine::m_output_file;

// Define the static activity flag member.
bool TraceEngine::m_is_active = false;

// Define the static shutdown flag member.
bool TraceEngine::m_is_shutdown = false;

void TraceEngine::Initialize(std::string const& trace_file)
{
    // Check if already active or shutdown.
    if (m_is_active)
        throw std::runtime_error("TraceEngine is already initialized!");

    if (m_is_shutdown)
        throw std::runtime_error("Cannot initialize TraceEngine: it has already been shutdown!");

    // Open the output file.
    m_output_file.open(trace_file, std::ios::trunc); 

    // Check if the file opened successfully.
    if (!m_output_file.is_open())
        throw std::runtime_error("Could not write to output file " + trace_file);

    // Set active flag.
    m_is_active = true;
}

void TraceEngine::CheckActive()
{
    // Check if active.
    if (!m_is_active)
    {
        // Not active, check if shutdown.
        if (!m_is_shutdown)
            throw std::runtime_error("TraceEngine has not been initialized!");

        throw std::runtime_error("TraceEngine is already shutdown!");
    }
}

void TraceEngine::Load(address_t const address)
{
    // Log a load operation.
    CheckActive();
    m_output_file << "LD " << std::hex << address << std::dec << std::endl;
}


void TraceEngine::Store(address_t const address)
{
    // Log a store operation.
    CheckActive();
    m_output_file << "ST " << std::hex << address << std::dec << std::endl;
}

void TraceEngine::Shutdown()
{
    // Close the output file.
    m_output_file.close();

    // Set the trace engine to inactive and shutdown.
    m_is_active = false;
    m_is_shutdown = true;
}