#ifndef GALE01_32904C
#define GALE01_32904C

#include <placeholder.h>

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
/* 32A184 */ UNK_RET TRKTargetGetPC(UNK_PARAMS);
/* 32A194 */ UNK_RET TRKTargetSupportRequest(UNK_PARAMS);
/* 32A284 */ UNK_RET TRKTargetFlushCache(UNK_PARAMS);
/* 32A2C0 */ UNK_RET TRKTargetStopped(UNK_PARAMS);
/* 32A2D0 */ UNK_RET TRKTargetSetStopped(UNK_PARAMS);
/* 32A2E0 */ UNK_RET TRKTargetStop(UNK_PARAMS);
/* 32A308 */ UNK_RET TRKPPCAccessSPR(UNK_PARAMS);
/* 32A3B8 */ UNK_RET TRKPPCAccessPairedSingleRegister(UNK_PARAMS);
/* 32A430 */ UNK_RET TRKPPCAccessFPRegister(UNK_PARAMS);
/* 32A5B0 */ UNK_RET TRKPPCAccessSpecialReg(UNK_PARAMS);
/* 32A618 */ UNK_RET TRKTargetSetInputPendingPtr(UNK_PARAMS);

#endif
