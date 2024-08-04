#include <dolphin.h>
#include <dolphin/mcc.h>

// .bss
volatile static u8 gBuf[8192]; // size: 0x2000, address: 0x0

// .sbss
static u32 gOldEvent;
volatile static enum MCC_CHANNEL gChID;
volatile static int gQuery;
volatile static u32 gReadDone; // size: 0x4, address: 0xC
volatile static u32 gPrintfID; // size: 0x4, address: 0x10
volatile static u32 gBufHead; // size: 0x4, address: 0x14
volatile static u32 gBufTail; // size: 0x4, address: 0x18

// functions
static int ttyIsInitialized();
void ShowChannelInfo(enum MCC_CHANNEL chID);
static void ttyMccChannelEvent(enum MCC_CHANNEL chID, u32 event, u32 value);
int TTYInit(enum MCC_EXI exiChannel, enum MCC_CHANNEL chID);
void TTYExit(void);
int TTYQuery(void);
int TTYPrintf(const char *format, ...);
int TTYFlush(void);
static void ttyClearProperty(enum MCC_CHANNEL chID);
static int ttyWaiting(int timeout, volatile int *flag);
static int ttyWrite(u32 offset, void *data, long size);
static int ttyFlush(u32 msgID, int waitResult);

static int ttyIsInitialized() {
    int bResult = (gChID != 0);

    return bResult;
}

static void ShowChannelInfo(enum MCC_CHANNEL chID) {
    MCC_Info info;

    MCCGetChannelInfo(chID, &info);
    OSReport("%2d: FirstBlock:%02d,BlockLength:%02d,Connect:%s,Lock:%s.\n", chID, 
              info.firstBlock,info.blockLength, (info.connect == 0)  ? "DISCONNECT"  :
                                                (info.connect == 1)  ? "HOST_OPEN"   :
                                                (info.connect == 2)  ? "TARGET_OPEN" :
                                                (info.connect == 3)  ? "CONNECTED"   : "UNKNOWN",
                                                (info.isLocked == 0) ? "UNLOCKED"    :
                                                (info.isLocked == 1) ? "LOCKED"      : "UNKNOWN");
}

static void ttyMccChannelEvent(enum MCC_CHANNEL chID, u32 event, u32 value) {
    u32 notify;
    u32 size;
    u32 msgID;

    switch(event) {
        case 1:
            gChID = chID;
            return;
        case 2:
            gChID = 0;
            return;
        case 0x100:
            notify = (value & (0xF00000));
            switch(notify) {
                case 0x200000:                              
                    if ((u16)value == 0x210) {
                        gQuery = 1;
                    }
                    return;
                case 0x400000:                              
                    size = (value >> 8) & 0xFF;
                    msgID = (value) & 0xFF;
                    if ((gBufTail - gBufHead) >= 0x2000) {
                        gBufHead = ((u32) gBufHead < 0x2000U) ? gBufHead : gBufHead - 0x2000;
                        gBufTail = ((u32) gBufTail < 0x2000U) ? gBufTail : gBufTail - 0x2000;
                    }
                    if ((u32) gBufHead >= 0x2000U) {
                        gBufHead -= 0x2000;
                        gBufTail -= 0x2000;
                    }
                    if (size == 0) {
                        gBufHead += size << 5;
                        gReadDone = (u32) msgID;
                        return;
                    }
                    gBufHead += size << 5;
                    gReadDone = (u32) msgID;
            }
    }
}

int TTYInit(enum MCC_EXI exiChannel, enum MCC_CHANNEL chID) {
    if (ttyIsInitialized()) {
        return 0;
    }
    if ((MCCInit(exiChannel, 5, 0)) && (MCCOpen(chID, 1, ttyMccChannelEvent))) {
        gOldEvent = MCCSetChannelEventMask(chID, 0x30);
        ttyClearProperty(chID);
        return 1;
    }
    return 0;
}

void TTYExit(void) {
    if (ttyIsInitialized() != 0) {
        MCCSetChannelEventMask(gChID, gOldEvent);
        if (MCCClose(gChID) != 0) {
            ttyClearProperty(0);
        }
    }
}

