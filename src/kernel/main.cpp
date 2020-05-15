#include "serial.hpp"
#include "bootInfo.hpp"

extern "C"
void KernelMain(BootInfo* bootInfo){
    FrameBuffer fb = bootInfo->fb;
    uint8_t red = 0;
    uint8_t green = 255;
    uint8_t blue = 0;
    for(uint32_t y = 0; y < fb.vr;y++){
        for(uint32_t x = 0; x < fb.hr;x++){
            PixelFormat *p = reinterpret_cast<PixelFormat*>(fb.base + sizeof(PixelFormat)*((fb.hr * y) + x));
            p->r = red;
            p->g = green;
            p->b = blue;
        }
    }
    char str[20] = "Hello, kernel!";
    for(int i = 0;i < 20 && str[i] != '\0';i++){
        WriteIOPort8(0x3f8, str[i]);
    }
    while(1);
}
