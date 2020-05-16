#pragma once

#include "common.hpp"
#include "bootInfo.hpp"

class Point {
    public:
    uint32_t x;
    uint32_t y;
    Point(uint32_t x, uint32_t y): x(x), y(y){};
};

struct Color {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    Color(uint8_t b, uint8_t g, uint8_t r): b(b), g(g), r(r){};
};

struct Pallet {
    const Color green = Color(0, 255, 0);
    const Color blue = Color(255, 0, 0);
    const Color reg = Color(0, 0, 255);
};

struct Rect {
    Point begin;
    uint32_t width;
    uint32_t height;
};
struct PixelFormat {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t _reserved;
    void SetColor(Color color){
        b = color.b;
        g = color.g;
        r = color.r;
    }
};


class FrameBuffer{
    private:
    PixelFormat *m_base;
    uint64_t m_size;
    uint32_t m_hr;
    uint32_t m_vr;
    PixelFormat *getPixelFormat(Point point);
    public:
    FrameBuffer(FrameBufferInfo info);
    void testFrameBuffer();
    void drawLine(Point start, Point end, Color color);
    void drawPoint(Point point, Color color);
    void drawRect(Rect rect, Color color);
};
