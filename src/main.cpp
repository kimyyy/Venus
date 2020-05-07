#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "cstring.hpp"
#include "memmanage.hpp"
#include "wstring.hpp"
#include "serial.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

EfiGuid EfiFileInfoGuid = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    test_cstring();
    EfiLoadedImageProtocol* lip;
    EfiFileProtocol *root;
    EfiFileProtocol *kernelFile;
    char kernelFileInfoBuf[200];
    EfiFileInfo *kernelFileInfo;
    ull buffersize = 200;
    ull status = ST->BootServices->HandleProtocol(ImageHandle, &lip_guid, (void**)&lip);
    assert_status(status, L"getLoadedImageProtocol");
    status = ST->BootServices->HandleProtocol(lip->DeviceHandle, &sfsp_guid, (void**)&SFSP);
    assert_status(status, L"getSympleFileSystemProtocol");
    status = SFSP->OpenVolume(SFSP, &root);
    assert_status(status, L"getroot");
    status = root->Open(root, &kernelFile, L"\\kernel.elf", EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    assert_status(status, L"OpenkernelFile");
    kernelFile->GetInfo(kernelFile, &EfiFileInfoGuid, &buffersize, (void*)kernelFileInfoBuf);
    assert_status(status, L"GetkernelFileInfo");
    kernelFileInfo = reinterpret_cast<EfiFileInfo*>(kernelFileInfoBuf);
    puts(kernelFileInfo->FileName);
    ClearScreen();

    // panic
    while(TRUE);
}
