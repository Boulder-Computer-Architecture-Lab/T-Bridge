/**
 * @file      cache.h
 * @brief     Cache class definition.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#ifndef CACHE_H
#define CACHE_H

#include <tuple>
#include <vector>

#include <core/cache_components.h>

class Cache
{
public:
    // Constructor. Initializes all the members.
    Cache(std::size_t sets, std::size_t ways, std::size_t line_size);

    // Destructor. Deallocates all the members.
    ~Cache();

    
    // Perform an operation on the cache.
    void PerformOperation(Operation const operation, address_t const address);

    // Flush all cache sets.
    void Flush();
private:
    // Amount of sets.
    std::size_t const c_set_count;

    // Amount of ways.
    std::size_t const c_way_count;
    
    // Cache Line size.
    std::size_t const c_line_size;

    // Shift needed from address to get set.
    address_t const c_set_shift;

    // Shift needed from address to get tag.
    address_t const c_tag_shift;

    // Byte within line mask.
    address_t const c_byte_mask;

    // Set mask.
    address_t const c_set_mask;


    // Cache Sets.
    std::vector<CacheSet*> m_sets;


    // Parses the tag and set from an address.
    std::tuple<address_t, tag_t, set_t> ParseAddress(address_t address) const;
};

#endif // CACHE_H