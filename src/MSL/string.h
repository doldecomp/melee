#ifndef MSL_STRING_H
#define MSL_STRING_H

#include <Runtime/platform.h>

char* strncpy(char* __restrict dst, const char* __restrict src,
              unsigned long n);
int __StringRead(void* isc, int ch, int Action);
char* strchr(const char* str, int chr);
int strncmp(const char* str1, const char* str2, unsigned long n);
int strcmp(const char* str1, const char* str2);
char*(strcpy) (char* __restrict dst, const char* __restrict src);

#endif
