#include "efi.hpp"
#pragma once

struct Rect {
    unsigned int x,y;
    unsigned int w,h;
};

extern const EfiGraphicsOutputBitPixel white;

void draw_pixel(unsigned int x, unsigned int y, EfiGraphicsOutputBitPixel color);
void draw_rect(Rect rect, EfiGraphicsOutputBitPixel color);
