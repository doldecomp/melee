#ifndef _DOLPHIN_OS_EXCEPTION_
#define _DOLPHIN_OS_EXCEPTION_

#include <platform.h>

#include <dolphin/os/OSContext.h>

typedef enum OSException {
    OS_EXCEPTION_FLOATING_POINT = 7,
    OS_EXCEPTION_COUNT = 15,
} OSException;

typedef u8 __OSException;
typedef void (*__OSExceptionHandler)(__OSException exception,
                                     OSContext* context);

#define OS_EXCEPTION_SAVE_GPRS(context)                                       \
    stw r0, OS_CONTEXT_R0(context);                                           \
    stw r1, OS_CONTEXT_R1(context);                                           \
    stw r2, OS_CONTEXT_R2(context);                                           \
    stmw r6, OS_CONTEXT_R6(context);                                          \
    mfspr r0, GQR1;                                                           \
    stw r0, OS_CONTEXT_GQR1(context);                                         \
    mfspr r0, GQR2;                                                           \
    stw r0, OS_CONTEXT_GQR2(context);                                         \
    mfspr r0, GQR3;                                                           \
    stw r0, OS_CONTEXT_GQR3(context);                                         \
    mfspr r0, GQR4;                                                           \
    stw r0, OS_CONTEXT_GQR4(context);                                         \
    mfspr r0, GQR5;                                                           \
    stw r0, OS_CONTEXT_GQR5(context);                                         \
    mfspr r0, GQR6;                                                           \
    stw r0, OS_CONTEXT_GQR6(context);                                         \
    mfspr r0, GQR7;                                                           \
    stw r0, OS_CONTEXT_GQR7(context);

#endif
