#include "efi.hpp"
#pragma once

struct Rect {
    unsigned int x,y;
    unsigned int w,h;
};

extern const EfiGraphicsOutputBitPixel white;
extern const EfiGraphicsOutputBitPixel yellow;

void draw_pixel(unsigned int x, unsigned int y, EfiGraphicsOutputBitPixel color);
void draw_rect(Rect rect, EfiGraphicsOutputBitPixel color);
EfiGraphicsOutputBitPixel get_pixel(unsigned int x, unsigned int y);
unsigned char is_in_rect(unsigned int x, unsigned int y, Rect r);
