/*
*	scr.hpp
*/

#ifndef __SCR
#define __SCR

#include <stdlib.h>
#include <ncurses.h>

void scr_setup() {
    initscr();
	cbreak();
	noecho();
	intrflush(stdscr, true);
	keypad(stdscr, true);
}

#define scr_end()           endwin()

#endif
