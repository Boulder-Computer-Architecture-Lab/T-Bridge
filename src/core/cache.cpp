/**
 * @file      cache.cpp
 * @brief     Cache class implementation.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <core/cache.h>

#include <utils/clock.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

Cache::Cache(std::size_t sets, std::size_t ways, std::size_t line_size) :
        c_set_count(sets),
        c_way_count(ways),
        c_line_size(line_size),
        c_set_shift(static_cast<address_t>(log2(c_line_size))),
        c_tag_shift(static_cast<address_t>(log2(c_set_count)) + c_set_shift),
        c_byte_mask((1 << static_cast<address_t>(log2(c_line_size))) - 1),
        c_set_mask((1 << static_cast<address_t>(log2(c_set_count))) - 1),
        m_sets(sets)
{
    std::cout << "Cache:          " << std::endl;
    std::cout << "    Sets:       " << c_set_count << std::endl;
    std::cout << "    Ways:       " << c_way_count << std::endl;
    std::cout << "    Line size:  " << line_size << " bytes" << std::endl;
    std::cout << "    Cache size: " << c_set_count * c_way_count * line_size << " bytes" << std::endl;
    std::cout << std::endl;
    std::cout << "    Tag shift:  " << c_tag_shift << std::endl;
    std::cout << "    Set shift:  " << c_set_shift << std::endl;
    std::cout << "    Byte mask:  " << std::hex << std::setfill('0') << std::setw(16) << c_byte_mask << std::dec << std::endl;
    std::cout << "    Set mask:   " << std::hex << std::setfill('0') << std::setw(16) << c_set_mask << std::dec << std::endl;

    // Validate parameters.
    if (!IsPow2(line_size))
        throw std::invalid_argument("Cache line size must be a power of 2.");

    if (!IsPow2(c_set_count))
        throw std::invalid_argument("Cache sets amount must be a power of 2.");

    if (!IsPow2(c_way_count))
        throw std::invalid_argument("Cache ways amount must be a power of 2.");

    // Initialize cache sets.
    for (set_t i = 0; i < c_set_count; ++i)
        m_sets[i] = new CacheSet(c_way_count, static_cast<set_t>(i));
}

void Cache::PerformOperation(Operation const operation, address_t const address)
{
    // Parse address.
    auto [full_address, tag, set] = ParseAddress(address);

    // Perform operation.
    switch (operation)
    {
        case Operation::LOAD:
            std::cout << "LD 0x" << std::hex << full_address << std::dec << std::endl;
            m_sets[set]->Load(full_address, tag);
            break;
        case Operation::STORE:
            std::cout << "ST 0x" << std::hex << full_address << std::dec << std::endl;
            m_sets[set]->Store(full_address, tag);
            break;
        default:
            throw std::invalid_argument("Unknown cache operation.");
    }

    // Increment global clock.
    GlobalClock::Increment();
}

std::tuple<address_t, tag_t, set_t> Cache::ParseAddress(address_t address) const
{
    // Mask out byte offset.
    address &= ~c_byte_mask;
    
    // Return masked address, tag, and set.
    return {address, (address >> c_tag_shift), (address >> c_set_shift) & c_set_mask};
}

void Cache::Flush()
{
    // Flush all cache sets.
    for (auto set : m_sets)
        set->Flush();
}

Cache::~Cache()
{
    // Destructor: Flush the cache and deallocate sets.
    Flush();
    
    for (auto set : m_sets)
        delete set;
}