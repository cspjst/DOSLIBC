#include "dos_environment.h"
#include "dos_environment_constants.h"

#include "../STD/dos_string.h"

unsigned int dos_environment_is_DOSBox() {

    char* p = (char*)memmem(MEM_BLOCK_ROM_BIOS.begin.ptr, 32, SEARCH_DOSBOX, 6);
    if(p)
}
