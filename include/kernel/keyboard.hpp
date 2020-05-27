#pragma once

#include "common.hpp"
#include "common_k.hpp"
#include "serial.hpp"
#include <stdlib.h>
#include <stdio.h>

enum class Port_KBD: uint16_t {
    Data = 0x60,
    Status = 0x64
};

class Keyboard {
    private:
        uint8_t readStatus();
        uint8_t readData();
        uint8_t scanKeycode();
    public:
        uint8_t getc();
        static void test();
};
