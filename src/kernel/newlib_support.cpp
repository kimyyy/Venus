#include "common_k.hpp"
#include "serial.hpp"
#include "bootInfo.hpp"
#include <sys/stat.h>

HeapInfo heapinfo;

extern "C" {
int close(int file){
    panic();
}

void _exit(){
    panic();
}

int fstat(int file, struct stat *st){
    st->st_mode = S_IFCHR;
    return 0;
}

int getpid(void){
    panic();
}

int isatty(int file){
    return 1;
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
    Serial serial(IOPort::QemuCOM1);
    serial.puts((uint8_t *)ptr);
    return len;
}

}
