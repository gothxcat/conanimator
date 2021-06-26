/*
*   String tools
*/

#ifndef __STR
#define __STR

#include <stdlib.h>
#include <string.h>

struct PortableString {
    const char *str;
    size_t len;
};

#endif