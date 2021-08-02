/*
*   Maths and conversion defs
*/

#ifndef __MATHS
#define __MATHS

#include <cstdlib>
#include <math.h>

// Unit conversion macros 
#define S_TO_USECONDS(s)            ((s)*1000000)
#define MS_TO_USECONDS(ms)          ((ms)*1000)

// Frame renderer macros via reciprocals 
#define FRAMERATE(frametime)        (round(1/(frametime)))
#define FRAMETIME(framerate)        (round(1/(framerate)))

// Storage sizes
#define SIZE_CHAR                   sizeof(char)

struct Point {
    int x,y;
};

/*  Calculate delay in microseconds to reach target frametime -> stabilise framerate
*   Round down difference between current and target, zero if behind */
useconds_t get_delay(float frametime_s, float target_frametime_s) {
    int diff = floor(S_TO_USECONDS(target_frametime_s - frametime_s));
    return diff > 0 ? diff : 0;
}

#endif