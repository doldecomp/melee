#ifndef MSL_STRING_H
#define MSL_STRING_H

#include <platform.h>

char* strncpy(char* ATTRIBUTE_RESTRICT dst, const char* ATTRIBUTE_RESTRICT src,
              unsigned long n);
int __StringRead(void* isc, int ch, int Action);
char* strchr(const char* str, int chr);
int strncmp(const char* str1, const char* str2, unsigned long n);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* ATTRIBUTE_RESTRICT dst, const char* ATTRIBUTE_RESTRICT src);
size_t strlen(const char* s);

#endif
