/**
 * @file      clock.cpp
 * @brief     Global clock class implementation.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

 #include <clock.h>

// Define the static m_cycle member.
timestamp_t GlobalClock::m_cycle = 1;

void GlobalClock::Increment()
{
    // Increment the global cycle counter.
    m_cycle++;
}

void GlobalClock::Reset()
{
    // Reset the global cycle counter.
    m_cycle = 0;
}

timestamp_t GlobalClock::GetCycle()
{
    // Get the current global cycle count.
    return m_cycle;
}