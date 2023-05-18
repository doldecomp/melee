#ifndef DOLPHIN_OS_FORWARD_H
#define DOLPHIN_OS_FORWARD_H

#include <platform.h>

typedef u16 OSError;
typedef s16 __OSInterrupt;
typedef u32 OSInterruptMask;

typedef struct OSContext OSContext;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSMutexLink OSMutexLink;
typedef struct OSThread OSThread;
typedef struct _OSThread_Unk1 OSThread_Unk1;
typedef struct _OSThread_Unk2 OSThread_Unk2;
typedef struct _OSThread_Unk3 OSThread_Unk3;
typedef struct _OSThread_Unk4 OSThread_Unk4;
typedef struct OSAlarm OSAlarm;

typedef enum OSException {
    OS_EXCEPTION_FLOATING_POINT = 7,
    OS_EXCEPTION_COUNT = 15,
} OSException;

typedef enum OSInterruptType {
    OS_INTR_MEM_0,
    OS_INTR_MEM_1,
    OS_INTR_MEM_2,
    OS_INTR_MEM_3,
    OS_INTR_MEM_ADDRESS,
    OS_INTR_DSP_AI,
    OS_INTR_DSP_ARAM,
    OS_INTR_DSP_DSP,
    OS_INTR_AI_AI,
    OS_INTR_EXI_0_EXI,
    OS_INTR_EXI_0_TC,
    OS_INTR_EXI_0_EXT,
    OS_INTR_EXI_1_EXI,
    OS_INTR_EXI_1_TC,
    OS_INTR_EXI_1_EXT,
    OS_INTR_EXI_2_EXI,
    OS_INTR_EXI_2_TC,
    OS_INTR_PI_CP,
    OS_INTR_PI_PE_TOKEN,
    OS_INTR_PI_PE_FINISH,
    OS_INTR_PI_SI,
    OS_INTR_PI_DI,
    OS_INTR_PI_RSW,
    OS_INTR_PI_ERROR,
    OS_INTR_PI_VI,
    OS_INTR_PI_DEBUG,
    OS_INTR_PI_HSP,
    OS_INTR_PI_ACR,
    OS_INTR_28,
    OS_INTR_29,
    OS_INTR_30,
    OS_INTR_31,

    OS_INTR_MAX
} OSInterruptType;

typedef enum {
    EXI_STATE_DMA_ACCESS = (1 << 0),
    EXI_STATE_IMM_ACCESS = (1 << 1),
    EXI_STATE_SELECTED = (1 << 2),
    EXI_STATE_ATTACHED = (1 << 3),
    EXI_STATE_LOCKED = (1 << 4),
    EXI_STATE_BUSY = EXI_STATE_DMA_ACCESS | EXI_STATE_IMM_ACCESS
} EXIState;

typedef enum {
    EXI_CHAN_0,
    EXI_CHAN_1,
    EXI_CHAN_2,
    EXI_MAX_CHAN
} EXIChannel;

typedef enum {
    EXI_READ,
    EXI_WRITE,
    EXI_TYPE_2,
    EXI_MAX_TYPE
} EXIType;

typedef enum {
    OS_THREAD_STATE_EXITED = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_SLEEPING = 4,
    OS_THREAD_STATE_MORIBUND = 8
} OSThreadState;

typedef enum {
    OS_THREAD_DETACHED = (1 << 0)
} OSThreadFlag;

typedef void (*__OSExceptionHandler)(OSException exception,
                                     OSContext* context);
typedef void (*OSErrorHandler)(OSError error, OSContext* context, ...);
typedef void (*EXICallback)(EXIChannel, OSContext*);
typedef void (*OSSwitchThreadCallback)(OSThread*, OSThread*);
typedef OSThread_Unk3* (*OSThreadFunc)(OSThread_Unk4*);
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

#endif
