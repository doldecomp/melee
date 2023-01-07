#ifndef __TYPES_H__
#define __TYPES_H__

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;
typedef double f64;
typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef int BOOL;

typedef int intptr_t;
typedef unsigned int uintptr_t;

typedef unsigned long size_t;
typedef void* unk_t;
typedef void (*jmp_t)(void);
typedef jmp_t jtbl_t[];

#define TRUE (1)
#define FALSE (0)

#define NULL ((void*) 0)

#define FLT_MAX 3.4028235E38

#define assert_line(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))

#define STRUCT_PLACEHOLDER(module, number)                                     \
    extern struct _##module##_Unk##number;                                     \
    typedef struct _##module##_Unk##number module##_Unk##number;

#define CALLBACK_PLACEHOLDER(module, number)                                   \
    typedef void (*module##_UnkCallback##number)(void);

#define UNK_FUNC(name) unk_t name()

#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num)
#else
#error unknown compiler
#endif
#endif

#if defined(PERMUTER)
#define AT_ADDRESS(x) = FIXEDADDR(x)
#elif defined(__MWERKS__)
#define AT_ADDRESS(x) : (x)
#else
#define AT_ADDRESS(x)
#endif

#pragma region "macros.inc"
#define qr0 0
#define qr1 1
#define qr2 2
#define qr3 3
#define qr4 4
#define qr5 5
#define qr6 6
#define qr7 7
#pragma endregion

#endif
