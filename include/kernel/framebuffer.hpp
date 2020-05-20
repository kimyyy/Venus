#pragma once

#include "common.hpp"
#include "bootInfo.hpp"
#include <stdlib.h>

template<typename T>
T& max(T& a, T& b){
   return (a < b)? b : a; 
}

template<typename T>
T& min(T& a, T& b){
   return (a < b)? a : b; 
}

class Point {
    public:
    uint32_t x;
    uint32_t y;
    Point(){};
    Point(uint32_t x, uint32_t y): x(x), y(y){};
    Point operator +(Point p){
        return Point(x+p.x, y + p.y);
    }
    Point operator *(uint32_t scalar){
        return Point(x * scalar, y * scalar);
    }
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
    const Color red = Color(0, 0, 255);
};

class Rect {
    public:
    Point begin;
    uint32_t width;
    uint32_t height;
    Rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h): begin(Point(x, y)),width(w), height(h){};
    Rect(Point point, uint32_t w, uint32_t h): begin(point), width(w), height(h){};
    Rect(Point p1, Point p2){
        begin = Point(min(p1.x, p2.x), min(p1.y , p2.y));
        width = abs(p1.x - p2.x);
        height = abs(p1.y - p2.y);
    };
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
    void drawRect(Point start, Point end, Color color);
    void fillRect(Rect rect, Color color);
    void fillRect(Point start, Point end, Color color);
};
