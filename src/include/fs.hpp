/*
*   Filesystem and data parsing
*/

#ifndef __FS
#define __FS

#include <animations.hpp>

int read_file(char **data, const char *path);
Animation load_animation(const char *json_string);

#include "../defs/fs.cpp"

#endif
