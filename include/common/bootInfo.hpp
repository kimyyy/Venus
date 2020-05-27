#include "common.hpp"
#pragma once

struct FrameBufferInfo {
    uint64_t base;
    uint64_t size;
    uint32_t hr;
    uint32_t vr;
};

struct HeapInfo {
    uint64_t start;
    uint64_t size;
};

struct BootInfo {
    FrameBufferInfo fb;
    HeapInfo heapinfo;
};
