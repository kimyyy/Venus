#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "string.hpp"

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

void panic(const wchar_t *message){
    puts(message);
    while(TRUE);
}

void * malloc(unsigned long size) {
    void * buf;
    ull status = ST->BootServices->AllocatePool(EfiLoaderData, size, &buf);
    assert(status,L"malloc");
    return buf;
}

void free(void* buf){
    ull status = ST->BootServices->FreePool(buf);
    assert(status, L"free");
}

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


class wString {
    private:
    wchar_t *m_data;
    ull m_size;
    ull m_capasity;
    unsigned int capasity_offset = 30;

    public:
    wString(const ull size, const wchar_t *c){
        m_size = size;
        m_capasity = m_size + capasity_offset;
        m_data = new wchar_t[m_capasity];
        strncpy(m_data, c , m_size);
    }

    wchar_t * data(){
        return m_data;
    }

    ull size(){
        return m_size;
    }

    bool empty(){
        return m_size == 0? true:false;
    }
};

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();
    wString str = wString(3, L"Hello");
    puts(str.data());

    // panic
    while(TRUE);
}
