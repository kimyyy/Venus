#include "typedef.h"

#pragma once

struct EFI_INPUT_KEY {
    wchar_t ScanCode;
    wchar_t UnicodeChar;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    ull _buf;
    ull (*OutputString) (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, wchar_t *String);
    ull _buf2[4];
    ull (*ClearScreen) (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
};

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    ull _buf;
    ull (*ReadKeyStroke) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    void *WaitForKey;
};

struct EFI_SYSTEM_TABLE {
    char _buf[44];
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    ull _buf2;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
};

