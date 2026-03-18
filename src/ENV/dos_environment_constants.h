#ifndef DOS_ENVIRONMENT_CONSTANTS_H
#define DOS_ENVIRONMENT_CONSTANTS_H

#include "../DOS/dos_memory_types.h"

#define ROM_SEG_BEGIN   0xFE00
#define ROM_OFF_BEGIN   0x0000
#define ROM_SEG_END     0xF000
#define ROM_OFF_END     0xFFFF

extern const dos_mem_block_t MEM_BLOCK_IVT;
extern const dos_mem_block_t MEM_BLOCK_BDA;
extern const dos_mem_block_t MEM_BLOCK_VIDEO_MONO_PAGE_0;
extern const dos_mem_block_t MEM_BLOCK_VIDEO_COLOUR_PAGE_0;
extern const dos_mem_block_t MEM_BLOCK_ROM_BIOS;

extern const char SEARCH_DOSBOX[];
extern const char SEARCH_DOSBOX_X[];

typedef enum


#endif
