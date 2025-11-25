/**
 * @file      clock.h
 * @brief     Global clock class definition.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */


#ifndef CLOCK_H
#define CLOCK_H

#include <typedefs.h>

class GlobalClock
{
public:

    // Increment the Global Clock.
    static void Increment();

    // Reset the Global Clock.
    static void Reset();

    // Get the current cycle of the Global Clock.
    static timestamp_t GetCycle();
    
private:
    // Output file stream.
    static timestamp_t m_cycle;
};

#endif // CLOCK_H