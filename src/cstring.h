#ifndef __CSTRING_H__
#define __CSTRING_H__

#include <Runtime/platform.h>
#include <stddef.h>

int wcstombs(void* dst, const void* src, size_t len);
int memcmp(const void* str1, const void* str2, size_t len);
void* memchr(const void* str, int c, size_t len);
void* memmove(void* dst, const void* src, size_t len);

#endif
