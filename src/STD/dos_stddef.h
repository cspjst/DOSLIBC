#ifndef __WATCOMC__
    #error "This module requires the (Open) Watcom C compiler!"
#endif

/**
 * @brief C99 stddef types and macros for 8086 large-model freestanding DOS
 * @note Defines size_t, ptrdiff_t, NULL, and offsetof()
 */
#ifndef DOS_STDDEF_H
#define DOS_STDDEF_H

/**
 * 8086 large model: objects live within 64KB segments, ergo 16-bit sufficient
 */
typedef unsigned short size_t;

/**
 * signed counterpart to size_t for pointer arithmetic
 */
typedef signed short ptrdiff_t;

/**
 * C standard: integer constant expression with value 0, cast to void*
 */
#define NULL ((void*)0)

/**
 * Standard compatible implementation: treat address 0 as base, take member address
 */
#define offsetof(type, member) ((size_t)&(((type*)0)->member))

#endif
