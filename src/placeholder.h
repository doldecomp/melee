#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include "ft/forward.h"
#include <baselib/forward.h>

#include <m2c_macros.h>
#include <dolphin/os/os.h>

#if defined(__clang__) || defined(__GNUC__)
#define NOT_IMPLEMENTED                                                       \
    OSPanic(__FILE__, __LINE__, "%s is not implemented!", __func__)
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

#define CONV_LO 4503599627370496.0
#define CONV_HI 4503601774854144.0

#endif
