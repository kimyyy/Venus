#include "serial.hpp"
#include "bootInfo.hpp"
#include "framebuffer.hpp"
#include "psf.hpp"
#include <stdlib.h>
#include "keyboard.hpp"

void testnewlib() {
    int hoge = atoi("4");
}

extern "C"
void KernelMain(BootInfo* bootInfo){
    FrameBuffer fb = FrameBuffer(bootInfo->fb);
    //fb.test();
    //Serial::test();
    Keyboard::test();
    panic();
}
