#ifndef DOS_BOOL_H
#define DOS_BOOL_H

#ifdef USE_DOSLIBC

    typedef unsigned char dos_bool;
    #define true 1
    #define false 0

    #ifdef USE_DOSLIBC
        #define bool  dos_bool
    #endif

#else

    #include <stdbool.h>

#endif // USE_DOSLIBC

#endif
