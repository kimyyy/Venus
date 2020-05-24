#pragma once

#include "common.hpp"

void writeIOPort(uint16_t port, uint8_t data);
void writeIOPort(uint16_t port, uint16_t data);
void writeIOPort(uint16_t port, uint32_t data);
uint8_t readIOPort8(uint16_t port);
uint16_t readIOPort16(uint16_t port);
uint32_t readIOPort32(uint16_t port);

enum class IOPort: uint16_t {
    QemuCOM1 = 0x3f8,
    QemuCOM2 = 0x2F8,
    QemuCOM3 = 0x3E8,
    QemuCOM4 = 0x2E8
};

class Serial {
    IOPort port;
    public:
    Serial(IOPort p):port(p){};
    void putc(const uint8_t c);
    void puts(const uint8_t* c);
    void putc(const wchar_t c);
    static void test();
};
