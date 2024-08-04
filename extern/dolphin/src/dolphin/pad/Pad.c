#include <dolphin.h>
#include <dolphin/pad.h>
#include <dolphin/si.h>

#include "os/__os.h"

#define LATENCY 8

#define PAD_ALL                                                                                                        \
    (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_DOWN | PAD_BUTTON_UP | PAD_TRIGGER_Z | PAD_TRIGGER_R              \
     | PAD_TRIGGER_L | PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y | PAD_BUTTON_MENU | 0x2000 | 0x0080)

u16 __OSWirelessPadFixMode : 0x800030E0;

static long ResettingChan = 0x00000020; // size: 0x4, address: 0x0
static unsigned long AnalogMode = 0x00000300; // size: 0x4, address: 0x4
static unsigned long Spec = 0x00000005; // size: 0x4, address: 0x8

static int Initialized; // size: 0x4, address: 0x0
static unsigned long EnabledBits; // size: 0x4, address: 0x4
static unsigned long ResettingBits; // size: 0x4, address: 0x8
static unsigned long ProbingBits; // size: 0x4, address: 0xC
static unsigned long RecalibrateBits; // size: 0x4, address: 0x10
static unsigned long WaitingBits; // size: 0x4, address: 0x14
static unsigned long CheckingBits; // size: 0x4, address: 0x18

static unsigned long Type[4]; // size: 0x10, address: 0x0
static struct PADStatus Origin[4]; // size: 0x30, address: 0x10

// functions
static u16 GetWirelessID(long chan);
static void SetWirelessID(long chan, u16 id);
static int DoReset();
static void PADEnable(long chan);
static void ProbeWireless(long chan);
static void PADProbeCallback(s32 chan, u32 error, OSContext *context);
static void PADDisable(long chan);
static void UpdateOrigin(s32 chan);
static void PADOriginCallback(s32 chan, u32 error, OSContext *context);
static void PADFixCallback(long unused, unsigned long error, struct OSContext *context);
static void PADResetCallback(long unused, unsigned long error, struct OSContext *context);
int PADReset(unsigned long mask);
BOOL PADRecalibrate(u32 mask);
BOOL PADInit();
static void PADReceiveCheckCallback(s32 chan, unsigned long error, OSContext *arg2);
void PADRead(struct PADStatus * status);
void PADSetSamplingRate(unsigned long msec);
void __PADTestSamplingRate(unsigned long tvmode);
void PADControlAllMotors(const u32 *commandArray);
void PADControlMotor(s32 chan, u32 command);
void PADSetSpec(u32 spec);
unsigned long PADGetSpec();
static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static s8 ClampS8(s8 var, s8 org);
static u8 ClampU8(u8 var, u8 org);
static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
int PADGetType(long chan, unsigned long * type);
BOOL PADSync(void);
void PADSetAnalogMode(u32 mode);
static BOOL OnReset(BOOL f);

static void (* MakeStatus)(long, struct PADStatus *, unsigned long *) = SPEC2_MakeStatus; // size: 0x4, address: 0xC

static OSResetFunctionInfo ResetFunctionInfo = {
    OnReset,
    127,
    NULL,
    NULL,
};

static u16 GetWirelessID(long chan) {
    struct OSSramEx * sram;
    u16 id;

    sram = __OSLockSramEx();
    id = sram->wirelessPadID[chan];
    __OSUnlockSramEx(0);
    return id;
}

static void SetWirelessID(long chan, u16 id) {
    struct OSSramEx * sram = __OSLockSramEx();

    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        __OSUnlockSramEx(1);
        return;
    }
    __OSUnlockSramEx(0);
}

static int DoReset() {
    int rc;
    unsigned long frame;
    unsigned long chanBit;

    rc = 1;
    ResettingChan = __cntlzw(ResettingBits);
    if ((ResettingChan >= 0) && (ResettingChan < 4)) {
        frame = 0;
        memset(&Origin[ResettingChan], 0, 0xC);
        Type[ResettingChan] = 0;
        rc = SITransfer(ResettingChan, &frame, 1, &Type[ResettingChan], 3, PADResetCallback, 0);
        chanBit = (0x80000000 >> ResettingChan);
        ResettingBits &= ~chanBit;
        if (rc == 0) {
            ResettingChan = 0x20;
            ResettingBits = 0;
        }
    }
    return rc;
}

