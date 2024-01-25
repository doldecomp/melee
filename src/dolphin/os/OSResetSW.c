#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSResetSW.h>
#include <dolphin/os/OSTime.h>

typedef void (*OSResetCallback)(void);

extern u8 GameChoice AT_ADDRESS(0x800030E3);

static OSResetCallback ResetCallback;
static bool Down;
static bool LastState;
static OSTime HoldUp;
static OSTime HoldDown;

extern OSTime __OSStartTime;

void __OSResetSWInterruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    HoldDown = __OSGetSystemTime();
    while (__OSGetSystemTime() - HoldDown < OSMicrosecondsToTicks(100) &&
           !(__PIRegs[0] & 0x10000))
    {
        ;
    }
    if (!(__PIRegs[0] & 0x10000)) {
        LastState = Down = true;
        __OSMaskInterrupts(0x80000000U >> OS_INTR_PI_RSW);
        if (ResetCallback) {
            OSResetCallback callback = ResetCallback;
            ResetCallback = NULL;
            callback();
        }
    }
    __PIRegs[0] = 2;
}

bool OSGetResetButtonState(void)
{
    bool enabled = OSDisableInterrupts();
    bool state;
    OSTime now = __OSGetSystemTime();
    u32 reg = __PIRegs[0];

    if (!(reg & 0x00010000)) {
        if (!Down) {
            Down = true;
            state = HoldUp ? true : false;
            HoldDown = now;
        } else {
            state = HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown)
                        ? true
                        : false;
        }
    } else if (Down) {
        Down = false;
        state = LastState;
        if (state) {
            HoldUp = now;
        } else {
            HoldUp = 0;
        }
    } else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
        state = true;
    } else {
        state = false;
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
                state = true;
            } else {
                state = false;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return state;
}

bool OSGetResetSwitchState(void)
{
    return OSGetResetButtonState();
}
