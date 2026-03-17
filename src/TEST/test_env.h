#ifndef TEST_ENV_H
#define TEST_ENV_H


#ifdef POLICY_USE_DOS_STD
    #include "../STD/dos_stdio.h"
    #include "../STD/dos_assert.h"
#else
    #include <stdio.h>
    #include <assert.h>
#endif

#include "../ENV/dos_environment_types.h"
#include "../ENV/dos_environment_constants.h"
#include "../DOS/dos_memory_tools.h"
#include "../DOS/dos_memory_constants.h"

void test_types() {
    printf("Testing DOS environment types...\n");

    assert(mem_block_rom_bios.begin.segoff.segment == ROM_SEG_BEGIN);
    assert(mem_block_rom_bios.begin.segoff.offset == ROM_OFF_BEGIN);
    assert(mem_block_rom_bios.end.segoff.segment == ROM_SEG_END);
    assert(mem_block_rom_bios.end.segoff.offset == ROM_OFF_END);

    char str[] = "0123456789ABCDEF";

    dos_dump_paragraph(str);

    printf("DOS environment types passed\n\n");
}

void test_env() {
    test_types();
}

#endif
