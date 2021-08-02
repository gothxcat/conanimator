/*
*	Program entrypoint
*/

#include <cstdlib>

// Library headers
#include <argparse/argparse.hpp>

// Program headers
#include <parser.hpp>

int main(int argc, char **argv) {
	// Setup and start argparser 
	argparse::ArgumentParser program = setup(
		"conanimator", "1.0.0", "A terminal-based 2D text/ASCII animator.");

	int ret = EXIT_SUCCESS;
	ret = parse(&program, argc, argv);
	if (ret == EXIT_SUCCESS) {
		ret = process(&program);
	}

	return ret;
}
