/**
 * @file      main.cpp
 * @brief     Main program to demonstrate cache operations and trace engine usage.
 * @author    Victor Jimenez (victor.jimenez@colorado.edu)
 * @date      2025-11-25
 * 
 * Boulder Computer Architecture Research Lab, University of Colorado Boulder, Colorado, USA
 * 
 * If you use this code for your research, please cite:
 * Victor Jimenez, "Unpublished Research", 2025.
 */

#include <iostream>
#include <stdint.h>
#include <stdio.h>

#include <trace_engine.h>
#include <cache.h>

int main(int argc, char* argv[])
{
    TraceEngine::Initialize("trace.out");
    Cache cache(/* Sets */ 32768, /* Ways */ 8, /* Line size */ 64);

    cache.PerformOperation(Operation::LOAD, 0x1234567890ABCDEF);
    cache.PerformOperation(Operation::STORE, 0x1234567890ABCDE0);
    cache.PerformOperation(Operation::STORE, 0x1244567890ABCDE0);
    cache.Flush();

    TraceEngine::Shutdown();
    return 0;
}
