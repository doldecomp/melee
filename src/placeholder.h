#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <platform.h>

#include <m2c_macros.h> // IWYU pragma: export

/// A label in a jump table
typedef void (*jmp_t)(void);

/// A jump table
typedef jmp_t jtbl_t[];

#if defined(__clang__) || defined(__GNUC__)
#include <dolphin/os.h>
#define NOT_IMPLEMENTED                                                       \
    OSPanic(__FILE__, __LINE__, "%s is not implemented!", __func__)
#elif defined(__MWERKS__) && !defined(BUGFIX)
#define NOT_IMPLEMENTED asm { nop }
#else
#include <dolphin/os.h>
#define NOT_IMPLEMENTED \
    OSPanic(__FILE__, __LINE__, "Function is not implemented!")
#endif

#ifndef UNK_T
#ifdef M2CTX
#define UNK_T M2C_UNK
#else
#define UNK_T void*
#endif
#endif

#ifndef UNK_RET
#ifdef M2CTX
#define UNK_RET M2C_UNK
#else
#define UNK_RET void
#endif
#endif

#ifndef UNK_PARAMS
#ifdef M2CTX
#define UNK_PARAMS
#else
#define UNK_PARAMS void
#endif
#endif

#ifndef UNK_SIZE_ARRAY
#if defined(__MWERKS__) && !defined(M2CTX)
#define UNK_SIZE_ARRAY []
#else
#define UNK_SIZE_ARRAY [0]
#endif
#endif

#define U32_TO_F32 4503599627370496.0
#define S32_TO_F32 4503601774854144.0

#ifdef MWERKS_GEKKO
#define ASM asm
#else
#define ASM
#endif

#ifndef UNUSED
#if defined(__clang__) || defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif

#define PAD_STACK(bytes)                                                      \
    do {                                                                      \
        UNUSED unsigned char _[(bytes)];                                      \
    } while (0)

/// @warning Creates fake @c .rodata entries!
#define FORCE_PAD_STACK(bytes)                                                \
    do {                                                                      \
        UNUSED unsigned char _[(bytes)] = { 0 };                              \
    } while (0)

#define FORCE_PAD_STACK_8                                                     \
    do {                                                                      \
        UNUSED u64 _0 = 0;                                                    \
    } while (0)

#define FORCE_PAD_STACK_16                                                    \
    do {                                                                      \
        UNUSED u64 _0 = 0, _1 = 0;                                            \
    } while (0)

#define FORCE_PAD_STACK_32                                                    \
    do {                                                                      \
        UNUSED u64 _0 = 0, _1 = 0, _2 = 0, _3 = 0;                            \
    } while (0)
#endif