static void PADEnable(long chan) {
    unsigned long cmd;
    unsigned long chanBit;
    unsigned long data[2];

    chanBit = 0x80000000 >> chan;
    EnabledBits |= chanBit;
    SIGetResponse(chan, &data);
    ASSERTLINE(0x1C4, !(Type[chan] & RES_WIRELESS_LITE));
    cmd = (AnalogMode | 0x400000);
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

static void ProbeWireless(long chan) {
    unsigned long cmd;
    unsigned long chanBit;
    unsigned long data[2];
    unsigned long type;

    chanBit = 0x80000000 >> chan;
    EnabledBits |= chanBit;
    ProbingBits |= chanBit;
    SIGetResponse(chan, &data);
    type = Type[chan];
    if (!(type & 0x02000000)) {
        cmd = (chan << 0xE) | 0x4D0000 | (__OSWirelessPadFixMode & 0x3FFF);
    } else if (((type & 0xC0000) + 0xFFFC0000) == 0) {
        cmd = 0x500000;
    } else {
        cmd = (type & 0x70000) + 0x440000;
    }
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

static void PADProbeCallback(s32 chan, u32 error, OSContext *context) {
    unsigned long type;
    ASSERTLINE(0x1F5, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);
    ASSERTLINE(0x1F6, chan == ResettingChan);
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        type = Type[chan];
        if (!(type & 0x80000) && !(type & 0x40000))
        {
            PADEnable(ResettingChan);
            WaitingBits |= PAD_CHAN0_BIT >> ResettingChan;
        }
        else
            ProbeWireless(ResettingChan);
    }
    DoReset();
}

static void PADDisable(long chan) {
    int enabled;
    unsigned long chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    ProbingBits &= ~chanBit;
    SetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

static void UpdateOrigin(s32 chan) {
    PADStatus *origin;

    origin = &Origin[chan];
    switch (AnalogMode & 0x00000700u)
    {
    case 0x00000000u:
    case 0x00000500u:
    case 0x00000600u:
    case 0x00000700u:
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000100u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000200u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        break;
    case 0x00000300u: break;
    case 0x00000400u: break;
    }

    origin->stickX -= 128;
    origin->stickY -= 128;
    origin->substickX -= 128;
    origin->substickY -= 128;
}

static void PADOriginCallback(s32 chan, u32 error, OSContext *context) {
    ASSERTLINE(0x267, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);
    ASSERTLINE(0x268, chan == ResettingChan);
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        UpdateOrigin(ResettingChan);
        PADEnable(ResettingChan);
    }
    DoReset();
}

static void PADOriginUpdateCallback(s32 chan, u32 error, OSContext *context)
{
    ASSERTLINE(0x285, 0 <= chan && chan < SI_MAX_CHAN);
    if (!(EnabledBits & (PAD_CHAN0_BIT >> chan)))
        return;
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
        UpdateOrigin(chan);
}

static void PADFixCallback(long unused, unsigned long error, struct OSContext *context) {
    unsigned long type;
    unsigned long id;
    unsigned long frame;

    ASSERTLINE(0x2A9, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);

    if (!(error & 0xF)) {
        type = Type[ResettingChan];
        id = (GetWirelessID(ResettingChan) << 8);
        if (!(type & 0x100000) || ((id & 0xCFFF00u) != (type & 0xCFFF00))) {
            DoReset();
            return;
        }
        if ((type & 0x40000000) && !(type & 0x80000) && !(type & 0x40000)) {
            frame = 0x41000000;
            SITransfer(ResettingChan, &frame, 1, &Origin[ResettingChan], 0xA, PADOriginCallback, 0);
            return;
        }
        frame = (ResettingChan << 0x16) | 0x4D000000 | (__OSWirelessPadFixMode << 8) & 0x3FFF00u;
        SITransfer(ResettingChan, &frame, 3, &Origin[ResettingChan], 8, PADProbeCallback, 0);
        return;
    }
    DoReset();
}

unsigned long __PADFixBits; // size: 0x4, address: 0x24

static void PADResetCallback(long unused, unsigned long error, struct OSContext *context) {
    unsigned long type;
    unsigned long id;
    unsigned long recalibrate;
    unsigned long chanBit;
    int fix;
    unsigned long frame;

    ASSERTLINE(0x2E9, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);

    type = Type[ResettingChan];
    chanBit = 0x80000000 >> ResettingChan;
    recalibrate = RecalibrateBits & chanBit;
    RecalibrateBits &= ~chanBit;
    fix = __PADFixBits & chanBit;
    __PADFixBits &= ~chanBit;
    if ((error & 0xF) || (((type & 0x18000000) + 0xF8000000) != 0)) {
        SetWirelessID(ResettingChan, 0);
        DoReset();
        return;
    }
    if (Spec < 2) {
        PADEnable(ResettingChan);
        DoReset();
        return;
    }
    if (!(type & 0x80000000) || (type & 0x04000000)) {
        SetWirelessID(ResettingChan, 0);
        if (!(type & 0x01000000)) {
            DoReset();
            return;
        }
        if (recalibrate != 0) {
            frame = 0x42000000;
            SITransfer(ResettingChan, &frame, 3, &Origin[ResettingChan], 0xA, PADOriginCallback, 0);
            return;
        }
        frame = 0x41000000;
        SITransfer(ResettingChan, &frame, 1, &Origin[ResettingChan], 0xA, PADOriginCallback, 0);
        return;
    }
    id = (GetWirelessID(ResettingChan) << 8);
    if ((fix != 0) && (id & 0x100000)) {
        frame = (id & 0xCFFF00) | 0x4E000000 | 0x100000;
        SITransfer(ResettingChan, &frame, 3, &Type[ResettingChan], 3, PADFixCallback, 0);
        return;
    }
    if (type & 0x100000) {
        if ((id & 0xCFFF00) != (type & 0xCFFF00)) {
            if (!(id & 0x100000)) {
                id = (type & 0xCFFF00);
                id |= 0x100000;
                SetWirelessID(ResettingChan, (u16)(id >> 8) & 0xFFFFFF);
            }
            frame = id | 0x4E000000;
            SITransfer(ResettingChan, &frame, 3, &Type[ResettingChan], 3, PADFixCallback, 0);
            return;
        }
        if ((type & 0x40000000) && !(type & 0x80000) && !(type & 0x40000)) {
            frame = 0x41000000;
            SITransfer(ResettingChan, &frame, 1, &Origin[ResettingChan], 0xA, PADOriginCallback, 0);
            return;
        }
        frame = (ResettingChan << 0x16) | 0x4D000000 | ((__OSWirelessPadFixMode << 8) & 0x3FFF00u);
        SITransfer(ResettingChan, &frame, 3, &Origin[ResettingChan], 8, PADProbeCallback, 0);
        return;
    }
    if (type & 0x40000000) {
        unsigned long id = (type & 0xCFFF00);
        id |= 0x100000;
        SetWirelessID(ResettingChan, (u16)(id >> 8) & 0xFFFFFF);
        frame = id | 0x4E000000;
        SITransfer(ResettingChan, &frame, 3, &Type[ResettingChan], 3, PADFixCallback, 0);
        return;
    }
    SetWirelessID(ResettingChan, 0);
    ProbeWireless(ResettingChan);
    DoReset();
}

int PADReset(unsigned long mask) {
    int enabled;
    int rc;

    rc = 0;
    ASSERTMSGLINE(0x392, !(mask & 0x0FFFFFFF), "PADReset(): invalid mask");
    enabled = OSDisableInterrupts();
    mask = mask & ~(CheckingBits | (ProbingBits | WaitingBits));
    ResettingBits |= mask;
    EnabledBits &= ~mask;
    WaitingBits &= ~mask;
    if (Spec == 4) {
        RecalibrateBits |= mask;
    }
    SIDisablePolling(ResettingBits);
    if (ResettingChan == 0x20) {
        rc = DoReset();
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL PADRecalibrate(u32 mask) {
    BOOL intrEnabled;
    BOOL ret;

    ret = FALSE;
    ASSERTMSGLINE(0x3BD, !(mask & 0x0FFFFFFF), "PADReset(): invalid mask");
    intrEnabled = OSDisableInterrupts();
    mask &= ~(CheckingBits | (ProbingBits | WaitingBits));
    ResettingBits |= mask;
    EnabledBits &= ~mask;
    RecalibrateBits |= mask;
    SIDisablePolling(ResettingBits);
    if ((s32)ResettingChan == 32)
        ret = DoReset();
    OSRestoreInterrupts(intrEnabled);
    return ret;
}

unsigned long __PADSpec; // size: 0x4, address: 0x20

BOOL PADInit() {
    if (!Initialized)
    {
        if (__PADSpec)
            PADSetSpec(__PADSpec);

        if (__PADFixBits == 0xFFFFFFFF)
        {
            OSTime time = OSGetTime();
            __OSWirelessPadFixMode
                = (u16)((((time)&0xffff) + ((time >> 16) & 0xffff) + ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff))
                        & 0x3fffu);
        }

        Initialized = TRUE;

        PADSetSamplingRate(0);
        OSRegisterResetFunction(&ResetFunctionInfo);
    }
    return PADReset(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
}

static void PADReceiveCheckCallback(s32 chan, unsigned long error, OSContext *arg2) {
    unsigned long type;
    unsigned long chanBit;
    unsigned long frame;

    type = Type[chan];
    chanBit = 0x80000000 >> chan;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    if (EnabledBits & chanBit) {
        if (!(error & 0xF) && (type & 0x80000000) && (type & 0x02000000) && (type & 0x40000000) && !(type & 0x04000000)) {
            frame = 0x41000000;
            SITransfer(chan, &frame, 1, &Origin[chan], 0xA, PADOriginUpdateCallback, 0);
            return;
        }
        PADDisable(chan);
    }
}

void PADRead(struct PADStatus * status) {
    long chan;
    unsigned long data[2];
    unsigned long chanBit;
    unsigned long sr;
    int chanShift;
    unsigned long frame;
    int enabled;

    for(chan = 0; chan < 4; chan++, status++) {
        chanBit = 0x80000000 >> chan;
        chanShift = (3 - chan) * 8;
        if ((ResettingBits & chanBit) || (ResettingChan == chan)) {
            status->err = -2;
            memset(status, 0, 0xA);
        } else if (!(EnabledBits & chanBit)) {
            status->err = -1;
            memset(status, 0, 0xA);
        } else {
            sr = SIGetStatus();
            if (sr & (8 << chanShift)) {
                if (WaitingBits & chanBit) {
                    status->err = 0;
                    memset(status, 0, 0xA);
                    if (!(CheckingBits & chanBit)) {
                        enabled = OSDisableInterrupts();
                        frame = 0;
                        if (SITransfer(chan, &frame, 1, &Type[chan], 3, PADReceiveCheckCallback, 0) != 0) {
                            CheckingBits |= chanBit;
                        }
                        OSRestoreInterrupts(enabled);
                    }
                } else {
                    PADDisable(chan);
                    status->err = -1;
                    memset(status, 0, 0xA);
                }
            } else if (!(sr & (0x20 << chanShift))) {
                status->err = -3;
                memset(status, 0, 0xA);
            } else {
                SIGetResponse(chan, &data);
                if (data[0] & 0x80000000) {
                    status->err = -3;
                    memset(status, 0, 0xA);
                } else if (ProbingBits & chanBit) {
                    status->err = -1;
                    memset(status, 0, 0xA);
                } else if (status->button & 0x2000) {
                    status->err = -3;
                    memset(status, 0, 0xA);
                    frame = 0x41000000;
                    SITransfer(chan, &frame, 1, &Origin[chan], 0xA, PADOriginUpdateCallback, 0);
                } else {
                    status->err = 0;
                    MakeStatus(chan, status, data);
                    status->button &= 0xFFFFFF7F;
                }
            }
        }
    }
}

typedef struct XY {
    /* 0x00 */ u8 line;
    /* 0x01 */ u8 count;
} XY;

static XY XYNTSC[12] = {
    { 0xF7, 0x02 },
    { 0x0E, 0x13 },
    { 0x1D, 0x09 },
    { 0x25, 0x07 },
    { 0x34, 0x05 },
    { 0x41, 0x04 },
    { 0x57, 0x03 },
    { 0x57, 0x03 },
    { 0x57, 0x03 },
    { 0x83, 0x02 },
    { 0x83, 0x02 },
    { 0x83, 0x02 }
};

static XY XYPAL[12] = {
    { 0x94, 0x03 },
    { 0x0D, 0x18 },
    { 0x1A, 0x0C },
    { 0x27, 0x08 },
    { 0x34, 0x06 },
    { 0x3E, 0x05 },
    { 0x4E, 0x04 },
    { 0x68, 0x03 },
    { 0x68, 0x03 },
    { 0x68, 0x03 },
    { 0x68, 0x03 },
    { 0x9C, 0x02 }
};

void PADSetSamplingRate(unsigned long msec) {
    unsigned long tv;
    XY * xy;

    ASSERTMSGLINE(0x4CE, (msec <= 0xB), "PADSetSamplingRate(): out of rage (0 <= msec <= 11)");
    if (msec > 0xB) {
        msec = 0xB;
    }
    tv = VIGetTvFormat();
    switch (tv) {
        case VI_NTSC:
        case VI_MPAL:
            xy = XYNTSC;
            break;
        case VI_PAL:
            xy = XYPAL;
            break;
        default:
            OSPanic("Pad.c", 0x4DF, "PADSetSamplingRate: unknown TV format");
    }
    SISetXY(xy[msec].line, xy[msec].count);
    SIEnablePolling(EnabledBits);
}

#if DEBUG
void __PADTestSamplingRate(unsigned long tvmode) {
    unsigned long msec;
    unsigned long line;
    unsigned long count;
    struct XY * xy;

    switch(tvmode) {
        case VI_NTSC:
        case VI_MPAL:
            xy = XYNTSC;
            for(msec = 0; msec <= 0xB; msec++) {
                line = xy[msec].line;
                count = xy[msec].count;
                OSReport("%2d[msec]: count %3d, line %3d, last %3d, diff0 %2d.%03d, diff1 %2d.%03d\n", msec, count, line, (line * (count - 1)) + LATENCY, 
                    (line * 636) / 10000,
                    (line * 636) % 10000, 
                    636 * (263 - line * (count - 1)) / 10000,
                    636 * (263 - line * (count - 1)) % 10000);
                ASSERTLINE(0x505, line * (count - 1) + LATENCY < 263);
                if (msec != 0) {
                    ASSERTLINE(0x508, 636 * line < msec * 10000);
                    ASSERTLINE(0x509, 636 * (263 - line * (count - 1)) < msec * 10000);
                }
            }
            break;
        case VI_PAL:
            xy = XYPAL;
            for(msec = 0; msec <= 0xB; msec++) {
                line = xy[msec].line;
                count = xy[msec].count;
                OSReport("%2d[msec]: count %3d, line %3d, last %3d, diff0 %2d.%03d, diff1 %2d.%03d\n", msec, count, line, (line * (count - 1)) + LATENCY, 
                    (line * 640) / 10000,
                    (line * 640) % 10000, 
                    640 * (313 - line * (count - 1)) / 10000,
                    640 * (313 - line * (count - 1)) % 10000);
                ASSERTLINE(0x51D, line * (count - 1) + LATENCY < 313);
                if (msec != 0) {
                    ASSERTLINE(0x520, 640 * line < msec * 10000);
                    ASSERTLINE(0x521, 640 * (313 - line * (count - 1)) < msec * 10000);
                }
            }
            break;
    }
}
#endif

void PADControlAllMotors(const u32 *commandArray) {
    BOOL enabled;
    int chan;
    u32 command;
    BOOL commit;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    commit = FALSE;

    for (chan = 0; chan < SI_MAX_CHAN; chan++, commandArray++)
    {
        chanBit = PAD_CHAN0_BIT >> chan;
        if ((EnabledBits & chanBit) && !(ProbingBits & chanBit) && !(Type[chan] & 0x20000000))
        {
            command = *commandArray;
            ASSERTMSGLINE(0x545, !(command & 0xFFFFFFFC), "PADControlAllMotors(): invalid command");
            if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD)
                command = PAD_MOTOR_STOP;
            SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x00000001 | 0x00000002)));
            commit = TRUE;
        }
    }
    if (commit)
        SITransferCommands();
    OSRestoreInterrupts(enabled);
}

