#pragma once

#include "common_loader.hpp"
#define MAX_STR_BUF 100

unsigned int strlen(const wchar_t *s);
void strcpy(const wchar_t * dst, wchar_t * src);
unsigned int intToStr(wchar_t * buf, unsigned int buf_size, unsigned int buf_content_size, ull val);
void strncpy(wchar_t *dst, const wchar_t *src, ull n);
unsigned int strcat(wchar_t *buf, unsigned int buf_size, unsigned int buf_content_size, const wchar_t *s);
unsigned int strcat(wchar_t *dst, const wchar_t *src);
int strcmp(const wchar_t *s1, const wchar_t *s2);
void test_cstring();
