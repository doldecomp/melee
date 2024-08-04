#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

static OSResetCallback ResetCallback;
static int Down;
static long long Hold;

void __OSResetSWInterruptHandler(short exception, struct OSContext *context) {
    OSResetCallback callback;

    Down = 1;
    __PIRegs[0] = 2;
    __OSMaskInterrupts(0x200);

    if (ResetCallback) {
        callback = ResetCallback;
        ResetCallback = NULL;
        callback();
    }
}

OSResetCallback OSSetResetCallback(OSResetCallback callback) {
    int enabled;
    OSResetCallback prevCallback;

    enabled = OSDisableInterrupts();
    prevCallback = ResetCallback;
    ResetCallback = callback;

    if (callback) {
        __PIRegs[0] = 2;
        __OSUnmaskInterrupts(0x200);
    } else {
        __OSMaskInterrupts(0x200);
    }
    OSRestoreInterrupts(enabled);
    return prevCallback;
}

int OSGetResetSwitchState() {
    int enabled;
    int state;
    unsigned long reg;

    enabled = OSDisableInterrupts();
    reg = __PIRegs[0];

    if (!(reg & 0x10000)) {
        Down = 1;
        state = 1;
    } else if (Down != 0) {
        if (reg & 2) {
            __PIRegs[0] = 2;
            Down = 1;
        } else {
            Down = 0;
            Hold = __OSGetSystemTime();
        }
        state = 1;
    } else if (Hold && (__OSGetSystemTime() - Hold) < OSMillisecondsToTicks(50)) {
        state = 1;
    } else {
        state = 0;
        Hold = 0;
    }
    OSRestoreInterrupts(enabled);
    return state;
}
