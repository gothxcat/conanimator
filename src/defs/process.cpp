/*
*   ncurses animation start process
*/

#include <stdlib.h>
#include <ncurses.h>

// Program headers
#include <animators.hpp>

/*  Start the animator's thread with a reference to the exit value
*   and run the ncurses input loop */
void start(Animator *animator) {
    bool done = false;
    char key;
    animator->start(&done);
    while (key != 'q' && key != 'Q') {
		key = getch();
	}

    done = true;
    animator->end();
}