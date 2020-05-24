#include "keyboard.hpp"

uint8_t Keyboard::readStatus(){
    return readIOPort8((uint16_t)Port_KBD::Status);
}

uint8_t Keyboard::readData(){
    return readIOPort8((uint16_t)Port_KBD::Data);
}

void Keyboard::scanKeycode(uint8_t *c){
    while(!IsBitmatch(readStatus(), (uint8_t)1));
    uint8_t data = Bitmask(readData(), (uint8_t)0b01111111);
    intToStr16(data, c);
}


uint8_t Keyboard::getc(){
}

void Keyboard::test(){
    Keyboard kbd;
    Serial serialout(IOPort::QemuCOM1);
    uint8_t c[15];
    while(true){
        kbd.scanKeycode(c);
        serialout.puts(c);
    }
}
