#include "serial.hpp"
#include "bootInfo.hpp"
#include "framebuffer.hpp"
#include <stdlib.h>


void testnewlib() {
    int hoge = atoi("4");
}

extern "C"
void KernelMain(BootInfo* bootInfo){
    FrameBuffer fb = FrameBuffer(bootInfo->fb);
    Pallet pallet;
    fb.putc("a", Point(100, 100), pallet.white, pallet.black);
    char str[20] = "Hello, kernel!";
    for(int i = 0;i < 20 && str[i] != '\0';i++){
        WriteIOPort8(0x3f8, str[i]);
    }
    while(1);
}
