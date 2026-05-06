#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/si.h>
#include "__os.h"

static struct SIControl Si = {
    /* chan */      -1,
    /* poll */       0,
    /* inputBytes*/  0,
    /* input */      NULL,
    /* callback */   NULL
};

u32 __PADFixBits;

static struct SIPacket Packet[4];
static struct OSAlarm Alarm[4];
static u64 TypeTime[4];
static OSTime XferTime[SI_MAX_CHAN];
static SITypeAndStatusCallback TypeCallback[SI_MAX_CHAN][4];
static __OSInterruptHandler RDSTHandler[4];
static BOOL InputBufferValid[SI_MAX_CHAN];
static u32 InputBuffer[SI_MAX_CHAN][2];
static volatile u32 InputBufferVcount[SI_MAX_CHAN];
static u32 cmdFixDevice[SI_MAX_CHAN];

static u32 Type[SI_MAX_CHAN] = {
    SI_ERROR_NO_RESPONSE,
    SI_ERROR_NO_RESPONSE,
    SI_ERROR_NO_RESPONSE,
    SI_ERROR_NO_RESPONSE,
};

static unsigned long CompleteTransfer();
static void SITransferNext(long chan);
static void SIIntrruptHandler(short unused, struct OSContext * context);
static int __SITransfer(long chan, void * output, unsigned long outputBytes, void * input, unsigned long inputBytes, void (* callback)(long, unsigned long, struct OSContext *));
static void AlarmHandler(struct OSAlarm * alarm, struct OSContext * context);

#define SI_CHAN0_BIT 0x80000000
#define SI_CHAN1_BIT 0x40000000
#define SI_CHAN2_BIT 0x20000000
#define SI_CHAN3_BIT 0x10000000

int SIBusy() {
    return (Si.chan != -1) ? 1 : 0;
}

BOOL SIIsChanBusy(int chan)
{
    return (Packet[chan].chan != -1 || Si.chan == chan);
}

static void SIClearTCInterrupt()
{
    u32 reg;

    reg = __SIRegs[13];
    reg |= 0x80000000;
    reg &= ~0x00000001;
    __SIRegs[13] = reg;
}

static unsigned long CompleteTransfer() {
    unsigned long sr;
    unsigned long i;
    unsigned long rLen;
    unsigned char * input;
    unsigned long temp;

    sr = __SIRegs[SI_STATUS_IDX];
    SIClearTCInterrupt();

    if (Si.chan != -1) {
        XferTime[Si.chan] = __OSGetSystemTime();

        input = Si.input;
        rLen = (Si.inputBytes / 4);
        for(i = 0; i < rLen; i++) {
            *((u32*)input)++ = __SIRegs[i+0x20];
        }

        rLen = Si.inputBytes & 3;
        if (rLen != 0) {
            temp = __SIRegs[i + 32];
            for(i = 0; i < rLen; i++) {
                *(input++) = temp >> ((3 - i) * 8);
            }
        }

        if (__SIRegs[13] & 0x20000000) {
            sr >>= 8 * (3 - Si.chan);
            sr &= 0xF;

            if ((sr & SI_ERROR_NO_RESPONSE)
                && !(Type[Si.chan] & SI_ERROR_BUSY)) {
                Type[Si.chan] = SI_ERROR_NO_RESPONSE;
            }
            if (sr == 0) {
                sr = SI_ERROR_COLLISION;
            }
        } else {
            TypeTime[Si.chan] = __OSGetSystemTime();
            sr                = 0;
        }

        Si.chan = -1;
    }

    return sr;
}

static void SITransferNext(long chan) {
    int i;
    struct SIPacket * packet;

    for(i = 0; i < 4; i++) {
        chan++;
        chan %= 4;
        packet = &Packet[chan];

        if (packet->chan != -1) {
            if (packet->time <= __OSGetSystemTime()) {
                if (__SITransfer(packet->chan, packet->output, packet->outputBytes, packet->input, packet->inputBytes, packet->callback) != 0) {
                    OSCancelAlarm(&Alarm[chan]);
                    packet->chan = -1;
                }
                return;
            }
        }
    }
}

static BOOL SIGetResponseRaw(s32 chan);
static void GetTypeCallback(s32 chan, u32 error, OSContext* context);

