/*
*   Program test definitions
*/

#include <stdlib.h>
#include <map>

#include <tests.hpp>
#include <maths.hpp>
#include <animations.hpp>
#include <proc.hpp>
#include <animations.hpp>
#include <fs.hpp>

function_map tests = {
    { "frames", (func*)&test_frames },
    { "string", (func*)&test_string }
};

void test_frames() {
    FrameAnimator animator = FrameAnimator(ANIM_TEST);
	start(&animator);
}

void test_string() {
    const char *msg = "Hello, world!";
	useconds_t interval = MS_TO_USECONDS(25);
	StringAnimator animator = StringAnimator(msg, interval);
    start(&animator);
}
