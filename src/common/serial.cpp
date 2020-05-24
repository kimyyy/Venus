#include "serial.hpp"

// wrap in and out instruction
void writeIOPort(uint16_t port, uint8_t data){
    asm volatile("out %%al, %%dx":: "a" (data), "d" (port));
}

void writeIOPort(uint16_t port, uint16_t data){
    asm volatile("out %%ax, %%dx":: "a" (data), "d" (port));
}

void writeIOPort(uint16_t port, uint32_t data){
    asm volatile("out %%eax, %%dx":: "a" (data), "d" (port));
}

uint8_t readIOPort8(uint16_t port){
    uint8_t in;
    asm volatile("in %%dx, %%al": "=a" (in): "d" (port));
    return in;
}

uint16_t readIOPort16(uint16_t port){
    uint16_t in;
    asm volatile("in %%dx, %%ax": "=a" (in): "d" (port));
    return in;
}

uint32_t readIOPort32(uint16_t port){
    uint32_t in;
    asm volatile("in %%dx, %%eax": "=a" (in): "d" (port));
    return in;
}

void Serial::putc(const uint8_t c){
    writeIOPort((uint16_t)port, c);
}

void Serial::puts(const uint8_t *c){
    while(*c != '\0'){
        writeIOPort((uint16_t)port, *c);
        c++;
    }
}

void Serial::putc(const wchar_t c){
    writeIOPort((uint16_t)port, (uint16_t)c);
}

void Serial::test(){
    Serial serial(IOPort::QemuCOM1);
    serial.putc((const uint8_t )'a');
    serial.puts((const uint8_t *)"Hello, serial!\n");
    serial.puts((const uint8_t *)"testing \n...");
    serial.putc(L'b');
}