void PADControlMotor(s32 chan, u32 command) {
    BOOL enabled;
    u32 chanBit;

    ASSERTMSGLINE(0x568, !(command & 0xFFFFFFFC), "PADControlMotor(): invalid command");

    enabled = OSDisableInterrupts();
    chanBit = PAD_CHAN0_BIT >> chan;
    if ((EnabledBits & chanBit) && !(ProbingBits & chanBit) && !(Type[chan] & 0x20000000))
    {
        if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD)
            command = PAD_MOTOR_STOP;
        SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x00000001 | 0x00000002)));
        SITransferCommands();
    }
    OSRestoreInterrupts(enabled);
}

void PADSetSpec(u32 spec) {
    ASSERTLINE(0x58C, !Initialized);
    __PADSpec = 0;
    switch (spec)
    {
    case PAD_SPEC_0:
        MakeStatus = SPEC0_MakeStatus;
        break;
    case PAD_SPEC_1:
        MakeStatus = SPEC1_MakeStatus;
        break;
    case PAD_SPEC_2:
    case PAD_SPEC_3:
    case PAD_SPEC_4:
    case PAD_SPEC_5:
        MakeStatus = SPEC2_MakeStatus;
        break;
    }
    Spec = spec;
}

u32 PADGetSpec(void) {
    return Spec;
}

