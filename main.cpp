#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();
    EfiLoadedImageProtocol *lip;

    ull status;
    status = ST->BootServices->OpenProtocol(
            ImageHandle, &lip_guid, (void **)&lip, ImageHandle,NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol");
    puts(L"lip->FilePath: ");
    puts(DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    puts(L"\r\n");
    while(TRUE);
    //shell();

}
