#include "serial.hpp"
#include "bootInfo.hpp"
#include "framebuffer.hpp"
#include "psf.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "keyboard.hpp"

extern HeapInfo heapinfo;

void CPUID(){
    asm volatile("mov $0x80000001, %eax");
    asm volatile("cpuid");
}

void initStdio(){
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
}

void testnewlib() {
    int ret = puts("puts test");
    int hoge = atoi("4");
    uint8_t* hage = (uint8_t*)malloc(10);
    uint8_t* hage2 = (uint8_t*)malloc(80);
    free(hage);
    free(hage2);
    hoge = 1;
}

void InitKernel(BootInfo *bootInfo){
    initStdio();
    heapinfo = bootInfo->heapinfo;
}

extern "C"
void KernelMain(BootInfo* bootInfo){
    CPUID();
    InitKernel(bootInfo);
    //PsfFont::test();
    Serial serial(IOPort::QemuCOM1);
    //serial.puts((uint8_t *)"hello");
    FrameBuffer fb = FrameBuffer(bootInfo->fb);
    //fb.test();
    //Serial::test();
    //testnewlib();
    Keyboard::test();
    printf("kernel end");
    panic();
}
