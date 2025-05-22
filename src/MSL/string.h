#ifndef _STRING_H_
#define _STRING_H_

#include "stddef.h"

char* strcpy(char* dst, const char* src);
char* strncpy(char* dst, const char* src, size_t num);
char* strcat(char* dest, const char* src);
size_t strlen(const char* s);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strchr(const char* str, int chr);

void* memchr(const void* p, int val, size_t n);
int memcmp(const void* p1, const void* p2, size_t n);
void* memset(void* dst, int val, size_t n);
void* memcpy(void* dst, const void* src, size_t n);
void* memmove(void* dst, const void* src, size_t n);

#endif
