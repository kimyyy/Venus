#include "efi.hpp"
#include "common.hpp"

#define MAX_STR_BUF 100

void ClearScreen(void){
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

void puth(ull val, unsigned char num_digits){
    int i;
    wchar_t unicode_val;
    wchar_t str[MAX_STR_BUF];

    for(i = num_digits- 1;i >= 0 ;i--){
        unicode_val = (wchar_t)(val & 0x0f);
        if(unicode_val < 0xa)
            str[i] = L'0' + unicode_val;
        else
            str[i] = L'A' + (unicode_val - 0xa);
        val >>= 4;
    }
    str[num_digits] = L'\0';
    puts(str);
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

// return: string length
// WARN: do not input uninitialized string
unsigned int strlen(wchar_t *s){
    unsigned int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}

// convert int to string. (format is hexademial)
unsigned int intToStr(wchar_t * buf, unsigned int buf_size, unsigned int buf_content_size, ull val){
    int i = 0;
    wchar_t unicode_val;
    wchar_t str[MAX_STR_BUF];

    do{
        if(i == MAX_STR_BUF)return -1;
        unicode_val = (wchar_t)(val & 0x0f);
        if(unicode_val < 0xa)
            str[i] = L'0' + unicode_val;
        else
            str[i] = L'A' + (unicode_val - 0xa);
        val >>= 4;
        i++;
    }while(val != 0);

    int j;
    for(j = 0; j < i ;j++){
        if(buf_content_size + j == buf_size-1){
            // buf is full: return 0
            buf[buf_content_size + j] = '\0';
            return 0;
        }
        buf[buf_content_size + j] = str[i-j-1];
    }
    buf[buf_content_size + j] = '\0';
    return buf_content_size + j;
}


// string concat function
// if succeed, return: current content size,
// else, return: 0
unsigned int strcat(wchar_t *buf, unsigned int buf_size, unsigned int buf_content_size, const wchar_t *s){
    unsigned int i;
    for(i = buf_content_size; i < buf_size;i++){
        buf[i] = s[i-buf_content_size];
        if(buf[i] == '\0')return i;
    }
    return 0;
}

void strncpy(wchar_t *dst, wchar_t *src, ull n){
    while(n--){
        *dst++ = *src++;
    }
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


unsigned char check_warn_error(ull status, wchar_t *message){
    if(status){
        puts(message);
        puts(L":");
        puth(status, 16);
        puts(L"\r\n");
    }
    return !status;
}

void assert(ull status, wchar_t *message){
    if(!check_warn_error(status, message))
        while(1);
}
