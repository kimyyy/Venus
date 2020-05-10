#include "serial.hpp"

extern "C"
void KernelMain(int hoge, int foo){
    int hage = 114514;
    hage = hoge;
    int bar = 810893;
    bar = foo;
    bar = bar + hage;
    WriteIOPort8(0x3f8, 0xff);
    char str[20] = "Hello, kernel!";
    for(int i = 0;i < 20 && str[i] != '\0';i++){
        WriteIOPort8(0x3f8, str[i]);
    }
    while(1);
}
