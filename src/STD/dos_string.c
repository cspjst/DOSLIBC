#ifdef USE_DOSLIBC

#include "dos_string.h"
#include "dos_errno.h"

// String examination

size_t strlen(const char* s) {
    if (!s) return 0;

    size_t n = 0;
    while (*s++) n++;

    return n;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    if (!s1 || !s2) return (s1 > s2) - (s1 < s2);

    for (; n && *s1 && (*s1 == *s2); --n, ++s1, ++s2);

    return n ? (unsigned char)*s1 - (unsigned char)*s2 : 0;
}

char* strchr(const char *s, int c) {
    while (*s != '\0' && (unsigned char)*s != (unsigned char)c)
        s++;

    return (unsigned char)*s == (unsigned char)c ? (char*)s : NULL;
}

char* strrchr(const char *s, int c) {
    char* last = NULL;
    while (*s != '\0') {
        if (*s == c) last = (char*)s;
        s++;
    }
    if (c == '\0') return (char*)s;
    return last;
}

// Character array manipulation

int memcmp(const void *s1, const void *s2, size_t n) {
    if (!s1 || !s2) return (s1 > s2) - (s1 < s2);

    const unsigned char* _s1 = (const unsigned char*)s1;
    const unsigned char* _s2 = (const unsigned char*)s2;

    while (n--) {
        if (*_s1 != *_s2) return *_s1 - *_s2;
        _s1++;
        _s2++;
    }

    return 0;
}

void* memset(void *s, int c, size_t n) {
    if (!s) return NULL;

    unsigned char* _s = (unsigned char*)s;
    unsigned char _c = (unsigned char)c;

    while (n--) *_s++ = _c;

    return s;
}

void* memcpy(void *dest, const void *src, size_t n) {
    if (!dest || !src) return NULL;

    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    while (n--) *d++ = *s++;

    return dest;
}

void* memmem(const void* haystack, size_t hsize, const void* needle, size_t nsize) {
    if (!haystack || !hsize || !needle || (nsize > hsize)) return NULL;
    if (!nsize) return (void*)haystack;     // as per POSIX return haystack pointer if needle is empty

    const unsigned char* hay = (const unsigned char*)haystack;
    const unsigned char* ndl = (const unsigned char*)needle;

    while(nsize <= hsize--) {
        if(memcmp(hay, ndl, nsize) == 0) return (void*)hay;
        hay++;
    }

    return NULL;
}

// Error conversion

const char* strerror(int errnum) {
    switch (errnum) {
        case 0:       return "No error";
        case EPERM:   return "Operation not permitted";
        case ENOENT:  return "No such file or directory";
        case EIO:     return "Input/output error";
        case EBADF:   return "Bad file descriptor";
        case ENOMEM:  return "Cannot allocate memory";
        case EACCES:  return "Permission denied";
        case EFAULT:  return "Bad address";
        case EEXIST:  return "File exists";
        case EXDEV:   return "Cross-device link";
        case ENODEV:  return "No such device";
        case EINVAL:  return "Invalid argument";
        case EMFILE:  return "Too many open files";
        case ENOSYS:  return "Function not implemented";
        default:      return "Unknown error";
    }
}

#endif // USE_DOSLIBC
