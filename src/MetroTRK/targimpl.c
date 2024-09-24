#include "targimpl.h"

#include <placeholder.h>

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

/// #TRKTargetGetPC

/// #TRKTargetSupportRequest

/// #TRKTargetFlushCache

/// #TRKTargetStopped

/// #TRKTargetSetStopped

/// #TRKTargetStop

/// #TRKPPCAccessSPR

/// #TRKPPCAccessPairedSingleRegister

/// #TRKPPCAccessFPRegister

/// #TRKPPCAccessSpecialReg

/// #TRKTargetSetInputPendingPtr
