#ifndef _DOLPHIN_TYPES_H_
#define _DOLPHIN_TYPES_H_

typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long int s64;
typedef unsigned long long int u64;

typedef float f32;
typedef double f64;
typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef char* Ptr;

typedef int BOOL;

#define FALSE 0
#define TRUE 1

#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))

#ifndef NULL
#define NULL ((void*) 0)
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#include "cmath.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#endif
