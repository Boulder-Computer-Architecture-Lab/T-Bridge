/**
 * @file      cache_components.cpp
 * @brief     Cache components implementation: CacheLine and CacheSet.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <core/cache_components.h>

#include <utils/clock.h>
#include <utils/trace_engine.h>

#include <stdexcept>

CacheSet::CacheSet(way_t ways, set_t set) : c_ways_count(ways), c_set_index(set)
{
    // Allocate ways.
    m_ways = new CacheLine[c_ways_count];

    // Initializes the ways to invalid.
    for (way_t way = 0; way < c_ways_count; ++way)
    {
        CacheLine& line = m_ways[way];
        line.m_address = 0;
        line.m_tag = 0;
        line.m_way = way;

        line.m_valid = false;
        line.m_dirty = false;

        line.m_last_access = 0;
    }
}

void CacheSet::Load(address_t const address, tag_t const tag)
{
    // Load the line and update the last access timestamp.
    CacheLine& way = LocateAndAllocate(address, tag);
    way.m_last_access = GlobalClock::GetCycle();
    
}

void CacheSet::Store(address_t const address, tag_t const tag)
{
    // Load the line, update the last access timestamp, and mark it as dirty.
    CacheLine& way = LocateAndAllocate(address, tag);
    way.m_dirty = true;
    way.m_last_access = GlobalClock::GetCycle();
    
}

CacheLine& CacheSet::LocateAndAllocate(address_t const address, tag_t const tag)
{
    // Check if the address is already present.
    way_t way = IsPresent(address);

    // Found the address in the set.
    if (way != NO_WAY)
        return m_ways[way];
    
    // Look for an empty way first.
    for (way_t i = 0; i < c_ways_count; ++i)
    {
        if (!m_ways[i].m_valid)
        {
            way = i;
            break;
        }
    }

    // If there are no empty lines, we need to evict one.
    if (way == NO_WAY)
        way = EvictLRU();

    // Allocate the new line.
    CacheLine& line = m_ways[way];

    line.m_address = address;
    line.m_tag = tag;
        
    line.m_valid = true;
    line.m_dirty = false;

    // Issue a Load.
    TraceEngine::Load(line.m_address);

    return line;
}

way_t CacheSet::EvictLRU()
{
    // Find the least recently used way.
    way_t lru_way = 0;
    timestamp_t lru_timestamp = TIMESTAMP_MAX;

    // For each way, find the one with the smallest last access timestamp.
    for (way_t i = 0; i < c_ways_count; ++i)
    {
        CacheLine const& line = m_ways[i];

        // Sanity check: all lines should be valid.
        if (!line.m_valid)
            throw std::runtime_error("EvictLRU called on non-full set.");

        if (line.m_last_access < lru_timestamp)
            lru_way = line.m_way;
    }
    
    CacheLine& line = m_ways[lru_way];

    // Issue a load if the previous line was dirty.
    if (line.m_dirty)
        TraceEngine::Store(line.m_address);

    // Set valid and dirty to false.
    line.m_valid = false;
    line.m_dirty = false;

    return lru_way;
}

way_t CacheSet::IsPresent(address_t const address) const
{
    // Check each way for the address.
    for (way_t i = 0; i < c_ways_count; ++i)
    {
        CacheLine const& line = m_ways[i];
        if (line.m_valid && line.m_address == address)
            return line.m_way;
    }
    
    // Not found.
    return NO_WAY;
}

void CacheSet::Flush()
{
    // For each way, if valid and dirty, issue a store.
    for (way_t i = 0; i < c_ways_count; ++i)
    {
        CacheLine& line = m_ways[i];

        if (line.m_valid && line.m_dirty)
            TraceEngine::Store(line.m_address);

        // Set valid and dirty to false.
        line.m_valid = false;
        line.m_dirty = false;
    }
}

CacheSet::~CacheSet()
{
    // Destructor: Flush the cache set and deallocate ways.
    Flush();
    delete[] m_ways;
}
