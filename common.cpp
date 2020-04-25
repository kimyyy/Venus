#include "efi.hpp"
#include "common.hpp"

void clear(void){
    ST->ConOut->ClearScreen(ST->ConOut);
}

void putc(wchar_t c){
    wchar_t str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
}

void puts(wchar_t *s){
    ST->ConOut->OutputString(ST->ConOut, s);
}

wchar_t getc(void){
    EfiInputKey key;
    ull wait_index;
    ST->BootServices->WaitForEvent(1, &(ST->ConIn->WaitForKey), &wait_index);
    while(ST->ConIn->ReadKeyStroke(ST->ConIn, &key));

    return key.UnicodeChar;
}

unsigned int gets(wchar_t *buf, unsigned int buf_size){
    unsigned int i;
    for(i =0; i < buf_size - 1;){
        buf[i] = getc();
        putc(buf[i]);
        if(buf[i] == L'\r'){
            putc(L'\n');
            break;
        }
        i++;
    }
    buf[i] = L'\0';

    return i;
}

int strcmp(const wchar_t *s1, const wchar_t *s2){
    char is_equal = 1;
    for(;(*s1 != L'\0') && (*s2 != L'\0'); s1++, s2++){
        if(*s1!= *s2){
            is_equal = 0;
            break;
        }
    }

    if(is_equal){
        if(*s1 != L'\0'){
            return 1;
        }else if(*s2 != L'\0'){
            return -1;
        }else {
            return 0;
        }
    }else {
        return (int)(*s1-*s2);
    }
}
