#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include "ft/forward.h"
#include <baselib/forward.h>

#include <m2c_macros.h>
#include <dolphin/os.h>

/// A label in a jump table
typedef void (*jmp_t)(void);

/// A jump table
typedef jmp_t jtbl_t[];

#if defined(__clang__) || defined(__GNUC__)
#define NOT_IMPLEMENTED                                                       \
    OSPanic(__FILE__, __LINE__, "%s is not implemented!", __func__)
#elif MUST_MATCH
#define NOT_IMPLEMENTED asm { nop }
#else
#define NOT_IMPLEMENTED                                                       \
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

#if defined(MUST_MATCH) && !defined(WIP)
#define ASM asm
#else
#define ASM
#endif

#define LITERAL static ATTRIBUTE_USED

#ifndef SDATA
#if defined(__MWERKS__) && !defined(M2CTX)
#define SDATA __declspec(section ".sdata")
#else
#define SDATA
#endif
#endif

#endif