int TTYQuery(void) {
    u32 tick;

    if (ttyIsInitialized()) {
        gQuery = 0;
        if (MCCNotify(gChID, 0x100210)) {
            return ttyWaiting(5, &gQuery);
        }
    }
    tick = OSGetTick();
    do {} while(OSTicksToSeconds(OSGetTick() - tick) < 5);
    return 0;
}

int TTYPrintf(const char *format, ...) {
    if (ttyIsInitialized() && (format != NULL)) {
        MCC_Hdr *hdr;
        u32 *id;
        char *str;
        u32 maxDataSize;
        u32 formatLength;
        u32 dataSize;
        int err;
        char * eof;
        va_list argptr;
        u32 prosecced;

        hdr = (void*)&gBuf;
        id = (u32*)(hdr + 1);
        str = (char*)(id + 1);
        maxDataSize = 8179;
        formatLength = strlen(format);
        if (formatLength > maxDataSize) {
            eof = (void*)((-1 + maxDataSize + (u32)format));
            *(eof) = 0;
        }
        va_start(argptr, format);
        err = vsprintf(str, format, argptr);
        if (strlen(str) < maxDataSize) {
            str[strlen(str)] = 0;
        } else {
            err = -1;
        }
        if (err < 0) {
            return 0;
        }
        hdr->length = strlen(str) + 0xD;
        hdr->rsvd = 0;
        hdr->protocol = 0x210;
        dataSize = OSRoundUp32B(hdr->length) & ~1;
        if ((0x2000 - (gBufTail - gBufHead)) <= dataSize) {
            ttyFlush(gPrintfID, 1);
        }
        gPrintfID += 1;
        gPrintfID = (u8) gPrintfID;
        *id = gPrintfID;
        if ((0x2000 - (gBufTail & 0x1FFF)) < dataSize) {
            prosecced = 0x2000 - (gBufTail & 0x1FFF);
            ttyWrite(gBufTail & 0x1FFF, (char*)&gBuf, prosecced);
            ttyWrite(0, (char*)&gBuf + prosecced, dataSize - prosecced);
        } else {
            ttyWrite(gBufTail & 0x1FFF, (char*)&gBuf, dataSize);
        }
        gBufTail += dataSize;
        if (strchr(str, '\n') != 0U) {
            ttyFlush(gPrintfID, 1);
        } else if (gPrintfID == 0xFF) {
            ttyFlush(gPrintfID, 1);
        }
        va_end(format);
        return 1;
    }
    return 0;
}

int TTYFlush(void) {
    if (ttyIsInitialized() == 0) {
        return 0;
    }
    return ttyFlush(gPrintfID, 1);
}

static void ttyClearProperty(enum MCC_CHANNEL chID) {
    gChID = chID;
    gQuery = 0;
    gReadDone = 0;
    gPrintfID = 0;
    gBufHead = 0;
    gBufTail = 0;
}

static int ttyWaiting(int timeout, volatile int *flag) {
    u32 tickStart;
    u32 tickDist;

    tickStart = OSGetTick();
    timeout = OSSecondsToTicks(timeout);
    while(*flag == 0) {
        tickDist = OSGetTick() - tickStart;
        tickDist = (tickDist & 0x80000000) ? (0x80000000 - tickStart) + OSGetTick() : tickDist;
        if (OSTicksToSeconds(tickDist) >= timeout) {
            return 0;
        }
    }
    return 1;
}

static int ttyWrite(u32 offset, void *data, long size) {
    if (MCCWrite(gChID, offset, data, size, 0)) {
        return 1;
    }
    return 0;
}

static int ttyFlush(u32 msgID, int waitResult) {
    u32 notify;

    notify = msgID | 0x300000;

    if ((gBufTail - gBufHead) == 0) {
        return 1;
    }
    if (MCCNotify(gChID, notify) == 0) {
        while(1)
            ;
    }
    if (waitResult != 0) {
        do {} while (gReadDone != msgID);
    }
    return 1;
}
