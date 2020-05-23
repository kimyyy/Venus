#pragma once

#include "common.hpp"

template<typename T>
bool IsBitmatch(T value, T mask){
    T masked = value & mask;
    return masked!=0;
}
