#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSResetSW.h>
#include <dolphin/os/OSTime.h>

typedef void (*OSResetCallback)(void);

extern u8 GameChoice : 0x800030E3;
extern vu32 __PIRegs[12] : 0xCC003000;

static OSResetCallback ResetCallback;
static BOOL Down;
static BOOL LastState;
static OSTime HoldUp;
static OSTime HoldDown;

extern OSTime __OSStartTime;

void __OSResetSWInterruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    HoldDown = __OSGetSystemTime();
    while (__OSGetSystemTime() - HoldDown < OSMicrosecondsToTicks(100) &&
           !(__PIRegs[0] & 0x10000)) {
        ;
    }
    if (!(__PIRegs[0] & 0x10000)) {
        LastState = Down = TRUE;
        __OSMaskInterrupts(0x80000000U >> OS_INTR_PI_RSW);
        if (ResetCallback) {
            OSResetCallback callback = ResetCallback;
            ResetCallback = NULL;
            callback();
        }
    }
    __PIRegs[0] = 2;
}

BOOL OSGetResetButtonState(void)
{
    BOOL enabled = OSDisableInterrupts();
    BOOL state;
    OSTime now = __OSGetSystemTime();
    u32 reg = __PIRegs[0];

    if (!(reg & 0x00010000)) {
        if (!Down) {
            Down = TRUE;
            state = HoldUp ? TRUE : FALSE;
            HoldDown = now;
        } else {
            state = HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown) ? TRUE : FALSE;
        }
    } else if (Down) {
        Down = FALSE;
        state = LastState;
        if (state) {
            HoldUp = now;
        } else {
            HoldUp = 0;
        }
    } else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
        state = TRUE;
    } else {
        state = FALSE;
        HoldUp = 0;
    }

    LastState = state;

    if (GameChoice & 0x3F) {
        OSTime fire = (GameChoice & 0x3F) * 60;
        fire = __OSStartTime + OSSecondsToTicks(fire);
        if (fire < now) {
            now -= fire;
            now = OSTicksToSeconds(now) / 2;
            if ((now & 1) == 0) {
                state = TRUE;
            } else {
                state = FALSE;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return state;
}

BOOL OSGetResetSwitchState(void)
{
    return OSGetResetButtonState();
}
