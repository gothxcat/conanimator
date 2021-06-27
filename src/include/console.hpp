/*
*   Console and arguments header
*/

#ifndef __CONSOLE
#define __CONSOLE

#include <stdlib.h>
#include <argparse.hpp>
#include <string>

argparse::ArgumentParser setup(std::string name, std::string version, std::string description);
int parse(argparse::ArgumentParser program, int argc, char **argv);
int process(argparse::ArgumentParser program);
std::string gen_help_run();

#include "../defs/console.cpp"

#endif
