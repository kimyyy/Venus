#include "common_k.hpp"

void panic(){
    // stop working
    printf("panic now!");
    while(1);
}

void panic(const char *message){
    printf(message);
    panic();
}


void assert(bool condition){
    if(!condition){
        panic("assert failed!");
    }
}

uint8_t intToChar(uint8_t integer){
    return ((uint8_t)'0' + integer);
}

// input integer is mod 16
// return char8
uint8_t intToHex(uint8_t integer){
    if(integer <= 9){
        return ((uint8_t)'0' + integer);
    }else{
        uint8_t offset = integer - 10;
        return ((uint8_t)'A' + offset);
    }
}

void intToStr10(uint8_t value, uint8_t *c){
    uint8_t i = 0;
    uint8_t buf[5];
    while(value > 0){
        buf[i] = intToChar(value%10);
        value /= 10;
        i++;
    }
    for(uint8_t j = 0;j < i;j++){
        c[j] = buf[i-1-j];
    }
    c[i] = '\n';
    c[i+1] = '\0';
}

void intToStr16(uint8_t value, uint8_t *c){
    c[1] = intToHex(Bitmask(value, (uint8_t)0x0f));
    value = value >> 4;
    c[0] = intToHex(Bitmask(value, (uint8_t)0x0f));
    c[2] = '\n';
    c[3] = '\0';
}
