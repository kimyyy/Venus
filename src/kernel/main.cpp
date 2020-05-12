#include "serial.hpp"
#include "bootInfo.hpp"

extern "C"
void KernelMain(BootInfo* bootInfo){
    int hage = 114514;
    hage = bootInfo->hoge;
    char str[20] = "Hello, kernel!";
    for(int i = 0;i < 20 && str[i] != '\0';i++){
        WriteIOPort8(0x3f8, str[i]);
    }
    while(1);
}
