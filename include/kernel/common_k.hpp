#pragma once

#include "common.hpp"

void panic();

template<typename T>
void assert_test(T actual, T expected){
    if(actual != expected){
        // TODO: print message
        // "actual is hoge, expected is bar"
        panic();
    }
}

void assert(bool condition);
