#ifndef MSL_STRING_H
#define MSL_STRING_H

#include <ctypes.h>

#include <stddef.h>

int strcmp(const char * str1, const char * str2);
int __StringRead(unk_t, int, int);
char* strchr(const char*, int);
int strncmp(const char*, const char*, unsigned long);
int strcmp(const char*, const char*);
char* strncpy(char* __restrict, const char* __restrict, unsigned long);
char* strcpy(char* __restrict, const char* __restrict);
unsigned long strlen(const char*);

#endif
