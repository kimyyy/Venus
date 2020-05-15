#include "common.hpp"
#pragma once

struct PixelFormat {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t _reserved;
};

struct FrameBuffer {
    uint64_t base;
    uint64_t size;
    uint32_t hr;
    uint32_t vr;
};

struct BootInfo {
    FrameBuffer fb;
};
