#include "serial.hpp"
#include "bootInfo.hpp"
#include "framebuffer.hpp"
#include "psf.hpp"
#include <stdlib.h>
#include "keyboard.hpp"

void testnewlib() {
    int hoge = atoi("4");
    //uint8_t* hage = (uint8_t*)malloc(1);
}

extern "C"
void KernelMain(BootInfo* bootInfo){
    PsfFont::test();
    FrameBuffer fb = FrameBuffer(bootInfo->fb);
    //fb.test();
    //Serial::test();
    Keyboard::test();
    panic();
}
