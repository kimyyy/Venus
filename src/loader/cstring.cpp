#include "common_loader.hpp"
#include "cstring.hpp"


// return: string length
// WARN: do not input uninitialized string
unsigned int strlen(const wchar_t *s){
    unsigned int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}

void strcpy(wchar_t * dst, const wchar_t * src){
    while(*src != '\0'){
        *dst++ = *src++;
    }
    *dst++ = '\0';
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

int IntToStr(wchar_t *str, ull val){

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

unsigned int strcat(wchar_t *dst, const wchar_t *src){
    unsigned int len = strlen((const wchar_t *)dst);    
    unsigned int i;
    for(i = 0; src[i] != '\0';i++){
        dst[i+len] = src[i];
    }
    dst[i+len] = '\0';
    return i;
}

void strncpy(wchar_t *dst, const wchar_t *src, ull n){
    while(n--){
        *dst++ = *src++;
    }
    *dst++ = '\0';
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

void test_cstring(){
    const wchar_t str[] = L"Hello";
    assert(strlen(str)==5);
    wchar_t buf[100];
    strncpy(buf, str, 4);
    assert(!strcmp(str, L"Hello"));
    assert(!strcmp(buf, L"Hell"));
    strcat(buf, L"o");
    assert(!strcmp(buf, L"Hello"));
    strcpy(buf, L"world");
    assert(!strcmp(buf, L"world"));
};
