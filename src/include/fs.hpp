/*
*   Filesystem and data parsing
*/

#ifndef __FS
#define __FS

// Library headers
#include <cJSON.h>
#include <cJSON.c>

// Program headers
#include <animator.hpp>

int read_file(char **data, const char *path);
Animation load_animation(const char *json_string);

#include "../fs.cpp"

#endif