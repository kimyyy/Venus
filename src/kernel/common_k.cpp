#include "common_k.hpp"

void panic(){
    // TODO: print message
    while(1);
}


void assert(bool condition){
    if(!condition){
        // TODO: print message: panic now
        panic();
    }
}
