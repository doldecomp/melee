#ifndef INCLUDE_RUNTIME_PLATFORM_H
#define INCLUDE_RUNTIME_PLATFORM_H

#if defined(__MWERKS__) || defined(__GNUC__)
#define MWERKS_GNUC
#endif

#include <stdbool.h>
#include <stddef.h>

/// A signed 8-bit integer
typedef signed char s8;

/// A signed 16-bit integer
typedef signed short s16;

/// A signed 32-bit integer
typedef signed long s32;

/// A signed 64-bit integer
typedef signed long long s64;

/// An unsigned 8-bit integer
typedef unsigned char u8;

/// An unsigned 16-bit integer
typedef unsigned short u16;

/// An unsigned 32-bit integer
typedef unsigned long u32;

/// An unsigned 64-bit integer
typedef unsigned long long u64;

/// An unsigned integer of platform-dependent size
typedef unsigned int uint;

/// A volatile, unsigned 8-bit integer
typedef volatile u8 vu8;

/// A volatile, unsigned 16-bit integer
typedef volatile u16 vu16;

/// A volatile, unsigned 32-bit integer
typedef volatile u32 vu32;

/// A volatile, unsigned 64-bit integer
typedef volatile u64 vu64;

/// A volatile, signed 8-bit integer
typedef volatile s8 vs8;

/// A volatile, signed 16-bit integer
typedef volatile s16 vs16;

/// A volatile, signed 32-bit integer
typedef volatile s32 vs32;

/// A volatile, signed 64-bit integer
typedef volatile s64 vs64;

/// A 32-bit floating-point number
typedef float f32;

/// A 64-bit floating-point number
typedef double f64;

/// A volatile 32-bit floating-point number
typedef volatile f32 vf32;

/// A volatile 64-bit floating-point number
typedef volatile f64 vf64;

/// The underlying type of an @c enum, used as a placeholder
typedef int enum_t;

/// A pointer to an unknown type
typedef void* unk_t;

/// A pointer to an unspecified type, used for polymorphic data
typedef void* any_t;

/// A label in a jump table
typedef void (*jmp_t)(void);

/// A jump table
typedef jmp_t jtbl_t[];

/// A @c void callback with no arguments.
typedef void (*Event)(void);

#if defined(__MWERKS__) && defined(__PPCGEKKO__)
#define MWERKS_GEKKO
#endif

#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num)
#else
#error unknown compiler
#endif
#endif

#ifndef SECTION_INIT
#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_INIT __declspec(section ".init")
#else
#define SECTION_INIT
#endif
#endif

#ifndef ATTRIBUTE_NORETURN
#if defined(__clang__) || defined(__GNUC__)
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
#define ATTRIBUTE_NORETURN
#endif
#endif

#ifdef PERMUTER
#define AT_ADDRESS(x) = FIXEDADDR(x)
#elif defined(__MWERKS__) && !defined(M2CTX)
#define AT_ADDRESS(x) : (x)
#else
#define AT_ADDRESS(x)
#endif

#ifndef UNK_SIZE_ARRAY
#if defined(__MWERKS__) && !defined(M2CTX)
#define UNK_SIZE_ARRAY []
#else
#define UNK_SIZE_ARRAY [0]
#endif
#endif

#ifdef __PPCGEKKO__
#define qr0 0
#define qr1 1
#define qr2 2
#define qr3 3
#define qr4 4
#define qr5 5
#define qr6 6
#define qr7 7
#endif

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF
#define U32_MAX 0xFFFFFFFF
#define F32_MAX 3.4028235E38

#define FLAGS_NONE 0
#define HAS_FLAG(value, flag) ((value) & (flag))
#define NOT_FLAG(value, flag) (!((value) & (flag)))

#endif
