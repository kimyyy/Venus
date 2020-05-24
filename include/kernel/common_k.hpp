#pragma once

#include "common.hpp"

void panic();

template<typename T>
void assert(T actual, T expected){
    if(actual != expected){
        // TODO: print message
        // "actual is hoge, expected is bar"
        panic();
    }
}

void assert(bool condition);

uint8_t intToChar(uint8_t integer);

void intToStr10(uint8_t value, uint8_t *c);
void intToStr16(uint8_t value, uint8_t *c);
