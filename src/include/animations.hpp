/*
*   Animation objects and frame examples
*/

#ifndef __ANIMATIONS
#define __ANIMATIONS

#include <stdlib.h>
#include <vector>

// Program headers
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