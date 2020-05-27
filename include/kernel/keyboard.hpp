#pragma once

#include "common.hpp"
#include "common_k.hpp"
#include "serial.hpp"
#include <stdlib.h>
#include <stdio.h>

namespace {

constexpr uint8_t ASCII_ESC = 0x1B;
constexpr uint8_t ASCII_BACKSPACE = 0x8;
constexpr uint8_t ASCII_TAB = 0x9;
constexpr uint8_t ENTER = 0x0a;
constexpr uint8_t LEFT_CTRL = 0x0;
constexpr uint8_t LEFT_SHIFT = 0x0;
constexpr uint8_t RIGHT_SHIFT = 0x0;
constexpr uint8_t KEYPAD_KOME = 0x0;
constexpr uint8_t LEFT_ALT = 0x0;
constexpr uint8_t CAPSLOCK = 0x0;
constexpr uint8_t F1 = 0x0;
constexpr uint8_t F2 = 0x0;
constexpr uint8_t F3 = 0x0;
constexpr uint8_t F4 = 0x0;
constexpr uint8_t F5 = 0x0;
constexpr uint8_t F6 = 0x0;
constexpr uint8_t F7 = 0x0;
constexpr uint8_t F8 = 0x0;
constexpr uint8_t F9 = 0x0;
constexpr uint8_t F10 = 0x0;
constexpr uint8_t NUMLOCK = 0x0;

const uint8_t ascii_keymap[] = {
    0x0, ASCII_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', ASCII_BACKSPACE, ASCII_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER, LEFT_CTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', LEFT_SHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', RIGHT_SHIFT, KEYPAD_KOME, LEFT_ALT, ' ', CAPSLOCK, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUMLOCK
};

const uint8_t keycode_map[256] = {
  0,    0,    0,    0,  'a',  'b',  'c',  'd', // 0
  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l', // 8
  'm',  'n',  'o',  'p',  'q',  'r',  's',  't', // 16
  'u',  'v',  'w',  'x',  'y',  'z',  '1',  '2', // 24
  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0', // 32
  '\n', '\b', 0x08, '\t',  ' ',  '-',  '=',  '[', // 40
  ']', '\\',  '#',  ';', '\'',  '`',  ',',  '.', // 48
  '/',    0,    0,    0,    0,    0,    0,    0, // 56
  0,    0,    0,    0,    0,    0,    0,    0, // 64
  0,    0,    0,    0,    0,    0,    0,    0, // 72
  0,    0,    0,    0,  '/',  '*',  '-',  '+', // 80
  '\n',  '1',  '2',  '3',  '4',  '5',  '6',  '7', // 88
  '8',  '9',  '0',  '.', '\\',    0,    0,  '=', // 96
  0,    0,    0,    0,    0,    0,    0,    0, // 104
  0,    0,    0,    0,    0,    0,    0,    0, // 112
  0,    0,    0,    0,    0,    0,    0,    0, // 120
  0,    0,    0,    0,    0,    0,    0,    0, // 128
  0,    '\\', 0,    0,    0,    0,    0,    0, // 136
};

const char keycode_map_shifted[256] = {
  0,    0,    0,    0,  'A',  'B',  'C',  'D', // 0
  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L', // 8
  'M',  'N',  'O',  'P',  'Q',  'R',  'S',  'T', // 16
  'U',  'V',  'W',  'X',  'Y',  'Z',  '!',  '@', // 24
  '#',  '$',  '%',  '^',  '&',  '*',  '(',  ')', // 32
  '\n', '\b', 0x08, '\t',  ' ',  '_',  '+',  '{', // 40
  '}',  '|',  '~',  ':',  '"',  '~',  '<',  '>', // 48
  '?',    0,    0,    0,    0,    0,    0,    0, // 56
  0,    0,    0,    0,    0,    0,    0,    0, // 64
  0,    0,    0,    0,    0,    0,    0,    0, // 72
  0,    0,    0,    0,  '/',  '*',  '-',  '+', // 80
  '\n',  '1',  '2',  '3',  '4',  '5',  '6',  '7', // 88
  '8',  '9',  '0',  '.', '\\',    0,    0,  '=', // 96
  0,    0,    0,    0,    0,    0,    0,    0, // 104
  0,    0,    0,    0,    0,    0,    0,    0, // 112
  0,    0,    0,    0,    0,    0,    0,    0, // 120
  0,    0,    0,    0,    0,    0,    0,    0, // 128
  0,    '|',  0,    0,    0,    0,    0,    0, // 136
};

} // namespace
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
