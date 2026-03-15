#include "dos_memory_tools.h"

int dos_memcmp(const void* s1, const void* s2, size_t n) {
    if (!s1 || !s2) return (s1 > s2) - (s1 < s2);

    const unsigned char* l = (const unsigned char*)s1;
    const unsigned char* r = (const unsigned char*)s2;

    while (n--) {
        if (*l != *r) return *l - *r;
        l++;
        r++;
    }

    return 0;
}

void* dos_memmem(const void* haystack, size_t hsize, const void* needle, size_t nsize) {
    if (!haystack || !hsize || !needle || (nsize > hsize)) return NULL;
    if (!nsize) return (void*)haystack;     // as per POSIX return haystack pointer if needle is empty

    const unsigned char* hay = (const unsigned char*)haystack;
    const unsigned char* ndl = (const unsigned char*)needle;

    while(nsize <= hsize--) {
        if(dos_memcmp(hay, ndl, nsize) == 0) return (void*)hay;
        hay++;
    }

    return NULL;
}
