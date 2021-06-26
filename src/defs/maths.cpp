/*
*   Maths and conversion defs
*/

#include <stdlib.h>
#include <math.h>
#include "../include/maths.hpp"

useconds_t get_delay(float frametime_s, float target_frametime_s) {
    int diff = floor(S_TO_USECONDS(target_frametime_s - frametime_s));
    return diff > 0 ? diff : 0;
}
