#include "str.h"
#include "util.h"

U16 strLen(const char *s) {
	U16 c = 0;
	for (;*s != '\0'; ++c) ++s;
	return c;
}

