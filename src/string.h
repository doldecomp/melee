#ifndef __STRING_H__
#define __STRING_H__

#include <__mem.h>
#include <platform.h>
#include <stddef.h>

void* memset(void* ptr, int value, size_t num);
int __StringRead(void*, int, int);
char* strchr(const char*, int);
int strncmp(const char*, const char*, unsigned long);
int strcmp(const char*, const char*);
char* strncpy(char* ATTRIBUTE_RESTRICT, const char* ATTRIBUTE_RESTRICT,
              unsigned long);
char* strcpy(char* ATTRIBUTE_RESTRICT dst, const char* ATTRIBUTE_RESTRICT src);
size_t strlen(const char* s);

#endif
