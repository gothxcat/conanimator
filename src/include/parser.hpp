/*
*   Console and argument parsing
*/

#ifndef __CONSOLE
#define __CONSOLE

#include <cstdlib>
#include <string>

// Library headers
#include <argparse/argparse.hpp>

argparse::ArgumentParser setup(std::string name, std::string version, std::string description);
int parse(argparse::ArgumentParser program, int argc, char **argv);
int process(argparse::ArgumentParser program);
std::string gen_help_run();

#include "../parser.cpp"

#endif