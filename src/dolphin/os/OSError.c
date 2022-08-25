#include <dolphin/base/PPCArch.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <stdio.h>

void OSReport(char* msg, ...)
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