static void SIInterruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    u32 reg;

    reg = __SIRegs[13];

    if ((reg & 0xc0000000) == 0xc0000000) {
        s32 chan;
        u32 sr;
        SICallback callback;

        chan        = Si.chan;
        sr          = CompleteTransfer();
        callback    = Si.callback;
        Si.callback = 0;

        SITransferNext(chan);

        if (callback) {
            callback(chan, sr, context);
        }

        sr = __SIRegs[14];
        sr &= 0xf000000 >> (8 * chan);
        __SIRegs[14] = sr;

        if (Type[chan] == SI_ERROR_BUSY && !SIIsChanBusy(chan)) {
            static u32 cmdTypeAndStatus = 0 << 24;
            SITransfer(chan, &cmdTypeAndStatus, 1, &Type[chan], 3,
                       GetTypeCallback, OSMicrosecondsToTicks(65));
        }
    }

    if ((reg & 0x18000000) == 0x18000000) {

        int i;
        u32 vcount;
        u32 x;

        vcount = VIGetCurrentLine() + 1;
        x      = (Si.poll & 0x03ff0000) >> 16;

        for (i = 0; i < SI_MAX_CHAN; ++i) {
            if (SIGetResponseRaw(i)) {
                InputBufferVcount[i] = vcount;
            }
        }

        for (i = 0; i < SI_MAX_CHAN; ++i) {
            if (!(Si.poll & (SI_CHAN0_BIT >> (31 - 7 + i)))) {
                continue;
            }
            if (InputBufferVcount[i] == 0
                || InputBufferVcount[i] + (x / 2) < vcount) {
                return;
            }
        }

        for (i = 0; i < SI_MAX_CHAN; ++i) {
            InputBufferVcount[i] = 0;
        }

        for (i = 0; i < 4; ++i) {
            if (RDSTHandler[i]) {
                RDSTHandler[i](interrupt, context);
            }
        }
    }
}

static BOOL SIEnablePollingInterrupt(BOOL enable) {
    BOOL enabled;
    BOOL rc;
    u32 reg;
    int i;

    enabled = OSDisableInterrupts();
    reg     = __SIRegs[13];
    rc      = (reg & 0x08000000) ? TRUE : FALSE;
    if (enable) {
        reg |= 0x08000000;
        for (i = 0; i < SI_MAX_CHAN; ++i) {
            InputBufferVcount[i] = 0;
        }
    } else {
        reg &= ~0x08000000;
    }
    reg &= ~0x80000001;
    __SIRegs[13] = reg;
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL SIRegisterPollingHandler(__OSInterruptHandler handler) {
    BOOL enabled;
    int i;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; ++i) {
        if (RDSTHandler[i] == handler) {
            OSRestoreInterrupts(enabled);
            return TRUE;
        }
    }
    for (i = 0; i < 4; ++i) {
        if (RDSTHandler[i] == 0) {
            RDSTHandler[i] = handler;
            SIEnablePollingInterrupt(TRUE);
            OSRestoreInterrupts(enabled);
            return TRUE;
        }
    }
    OSRestoreInterrupts(enabled);
    return FALSE;
}

BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler) {
    BOOL enabled;
    int i;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; ++i) {
        if (RDSTHandler[i] == handler) {
            RDSTHandler[i] = 0;
            for (i = 0; i < 4; ++i) {
                if (RDSTHandler[i]) {
                    break;
                }
            }
            if (i == 4) {
                SIEnablePollingInterrupt(FALSE);
            }
            OSRestoreInterrupts(enabled);
            return TRUE;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return FALSE;
}

void SIInit() {
    Packet[0].chan = Packet[1].chan = Packet[2].chan = Packet[3].chan = -1;
    __SIRegs[0x30/4] = 0;
    do {} while(__SIRegs[SI_COMCSR_IDX] & SI_COMCSR_TSTART_MASK);
    __SIRegs[SI_COMCSR_IDX] = SI_COMCSR_TCINT_MASK;
    __OSSetInterruptHandler(0x14, SIInterruptHandler);
    __OSUnmaskInterrupts(0x800);
    SIGetType(0);
    SIGetType(1);
    SIGetType(2);
    SIGetType(3);
}

static int __SITransfer(long chan, void * output, unsigned long outputBytes, void * input, unsigned long inputBytes, void (* callback)(long, unsigned long, struct OSContext *)) {
    int enabled;
    unsigned long rLen;
    unsigned long i;
    unsigned long sr;
    union {
        unsigned long val;
        struct {
            unsigned long tcint : 1;
            unsigned long tcintmsk : 1;
            unsigned long comerr : 1;
            unsigned long rdstint : 1;
            unsigned long rdstintmsk : 1;
            unsigned long pad2 : 4;
            unsigned long outlngth : 7;
            unsigned long pad1 : 1;
            unsigned long inlngth : 7;
            unsigned long pad0 : 5;
            unsigned long channel : 2;
            unsigned long tstart : 1;
        } f;
    } comcsr;

    ASSERTMSGLINE(0x12A, (chan >= 0) && (chan < 4), "SITransfer(): invalid channel.");
    ASSERTMSGLINE(0x12C, (outputBytes != 0) && (outputBytes <= 128), "SITransfer(): output size is out of range (must be 1 to 128).");
    ASSERTMSGLINE(0x12E, (inputBytes != 0) && (inputBytes <= 128), "SITransfer(): input size is out of range (must be 1 to 128).");

    enabled = OSDisableInterrupts();
    if (Si.chan != -1) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    ASSERTLINE(0x138, (__SIRegs[SI_COMCSR_IDX] & (SI_COMCSR_TSTART_MASK | SI_COMCSR_TCINT_MASK)) == 0);
    sr = __SIRegs[SI_STATUS_IDX];
    sr &= (0x0F000000 >> (chan * 8));
    __SIRegs[SI_STATUS_IDX] = sr;

    Si.chan = chan;
    Si.callback = callback;
    Si.inputBytes = inputBytes;
    Si.input = input;

    rLen = ROUND(outputBytes, 4) / 4;
    for (i = 0; i < rLen; i++) {
        __SIRegs[i+0x20] = ((u32*)output)[i];
    }

    comcsr.val = __SIRegs[SI_COMCSR_IDX];
    comcsr.f.tcint = 1;
    comcsr.f.tcintmsk = callback ? 1 : 0;
    comcsr.f.outlngth = outputBytes == 0x80 ? 0 : outputBytes;
    comcsr.f.inlngth = inputBytes == 0x80 ? 0 : inputBytes;
    comcsr.f.channel = chan;
    comcsr.f.tstart = 1;

    __SIRegs[SI_COMCSR_IDX] = comcsr.val;
    OSRestoreInterrupts(enabled);
    return 1;
}

unsigned long SISync() {
    int enabled; // r31
    unsigned long sr; // r30

    do {} while(__SIRegs[SI_COMCSR_IDX] & SI_COMCSR_TSTART_MASK);

    enabled = OSDisableInterrupts();
    sr = CompleteTransfer();
    SITransferNext(4);
    OSRestoreInterrupts(enabled);
    return sr;
}

unsigned long SIGetStatus(int chan) {
    BOOL enabled;
    u32 status;

    enabled = OSDisableInterrupts();
    status = __SIRegs[SI_STATUS_IDX];
    status >>= ((3 - chan) * 8);
    if (status & 8) {
        if (!(Type[chan] & 0x80)) {
            Type[chan] = 8;
        }
    }
    OSRestoreInterrupts(enabled);
    return status;
}

static unsigned long SIGetStatus_dontinline(int chan) {
    return SIGetStatus(chan);
}

void SISetCommand(long chan, unsigned long command) {
    ASSERTMSGLINE(0x197, (chan >= 0) && (chan < 4), "SISetCommand(): invalid channel.");
    __SIRegs[chan * 3] = command;
}

unsigned long SIGetCommand(long chan) {
    ASSERTMSGLINE(0x1A9, (chan >= 0) && (chan < 4), "SIGetCommand(): invalid channel.");
    return __SIRegs[chan * 3];
}

void SITransferCommands() {
    __SIRegs[SI_STATUS_IDX] = SI_COMCSR_TCINT_MASK;
}

unsigned long SISetXY(unsigned long x, unsigned long y) {
    unsigned long poll;
    int enabled;

    ASSERTMSGLINE(0x1CA, x >= 8, "SISetXY(): x is out of range (8 <= x <= 255).");
    ASSERTMSGLINE(0x1CB, x <= 255, "SISetXY(): x is out of range (8 <= x <= 255).");
    ASSERTMSGLINE(0x1CC, y <= 255, "SISetXY(): y is out of range (0 <= y <= 255).");

    poll = x << 0x10;
    poll |= y << 8;
    enabled = OSDisableInterrupts();
    Si.poll &= 0xFC0000FF;
    Si.poll |= poll;
    poll = Si.poll;
    OSRestoreInterrupts(enabled);
    return poll;
}

unsigned long SIEnablePolling(unsigned long poll) {
    int enabled;
    unsigned long en;

    ASSERTMSGLINE(0x1E8, !(poll & 0x0FFFFFFF), "SIEnablePolling(): invalid chan bit(s).");
    if (poll == 0) {
        return Si.poll;
    }

    enabled = OSDisableInterrupts();
    poll = poll >> 24;
    en = poll & 0xF0;
    ASSERTLINE(0x202, en);
    poll &= ((en >> 4) | 0x03FFFFF0);
    poll &= 0xFC0000FF;

    Si.poll &= ~(en >> 4);
    Si.poll |= poll;
    poll = Si.poll;
    __SIRegs[0x38/4] = 0x80000000;
    __SIRegs[0x30/4] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}

unsigned long SIDisablePolling(unsigned long poll) {
    int enabled;

    ASSERTMSGLINE(0x22D, !(poll & 0x0FFFFFFF), "SIDisablePolling(): invalid chan bit(s).");
    if (poll == 0) {
        return Si.poll;
    }
    enabled = OSDisableInterrupts();
    poll = poll >> 24;
    poll &= 0xF0;
    ASSERTLINE(0x23A, poll);
    poll = Si.poll & ~poll;
    __SIRegs[0x30/4] = poll;
    Si.poll = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}

static int SIGetResponseRaw(long chan) {
    if (SIGetStatus_dontinline(chan) & SI_ERROR_RDST) {
        InputBuffer[chan][0]   = __SIRegs[3 * chan + 1];
        InputBuffer[chan][1]   = __SIRegs[3 * chan + 2];
        InputBufferValid[chan] = TRUE;
        return TRUE;
    }
    return FALSE;
}


BOOL SIGetResponse(s32 chan, void* data) {
    BOOL rc;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    SIGetResponseRaw(chan);
    rc = InputBufferValid[chan];
    InputBufferValid[chan] = FALSE;
    if (rc) {
        ((u32*)data)[0] = InputBuffer[chan][0];
        ((u32*)data)[1] = InputBuffer[chan][1];
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

static void AlarmHandler(struct OSAlarm * alarm, struct OSContext * context) {
    long chan;
    struct SIPacket * packet;

    chan = alarm-Alarm;

    ASSERTLINE(0x266, 0 <= chan && chan < SI_MAX_CHAN);
    ASSERTLINE(0x267, packet->time <= OSGetTime()); // WTF? Dereferencing a NULL POINTER?
    packet = &Packet[chan];

    if (packet->chan != -1 && __SITransfer(packet->chan, packet->output, packet->outputBytes, packet->input, packet->inputBytes, packet->callback)) {
        packet->chan = -1;
    }
}

int SITransfer(long chan, void * output, unsigned long outputBytes, void * input, unsigned long inputBytes,
                void (* callback)(long, unsigned long, struct OSContext *), OSTime delay) {
    int enabled;
    struct SIPacket * packet;
    OSTime now;
    OSTime time;

    packet = &Packet[chan];
    enabled = OSDisableInterrupts();

    if (packet->chan != -1 || Si.chan == chan) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    now = __OSGetSystemTime();
    if (delay == 0) {
        time = now;
    } else {
        time = XferTime[chan] + delay;
    }
    if (now < time) {
        delay = time - now;
        OSSetAlarm(&Alarm[chan], delay, AlarmHandler);
    } else if (__SITransfer(chan, output, outputBytes, input, inputBytes, callback)) {
        OSRestoreInterrupts(enabled);
        return 1;
    }
    packet->chan = chan;
    packet->output = output;
    packet->outputBytes = outputBytes;
    packet->input = input;
    packet->inputBytes = inputBytes;
    packet->callback = callback;
    packet->time = time;
    OSRestoreInterrupts(enabled);
    return 1;
}

static void CallTypeAndStatusCallback(s32 chan, u32 type) {
    SITypeAndStatusCallback callback;
    int i;

    for (i = 0; i < 4; ++i) {
        callback = TypeCallback[chan][i];
        if (callback) {
            TypeCallback[chan][i] = 0;
            callback(chan, type);
        }
    }
}

static void GetTypeCallback(s32 chan, u32 error, OSContext* context) {
    u32 type;
    u32 chanBit;
    BOOL fix;
    u32 id;

    Type[chan] &= ~SI_ERROR_BUSY;
    Type[chan] |= error;
    TypeTime[chan] = __OSGetSystemTime();

    type = Type[chan];

    chanBit = SI_CHAN0_BIT >> chan;
    fix     = (BOOL)(__PADFixBits & chanBit);
    __PADFixBits &= ~chanBit;

    if ((error
         & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE
            | SI_ERROR_COLLISION))
        || (type & SI_TYPE_MASK) != SI_TYPE_DOLPHIN || !(type & SI_GC_WIRELESS)
        || (type & SI_WIRELESS_IR)) {
        OSSetWirelessID(chan, 0);
        CallTypeAndStatusCallback(chan, Type[chan]);
        return;
    }

    id = (u32)(OSGetWirelessID(chan) << 8);

    if (fix && (id & SI_WIRELESS_FIX_ID)) {
        cmdFixDevice[chan]
            = 0x4Eu << 24 | (id & SI_WIRELESS_TYPE_ID) | SI_WIRELESS_FIX_ID;
        Type[chan] = SI_ERROR_BUSY;
        SITransfer(chan, &cmdFixDevice[chan], 3, &Type[chan], 3,
                   GetTypeCallback, 0);
        return;
    }

    if (type & SI_WIRELESS_FIX_ID) {
        if ((id & SI_WIRELESS_TYPE_ID) != (type & SI_WIRELESS_TYPE_ID)) {
            if (!(id & SI_WIRELESS_FIX_ID)) {
                id = type & SI_WIRELESS_TYPE_ID;
                id |= SI_WIRELESS_FIX_ID;
                OSSetWirelessID(chan, (u16)((id >> 8) & 0xffff));
            }

            cmdFixDevice[chan] = 0x4E << 24 | id;
            Type[chan]         = SI_ERROR_BUSY;
            SITransfer(chan, &cmdFixDevice[chan], 3, &Type[chan], 3,
                       GetTypeCallback, 0);
            return;
        }
    } else if (type & SI_WIRELESS_RECEIVED) {
        id = type & SI_WIRELESS_TYPE_ID;
        id |= SI_WIRELESS_FIX_ID;

        OSSetWirelessID(chan, (u16)((id >> 8) & 0xffff));

        cmdFixDevice[chan] = 0x4E << 24 | id;
        Type[chan]         = SI_ERROR_BUSY;
        SITransfer(chan, &cmdFixDevice[chan], 3, &Type[chan], 3,
                   GetTypeCallback, 0);
        return;
    } else {
        OSSetWirelessID(chan, 0);
    }

    CallTypeAndStatusCallback(chan, Type[chan]);
}

u32 SIGetType(s32 chan) {
    static u32 cmdTypeAndStatus;
    BOOL enabled;
    u32 type;
    OSTime diff;

    enabled = OSDisableInterrupts();

    type = Type[chan];
    diff = __OSGetSystemTime() - TypeTime[chan];
    if (Si.poll & (0x80 >> chan)) {
        if (type != SI_ERROR_NO_RESPONSE) {
            TypeTime[chan] = __OSGetSystemTime();
            OSRestoreInterrupts(enabled);
            return type;
        } else {
            type = Type[chan] = SI_ERROR_BUSY;
        }
    } else if (diff <= OSMillisecondsToTicks(50)
               && type != SI_ERROR_NO_RESPONSE) {
        OSRestoreInterrupts(enabled);
        return type;
    } else if (diff <= OSMillisecondsToTicks(75)) {
        Type[chan] = SI_ERROR_BUSY;
    } else {
        type = Type[chan] = SI_ERROR_BUSY;
    }
    TypeTime[chan] = __OSGetSystemTime();

    SITransfer(chan, &cmdTypeAndStatus, 1, &Type[chan], 3, GetTypeCallback,
               OSMicrosecondsToTicks(65));

    OSRestoreInterrupts(enabled);
    return type;
}

u32 SIGetTypeAsync(s32 chan, SITypeAndStatusCallback callback) {
    BOOL enabled;
    u32 type;

    enabled = OSDisableInterrupts();
    type    = SIGetType(chan);
    if (Type[chan] & SI_ERROR_BUSY) {
        int i;

        for (i = 0; i < 4; ++i) {
            if (TypeCallback[chan][i] == callback) {
                break;
            }
            if (TypeCallback[chan][i] == 0) {
                TypeCallback[chan][i] = callback;
                break;
            }
        }
    } else {
        callback(chan, type);
    }
    OSRestoreInterrupts(enabled);
    return type;
}

static void dummy()
{
    OSReport("No response");
    OSReport("N64 controller");
    OSReport("N64 microphone");
    OSReport("N64 keyboard");
    OSReport("N64 mouse");
    OSReport("GameBoy Advance");
    OSReport("Standard controller");
    OSReport("Wireless receiver");
    OSReport("WaveBird controller");
    OSReport("Keyboard");
}
