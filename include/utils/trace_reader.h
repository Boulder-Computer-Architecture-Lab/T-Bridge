/**
 * @file      trace_reader.h
 * @brief     Trace engine class definition. Handles reading memory operations from a trace file.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#ifndef TRACE_READER_H
#define TRACE_READER_H

#include <typedefs.h>
#include <string>

class TraceReader
{
public:
    // Constructor. The file is loaded and mmaped into memory.
    TraceReader(const std::string& filename);

    // Destructor. Unmaps the file and closes the file descriptor.
    ~TraceReader();

    // Retrieves the next memory access from the trace.
    bool GetNextAccess(Operation& op_type, address_t& address);
private:
    // Hexadecimal lookup table.
    static uint8_t c_hex_lookup[256];

    // Current cursor position in the mapped data.
    std::size_t m_cursor;

    // File descriptor.
    int m_fd;

    // Pointer to the memory-mapped data.
    char* m_data;

    // File size.
    std::size_t m_file_size;
};

#endif // TRACE_READER_H