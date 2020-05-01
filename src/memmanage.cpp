#include "memmanage.hpp"
#include "efi.hpp"

// allocation and free
void *malloc(unsigned long size) {
    void * buf;
    ull status = ST->BootServices->AllocatePool(EfiLoaderData, size, &buf);
    assert(status,L"malloc");
    return buf;
}

void free(void* buf){
    ull status = ST->BootServices->FreePool(buf);
    assert(status, L"free");
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

