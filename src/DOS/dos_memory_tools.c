#include "dos_memory_tools.h"
#include "dos_memory_constants.h"
#include "dos_memory_types.h"

#ifdef POLICY_USE_DOS_STD
    #include "../STD/dos_stdio.h"
    #include "../STD/dos_assert.h"
#else
    #include <stdio.h>
    #include <assert.h>
#endif

static const char DUMP_UPPER_CASE_HEX[] = "0123456789ABCDEF";
static const char DUMP_LOWER_CASE_HEX[] = "0123456789abcdef";


void dos_dump_char(char b, char delim) {
    if (b >= 32 && b < 127) fputc(b, stderr);
    else fputc('.', stderr);
    if(delim) fputc(delim, stderr);
}

void dos_dump_hex(char b, char delim, const char* hex_chars) {
    fputc(hex_chars[(b >> 4) & 0x0F], stderr);
    fputc(hex_chars[b & 0x0F], stderr);
    if(delim) fputc(delim, stderr);
}

void dos_dump_byte(char b, char delim, char fmt) {
    switch(fmt) {
        case 'b': //dos_dump_binary()
        case 'x': dos_dump_hex(b, delim, DUMP_LOWER_CASE_HEX);
        case 'X':
        default: dos_dump_hex(b, delim, DUMP_UPPER_CASE_HEX);
    }
}

void* dos_dump_chars(char* b, size_t n, char delim, char lhs, char rhs) {
    if (!b || !n) return NULL;
    if (lhs) fputc(lhs, stderr);
    while(n--) dos_dump_char(*b++, delim);
    if (rhs) fputc(rhs, stderr);
    return (void*)b;
}

void* dos_dump_bytes(char* b, size_t n, char delim, char lhs, char rhs) {
    if (!b || !n) return NULL;
    if (lhs) fputc(lhs, stderr);
    while(n--) dos_dump_byte(*b++, delim, 'X');
    if (rhs) fputc(rhs, stderr);
    return (void*)b;
}

void* dos_dump_paragraph(char* para) {
    if(!para) return NULL;
    //dos_dump_ptr(para, DUMP_BYTE_DELIM, 'X');
    dos_dump_bytes(para, DOS_PARAGRAPH_SIZE, DUMP_BYTE_DELIM, DUMP_BYTES_LHS, DUMP_BYTES_RHS);
    printf("\n");
    return (void*)para;
}

void* dos_dump_memory(dos_mem_block_t mem_block, size_t paragraphs) {
    if(!mem_block.begin.ptr || !mem_block.end.ptr || mem_block.begin.ptr > mem_block.end.ptr) return NULL;

    return mem_block.begin.ptr;
}
