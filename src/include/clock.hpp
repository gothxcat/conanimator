/*
*   Clock and timing defs
*/

#ifndef __CLOCK
#define __CLOCK

#include <stdlib.h>
#include <chrono>

typedef std::chrono::high_resolution_clock hres_clock;
typedef std::chrono::duration<double> duration_d;

#endif
