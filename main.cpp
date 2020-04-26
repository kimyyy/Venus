#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"

#define CAT(A, B) A##B
#define STRING(str) #str
#define WSTRING(A) CAT(L, #A)

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

extern "C"
void efi_main(void *ImageHandle __attribute__ ((unused)) , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();
    wchar_t buf[100] = L"HEllo: ";
    intToStr(buf, 100, strlen(buf), 0xf1);
    puts(buf);
    //shell();
    while(1);
}
