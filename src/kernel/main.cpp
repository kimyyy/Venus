#include "serial.hpp"
#include "bootInfo.hpp"
#include "framebuffer.hpp"
#include "psf.hpp"
#include <stdlib.h>
#include "keyboard.hpp"

extern HeapInfo heapinfo;

void testnewlib() {
    int hoge = atoi("4");
    uint8_t* hage = (uint8_t*)malloc(10);
}

extern "C"
void KernelMain(BootInfo* bootInfo){
    PsfFont::test();
    FrameBuffer fb = FrameBuffer(bootInfo->fb);
    uint64_t heapstart = bootInfo->heapinfo.start;
    heapinfo = bootInfo->heapinfo;
    //fb.test();
    //Serial::test();
    //Keyboard::test();
    testnewlib();
    panic();
}
