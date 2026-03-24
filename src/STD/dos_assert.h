/**
* @author      Jeremy Simon Thornton
* @copyright   2024 Jeremy Simon Thornton
* @version     0.1.0
*/
#ifndef DOS_ASSERT_H
#define DOS_ASSERT_H

#include "dos_stdlib.h"
#include "dos_stdio.h"

#ifdef NDEBUG
    #define dos_assert(expr) ((void)0)
#else
#define dos_assert(condition) \
    ((condition) \
    ? (void)0 \
    : (dos_printf("Assertion failed: %s, file %s, line %d\n", \
            #condition, __FILE__, __LINE__), \
        dos_exit(1)))
#endif

#endif
