#include <stdio.h>
#include <dolphin.h>
#include <dolphin/os.h>

// internal include
#include "__os.h"

static OSErrorHandler OSErrorTable[15];

void OSReport(char* msg, ...) {
  va_list marker;
  va_start(marker, msg);
  vprintf(msg, marker);
  va_end(marker);
}

void OSPanic(char* file, int line, char* msg, ...) {
  va_list marker;
  u32 i;
  u32* p;

  OSDisableInterrupts();
  va_start(marker, msg);
  vprintf(msg, marker);
  va_end(marker);
  OSReport(" in \"%s\" on line %d.\n", file, line);

  OSReport("\nAddress:      Back Chain    LR Save\n");
  for (i = 0, p = (u32*)OSGetStackPointer(); p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
    OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
  }

  PPCHalt();
}

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) {
    OSErrorHandler oldHandler;

    ASSERTMSGLINE(0x8F, error < __OS_EXCEPTION_MAX, "OSSetErrorHandler(): unknown error.");
    oldHandler = OSErrorTable[error];
    OSErrorTable[error] = handler;
    return oldHandler;
}

void __OSUnhandledException(unsigned char exception, struct OSContext * context, unsigned long dsisr, unsigned long dar) {
    if (!(context->srr1 & MSR_RI)) {
        OSReport("Non-recoverable Exception %d", exception);
    } else {
        if (OSErrorTable[exception]) {
            OSErrorTable[exception](exception, context, dsisr, dar);
            OSLoadContext(context);
        }
        if (exception == __OS_EXCEPTION_DECREMENTER) {
            OSLoadContext(context);
        }
        OSReport("Unhandled Exception %d", exception);
    }
#if DEBUG
    OSReport("(%s)", __OSExceptionNames[exception]);
#endif
    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR= 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);

    switch(exception) {
          case __OS_EXCEPTION_DSI:
            OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                     "invalid address 0x%x (read from DAR)\n",
                     context->srr0, dar);
            break;
          case __OS_EXCEPTION_ISI:
            OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                     "(read from SRR0)\n",
                     context->srr0);
            break;
          case __OS_EXCEPTION_ALIGNMENT:
            OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                     "unaligned address 0x%x (read from DAR)\n",
                     context->srr0, dar);
            break;
          case __OS_EXCEPTION_PROGRAM:
            OSReport("\nProgram exception : Possible illegal instruction/operation "
                     "at or around 0x%x (read from SRR0)\n",
                     context->srr0, dar);
            break;
    }
    PPCHalt();
}
