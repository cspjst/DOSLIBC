#ifndef DOS_BOOL_H
#define DOS_BOOL_H

typedef unsigned char dos_bool;
#define true 1
#define false 0

#ifdef USE_DOSLIBC
    #define bool  dos_bool
#endif

#endif
