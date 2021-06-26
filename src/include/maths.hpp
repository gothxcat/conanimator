/*
*   Maths and conversion defs
*/

#ifndef __MATHS
#define __MATHS

#include <stdlib.h>
#include <math.h>

#define S_TO_USECONDS(s)            ((s)*1000000)
#define MS_TO_USECONDS(ms)          ((ms)*1000)
#define FRAMERATE(frametime)        (1/(frametime))
#define FRAMETIME(framerate)        (round(1/(framerate)))

struct Point {
    int x,y;
};

#include "../defs/maths.cpp"

#endif
