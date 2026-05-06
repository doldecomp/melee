#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

struct Timer {
    void (* callback)();
    unsigned long currval;
    unsigned long startval;
    unsigned short mode;
    int stopped;
    int initialized;
};

static struct Timer Timer; // .bss

void (* OSSetTimerCallback(void (* callback)()))();
void OSInitTimer(unsigned long time, unsigned short mode);
void OSStartTimer(void);
void OSStopTimer(void);
static void DecrementerExceptionHandler(unsigned char exception, struct OSContext * context);

void (* OSSetTimerCallback(void (* callback)()))() {
    void (* prevCallback)();

#if DEBUG
    if(Timer.initialized == 0) {
        OSPanic("OSTimer.c", 127, "OSSetTimerCallback(): timer is not initialized.");
    }
#endif

    Timer.stopped = 1;
    prevCallback = Timer.callback;
    Timer.callback = callback;
    return prevCallback;
}

void OSInitTimer(unsigned long time, unsigned short mode) {
#if DEBUG
    if (time >= 0x80000000) {
        OSPanic("OSTimer.c", 0x97, "OSInitTimer(): time param must be less than 0x80000000.");
    }
#endif

    Timer.stopped = 1;
    Timer.currval = time;
    Timer.startval = time;
    Timer.mode = mode;
    if (Timer.initialized == 0) {
        __OSSetExceptionHandler(8, &DecrementerExceptionHandler);
        Timer.initialized = 1;
        Timer.callback = 0;
#if DEBUG
        OSReport("Timer initialized\n");
#endif
    }
}

void OSStartTimer(void) {
    int enabled;

#if DEBUG
    if (Timer.initialized == 0) {
        OSPanic("OSTimer.c", 0xB8, "OSStartTimer(): timer is not initialized.");
    }
#endif
    enabled = OSDisableInterrupts();
    PPCMtdec(Timer.currval);
    Timer.stopped = 0;
    OSRestoreInterrupts(enabled);
}

void OSStopTimer(void) {
    int enabled;

#if DEBUG
    if (Timer.initialized == 0) {
        OSPanic("OSTimer.c", 0xD0, "OSStopTimer(): timer is not initialized.");
    }
#endif

    enabled = OSDisableInterrupts();
    if (Timer.stopped == 0) {
        Timer.stopped = 1;
        Timer.currval = PPCMfdec();
        if (Timer.currval & 0x80000000) {
            Timer.currval = 0;
        }
    }
    OSRestoreInterrupts(enabled);
}

static void DecrementerExceptionCallback(unsigned char exception, struct OSContext * context) {
    struct OSContext exceptionContext;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (Timer.stopped == 0) {
        if (Timer.mode == 1) {
            PPCMtdec(Timer.startval);
        }
        if (Timer.mode == 2) {
            Timer.stopped = 1;
        }
        if (Timer.callback != 0) {
            Timer.callback();
        }
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
    OSLoadContext(context);
}

static asm void DecrementerExceptionHandler(unsigned char exception,
                                            register struct OSContext* context) {
    // clang-format off
    nofralloc

    stw r0, context->gpr[0]
    stw r1, context->gpr[1]
    stw r2, context->gpr[2]
    stmw r6, context->gpr[6]

    mfspr r0, GQR1
    stw r0, context->gqr[1]
    mfspr r0, GQR2
    stw r0, context->gqr[2]
    mfspr r0, GQR3
    stw r0, context->gqr[3]
    mfspr r0, GQR4
    stw r0, context->gqr[4]
    mfspr r0, GQR5
    stw r0, context->gqr[5]
    mfspr r0, GQR6
    stw r0, context->gqr[6]
    mfspr r0, GQR7
    stw r0, context->gqr[7]

    b DecrementerExceptionCallback
    // clang-format on
}
