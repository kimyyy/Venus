#include "keyboard.hpp"

uint8_t Keyboard::readStatus(){
    return readIOPort8((uint16_t)Port_KBD::Status);
}

uint8_t Keyboard::readData(){
    return readIOPort8((uint16_t)Port_KBD::Data);
}

uint8_t Keyboard::scanKeycode(){
    while(!IsBitmatch(readStatus(), (uint8_t)1));
    while(!IsBitmatch(readData(), (uint8_t)0b10000000));
    return Bitmask(readData(), (uint8_t)0b01111111);
}


uint8_t Keyboard::getc(){
    uint8_t keycode = scanKeycode();
    return ascii_keymap[keycode];
}

void Keyboard::test(){
    Keyboard kbd;
    uint8_t c;
    while((c = kbd.getc()) != ASCII_ESC){
        printf("%c", c);
    }
}
