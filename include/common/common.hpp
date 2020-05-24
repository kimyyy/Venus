#pragma once

#include <stdint.h>
#include <stddef.h>

template<typename T>
bool IsBitmatch(T value, T mask){
    T masked = value & mask;
    return masked!=0;
}

template<typename T>
T Bitmask(T value, T mask){
    return value & mask;
}


template<typename T>
T& max(T& a, T& b){
   return (a < b)? b : a; 
}

template<typename T>
T& min(T& a, T& b){
   return (a < b)? a : b; 
}
