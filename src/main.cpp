/*
*	main.cpp
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <thread>

#include "scr.hpp"
#include "maths.hpp"
#include "animator.hpp"

int main(int argc, char **argv) {
	scr_setup();

	useconds_t interval = USECONDS(50);
	const char *msg = "Hello, world!";
	size_t len = strlen(msg);
	
	char key;
	char current_ch;
	bool done = false;
	std::thread animator(animate, msg, len, current_ch, interval, &done);

	while (key != 'q' && key != 'Q') {
		key = getch();
	}

	done = true;
	animator.join();
	scr_end();
	
	return 0;
}
