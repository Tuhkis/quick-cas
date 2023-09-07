#ifndef UTIL_H
#define UTIL_H

#define MIN(a, b) (b + ((a - b) & (a - b) >> 31))
#define MAX(a, b) (a - ((a - b) & (a - b) >> 31))
#define ABS(x) ((x) < 0 ? -(x) : (x))

#if defined(_WIN32) || defined(_WIN64)
#ifndef OS_WINDOWS
#define OS_WINDOWS
#endif /* OS_WINDOWS */
#elif defined(__APPLE__) && defined(__MACH__)
#ifndef OS_OSX
#define OS_OSX
#endif /* OS_OSX */
#elif defined(__unix__)
#ifndef OS_UNIX
#define OS_UNIX
#endif /* OS_UNIX */
#if defined(__linux__)
#ifndef OS_LINUX
#define OS_LINUX
#endif /* OS_LINUX */
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#ifndef OS_FREEBSD
#define OS_FREEBSD
#endif /* OS_FREEBSD */
#else
#warning Unknown Unix.
#endif
#else
#warning Unknown OS.
#endif

#include <stdio.h>
#ifdef OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
// void printf_s(const char *fmt, ...);
#define PRINTF(fmt, ...) printf_s(fmt)
#define MAIN int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
#define MAIN int main(int argc, char **argv)
#define PRINTF(fmt, ...) printf(fmt)
#endif /* OS_WINDOWS */

#define ASSERT(cond) \
	if (!(cond)) { \
		PRINTF("Assert failed: %s, file %s, line %d\n", \
		#cond, __FILE__, __LINE__); exit(1); }

typedef unsigned char U8;
typedef signed char I8;

typedef unsigned short U16;
typedef signed short I16;

typedef unsigned int U32;
typedef signed int I32;

typedef unsigned long U64;
typedef signed long I64;

typedef float F32;
typedef double F64;

typedef struct frac {
	I32 a, b;
} Frac;

#define FRAC(x, y) ((Frac) {x, y})
#define FRAC2FLOAT(f) ((F32)(f.a) / (F32)(f.b))

F32 sq_root(U32 x);
U32 countDigits(I32 num);

Frac fracAdd(Frac x, Frac y);
Frac fracSub(Frac x, Frac y);
Frac fracMul(Frac x, Frac y);
Frac fracDiv(Frac x, Frac y);

#endif /* UTIL_H */

