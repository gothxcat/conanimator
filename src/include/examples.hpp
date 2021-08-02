/*
*   Built-in example animations and test methods
*/

#ifndef __INTEGRATED_ANIMS
#define __INTEGRATED_ANIMS

#include <cstdlib>
#include <string>
#include <vector>
#include <map>

// Program headers
#include <animator.hpp>

typedef std::map<std::string, std::function<void()>> map_str_func;

void test_string();
void test_frames();

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

#include "../examples.cpp"

#endif