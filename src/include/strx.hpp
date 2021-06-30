/*
*   String definitions and extensions
*/

#ifndef __STR_X
#define __STR_X

#include <stdlib.h>
#include <string.h>

struct PortableString {
    const char *str;
    size_t len;
};

#endif