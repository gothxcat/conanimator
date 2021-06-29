/*
*	ncurses screen definitions
*/

#ifndef __SCR
#define __SCR

#include <stdlib.h>
#include <ncurses.h>

/* Initialise ncurses stdscr and set console UI/input props */
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
