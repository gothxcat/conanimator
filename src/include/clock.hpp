/*
*   Clock and timing definitions
*/

#ifndef __CLOCK
#define __CLOCK

#include <cstdlib>
#include <chrono>

typedef std::chrono::high_resolution_clock hres_clock;
typedef std::chrono::duration<double> duration_d;

#endif