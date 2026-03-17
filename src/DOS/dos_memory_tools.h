/**
 * @brief pretty printing to stderr
 * @note needs only fputc to be defined
 * formatting characters:
 * + 'x'  lower case hexadecimal
 * + 'X'  upper case hexadecimal
 * + 'b'  binary
 * + 'd'  decimal
 * delimiters:
 * + any printable char
 * + '\0' no delimiter
 * bookends lhs and rhs:
 * + any printable char
 * + '\0' no bookend
 */
#ifndef DOS_MEMORY_TOOLS_H
#define DOS_MEMORY_TOOLS_H

#include "dos_memory_types.h"

#ifdef POLICY_USE_DOS_STD
    #include "../STD/dos_stddef.h"
#else
    #include <stddef.h>
#endif

#define DUMP_BYTE_DELIM     ' '
#define DUMP_BYTES_LHS      ' '
#define DUMP_BYTES_RHS      ' '
#define DUMP_CHAR_DELIM     '.'
#define DUMP_CHARS_LHS      '|'
#define DUMP_CHARS_RHS      '|'

void dos_dump_char(char b, char delim);

void dos_dump_bin(char b, char delim);

void dos_dump_dec(char b, char delim);

void dos_dump_hex(char b, char delim, const char* hex_chars);

void dos_dump_byte(char b, char delim, char fmt);

void dos_dump_word(char b, char delim, char fmt);

void dos_dump_ptr(void* p, char delim, char fmt);

void* dos_dump_chars(char* b, size_t n, char delim, char lhs, char rhs);

void* dos_dump_bytes(char* b, size_t n, char delim, char lhs, char rhs);

void* dos_dump_paragraph(char* para);

void* dos_dump_memory(dos_mem_block_t mem_block, size_t paragraphs);

#endif
