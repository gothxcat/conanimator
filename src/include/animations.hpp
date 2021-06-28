/*
*   Animations and frames
*/

#ifndef __ANIMATIONS
#define __ANIMATIONS

#include <stdlib.h>
#include <vector>

#include <animator.hpp>

struct Animation {
    unsigned int framerate;
    std::vector<const char*> frames;
};

const Animation ANIM_TEST = {
    DEFAULT_FPS,
    {
        ".          ",
        "..         ",
        "...        ",
        "....       ",
        ".....      ",
        "......     ",
        ".......    ",
        "........   ",
        ".........  ",
        ".......... ",
        "...........",
        ".......... ",
        ".........  ",
        "........   ",
        ".......    ",
        "......     ",
        ".....      ",
        "....       ",
        "...        ",
        "..         ",
        ".          "
    }
};

#endif
