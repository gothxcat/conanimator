/*
*   Animator classes and definitions
*/

#ifndef __ANIMATOR
#define __ANIMATOR

#include <cstdlib>
#include <curses.h>
#include <thread>

#define DEFAULT_FPS 60

class Animator;
class StringAnimator;
class FrameAnimator;

struct Animation {
    unsigned int framerate;
    std::vector<const char*> frames;
};

#include "../animator.cpp"

#endif