#pragma once
#include "common.hpp"
#include "efi.hpp"

#define EfiPageSize (1<<12)

void memcpy(char *dst, const char *src, uint32_t n);
void memzero(char *dst, uint32_t n);
void mem_test();
void operator delete(void *p);
void operator delete(void *p, unsigned long long t);
void *operator new(unsigned long long size);
void *operator new[](unsigned long long size);
void *malloc(UINTN size);
void free(void* buf);
