#ifndef _METROTRK_TARGIMPL_H
#define _METROTRK_TARGIMPL_H

#include <platform.h>

#include "MetroTRK/msgbuf.h"
#include "MetroTRK/nubevent.h"
#include "MetroTRK/trk.h"

typedef enum ValidMemoryOptions {
    kValidMemoryReadable = 0,
    kValidMemoryWriteable = 1
} ValidMemoryOptions;

typedef enum MemoryAccessOptions {
    kUserMemory = 0,
    kDebuggerMemory = 1
} MemoryAccessOptions;

typedef struct DSVersions {
    /* 0x00 */ u8 kernelMajor;
    /* 0x01 */ u8 kernelMinor;
    /* 0x02 */ u8 protocolMajor;
    /* 0x03 */ u8 protocolMinor;
} DSVersions; // size = 0x04

typedef struct DSCPUType {
    /* 0x00 */ u8 cpuMajor;
    /* 0x01 */ u8 cpuMinor;
    /* 0x02 */ u8 bigEndian;
    /* 0x03 */ u8 defaultTypeSize;
    /* 0x04 */ u8 fpTypeSize;
    /* 0x05 */ u8 extended1TypeSize;
    /* 0x06 */ u8 extended2TypeSize;
} DSCPUType; // size = 0x07

void TRKTargetSetStopped(bool);
void TRKTargetSetInputPendingPtr(void*);
DSError TRKTargetAccessMemory(void*, u32, size_t*, MemoryAccessOptions, bool);
DSError TRKTargetAccessDefault(u32, u32, MessageBuffer*, size_t*, bool);
DSError TRKTargetAccessFP(u32 firstRegister, u32 lastRegister,
                          MessageBuffer* b, size_t* registerStorageSize,
                          s32 read);
DSError TRKTargetAccessExtended1(u32 firstRegister, u32 lastRegister,
                                 MessageBuffer* b, size_t* registerStorageSize,
                                 s32 read);
DSError TRKTargetAccessExtended2(u32, u32, MessageBuffer*, size_t*, bool);
DSError TRKTargetVersions(DSVersions*);
DSError TRKTargetSupportMask(DSSupportMask*);
DSError TRKTargetCheckException(void);
DSError TRKInitializeTarget(void);
DSError TRKTargetContinue(void);
void TRKSwapAndGo(void);
DSError TRKTargetInterrupt(NubEvent*);
DSError TRKTargetAddStopInfo(MessageBuffer*);
void TRKTargetAddExceptionInfo(MessageBuffer*);
DSError TRKTargetSingleStep(u32, bool);
DSError TRKTargetStepOutOfRange(u32, u32, bool);
u32 TRKTargetGetPC(void);
DSError TRKTargetSupportRequest(void);
DSError TRKTargetFlushCache(u8, u32, u32);
bool TRKTargetStopped(void);
void TRKTargetSetStopped(bool);
DSError TRKTargetStop(void);
u32 TRKTargetTranslate(u32 addr);
void TRKInterruptHandler(u16);
void TRKTargetSetInputPendingPtr(void*);
DSError TRKTargetCPUType(DSCPUType* cpuType);
void TRKInterruptHandlerEnableInterrupts(void);
bool TRKTargetStepDone(void);
DSError TRKTargetDoStep(void);

#endif
