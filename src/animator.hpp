/*
*	animator.hpp
*/

#ifndef __ANIMATOR
#define __ANIMATOR

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

void animate(const char *str, size_t len, char current_ch, useconds_t interval, bool *completed) {
	while (!*completed) {
		clear();
		for (int i=0; i<len; i++) {
			current_ch = str[i];
			addch(current_ch);
			refresh();
			usleep(interval);
		}
	}
}

#endif
