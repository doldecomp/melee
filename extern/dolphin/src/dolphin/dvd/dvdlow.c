#include <dolphin.h>
#include <dolphin/dvd.h>

#include "__dvd.h"
#include "__os.h"

// .sbss
static void (* Callback)(unsigned long); // size: 0x4, address: 0x0
static void (* ResetCoverCallback)(unsigned long); // size: 0x4, address: 0x4
static volatile long long LastResetEnd; // size: 0x8, address: 0x8
static volatile unsigned long ResetOccurred; // size: 0x4, address: 0x10
static int WaitingCoverClose; // size: 0x4, address: 0x14
static volatile int Breaking; // size: 0x4, address: 0x18

void __DVDInterruptHandler(short unused, struct OSContext * context) {
    struct OSContext exceptionContext;
    unsigned long cause;
    unsigned long reg;
    unsigned long intr;
    unsigned long mask;

    cause = 0;
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
    if (cause != 0) {
        ResetOccurred = 0U;
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
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (cause != 0) {
        if (Callback) {
            Callback(cause);
        }
        Breaking = 0;
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

int DVDLowRead(void * addr, unsigned long length, unsigned long offset, void (* callback)(unsigned long)) {
    ASSERTMSGLINE(0x143, !OFFSET(addr, 32), "DVDLowRead(): address must be aligned with 32 byte boundary.");
    ASSERTMSGLINE(0x144, !(length % 32), "DVDLowRead(): length must be a multiple of 32.");
    ASSERTMSGLINE(0x145, !(offset % 4), "DVDLowRead(): offset must be a multiple of 4.");
    ASSERTMSGLINE(0x147, (length != 0), "DVD read: 0 was specified to length of the read\n");
    Callback = callback;
    __DIRegs[2] = 0xA8000000;
    __DIRegs[3] = (offset >> 2);
    __DIRegs[4] = (length);
    __DIRegs[5] = (u32)addr;
    __DIRegs[6] = (length);
    __DIRegs[7] = 3;
    return 1;
}

int DVDLowSeek(unsigned long offset, void (* callback)(unsigned long)) {
    ASSERTMSGLINE(0x166, !(offset % 4), "DVDLowSeek(): offset must be a multiple of 4.");
    Callback = callback;
    __DIRegs[2] = 0xAB000000;
    __DIRegs[3] = (offset >> 2);
    __DIRegs[7] = 1;
    return 1;
}

int DVDLowWaitCoverClose(void (* callback)(unsigned long)) {
    Callback = callback;
    WaitingCoverClose = 1;
    __DIRegs[1] = 2;
    return 1;
}

int DVDLowReadDiskID(struct DVDDiskID * diskID, void (* callback)(unsigned long)) {
    ASSERTMSGLINE(0x19B, !OFFSET(diskID, 32), "DVDLowReadID(): id must be aligned with 32 byte boundary.");
    Callback = callback;
    __DIRegs[2] = 0xA8000040;
    __DIRegs[3] = 0;
    __DIRegs[4] = 0x20;
    __DIRegs[5] = (u32)diskID;
    __DIRegs[6] = 0x20;
    __DIRegs[7] = 3;
    return 1;
}

int DVDLowStopMotor(void (* callback)(unsigned long)) {
    Callback = callback;
    __DIRegs[2] = 0xE3000000;
    __DIRegs[7] = 1;
    return 1;
}

int DVDLowRequestError(void (* callback)(unsigned long)) {
    Callback = callback;
    __DIRegs[2] = 0xE0000000;
    __DIRegs[7] = 1;
    return 1;
}

int DVDLowInquiry(struct DVDDriveInfo * info, void (* callback)(unsigned long)) {
    Callback = callback;
    __DIRegs[2] = 0x12000000;
    __DIRegs[4] = 0x20;
    __DIRegs[5] = (u32)info;
    __DIRegs[6] = 0x20;
    __DIRegs[7] = 3;
    return 1;
}

int DVDLowAudioStream(unsigned long subcmd, unsigned long length, unsigned long offset, void (* callback)(unsigned long)) {
    Callback = callback;
    __DIRegs[2] = (subcmd | 0xE1000000);
    __DIRegs[3] = (offset >> 2);
    __DIRegs[4] = length;
    __DIRegs[7] = 1;
    return 1;
}

int DVDLowRequestAudioStatus(unsigned long subcmd, void (* callback)(unsigned long)) {
    Callback = callback;
    __DIRegs[2] = (subcmd | 0xE2000000);
    __DIRegs[7] = 1;
    return 1;
}

int DVDLowAudioBufferConfig(int enable, unsigned long size, void (* callback)(unsigned long)) {
    unsigned long bufSize;
    unsigned long trigger;

    Callback = callback;
    bufSize = size & 0xF;
    trigger = (size >> 4) & 0xF;
    ASSERTLINE(0x25B, bufSize < 16);
    ASSERTLINE(0x25C, trigger <= 2);
    __DIRegs[2] = ((enable ? 0x10000 : 0) | 0xE4000000 | size);
    __DIRegs[7] = 1;
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
    unsigned long statusReg;

    statusReg = __DIRegs[0];
    statusReg |= 0x41;

    __DIRegs[0] = statusReg;
    Breaking = 1;
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
