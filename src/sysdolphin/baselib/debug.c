#include "debug.h"

#include <dolphin/os.h>
#include <MSL/stdio.h>

struct DebugContext {
    OSContext context;
    u8 unk[0x10];
} HSD_Debug_804C2608;

__io_proc logFunc;
PanicCallback panicCallback;
ReportCallback reportCallback;

#pragma peephole off

int report_func(__file_handle arg0, unsigned char* arg1, size_t* arg2,
                __idle_proc arg3)
{
    if (reportCallback != NULL) {
        reportCallback(arg1, *arg2);
    }
    logFunc(arg0, arg1, arg2, arg3);
    return 0;
}

void HSD_LogInit(void)
{
    if (logFunc == NULL) {
        logFunc = stdout->write_proc;
    }
    stdout->write_proc = report_func;
    stdout->state.error = 0;
}

void __assert(char* str, u32 arg1, char* arg2)
{
    OSReport("assertion \"%s\" failed", arg2);
    HSD_Panic(str, arg1, "");
}

void HSD_Panic(char* arg0, u32 line, char* arg2)
{
    if (panicCallback != NULL) {
        OSSaveContext(&HSD_Debug_804C2608.context);
        OSReport("%s in %s on line %d.\n", arg2, arg0, line);
        panicCallback(&HSD_Debug_804C2608.context);
    }
    OSPanic(arg0, line, arg2);
}

void HSD_SetReportCallback(ReportCallback cb)
{
    reportCallback = cb;
}

void HSD_SetPanicCallback(PanicCallback cb)
{
    panicCallback = cb;
}
