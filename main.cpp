#include "typedef.h"
#include "efi.h"

extern "C"
void efi_main(void *ImageHandle __attribute__ ((unused)) , EFI_SYSTEM_TABLE *SystemTable){
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, world!\n");
    EFI_INPUT_KEY key;
    wchar_t str[3];
    while(1) {
        if(!SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key)) {
            if(key.UnicodeChar != L'\r') {
                str[0] = key.UnicodeChar;
                str[1] = L'\0';
            } else {
                str[0] = L'\r';
                str[1] = L'\n';
                str[2] = L'\0';
            }
            SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
        }
    }
}
