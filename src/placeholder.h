#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <dolphin/os/os.h>
#include <m2c_macros.h>

#define NOT_IMPLEMENTED                                                        \
    OSPanic(__FILE__, __LINE__, "%s is not implemented!", __func__)

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

#endif
