#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    void *image;
    efi_init(SystemTable);
    ClearScreen();
    EfiLoadedImageProtocol *lip;
    EfiDevicePathProtocol *dev_path;
    EfiDevicePathProtocol *dev_node;
    EfiDevicePathProtocol *dev_path_merged;

    ull status;
    
    // BOOTX64.EFI device path to string
    status = ST->BootServices->OpenProtocol(
            ImageHandle, &lip_guid, (void **)&lip, ImageHandle,NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol(lip)");
    puts(L"lip->FilePath: ");
    puts(DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    puts(L"\r\n");

    // get devicepathprotocol using lip->DeviceHandle. dev_path is initialized
    status = ST->BootServices->OpenProtocol(
            lip->DeviceHandle, &dpp_guid, (void**)&dev_path, ImageHandle,
            NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL
            );
    assert(status ,L"Openprotocol(dpp)");

    // output dev_path
    puts(L"dev_path: ");
    puts(DPTTP->ConvertDevicePathToText(dev_path, FALSE, FALSE));
    puts(L"\r\n");

    // string to device path. dev_node is initialized
    dev_node = DPFTP->ConvertTextToDevicePath(L"test.efi");

    // append dev_node to dev_path
    dev_path_merged = DPUP->AppendDeviceNode(dev_path, dev_node);

    // output merged path
    puts(L"dev_path_merged: ");
    puts(DPTTP->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
    puts(L"\r\n");

    // Load Image
    status = ST->BootServices->LoadImage(FALSE, ImageHandle, dev_path_merged, NULL, 0, &image);
    assert(status ,L"LoadImage");
    puts(L"LoadImage: Success!\r\n");
    while(TRUE);
    //shell();

}
