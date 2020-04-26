#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

extern "C"
void efi_main(void *ImageHandle __attribute__ ((unused)) , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();
    shell();
}
