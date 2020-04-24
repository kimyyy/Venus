#pragma once

typedef unsigned long long ull;

#define NULL   (void *)0
#define TRUE   1
#define FALSE  0

void putc(wchar_t c);
void puts(wchar_t *s);
wchar_t getc(void);
unsigned int gets(wchar_t *buf, unsigned int buf_size);
int strcmp(const wchar_t *s1, const wchar_t *s2);
