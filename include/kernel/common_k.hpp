#pragma once

#include "common.hpp"
#include "bootInfo.hpp"
#include <stdio.h>

void panic();
void panic(const char *message);

template<typename T>
void assert(T actual, T expected){
    if(actual != expected){
        panic("assert failed!");
    }
}

template <typename T>
void assert(T& actual, T& expected, uint32_t length){
    for(uint32_t i = 0;i < length;i++){
        assert(actual[i], expected[i]);
    }
}


void assert(bool condition);

uint8_t intToChar(uint8_t integer);

void intToStr10(uint8_t value, uint8_t *c);
void intToStr16(uint8_t value, uint8_t *c);
