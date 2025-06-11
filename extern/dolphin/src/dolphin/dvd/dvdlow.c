#include <dolphin.h>
#include <dolphin/dvd.h>

#include "__dvd.h"
#include "__os.h"

typedef void (*DVDLowCallback)(u32);

typedef struct {
    int cmd;
    void* addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

static DVDCommand CommandList[3];
static OSAlarm AlarmForWA;
static OSAlarm AlarmForTimeout;
static OSAlarm AlarmForBreak;

// Smaller version of DVDBB2
static struct {
    /* 0x00 */ void* bootFilePosition;
    /* 0x04 */ u32 FSTPosition;
    /* 0x08 */ u32 FSTLength;
} Prev, Curr;

// .sbss
static volatile BOOL StopAtNextInt;
static int LastLength;
static void (* Callback)(unsigned long); // size: 0x4, address: 0x0
static void (* ResetCoverCallback)(unsigned long); // size: 0x4, address: 0x4
static volatile long long LastResetEnd; // size: 0x8, address: 0x8
static volatile unsigned long ResetOccurred; // size: 0x4, address: 0x10
static volatile int WaitingCoverClose; // size: 0x4, address: 0x14
static volatile int Breaking; // size: 0x4, address: 0x18
static volatile u32 WorkAroundType;
static u32 WorkAroundSeekLocation;
static volatile OSTime LastReadFinished;
static volatile OSTime LastReadIssued;
static volatile BOOL LastCommandWasRead;
static volatile int NextCommandNumber;

static BOOL FirstRead = TRUE;

static void __DVDLowSetWAType(u32, u32);

void __DVDInitWA(void)
{
    NextCommandNumber = 0;
    CommandList[0].cmd = -1;
    __DVDLowSetWAType(0, 0);
    OSInitAlarm();
}

static void Read(void* addr, u32 length, u32 offset, DVDLowCallback callback);

static BOOL ProcessNextCommand(void)
{
    s32 n = NextCommandNumber;

    if (CommandList[n].cmd == 1) {
        ++NextCommandNumber;
        Read(CommandList[n].addr, CommandList[n].length, CommandList[n].offset,
             CommandList[n].callback);
        return TRUE;
    } else if (CommandList[n].cmd == 2) {
        ++NextCommandNumber;
        DVDLowSeek(CommandList[n].offset, CommandList[n].callback);
        return TRUE;
    }

    return FALSE;
}

void __DVDInterruptHandler(short unused, struct OSContext * context) {
    struct OSContext exceptionContext;
    unsigned long cause;
    unsigned long reg;
    unsigned long intr;
    unsigned long mask;

    cause = 0;

    OSCancelAlarm(&AlarmForTimeout);

    if (LastCommandWasRead) {
        LastReadFinished = __OSGetSystemTime();
        FirstRead = FALSE;
        Prev.bootFilePosition = Curr.bootFilePosition;
        Prev.FSTPosition = Curr.FSTPosition;
        Prev.FSTLength = Curr.FSTLength;
        if (StopAtNextInt == TRUE) {
            cause |= 8;
        }
    }
    LastCommandWasRead = FALSE;
    StopAtNextInt = FALSE;

    reg = __DIRegs[0];
    mask = (reg & 0x0000002A);
    intr = (reg & 0x00000054) & (mask << 1);
    if (intr & 0x40) {
        cause |= 8;
    }
    if (intr & 0x10) {
        cause |= 1;
    }
    if (intr & 4) {
        cause |= 2;
    }
    if (cause) {
        ResetOccurred = FALSE;
    }
    __DIRegs[0] = (intr | mask);

    if ((ResetOccurred != 0) && ((__OSGetSystemTime() - LastResetEnd)) < OSMillisecondsToTicks(200)) {
        reg = __DIRegs[1];
        mask = (reg & 2);
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            if (ResetCoverCallback) {
                ResetCoverCallback(4);
            }
            ResetCoverCallback = NULL;
        }
        __DIRegs[1] = __DIRegs[1];
    } else if (WaitingCoverClose) {
        reg = __DIRegs[1];
        mask = (reg & 2);
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            cause |= 4;
        }
        __DIRegs[1] = (intr | mask);
        WaitingCoverClose = 0;
    } else {
        __DIRegs[1] = 0;
    }
    if ((cause & 8) && (Breaking == 0)) {
        cause &= 0xFFFFFFF7;
    }
    if ((cause & 1)) {
        if (ProcessNextCommand()) {
            return;
        }
    } else {
        CommandList[0].cmd = -1;
        NextCommandNumber = 0;
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (cause != 0) {
        DVDLowCallback callback = Callback;
        Callback = 0;
        if (callback) {
            callback(cause);
        }
        Breaking = 0;
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

static void AlarmHandler(OSAlarm* alarm, OSContext* context)
{
    ProcessNextCommand();
}

static void AlarmHandlerForTimeout(OSAlarm* alarm, OSContext* context)
{
    OSContext tmpContext;
    DVDLowCallback callback;
    __OSMaskInterrupts(0x400);
    OSClearContext(&tmpContext);
    OSSetCurrentContext(&tmpContext);
    callback = Callback;
    Callback = NULL;
    if (callback != NULL) {
        callback(0x10);
    }
    OSClearContext(&tmpContext);
    OSSetCurrentContext(context);
}

static void SetTimeoutAlarm(OSTime timeout)
{
    OSCreateAlarm(&AlarmForTimeout);
    OSSetAlarm(&AlarmForTimeout, timeout, AlarmHandlerForTimeout);
}

static void Read(void* addr, u32 length, u32 offset, DVDLowCallback callback)
{
    StopAtNextInt = FALSE;
    LastCommandWasRead = TRUE;
    Callback = callback;
    LastReadIssued = __OSGetSystemTime();

    __DIRegs[2] = 0xa8000000;
    __DIRegs[3] = offset / 4;
    __DIRegs[4] = length;
    __DIRegs[5] = (u32) addr;
    __DIRegs[6] = length;
    LastLength = length;
    __DIRegs[7] = 3;

    if (length > 0xa00000) {
        SetTimeoutAlarm(OSSecondsToTicks(20));
    } else {
        SetTimeoutAlarm(OSSecondsToTicks(10));
    }
}

static BOOL HitCache(void)
{
    u32 uVar1 = (Prev.FSTLength + Prev.FSTPosition - 1) >> 15;
    u32 uVar2 = (Curr.FSTLength >> 15);
    u32 iVar3 = (DVDGetCurrentDiskID()->streaming ? TRUE : FALSE) ? 5 : 15;

    if ((uVar2 > uVar1 - 2) || (uVar2 < uVar1 + iVar3 + 3)) {
        return TRUE;
    }
    return FALSE;
}

static void DoJustRead(void* addr, u32 length, u32 offset,
                       DVDLowCallback callback)
{
    CommandList[0].cmd = -1;
    NextCommandNumber = 0;
    Read(addr, length, offset, callback);
}

static void SeekTwiceBeforeRead(void* addr, u32 length, u32 offset,
                                DVDLowCallback callback)
{
    u32 newOffset = offset & ~0x7FFF;
    if (!newOffset) {
        newOffset = 0;
    } else {
        newOffset += WorkAroundSeekLocation;
    }
    CommandList[0].cmd = 2;
    CommandList[0].offset = newOffset;
    CommandList[0].callback = callback;
    CommandList[1].cmd = 1;
    CommandList[1].addr = addr;
    CommandList[1].length = length;
    CommandList[1].offset = offset;
    CommandList[1].callback = callback;
    CommandList[2].cmd = -1;
    NextCommandNumber = 0;
    DVDLowSeek(newOffset, callback);
}

static void WaitBeforeRead(void* addr, u32 length, u32 offset,
                           DVDLowCallback callback, OSTime timeout)
{
    CommandList[0].cmd = 1;
    CommandList[0].addr = addr;
    CommandList[0].length = length;
    CommandList[0].offset = offset;
    CommandList[0].callback = callback;
    CommandList[1].cmd = -1;
    NextCommandNumber = 0;
    OSCreateAlarm(&AlarmForWA);
    OSSetAlarm(&AlarmForWA, timeout, AlarmHandler);
}

BOOL DVDLowRead(void* addr, u32 length, u32 offset,
                     DVDLowCallback callback)
{
    OSTime diff;
    u32 prev;

    __DIRegs[6] = length;
    Curr.bootFilePosition = addr;
    Curr.FSTPosition = length;
    Curr.FSTLength = offset;

    if (WorkAroundType == 0) {
        DoJustRead(addr, length, offset, callback);
    } else if (WorkAroundType == 1) {
        if (FirstRead) {
            SeekTwiceBeforeRead(addr, length, offset, callback);
        } else if (!HitCache()) {
            DoJustRead(addr, length, offset, callback);
        } else {
            prev = (Prev.FSTLength + Prev.FSTPosition - 1) >> 15;
            if (prev == Curr.FSTLength >> 15 ||
                prev + 1 == Curr.FSTLength >> 15)
            {
                diff = __OSGetSystemTime() - LastReadFinished;
                if (OSMillisecondsToTicks(5) < diff) {
                    DoJustRead(addr, length, offset, callback);
                } else {
                    WaitBeforeRead(addr, length, offset, callback,
                                   OSMillisecondsToTicks(5) - diff +
                                       OSMicrosecondsToTicks(500));
                }
            } else {
                SeekTwiceBeforeRead(addr, length, offset, callback);
            }
        }
    }
    return TRUE;
}

int DVDLowSeek(unsigned long offset, void (* callback)(unsigned long)) {
    ASSERTMSGLINE(0x166, !(offset % 4), "DVDLowSeek(): offset must be a multiple of 4.");
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = 0xAB000000;
    __DIRegs[3] = (offset >> 2);
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowWaitCoverClose(void (* callback)(unsigned long)) {
    Callback = callback;
    WaitingCoverClose = TRUE;
    StopAtNextInt = FALSE;
    __DIRegs[1] = 2;
    return 1;
}

int DVDLowReadDiskID(struct DVDDiskID * diskID, void (* callback)(unsigned long)) {
    ASSERTMSGLINE(0x19B, !OFFSET(diskID, 32), "DVDLowReadID(): id must be aligned with 32 byte boundary.");
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = 0xA8000040;
    __DIRegs[3] = 0;
    __DIRegs[4] = sizeof(DVDDiskID);
    __DIRegs[5] = (u32)diskID;
    __DIRegs[6] = sizeof(DVDDiskID);
    __DIRegs[7] = 3;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowStopMotor(void (* callback)(unsigned long)) {
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = 0xE3000000;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowRequestError(void (* callback)(unsigned long)) {
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = 0xE0000000;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowInquiry(struct DVDDriveInfo * info, void (* callback)(unsigned long)) {
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = 0x12000000;
    __DIRegs[4] = sizeof(DVDDriveInfo);
    __DIRegs[5] = (u32)info;
    __DIRegs[6] = sizeof(DVDDriveInfo);
    __DIRegs[7] = 3;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowAudioStream(unsigned long subcmd, unsigned long length, unsigned long offset, void (* callback)(unsigned long)) {
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = (subcmd | 0xE1000000);
    __DIRegs[3] = (offset >> 2);
    __DIRegs[4] = length;
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowRequestAudioStatus(unsigned long subcmd, void (* callback)(unsigned long)) {
    StopAtNextInt = FALSE;
    Callback = callback;
    __DIRegs[2] = (subcmd | 0xE2000000);
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

int DVDLowAudioBufferConfig(int enable, unsigned long size, void (* callback)(unsigned long)) {
    unsigned long trigger;

    StopAtNextInt = FALSE;
    Callback = callback;
    trigger = (size >> 4) & 0xF;
    ASSERTLINE(0x25B, size & 0xF < 16);
    ASSERTLINE(0x25C, trigger <= 2);
    __DIRegs[2] = ((enable ? 0x10000 : 0) | 0xE4000000 | size);
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(10));
    return 1;
}

void DVDLowReset() {
    unsigned long reg;
    long long resetStart;

    __DIRegs[1] = 2;
    reg = __PIRegs[9];
    __PIRegs[9] = (reg & 0xFFFFFFFB) | 1;
    resetStart = __OSGetSystemTime();
    while((__OSGetSystemTime() - resetStart) < OSMicrosecondsToTicks(12)) 
        ;
    __PIRegs[9] = (reg | 4 | 1);
    ResetOccurred = 1;
    LastResetEnd = __OSGetSystemTime();
}

void (* DVDLowSetResetCoverCallback(void (* callback)(unsigned long)))(unsigned long) {
    void (* old)(unsigned long);
    int enabled;

    enabled = OSDisableInterrupts();
    old = ResetCoverCallback;
    ResetCoverCallback = callback;
    OSRestoreInterrupts(enabled);
    return old;
}

int DVDLowBreak() {
    StopAtNextInt = TRUE;
    Breaking = TRUE;
    return 1;
}

void (* DVDLowClearCallback())(unsigned long) {
    void (* old)(unsigned long);

    __DIRegs[1] = 0;
    old = Callback;
    Callback = NULL;
    return old;
}

unsigned long DVDLowGetCoverStatus() {
    if (((__OSGetSystemTime() - LastResetEnd)) < OSMillisecondsToTicks(100)) {
        return 0;
    }
    if (__DIRegs[1] & 1) {
        return 1;
    }
    return 2;
}

static void __DVDLowSetWAType(u32 type, u32 location)
{
    BOOL enabled = OSDisableInterrupts();
    WorkAroundType = type;
    WorkAroundSeekLocation = location;
    OSRestoreInterrupts(enabled);
}
