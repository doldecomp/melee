#include <__mem.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/os/OSSerial.h>
#include <dolphin/pad/pad.h>
#include <dolphin/sipriv.h>
#include <MetroTRK/intrinsics.h>

#define PAD_CHAN0_BIT 0x80000000

extern PADStatus Origin[];

extern u32 XPatchBits;
extern u32 AnalogMode;
extern u32 EnabledBits;
extern s32 ResettingChan;
extern u32 ResettingBits;
extern u32 WaitingBits;
extern u32 CheckingBits;
extern u32 ProbingBits;

static void PADEnable(s32 chan)
{
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = PAD_CHAN0_BIT >> chan;
    EnabledBits |= chanBit;
    SIGetResponse(chan, data);
    cmd = (0x40 << 16) | AnalogMode;
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

static void PADDisable(s32 chan)
{
    bool enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();

    chanBit = PAD_CHAN0_BIT >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    ProbingBits &= ~chanBit;
    OSSetWirelessID(chan, 0);

    OSRestoreInterrupts(enabled);
}

static void DoReset(void)
{
    u32 chanBit;

    ResettingChan = __cntlzw(ResettingBits);
    if (ResettingChan == 32) {
        return;
    }

    chanBit = PAD_CHAN0_BIT >> ResettingChan;
    ResettingBits &= ~chanBit;

    memset(&Origin[ResettingChan], 0, sizeof(PADStatus));
    SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
}

void UpdateOrigin(s32 arg0)
{
    PADStatus* origin = &Origin[arg0];
    u32 temp_r4 = AnalogMode & 0x700;
    u32 bit = PAD_CHAN0_BIT >> arg0;
    switch (temp_r4) {
    case 0x0:
    case 0x500:
    case 0x600:
    case 0x700:
        origin->triggerLeft &= ~0xF;
        origin->triggerRight &= ~0xF;
        origin->analogA &= ~0xF;
        origin->analogB &= ~0xF;
        break;
    case 0x100:
        origin->substickX &= ~0xF;
        origin->substickY &= ~0xF;
        origin->analogA &= ~0xF;
        origin->analogB &= ~0xF;
        break;
    case 0x200:
        origin->substickX &= ~0xF;
        origin->substickY &= ~0xF;
        origin->triggerLeft &= ~0xF;
        origin->triggerRight &= ~0xF;
        break;
    case 0x300:
    case 0x400:
        break;
    }
    origin->stickX -= 0x80;
    origin->stickY -= 0x80;
    origin->substickX -= 0x80;
    origin->substickY -= 0x80;
    if ((XPatchBits & bit) && origin->stickX > 0x40 &&
        (SIGetType(arg0) & 0xFFFF0000) == 0x9000000)
    {
        origin->stickX = 0U;
    }
}

inline void foo(s32 chan)
{
    /// @todo @c sp1C is a struct.
    u32 sp1C[6];
    EnabledBits |= PAD_CHAN0_BIT >> chan;
    SIGetResponse(chan, sp1C + 3);
    SISetCommand(chan, AnalogMode | 0x400000);
}

void PADOriginCallback(s32 unused0, s32 arg1)
{
    if (!(arg1 & 0xF)) {
        UpdateOrigin(ResettingChan);
        foo(ResettingChan);
        SIEnablePolling(EnabledBits);
    }

    ResettingChan = __cntlzw(ResettingBits);
    if (ResettingChan != 32) {
        ResettingBits &= ~(PAD_CHAN0_BIT >> ResettingChan);
        memset(&Origin[ResettingChan], 0, sizeof(Origin[0]));
        SIGetTypeAsync(ResettingChan, &PADTypeAndStatusCallback);
    }
}

void PADOriginUpdateCallback(s32 chan, u32 error, OSContext* context)
{
    if (!(EnabledBits & (PAD_CHAN0_BIT >> chan))) {
        return;
    }

    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN |
                   SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        UpdateOrigin(chan);
    }

    if (error & SI_ERROR_NO_RESPONSE) {
        PADDisable(chan);
    }
}

void PADProbeCallback(s32 chan, u32 error, OSContext* context)
{
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN |
                   SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        PADEnable(ResettingChan);
        WaitingBits |= PAD_CHAN0_BIT >> ResettingChan;
    }
    DoReset();
}
