#include "db.h"

#include <melee/lb/lbcardgame.h>
#include <dolphin/db.h>
#include <dolphin/os.h>
#include <dolphin/base/PPCArch.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/particle.h>
#include <sysdolphin/baselib/video.h>

void db_ClearFPUExceptions(void)
{
    OSContext* ctx;

    PPCMtmsr(PPCMfmsr() | 0x900);
    ctx = OSGetCurrentContext();
    OSSaveFPUContext(ctx);
    ctx->fpscr &= 0xFFFFF;
    OSLoadFPUContext(ctx);
}

static void fn_HSDPanicHandler(OSContext* ctx)
{
    HSD_VISetUserPreRetraceCallback(NULL);
    HSD_VISetUserPostRetraceCallback(NULL);
    lb_80019A48();
    OSReport("%s\n", db_build_timestamp);
    Exception_ReportStackTrace(ctx, 0x10);
    hsd_80397DFC(0x1388);
    Exception_StoreDebugLevel(g_debugLevel);
    hsd_80397DA4(ctx);
}

static void fn_OSErrorHandler(u16 error, OSContext* ctx, ...)
{
    int dsisr, dar;

    va_list va;
    va_start(va, ctx);

    dsisr = va_arg(va, int);
    dar = va_arg(va, int);

    HSD_VISetUserPreRetraceCallback(NULL);
    HSD_VISetUserPostRetraceCallback(NULL);
    lb_80019A48();
    OSReport("%s\n", db_build_timestamp);
    Exception_ReportStackTrace(ctx, 0x10);
    Exception_ReportCodeline(error, dsisr, dar, ctx);
    hsd_80397DFC(0x1388);
    Exception_StoreDebugLevel(g_debugLevel);
    hsd_80397DA4(ctx);

    va_end(va);
}

void db_SetupCrashHandler(void)
{
    u16 x;
    if (DBIsDebuggerPresent() == 0) {
        void* mem = OSAllocFromArenaLo(0x2000, 4);
        hsd_80393DA0(mem, 0x2000);
        HSD_SetPanicCallback((PanicCallback) fn_HSDPanicHandler);
        for (x = 0; x < 16; x++) {
            switch (x) {
            case 4:
            case 7:
            case 8:
            case 9:
                break;
            default:
                OSSetErrorHandler(x, fn_OSErrorHandler);
            }
        }
    }
}
