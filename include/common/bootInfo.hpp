#include "common.hpp"
#pragma once

struct FrameBuffer {
    uint64_t base;
    uint64_t size;
    uint32_t hr;
    uint32_t vr;
};

struct BootInfo {
    FrameBuffer fb;
};
