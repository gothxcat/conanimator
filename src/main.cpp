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
	// useconds_t interval = MS_TO_USECONDS(25);
	// StringAnimator animator = StringAnimator(msg, interval);

	FrameAnimator animator = FrameAnimator(ANIM_TEST, 60);
	start(&animator);
	
	return 0;
}
