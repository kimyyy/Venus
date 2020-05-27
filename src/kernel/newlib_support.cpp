#include "common_k.hpp"
#include "bootInfo.hpp"

HeapInfo heapinfo;

extern "C" {
int close(int file){
    panic();
}

int getpid(void){
    panic();
}

int isatty(int file){
    panic();
}

int kill(int pid, int sig){
    panic();
}

int link(char *old, char *_new){
    panic();
}

int lseek(int file, int ptr, int dir){
    panic();
}

int open(const char *name, int flags, int mode){
    panic();
}

int read(int file, char *ptr, int len){
    panic();
}

char* sbrk(int incr){
    static char* heap_end;
    char* prev_heap_end;
    if(heap_end == NULL){
        heap_end = (char*)heapinfo.start;
    }
    prev_heap_end = heap_end;
    if((uint64_t)heap_end + incr > heapinfo.start + heapinfo.size){
        panic();
    }
    heap_end += incr;
    return prev_heap_end;
}

int write(int file, char* ptr, int len){
    panic();
}


}
