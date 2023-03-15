/// @file
/// @todo Assumes @c __PPCGEKKO__.
#ifndef __STDDEF_H__
#define __STDDEF_H__

typedef unsigned short wchar_t;
typedef signed int ssize_t;

/// @todo This should be <tt>unsigned int</tt>.
typedef unsigned long size_t;

typedef signed int intptr_t;
typedef unsigned int uintptr_t;

/// A null pointer
#define NULL ((any_t) 0)

#endif
