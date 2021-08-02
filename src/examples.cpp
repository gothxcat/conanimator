/*
*   Built-in animation functions
*/

#include <cstdlib>
#include <map>

// Program headers
#include <examples.hpp>
#include <maths.hpp>
#include <animator.hpp>
#include <loader.hpp>
#include <fs.hpp>

// string to function pointer map 
map_str_func tests = {
    { "frames", &test_frames },
    { "string", &test_string }
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