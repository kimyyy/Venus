#include "efi.hpp"
#include "common.hpp"
#include "graphics.hpp"

const EfiGraphicsOutputBitPixel white = {0xff, 0xff, 0xff, 0xff};
const EfiGraphicsOutputBitPixel yellow = {0x00, 0xff, 0xff, 0xff};

void draw_pixel(unsigned int x, unsigned int y, EfiGraphicsOutputBitPixel color){
    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    EfiGraphicsOutputBitPixel *base = (EfiGraphicsOutputBitPixel *)GOP->Mode->FrameBufferBase;
    EfiGraphicsOutputBitPixel *p = base + (hr * y) + x;

    p->Blue = color.Blue;
    p->Green = color.Green;
    p->Red = color.Red;
    p->Reserved = color.Reserved;
}

void draw_rect(Rect rect, EfiGraphicsOutputBitPixel color){
    unsigned int i;

    for(i = rect.x; i < (rect.x + rect.w); i++)
        draw_pixel(i, rect.y, color);
    for(i = rect.x; i < (rect.x + rect.w); i++)
        draw_pixel(i, rect.y + rect.h - 1, color);

    for(i = rect.y;i < (rect.y + rect.h); i++)
        draw_pixel(rect.x, i, color);
    for(i = rect.y; i < (rect.y + rect.h); i++)
        draw_pixel(rect.x + rect.w -1, i, color);
}

EfiGraphicsOutputBitPixel get_pixel(unsigned int x, unsigned int y){
    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    EfiGraphicsOutputBitPixel *base = (EfiGraphicsOutputBitPixel *)GOP->Mode->FrameBufferBase;
    EfiGraphicsOutputBitPixel *p = base + (hr * y) + x;

    return *p;
}

unsigned char is_in_rect(unsigned int x, unsigned int y, Rect r){
    if((r.x <= x) && (x <= (r.x + r.w -1)) && (r.y <= y) && (y <= (r.y + r.h - 1)))
        return TRUE;
    return FALSE;
}