static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2]) {
    status->button = 0;
    status->button |= ((data[0] >> 16) & 0x0008) ? PAD_BUTTON_A : 0;
    status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_B : 0;
    status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_X : 0;
    status->button |= ((data[0] >> 16) & 0x0001) ? PAD_BUTTON_Y : 0;
    status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_START : 0;
    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)(data[1]);
    status->substickY = (s8)(data[1] >> 8);
    status->triggerLeft = (u8)(data[0] >> 8);
    status->triggerRight = (u8)data[0];
    status->analogA = 0;
    status->analogB = 0;
    if (170 <= status->triggerLeft)
        status->button |= PAD_TRIGGER_L;
    if (170 <= status->triggerRight)
        status->button |= PAD_TRIGGER_R;
    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}

static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2]) {
    status->button = 0;
    status->button |= ((data[0] >> 16) & 0x0080) ? PAD_BUTTON_A : 0;
    status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_B : 0;
    status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_X : 0;
    status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_Y : 0;
    status->button |= ((data[0] >> 16) & 0x0200) ? PAD_BUTTON_START : 0;

    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)(data[1]);
    status->substickY = (s8)(data[1] >> 8);

    status->triggerLeft = (u8)(data[0] >> 8);
    status->triggerRight = (u8)data[0];

    status->analogA = 0;
    status->analogB = 0;

    if (170 <= status->triggerLeft)
        status->button |= PAD_TRIGGER_L;
    if (170 <= status->triggerRight)
        status->button |= PAD_TRIGGER_R;

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}

