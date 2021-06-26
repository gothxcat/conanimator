/*
*	Program entrypoint
*/

#include <stdlib.h>
#include "include/maths.hpp"
#include "include/animators.hpp"
#include "include/proc.hpp"
#include "include/frames.hpp"

int main(int argc, char **argv) {
	// const char *msg = "Hello, world!";
	useconds_t interval = USECONDS(25);

	// StringAnimator animator = StringAnimator(msg, interval);
	FrameAnimator animator = FrameAnimator(ANIM_TEST, interval);
	start(&animator);
	
	return 0;
}
