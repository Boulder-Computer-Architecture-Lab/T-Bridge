/**
 * @file      trace_reader.cpp
 * @brief     Trace reader class implementation.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <utils/trace_reader.h>

#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

// Initialize static hex lookup table.
uint8_t TraceReader::c_hex_lookup[256] =
{
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    0, 1, 2, 3, 4, 5, 6, 7, 
    8, 9, 255, 255, 255, 255, 255, 255, 
    255, 10, 11, 12, 13, 14, 15, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 10, 11, 12, 13, 14, 15, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255, 
    255, 255, 255, 255, 255, 255, 255, 255
};


TraceReader::TraceReader(const std::string& filename) : m_cursor(0), m_fd(-1), m_data(nullptr), m_file_size(0)
{
    // Open file descriptor.
    m_fd = open(filename.c_str(), O_RDONLY);
    if (m_fd == -1) 
        throw std::runtime_error("Error: Could not open file " + filename);

    // Get file size.
    struct stat sb;

    if (fstat(m_fd, &sb) == -1)
        throw std::runtime_error("Error: Could not get file size for " + filename);

    m_file_size = sb.st_size;

    // Memory Map the file.
    // PROT_READ: We only need to read.
    // MAP_PRIVATE: Changes are not written back to disk.
    m_data = (char*) mmap(nullptr, m_file_size, PROT_READ, MAP_PRIVATE, m_fd, 0);

    if (m_data == MAP_FAILED)
        throw std::runtime_error("Error: mmap failed for file " + filename);
    
    // Use madvise to tell OS we will read sequentially (triggers aggressive pre-fetching)
    madvise(m_data, m_file_size, MADV_SEQUENTIAL);
}

TraceReader::~TraceReader()
{
    // Unmap memory
    if (m_data && m_data != MAP_FAILED)
        munmap(m_data, m_file_size);
    
    // Close file descriptor
    if (m_fd != -1)
        close(m_fd);
}

bool TraceReader::GetNextAccess(Operation& op_type, address_t& address)
{
    // Check for end of file after reading operation type and whitespace.
    if (m_cursor + 3 >= m_file_size) return false;

    // Read operation type. 
    char const op_type_char[2] = {m_data[m_cursor++], m_data[m_cursor++]};
    if (op_type_char[0] == 'L' && op_type_char[1] == 'D')
        op_type = LOAD;
    else if (op_type_char[0] == 'S' && op_type_char[1] == 'T')
        op_type = STORE;
    else
        throw std::runtime_error("TraceReader Error: Unknown operation type '" + std::string(op_type_char, 2) + "' in trace file.");
    
    // Expect whitespace after operation type.
    if (m_data[m_cursor++] != ' ')
        throw std::runtime_error("TraceReader Error: Expected whitespace after operation type!");

    // Skip "0x" if present.
    if (m_cursor + 1 < m_file_size && (m_data[m_cursor + 1] == 'x' || m_data[m_cursor + 1] == 'X'))
        m_cursor += 2;

    // Initialize address to zero.
    address = 0;
    
    // Read hexadecimal address.
    char character;
    while (m_cursor < m_file_size)
    {
        // Read the next character.
        character = m_data[m_cursor++];

        // Lookup the hex value using the lookup table.
        uint8_t val = c_hex_lookup[static_cast<uint8_t>(character)];

        // If non-hex character, break.
        if (val == 255) break; 

        // Shift address left by 4 bits and add the new hex digit.
        address = (address << 4) | val;
    }

    if (character != '\n' && character != '\r' && m_cursor < m_file_size)
        throw std::runtime_error("TraceReader Error: Expected newline after address!");

    return true;
}