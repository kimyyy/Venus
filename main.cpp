#include "common.hpp"
#include "efi.hpp"

extern "C"
void efi_main(void *ImageHandle __attribute__ ((unused)) , EfiSystemTable *SystemTable){
    efi_init(SystemTable);
    ST->ConOut->ClearScreen(SystemTable->ConOut);
    puts(L"Hello,UEFI!\n");
    wchar_t buf = getc();
    putc(buf);
    while(1) {
    }
}
