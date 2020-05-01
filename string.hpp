#pragma once

#include "common.hpp"
#define MAX_STR_BUF 100

unsigned int strlen(wchar_t *s);
void strcpy(const wchar_t * src, wchar_t * dst);
unsigned int intToStr(wchar_t * buf, unsigned int buf_size, unsigned int buf_content_size, ull val);
void strncpy(wchar_t *dst, const wchar_t *src, ull n);
unsigned int strcat(wchar_t *buf, unsigned int buf_size, unsigned int buf_content_size, const wchar_t *s);
int strcmp(const wchar_t *s1, const wchar_t *s2);
