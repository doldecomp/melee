#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>

void memcpy(void* dst, void* src, size_t num);
void* memset(void* ptr, int value, size_t num);
int __StringRead(void*, int, int);
char* strchr(const char*, int);
int strncmp(const char*, const char*, unsigned long);
int strcmp(const char*, const char*);
char* strncpy(char* __restrict, const char* __restrict, unsigned long);
char* strcpy(char* __restrict, const char* __restrict);
unsigned long strlen(const char*);

#endif
