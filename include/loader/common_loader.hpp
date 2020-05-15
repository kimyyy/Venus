#pragma once

#include "common.hpp"

typedef unsigned long long ull;

#define __NULL   (void *)0
#define TRUE   1
#define FALSE  0

#define CAT(A, B) A##B
#define STRING(str) #str
#define WSTRING(A) CAT(L, #A)

#define SC_OFS 0x1680
#define SC_ESC (SC_OFS + 0x0017)

void panic(const wchar_t *message);
void ClearScreen(void);
void putc(const wchar_t c);
void puts(const wchar_t *s);
void puth(ull val, unsigned char num_digits);
wchar_t getc(void);
unsigned int gets(wchar_t *buf, unsigned int buf_size);
unsigned char check_warn_error(ull status, const wchar_t *name);
void assert_status(ull status, const wchar_t *message);
void assert(bool condition);
