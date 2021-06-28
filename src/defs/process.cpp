/*
*   ncurses animation process
*/

#include <stdlib.h>

#include <animators.hpp>

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
