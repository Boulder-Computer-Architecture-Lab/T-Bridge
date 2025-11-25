
/**
 * @file      cache_components.h
 * @brief     Components that make up the cache: CacheLine and CacheSet.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

 #ifndef CACHE_COMPONENTS_H
#define CACHE_COMPONENTS_H

#include <typedefs.h>

struct CacheLine
{
    // Cache Line full address.
    address_t m_address;

    // Tag of the cache line.
    tag_t m_tag;

    // Way index.
    way_t m_way;

    // Valid bit.
    bool m_valid;

    // Dirty bit.
    bool m_dirty;

    // Last Access Timestamp.
    timestamp_t m_last_access;
};

class CacheSet
{
public:
    // Initialize the cache set.
    CacheSet(way_t ways, set_t set);

    // Class Destructor.
    ~CacheSet();
    
    
    // Perform a Load.
    void Load(address_t const address, tag_t const tag);

    // Perform a Store.
    void Store(address_t const address, tag_t const tag);

    // Flush existing lines to memory.
    void Flush();

private:
    // Amount of ways.
    way_t c_ways_count;

    // Cache set index.
    set_t c_set_index;

    // All the ways in the set.
    CacheLine* m_ways;


    // Locate a line for a given address. If not present, allocate a line for the given address.
    CacheLine& LocateAndAllocate(address_t const address, tag_t const tag);

    // Evict a line using LRU policy. Returns the way evicted.
    way_t EvictLRU();

    // Is the address in the set?
    // Returns the way if found, NO_WAY otherwise.
    way_t IsPresent(address_t const address) const;
};

#endif // CACHE_COMPONENTS_H