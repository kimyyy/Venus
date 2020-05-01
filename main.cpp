#include "common.hpp"
#include "efi.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "cstring.hpp"
#include "memmanage.hpp"

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

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

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

class wstring {
private:
  wchar_t *m_data;
  ull m_size;
  ull m_capasity;
  unsigned int capasity_offset = 30;

public:
  // Constructors

  wstring(const ull size, const wchar_t *c) {
    m_size = size;
    m_capasity = m_size + capasity_offset;
    m_data = new wchar_t[m_capasity];
    strncpy(m_data, c, m_size);
  }

  wstring(const wchar_t *c) {
    m_size = strlen(c);
    m_capasity = m_size + capasity_offset;
    m_data = new wchar_t[m_capasity];
    strncpy(m_data, c, m_size);
  }

  wstring(const wstring &s){
      m_capasity = s.m_capasity;
      m_size = s.m_size;
      m_data = new wchar_t[m_capasity];
      strncpy(m_data, (const wchar_t *)s.m_data, m_size);
  }

  // Operators
  wstring operator += (const wchar_t *c){
      unsigned int len = strlen(c);
      if(m_size + len > m_capasity){
        
      }else{
        m_size = m_size + len;
        strcat(m_data, c);
        return *this;
      }
  }

  wstring operator +(const wchar_t *c){
      wstring str(*this);
      str+= c;
      return str;
  }

  // member functions
  wchar_t *data() { return m_data; }

  ull size() { return m_size; }

  bool empty() { return m_size == 0 ? true : false; }
};

extern "C"
void efi_main(void *ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    ClearScreen();
    wstring str = wstring(3, L"Hello");
    wstring str1 = L"world";
    puts(str.data());

    // panic
    while(TRUE);
}
