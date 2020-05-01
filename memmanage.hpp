#pragma once
#include "common.hpp"

void operator delete(void *p);
void operator delete(void *p, unsigned long long t);
void *operator new(unsigned long long size);
void *operator new[](unsigned long long size);
void *malloc(unsigned long size);
void free(void* buf);
