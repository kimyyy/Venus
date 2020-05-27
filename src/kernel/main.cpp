#include "serial.hpp"
#include "bootInfo.hpp"
#include "framebuffer.hpp"
#include "psf.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "keyboard.hpp"

extern HeapInfo heapinfo;

void initStdio(){
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
}

void testnewlib() {
    int ret = puts("puts test");
    int hoge = atoi("4");
    uint8_t* hage = (uint8_t*)malloc(10);
}

void InitKernel(){
    initStdio();
}

extern "C"
void KernelMain(BootInfo* bootInfo){
    InitKernel();
    PsfFont::test();
    Serial serial(IOPort::QemuCOM1);
    serial.puts((uint8_t *)"hello");
    FrameBuffer fb = FrameBuffer(bootInfo->fb);
    uint64_t heapstart = bootInfo->heapinfo.start;
    heapinfo = bootInfo->heapinfo;
    //fb.test();
    //Serial::test();
    //testnewlib();
    Keyboard::test();
    panic();
}
