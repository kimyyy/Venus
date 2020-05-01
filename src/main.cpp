#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "cstring.hpp"
#include "memmanage.hpp"
#include "wstring.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();
    wstring str = wstring(3, L"Hello");
    wstring str1 = L"world";
    puts(str.data());

    // panic
    while(TRUE);
}
