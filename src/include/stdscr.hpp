/*
*	ncurses screen definitions
*/

#ifndef __SCR
#define __SCR

#include <stdlib.h>
#include <ncurses.h>

WINDOW *scr_setup() {
    initscr();
	cbreak();
	noecho();
	intrflush(stdscr, true);
	keypad(stdscr, true);
	return stdscr;
}

#define scr_end()           endwin()

#endif
