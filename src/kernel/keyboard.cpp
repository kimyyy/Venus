#include "keyboard.hpp"

uint8_t Keyboard::readStatus(){
    return readIOPort8((uint16_t)Port_KBD::Status);
}

uint8_t Keyboard::readData(){
    return readIOPort8((uint16_t)Port_KBD::Data);
}

uint8_t Keyboard::scanKeycode(){
    while(!IsBitmatch(readStatus(), (uint8_t)1));
    return Bitmask(readData(), (uint8_t)0b01111111);
}


uint8_t Keyboard::getc(){
}

void Keyboard::test(){
    Keyboard kbd;
    while(true){
        uint8_t code = kbd.scanKeycode();
        int ret = printf("keycode is %x\n", code);
        ret = 8;
    }
}
