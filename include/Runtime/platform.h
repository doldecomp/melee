#ifndef INCLUDE_RUNTIME_PLATFORM_H
#define INCLUDE_RUNTIME_PLATFORM_H

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

#endif