static s8 ClampS8(s8 var, s8 org) {
    if (0 < org)
    {
        s8 min = (s8)(-128 + org);
        if (var < min)
            var = min;
    }
    else if (org < 0)
    {
        s8 max = (s8)(127 + org);
        if (max < var)
            var = max;
    }
    return var -= org;
}

static u8 ClampU8(u8 var, u8 org) {
    if (var < org)
        var = org;
    return var -= org;
}

static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2]) {
    PADStatus *origin;

    status->button = (u16)((data[0] >> 16) & PAD_ALL);
    status->stickX = (s8)(data[0] >> 8);
    status->stickY = (s8)(data[0]);

    switch (AnalogMode & 0x00000700)
    {
    case 0x00000000:
    case 0x00000500:
    case 0x00000600:
    case 0x00000700:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = (u8)(((data[1] >> 12) & 0x0f) << 4);
        status->triggerRight = (u8)(((data[1] >> 8) & 0x0f) << 4);
        status->analogA = (u8)(((data[1] >> 4) & 0x0f) << 4);
        status->analogB = (u8)(((data[1] >> 0) & 0x0f) << 4);
        break;
    case 0x00000100:
        status->substickX = (s8)(((data[1] >> 28) & 0x0f) << 4);
        status->substickY = (s8)(((data[1] >> 24) & 0x0f) << 4);
        status->triggerLeft = (u8)(data[1] >> 16);
        status->triggerRight = (u8)(data[1] >> 8);
        status->analogA = (u8)(((data[1] >> 4) & 0x0f) << 4);
        status->analogB = (u8)(((data[1] >> 0) & 0x0f) << 4);
        break;
    case 0x00000200:
        status->substickX = (s8)(((data[1] >> 28) & 0x0f) << 4);
        status->substickY = (s8)(((data[1] >> 24) & 0x0f) << 4);
        status->triggerLeft = (u8)(((data[1] >> 20) & 0x0f) << 4);
        status->triggerRight = (u8)(((data[1] >> 16) & 0x0f) << 4);
        status->analogA = (u8)(data[1] >> 8);
        status->analogB = (u8)(data[1] >> 0);
        break;
    case 0x00000300:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = (u8)(data[1] >> 8);
        status->triggerRight = (u8)(data[1] >> 0);
        status->analogA = 0;
        status->analogB = 0;
        break;
    case 0x00000400:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = 0;
        status->triggerRight = 0;
        status->analogA = (u8)(data[1] >> 8);
        status->analogB = (u8)(data[1] >> 0);
        break;
    }

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;

    origin = &Origin[chan];
    status->stickX = ClampS8(status->stickX, origin->stickX);
    status->stickY = ClampS8(status->stickY, origin->stickY);
    status->substickX = ClampS8(status->substickX, origin->substickX);
    status->substickY = ClampS8(status->substickY, origin->substickY);
    status->triggerLeft = ClampU8(status->triggerLeft, origin->triggerLeft);
    status->triggerRight = ClampU8(status->triggerRight, origin->triggerRight);
}

