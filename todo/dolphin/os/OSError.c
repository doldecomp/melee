#include <stdarg.h>
#include <stdio.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/dsp/dsp.h>
#include <dolphin/os.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSTime.h>

WEAK void OSReport(const char* msg, ...)
{
    va_list args;

    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
}

void OSPanic(char* file, int line, char* msg, ...)
{
    va_list args;
    u32 i;
    u32* sp;

    OSDisableInterrupts();

    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    // Print stack trace
    OSReport("\nAddress:      Back Chain    LR Save\n");
    i = 0;
    sp = (u32*) OSGetStackPointer();
    while (sp != NULL && (u32) sp != 0xFFFFFFFF && i++ < 16) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", (u32) sp, sp[0], sp[1]);
        sp = (u32*) sp[0];
    }
    PPCHalt();
}

OSErrorHandler __OSErrorTable[16];

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler)
{
    OSErrorHandler prevHandler = __OSErrorTable[error];

    __OSErrorTable[error] = handler;
    return prevHandler;
}

void __OSUnhandledException(u8 error, OSContext* context, u32 dsisr, u32 dar)
{
    if (!(context->srr1 & (1 << 1))) {
        OSReport("Non-recoverable Exception %d", error);
    } else {
        if (__OSErrorTable[error] != NULL) {
            OSDisableScheduler();
            __OSErrorTable[error](error, context, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
        if (error == OS_ERROR_DECREMENTER) {
            OSLoadContext(context);
        }
        OSReport("Unhandled Exception %d", error);
    }

    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    OSReport("TB = 0x%016llx\n", OSGetTime());
    switch (error) {
    case OS_ERROR_DSI:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "invalid address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case OS_ERROR_ISI:
        OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                 "(read from SRR0)\n",
                 context->srr0);
        break;
    case OS_ERROR_ALIGNMENT:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "unaligned address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case OS_ERROR_PROGRAM:
        OSReport(
            "\nProgram exception : Possible illegal instruction/operation "
            "at or around 0x%x (read from SRR0)\n",
            context->srr0, dar);
        break;
    case 15:
        OSReport("\n");
        OSReport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[24],
                 __DSPRegs[25]);
        OSReport("ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[16],
                 __DSPRegs[17]);
        OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
        break;
    }
    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n",
             __OSLastInterrupt, __OSLastInterruptSrr0, __OSLastInterruptTime);
    PPCHalt();
}
