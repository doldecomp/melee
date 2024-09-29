#include <placeholder.h>

#include "targimpl.h"

int __TRK_get_MSR(void)
{
#ifdef MWERKS_GEKKO
    asm { mfmsr r3 }
#else
    NOT_IMPLEMENTED;
#endif
}

#ifdef MWERKS_GEKKO
void __TRK_set_MSR(register int value)
{
    asm { mtmsr r3 }
}
#else
void __TRK_set_MSR(int value)
{
    NOT_IMPLEMENTED;
}
#endif

/// #TRKValidMemory32

/// #TRK_ppc_memcpy

/// #TRKTargetAccessMemory

/// #TRKTargetReadInstruction

/// #TRKTargetAccessDefault

/// #TRKTargetAccessFP

/// #TRKTargetAccessExtended1

/// #TRKTargetAccessExtended2

/// #TRKTargetVersions

/// #TRKTargetSupportMask

/// #TRKTargetCPUType

/// #TRKInterruptHandler

/// #TRKExceptionHandler

/// #TRKPostInterruptEvent

/// #TRKInterruptHandlerEnableInterrupts

/// #TRKTargetInterrupt

/// #TRKTargetAddStopInfo

/// #TRKTargetAddExceptionInfo

/// #TRKTargetEnableTrace

/// #TRKTargetStepDone

/// #TRKTargetDoStep

/// #TRKTargetCheckStep

/// #TRKTargetSingleStep

/// #TRKTargetStepOutOfRange

s32 TRKTargetGetPC(void)
{
    return gTRKCPUState.unk_80;
}

/// #TRKTargetSupportRequest

/// #TRKTargetFlushCache

s32 TRKTargetStopped(void)
{
    return gTRKState.unk_98;
}

void TRKTargetSetStopped(s32 arg0)
{
    gTRKState.unk_98 = arg0;
}

/// #TRKTargetStop

/// #TRKPPCAccessSPR

/// #TRKPPCAccessPairedSingleRegister

/// #TRKPPCAccessFPRegister

/// #TRKPPCAccessSpecialReg

void TRKTargetSetInputPendingPtr(s32 arg0)
{
    gTRKState.unk_A0 = arg0;
}
