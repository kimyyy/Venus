#include "efi.hpp"
#include "common.hpp"

EfiSystemTable *ST;
EfiGraphicsOutputPtorocol *GOP;
EfiSimplePointerProtocol *SPP;
EfiSimpleFileSystemProtocol *SFSP;

void efi_init(EfiSystemTable *SystemTable){
    EfiGuid gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
    EfiGuid spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
    EfiGuid sfsp_guid = {0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
    ST = SystemTable;
    ST->BootServices->SetWatchdogTimer(0, 0, 0, (wchar_t *)NULL);
    ST->BootServices->LocateProtocol(&gop_guid, NULL, (void**)&GOP);
    ST->BootServices->LocateProtocol(&spp_guid, NULL, (void**)&SPP);
    ST->BootServices->LocateProtocol(&sfsp_guid, NULL, (void**)&SFSP);;
}
