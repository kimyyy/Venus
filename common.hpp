#pragma once

typedef unsigned long long ull;

#define NULL   (void *)0
#define TRUE   1
#define FALSE  0

#define CAT(A, B) A##B
#define STRING(str) #str
#define WSTRING(A) CAT(L, #A)

void ClearScreen(void);
void putc(const wchar_t c);
void puts(const wchar_t *s);
void puth(ull val, unsigned char num_digits);
wchar_t getc(void);
unsigned int gets(wchar_t *buf, unsigned int buf_size);
unsigned int strlen(wchar_t *s);
unsigned int intToStr(wchar_t * buf, unsigned int buf_size, unsigned int buf_content_size, ull val);
void strncpy(wchar_t *dst, wchar_t *src, ull n);
unsigned int strcat(wchar_t *buf, unsigned int buf_size, unsigned int buf_content_size, const wchar_t *s);
int strcmp(const wchar_t *s1, const wchar_t *s2);
unsigned char check_warn_error(ull status, const wchar_t *name);
void assert(ull status, const wchar_t *message);
