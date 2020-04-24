#include "efi.hpp"

EfiSystemTable *ST;

extern "C" void efi_init(EfiSystemTable *SystemTable){
    ST = SystemTable;
    ST->BootServices.SetWatchdogTimer(0, 0, 0, (wchar_t *)NULL);
}
