/*
*	ncurses screen definitions
*/

#ifndef __SCR
#define __SCR

#include <cstdlib>
#include <curses.h>

/* Initialise ncurses stdscr and set console UI/input props */
WINDOW *scr_setup() {
    initscr();
	cbreak();
	noecho();
	nonl();
	curs_set(0);
	intrflush(stdscr, true);
	keypad(stdscr, true);
	return stdscr;
}

#define scr_end()           endwin()

#endif