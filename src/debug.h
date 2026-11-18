#include <stdio.h>
#include <stdbool.h>

#ifndef DEBUG_H
#define DEBUG_H

#ifdef _STDIO_H
#define test_debugging(...) fprintf(stderr, __VA_ARGS__)
#else
#define test_debugging(...) ((void)0)
#endif

#ifndef c_assert
#define c_assert(expr) ((expr) ? (true) : (test_debugging("%s, line %d: assertion '%s' failed!\n", __FILE__, __LINE__, #expr), (false)))
#endif

#endif