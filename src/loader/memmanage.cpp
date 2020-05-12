#include "memmanage.hpp"
#include "efi.hpp"

// memory operation

// memory copy for n bytes
void memcpy(char *dst, const char *src, uint32_t n){
    while(n--){
        *dst++ = *src++;
    }
}

// memory zero for n bytes
void memzero(char *dst, uint32_t n){
    while(n--){
        *dst++ = 0;
    }
}

// testing
void mem_test(){
    char src[] = "testing";
    char buf[10];
    memcpy(buf, src, 4);
    memzero(buf, 4);
}

// allocation and free
void *malloc(UINTN size) {
    void * buf;
    ull status = ST->BootServices->AllocatePool(EfiLoaderData, size, &buf);
    assert_status(status,L"malloc");
    return buf;
}

void free(void* buf){
    ull status = ST->BootServices->FreePool(buf);
    assert_status(status, L"free");
}

// operator
void operator delete(void *p){
    free(p);
}

void operator delete(void *p, unsigned long long t){
    free(p);
}

void *operator new(unsigned long long size){
   void *ptr = malloc(size); 
   if(ptr == nullptr)panic(L"new operator failed");
   return ptr;
}

void *operator new[](unsigned long long size){
   void *ptr = malloc(size); 
   if(ptr == nullptr)panic(L"new[] operator failed");
   return ptr;
}

