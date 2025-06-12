#ifndef RUNTIME_PLATFORM_H
#define RUNTIME_PLATFORM_H

#include <stdbool.h> // IWYU pragma: export
#include <stddef.h>  // IWYU pragma: export
#include <dolphin/types.h>

/// The underlying type of an @c enum, used as a placeholder
typedef int enum_t;

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

#ifndef SECTION_CTORS
#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_CTORS __declspec(section ".ctors")
#else
#define SECTION_CTORS
#endif
#endif

#ifndef SECTION_DTORS
#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_DTORS __declspec(section ".dtors")
#else
#define SECTION_DTORS
#endif
#endif

#ifndef ATTRIBUTE_NORETURN
#if defined(__clang__) || defined(__GNUC__)
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
#define ATTRIBUTE_NORETURN
#endif
#endif

#ifndef ATTRIBUTE_RESTRICT
#if defined(__MWERKS__) && !defined(M2CTX)
#define ATTRIBUTE_RESTRICT __restrict
#else
#define ATTRIBUTE_RESTRICT
#endif
#endif

#ifdef PERMUTER
#define AT_ADDRESS(x) = FIXEDADDR(x)
#elif defined(__MWERKS__) && !defined(M2CTX)
#define AT_ADDRESS(x) : (x)
#else
#define AT_ADDRESS(x)
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
#define S8_MAX 0x7F
#define S16_MAX 0x7FFF
#define S32_MAX 0x7FFFFFFF
#define F32_MAX 3.4028235e38f

#define SQ(x) ((x) * (x))
#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#ifdef __cplusplus
#ifndef _Static_assert
#define _Static_assert static_assert
#endif
#endif
#ifdef __MWERKS__
#define STATIC_ASSERT(cond)                                                   \
    struct {                                                                  \
        int x[1 - 2 * !(cond)];                                               \
    };
#else
#define STATIC_ASSERT(cond) _Static_assert((cond), "(" #cond ") failed")
#endif

#define RETURN_IF(cond)                                                       \
    do {                                                                      \
        if ((cond)) {                                                         \
            return;                                                           \
        }                                                                     \
    } while (0)

#if defined(__MWERKS__) && !defined(M2CTX)
#define SDATA __declspec(section ".sdata")
#define WEAK __declspec(weak)
#else
#define SDATA
#define WEAK
#endif

#endif
