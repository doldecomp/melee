#ifndef INCLUDE_RUNTIME_PLATFORM_H
#define INCLUDE_RUNTIME_PLATFORM_H

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

/// A signed integer used to contain boolean values
/// @todo Rename to @c bool.
///       C++ can use its native type via preprocessor conditions.
typedef int BOOL;

/// The underlying type of an @c enum, used as a placeholder
typedef int enum_t;

typedef int intptr_t;
typedef unsigned int uintptr_t;
typedef unsigned long size_t;
typedef signed long ssize_t;

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

/// #BOOL true
#define TRUE (1)

/// #BOOL false
#define FALSE (0)

/// A null pointer
#define NULL ((any_t) 0)

#if defined(__MWERKS__) && defined(GEKKO)
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

#ifndef ATTRIBUTE_NORETURN
#if defined(__MWERKS__)
#define ATTRIBUTE_NORETURN
#elif defined(__clang__) || defined(__GNUC__)
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
#error unknown compiler
#endif
#endif

#ifdef PERMUTER
#define AT_ADDRESS(x) = FIXEDADDR(x)
#elif defined(__MWERKS__)
#define AT_ADDRESS(x) : (x)
#else
#define AT_ADDRESS(x)
#endif

#ifdef GEKKO
#define qr0 0
#define qr1 1
#define qr2 2
#define qr3 3
#define qr4 4
#define qr5 5
#define qr6 6
#define qr7 7
#endif

#define FLT_MAX (3.4028235E38)

#endif
