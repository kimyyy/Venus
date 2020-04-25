#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"

extern "C"
void efi_main(void *ImageHandle __attribute__ ((unused)) , EfiSystemTable *SystemTable){
    efi_init(SystemTable);
    ST->ConOut->ClearScreen(ST->ConOut);
    puts(L"Hello,UEFI!\r\n");
    shell();
}
