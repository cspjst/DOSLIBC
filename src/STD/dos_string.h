#ifndef STRING_H
#define STRING_H

#ifdef USE_DOSLIBC

    #include "dos_stddef.h"

    // String manipulation
    // strcpy // copies one string to another
    // strcat // concatenates two strings
    // strdup // allocates a copy of a string - must free

    // String examination
    size_t strlen(const char* s);                 // returns the length of a given string
    int strcmp(const char* s1, const char* s2);     // compares two strings
    int strncmp(const char *s1, const char *s2, size_t n); // compares a certain amount of characters of two strings
    char* strchr(const char *s, int c);          // finds the first occurrence of a character
    char* strrchr(const char *s, int c);         // finds the last occurrence of a character
    // strspn // returns the length of the maximum initial segment that consists of only the characters found in another byte string
    // strcspn returns the length of the maximum initial segment that consists of only the characters not found in another byte string
    // strpbrk // finds the first location of any character in one string, in another string
    // strstr //finds the first occurrence of a substring of characters
    // strtok // finds the next token in a byte string

    // Character array manipulation
    // memchr   // searches an array for the first occurrence of a character
    int memcmp(const void *s1, const void *s2, size_t n);   // compares two buffers
    void* memset(void *s, int c, size_t n);   // fills a buffer with a character
    void* memcpy(void *dest, const void *src, size_t n);   // copies one buffer to another
    // memmove  // moves one buffer to another
    // memccpy  // copies one buffer to another, stopping after the specified delimiter
    void* memmem(const void* haystack, size_t hsize, const void* needle, size_t nsize); // finds the start of the first occurrence of the substring needle of size nsize in the memory area haystack of size hsize

    // Miscellaneous
    const char* strerror(int errnum);

#else

    #include <string.h>

#endif // USE_DOSLIBC

#endif
