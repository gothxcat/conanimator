/*
*   Maths and conversion defs
*/

#include <stdlib.h>
#include <math.h>

#include <maths.hpp>

/*  Calculate delay in microseconds to reach target frametime -> stabilise framerate
*   Round down difference between current and target, zero if behind */
useconds_t get_delay(float frametime_s, float target_frametime_s) {
    int diff = floor(S_TO_USECONDS(target_frametime_s - frametime_s));
    return diff > 0 ? diff : 0;
}