int PADGetType(long chan, unsigned long * type) {
    unsigned long chanBit;

    *type = Type[chan];
    chanBit = 0x80000000 >> chan;
    if (ResettingBits & chanBit || ResettingChan == chan || !(EnabledBits & chanBit)) {
        return 0;
    }
    return 1;
}

BOOL PADSync(void) {
    return ResettingBits == 0 && (s32)ResettingChan == 32 && !SIBusy();
}

void PADSetAnalogMode(u32 mode) {
    BOOL enabled;
    u32 mask;

    ASSERTMSGLINE(0x6C9, (mode < 8), "PADSetAnalogMode(): invalid mode");

    enabled = OSDisableInterrupts();
    AnalogMode = mode << 8;
    mask = EnabledBits & ~ProbingBits;

    EnabledBits &= ~mask;
    WaitingBits &= ~mask;
    CheckingBits &= ~mask;

    SIDisablePolling(mask);
    OSRestoreInterrupts(enabled);
}

static BOOL OnReset(BOOL f) {
    BOOL sync;
    static BOOL recalibrated = FALSE;

    if (!f)
    {
        sync = PADSync();
        if (!recalibrated && sync)
        {
            recalibrated = PADRecalibrate(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
            return FALSE;
        }
        return sync;
    }
    else
        recalibrated = FALSE;

    return TRUE;
}
