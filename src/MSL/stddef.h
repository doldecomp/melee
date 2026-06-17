#ifndef __STDDEF_H__
#define __STDDEF_H__

typedef unsigned short wchar_t;
typedef signed int ssize_t;

/// @deprecated Use #usize_t.
typedef unsigned long size_t;

/// @todo Rename to @c size_t when #size_t is deleted.
typedef unsigned int usize_t;

typedef signed int intptr_t;
typedef unsigned int uintptr_t;

#define offsetof(type, member) ((size_t) &(((type*) 0)->member))

#ifndef NULL
#define NULL 0L
#endif

#endif
