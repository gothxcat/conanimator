/*
*   Program test definitions
*/

#include <stdlib.h>
#include <map>
#include "../include/tests.hpp"
#include "../include/maths.hpp"
#include "../include/animators.hpp"
#include "../include/proc.hpp"
#include "../include/frames.hpp"

function_map tests = {
    { "frames", (func*)&test_frames },
    { "string", (func*)&test_string }
};

void test_frames() {
    FrameAnimator animator = FrameAnimator(ANIM_TEST, DEFAULT_FPS);
	start(&animator);
}

void test_string() {
    const char *msg = "Hello, world!";
	useconds_t interval = MS_TO_USECONDS(25);
	StringAnimator animator = StringAnimator(msg, interval);
    start(&animator);
}
