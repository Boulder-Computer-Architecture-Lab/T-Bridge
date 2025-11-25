/**
 * @file      trace_engine.h
 * @brief     Trace engine class definition. Handles recording memory operations to a trace file.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#ifndef TRACE_ENGINE_H
#define TRACE_ENGINE_H

#include <typedefs.h>
#include <string>

class TraceEngine
{
public:
    // Opens the output file.
    static void Initialize(std::string const& trace_file);

    // Closes the output file.
    static void Shutdown();

    // Record a load in the trace.
    static void Load(address_t const address);

    // Record a store in the trace.
    static void Store(address_t const address);
private:
    // Output file stream.
    static std::ofstream m_output_file;

    // Is active.
    static bool m_is_active;

    // Has it been shutdown.
    static bool m_is_shutdown;


    // Is the TraceEngine Active? (Initialized and not shutdown)
    static void CheckActive();
};

#endif // TRACE_ENGINE_H