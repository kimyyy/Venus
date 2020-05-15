#include "serial.hpp"
#include "bootInfo.hpp"

struct PixelFormat {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t _reserved;
};

extern "C"
void KernelMain(BootInfo* bootInfo){
    char str[20] = "Hello, kernel!";
    for(int i = 0;i < 20 && str[i] != '\0';i++){
        WriteIOPort8(0x3f8, str[i]);
    }
    while(1);
}
