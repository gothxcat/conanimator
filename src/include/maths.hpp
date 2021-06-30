/*
*   Maths and conversion defs
*/

#ifndef __MATHS
#define __MATHS

#include <stdlib.h>
#include <math.h>

// Unit conversion macros 
#define S_TO_USECONDS(s)            ((s)*1000000)
#define MS_TO_USECONDS(ms)          ((ms)*1000)

// Frame renderer macros via reciprocals 
#define FRAMERATE(frametime)        (1/(frametime))
#define FRAMETIME(framerate)        (round(1/(framerate)))

struct Point {
    int x,y;
};

#include "../defs/maths.cpp"

#endif