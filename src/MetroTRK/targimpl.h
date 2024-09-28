#ifndef GALE01_32904C
#define GALE01_32904C

#include <placeholder.h>

struct gTRKCPUState_t {
    /* 0x000 */ char pad_0[0x80];
    /* 0x080 */ s32 unk_80;         /* inferred */
    /* 0x084 */ char pad_84[0x3AC]; /* maybe part of unk_80[0xEC]? */
}; /* size = 0x430 */
STATIC_ASSERT(sizeof(struct gTRKCPUState_t) == 0x430);

struct gTRKState_t {
    /* 0x00 */ char pad_0[0x98];
    /* 0x98 */ s32 unk_98;
    /* 0x9C */ char pad_9C[4];
    /* 0xA0 */ s32 unk_A0; /* inferred */
}; /* size = 0xA4 */
STATIC_ASSERT(sizeof(struct gTRKState_t) == 0xA4);

/* 4A4BF0 */ extern struct gTRKState_t gTRKState;

/* 32904C */ int __TRK_get_MSR(void);
/* 329054 */ void __TRK_set_MSR(int);
/* 32905C */ UNK_RET TRKValidMemory32(UNK_PARAMS);
/* 329194 */ UNK_RET TRK_ppc_memcpy(UNK_PARAMS);
/* 3291D0 */ UNK_RET TRKTargetAccessMemory(UNK_PARAMS);
/* 329334 */ UNK_RET TRKTargetReadInstruction(UNK_PARAMS);
/* 329380 */ UNK_RET TRKTargetAccessDefault(UNK_PARAMS);
/* 32947C */ UNK_RET TRKTargetAccessFP(UNK_PARAMS);
/* 3295C4 */ UNK_RET TRKTargetAccessExtended1(UNK_PARAMS);
/* 32973C */ UNK_RET TRKTargetAccessExtended2(UNK_PARAMS);
/* 3298B8 */ UNK_RET TRKTargetVersions(UNK_PARAMS);
/* 3298E0 */ UNK_RET TRKTargetSupportMask(UNK_PARAMS);
/* 329984 */ UNK_RET TRKTargetCPUType(UNK_PARAMS);
/* 3299EC */ UNK_RET TRKInterruptHandler(UNK_PARAMS);
/* 329B80 */ UNK_RET TRKExceptionHandler(UNK_PARAMS);
/* 329C1C */ UNK_RET TRKPostInterruptEvent(UNK_PARAMS);
/* 329CCC */ UNK_RET TRKInterruptHandlerEnableInterrupts(UNK_PARAMS);
/* 329DE4 */ UNK_RET TRKTargetInterrupt(UNK_PARAMS);
/* 329E48 */ UNK_RET TRKTargetAddStopInfo(UNK_PARAMS);
/* 329ED8 */ UNK_RET TRKTargetAddExceptionInfo(UNK_PARAMS);
/* 329F60 */ UNK_RET TRKTargetEnableTrace(UNK_PARAMS);
/* 329F9C */ UNK_RET TRKTargetStepDone(UNK_PARAMS);
/* 32A020 */ UNK_RET TRKTargetDoStep(UNK_PARAMS);
/* 32A090 */ UNK_RET TRKTargetCheckStep(UNK_PARAMS);
/* 32A0F8 */ UNK_RET TRKTargetSingleStep(UNK_PARAMS);
/* 32A13C */ UNK_RET TRKTargetStepOutOfRange(UNK_PARAMS);
/* 32A184 */ s32 TRKTargetGetPC(void);
/* 32A194 */ UNK_RET TRKTargetSupportRequest(UNK_PARAMS);
/* 32A284 */ UNK_RET TRKTargetFlushCache(UNK_PARAMS);
/* 32A2C0 */ s32 TRKTargetStopped(void);
/* 32A2D0 */ void TRKTargetSetStopped(s32 arg0);
/* 32A2E0 */ UNK_RET TRKTargetStop(UNK_PARAMS);
/* 32A308 */ UNK_RET TRKPPCAccessSPR(UNK_PARAMS);
/* 32A3B8 */ UNK_RET TRKPPCAccessPairedSingleRegister(UNK_PARAMS);
/* 32A430 */ UNK_RET TRKPPCAccessFPRegister(UNK_PARAMS);
/* 32A5B0 */ UNK_RET TRKPPCAccessSpecialReg(UNK_PARAMS);
/* 32A618 */ void TRKTargetSetInputPendingPtr(s32 arg0);
/* 4A4C98 */ extern struct gTRKCPUState_t gTRKCPUState;

#endif
