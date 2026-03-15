/**
 * @brief Extra file functions, missing from DOS, that assist the programmer.
 */
#ifndef DOS_MEMORY_TOOLS_H
#define DOS_MEMORY_TOOLS_H

#ifdef POLICY_USE_DOS_STD
    #include "../STD/dos_stdint.h"
    #include "../STD/dos_stddef.h"
#else
    #include <stdint.h>
    #include <stddef.h>
#endif

/**
 * The dos_memmem() function finds the start of the first occurrence of the substring needle of size nsize
 * in the memory area haystack of size hsize.
 * @note the bytes of the memory area pointed to by haystack and needle are interpreted as unsigned char.
 * @return pointer to the beginning of the substring, or NULL if the substring is not found.
 */
void* dos_memmem(const void* haystack, size_t hsize, const void* needle, size_t nsize);

#endif
