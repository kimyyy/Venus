#include "serial.hpp"

void WriteIOPort8(unsigned short port, char c){
    asm volatile("out %%al, %%dx":: "a" (c), "d" (port));
}
