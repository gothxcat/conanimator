/*
*   Filesystem and animation loader
*/

#ifndef __LOADER
#define __LOADER

#include <cstdlib>
#include <vector>
#include <map>

// Program headers
#include <animator.hpp>

class Loader;
typedef std::map<char, std::function<int(Loader*)>> map_kb_func;

void start(Animator *animator);
int run_anim(const char *path);

#include "../loader.cpp"

#endif