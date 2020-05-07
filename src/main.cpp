#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "cstring.hpp"
#include "memmanage.hpp"
#include "wstring.hpp"
#include "serial.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();

    // panic
    while(TRUE);
}
