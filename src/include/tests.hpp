/*
*   Program tests
*/

#ifndef __TESTS
#define __TESTS

#include <stdlib.h>
#include <string>
#include <map>

typedef void                            func(void);
typedef std::map<std::string, func*>    function_map;

void test_string();
void test_frames();

#include "../defs/tests.cpp"

#endif
