#include "efi.hpp"
#include "common.hpp"

EfiSystemTable *ST;
EfiGraphicsOutputPtorocol *GOP;
EfiSimplePointerProtocol *SPP;

void efi_init(EfiSystemTable *SystemTable){
    EfiGuid gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
    EfiGuid spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
    ST = SystemTable;
    ST->BootServices->SetWatchdogTimer(0, 0, 0, (wchar_t *)NULL);
    ST->BootServices->LocateProtocol(&gop_guid, NULL, (void**)&GOP);
    ST->BootServices->LocateProtocol(&spp_guid, NULL, (void**)&SPP);
}
