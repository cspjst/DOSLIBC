#ifndef DOS_STDLIB_H
#define DOS_STDLIB_H

#ifdef USE_DOSLIBC

    #include "dos_stddef.h"
    #include "../DOS/dos_services.h"

    void* malloc(size_t size);
    void free(void* p);
    void* calloc(size_t n, size_t size);

    #define exit(status) dos_terminate_process_with_return_code(status)

#else

    #include <stdlib.h>

#endif // USE_DOSLIBC

#endif
