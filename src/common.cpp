#include "common.hpp"
#include "efi.hpp"
#include "cstring.hpp"

void panic(const wchar_t *message){
    puts(message);
    while(TRUE);
}

void ClearScreen(void){
    ST->ConOut->ClearScreen(ST->ConOut);
}

void putc(const wchar_t c){
    wchar_t str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
}

void puts(const wchar_t *s){
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

    return (key.UnicodeChar)? key.UnicodeChar : (key.ScanCode + SC_OFS);;
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


unsigned char check_warn_error(ull status, const wchar_t *message){
    if(status){
        puts(message);
        puts(L":");
        puth(status, 16);
        puts(L"\r\n");
    }
    return !status;
}

void assert_status(ull status, const wchar_t *message){
    if(!check_warn_error(status, message))
        while(1);
}
