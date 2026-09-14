#ifndef __STDDEF_H__
#define __STDDEF_H__

typedef unsigned short wchar_t;

typedef unsigned long size_t;

#ifdef __MWERKS__
typedef signed int intptr_t;
typedef unsigned int uintptr_t;
#else
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
#endif

#define offsetof(type, member) ((size_t) &(((type*) 0)->member))

#ifndef NULL
#define NULL 0L
#endif

#endif
