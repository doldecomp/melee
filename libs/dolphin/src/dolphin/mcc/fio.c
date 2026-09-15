#include <dolphin.h>
#include <dolphin/mcc.h>

static u8 gBuf[8192];
static u8 gPrintBuf[1024];

static u8 gmSizeOfBlocks = 1;
static u8 gSizeOfBlocks = 1;
volatile static int gProcDone = 1;

static enum MCC_CHANNEL gmChID;
static enum MCC_CHANNEL gChID;
static int gQuery;
volatile static int gProcBusy;
volatile static u32 gStreamReady;
static u8 gLastErr;
static int bAsyncIsRead;
static enum FIO_ASYNC_STATE bAsyncBusy;
static void * bAsyncBuffer;
static u32 gAsyncDataSize;
static u32 gRequestSequenceNumber;

// functions
static int fioIsInitialized();
static u16 EndianConvert16(u16 n);
static u32 EndianConvert32(u32 n);
static int MPDWaiting(int timeout, volatile int * flag, int value);
static void ShowChannelInfo(enum MCC_CHANNEL chID);
static void fioErrorReport(char * msg);
static void fioMccChannelEvent(enum MCC_CHANNEL chID, u32 event, u32 value);
static void *fioPacketMakeHeader(u32 fioCode, u32 dataSize, int bEndianConvert);
static int fioPacketSendPacket(u8 sizeOfBlocks, void *pTopOfSecondBlockData);
static void *fioPacketReceiveResult(u32 fioCode, int bDone);
static void fioPacketReceiveDone(void);
static int fioPacketRead(int fd, void *buffer, int size, int async);
static int fioPacketWrite(int fd, void *buffer, int size, int async);
static int fioPacketResultRead(void *buffer, u32 dataSize);
static int fioPacketResultWrite(void *buffer, u32 dataSize);

static int fioIsInitialized() {
    return !!gChID;
}

static u16 EndianConvert16(u16 n) {
    return ((n & 0x00FF) << 8) | ((n & 0xFF00) >> 8);
}

static u32 EndianConvert32(u32 n) {
    return EndianConvert16((n >> 16) & 0xFFFF) | (EndianConvert16(n & 0xFFFF) << 0x10);
}

static int MPDWaiting(int timeout, volatile int * flag, int value) {
    u32 tickStart;
    u32 tickDist;

    tickStart = OSGetTick();
    while(*flag != value) {
        tickDist = OSGetTick() - tickStart;
        tickDist = (tickDist & 0x80000000) ? (0x80000000 - tickStart) + OSGetTick() : tickDist;
        if (OSTicksToSeconds(tickDist) >= timeout) {
            OSReport("Error:Time is over.\n");
            return 0;
        }
    }
    return 1;
}

static void ShowChannelInfo(enum MCC_CHANNEL chID) {
    MCC_Info info;

    MCCGetChannelInfo(chID, &info);
    OSReport("%2d: FirstBlock:%02d,BlockLength:%02d,Connect:%s,Lock:%s.\n", chID, info.firstBlock, info.blockLength,
                                                                            (info.connect == 0)  ? "DISCONNECT" : 
                                                                            (info.connect == 1)  ? "HOST_OPEN" : 
                                                                            (info.connect == 2)  ? "TARGET_OPEN" : 
                                                                            (info.connect == 3)  ? "CONNECTED" : "UNKNOWN",
                                                                            (info.isLocked == 0) ? "UNLOCKED" : 
                                                                            (info.isLocked == 1) ? "LOCKED" : "UNKNOWN");
}

static void fioErrorReport(char * msg) {
    OSReport("[fio] Error: %s\n", msg);
}

static void fioMccChannelEvent(enum MCC_CHANNEL chID, u32 event, u32 value) {
    u32 notify;

    switch(event) {
        case 0x1:
            gChID = chID;
            return;
        case 0x2:
            gChID = 0;
            return;
        case 0x100:
            notify = value & 0xF00000;
            switch (notify) {                         
            case 0x200000:                              
                if ((u16)value == 0x120) {
                    gQuery = 1;
                }
                return;
            case 0xF00000:                              
                gProcDone = 1;
                if ((s32) bAsyncBusy != 0) {
                    bAsyncBusy = 2;
                    return;
                }
                break;
            }
            break;
        case 0x10:
            gStreamReady = 0x10U;
            return;
        case 0x20:
            gStreamReady = 0x20U;
            break;
    }
}

int FIOInit(enum MCC_EXI exiChannel, enum MCC_CHANNEL chID, u8 blockSize) {
    if (MCCInit(exiChannel, 0xA, 0) == 0) {
        gLastErr = 0x87;
        goto exit;
    }
    if (MCCOpen(chID, blockSize, fioMccChannelEvent) == 0) {
        gLastErr = 0x87;
        goto exit;
    }
    gChID = chID;
    gmChID = chID;
    gSizeOfBlocks = blockSize;
    gmSizeOfBlocks = blockSize;
    gQuery = 0;
    gProcDone = 1;
    gProcBusy = 0;
    gLastErr = 0;
    bAsyncBusy = 0;
    bAsyncBuffer = NULL;
    bAsyncIsRead = 0;
    return 1;
exit:;
    return 0;
}

void FIOExit(void) {
    if (MCCClose(gChID) == 0) {
        gLastErr = 0x87;
        return;
    }
    gmChID = gChID = 0;
    gmSizeOfBlocks = gSizeOfBlocks = 1;
    gQuery = 0;
    gProcDone = 1;
    gProcBusy = 0;
    gLastErr = 0;
    bAsyncBusy = 0;
    bAsyncBuffer = NULL;
    bAsyncIsRead = 0;
}

int FIOQuery(void) {
    u32 tick;

    if (fioIsInitialized()) {
        gQuery = 0;
        if (MCCNotify(gChID, 0x100120) == 0) {
            gLastErr = 0x87;
            goto exit;
        }
        if (MPDWaiting(0xAU, &gQuery, 1) == 0) {
            gLastErr = 0x88;
            goto exit;
        }
        gLastErr = 0;
        return 1;
    }
exit:;
    tick = OSGetTick();
    do {} while(OSTicksToSeconds(OSGetTick() - tick) < 5);
    return 0;
}

u8 FIOGetLastError() {
    return gLastErr;
}

int FIOFopen(const char *filename, u32 mode) {
    struct FIO_Code {
        /* 0x00 */ u32 flag;
        /* 0x04 */ s8 filename; // dynamic length
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 descriptor;
    } *coder;

    if (filename == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (mode & ~0xE03) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(0, strlen(filename) + sizeof(u32) + sizeof(s8), 0);
    code->flag = mode;
    memcpy(&code->filename, filename, strlen(filename) + 1);
    if (fioPacketSendPacket(1U, NULL) != 0) {
        coder = fioPacketReceiveResult(1U, 1);
        if (coder != NULL) {
            if (coder->result != 0) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return coder->descriptor;
        }
    }
exit:;
    return -1;
}

int FIOFclose(int handle) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } * code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } * coder;

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(2, sizeof(struct FIO_Code), 0);
    code->descriptor = handle;
    if (fioPacketSendPacket(1, NULL) != 0) {
        coder = fioPacketReceiveResult(3, 1);
        if (coder != NULL) {
            gLastErr = coder->result;
            return 1;
        }
    }
exit:;
    return 0;
}

u32 FIOFread(int handle, void *data, u32 size) {
    char * pBuf;
    volatile int nSizeRemain;
    int nResult;
    int nReadSize;

    pBuf = data;
    nSizeRemain = size;
    nResult = -1; // loads a result var only to not use it.. Hudson pls

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (data == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (size == 0) {
        return 0;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    nReadSize = fioPacketRead(handle, pBuf, nSizeRemain, 0);
    nSizeRemain = nSizeRemain - nReadSize;
    if (nReadSize < 0) {
        gLastErr = 0x84;
        return -1;
    }
    gLastErr = 0;
    return size - nSizeRemain;
exit:;
    return -1;
}

u32 FIOFwrite(int handle, void * data, u32 size) {
    volatile int nSizeRemain;
    int nResult;
    int nWriteSize;

    nSizeRemain = size;
    nResult = 0;

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (data == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (size == 0) {
        return 0;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    nWriteSize = fioPacketWrite(handle, data, nSizeRemain, 0);
    nSizeRemain -= nWriteSize;
    if (nWriteSize < 0) {
        gLastErr = 0x83;
        return -1;
    }
    gLastErr = 0;
    return size - nSizeRemain;
exit:;
    return -1;
}

u32 FIOFseek(int handle, long offset, u32 mode) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 offset;
        /* 0x08 */ u32 base;
    } *code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ u32 pos;
    } *coder;

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (!((mode == 0) || (mode == 2) || (mode == 1U))) {
        gLastErr = 0xB0;
        goto exit;
    }
    if ((mode == 0U) && (offset < 0)) {
        gLastErr = 0xB0;
        goto exit;
    }
    if ((mode == 2U) && (offset > 0)) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(8, sizeof(struct FIO_Code), 0);
    code->descriptor = handle;
    code->offset = offset;
    code->base = mode;
    if (fioPacketSendPacket(1, NULL) != 0) {
        coder = fioPacketReceiveResult(9, 1);
        if ((coder != NULL) && (coder->result == 0)) {
            gLastErr = 0;
            return coder->pos;
        }
    }
exit:
    return -1;
}

int FIOFprintf(int handle, const char *format, ...) {
    char * str;
    int length;
    int err;
    va_list argptr;

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (format == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    str = (void*)gPrintBuf;
    va_start(argptr, format);
    err = vsprintf(str, format, argptr);
    if ((length = strlen((void*)str)) < 0x100) {
        str[length] = 0;
    } else {
        str[0xFF] = 0;
    }
    length = strlen((void*)str);
    if (err < 0) {
        gLastErr = 0x89;
        return -1;
    }
    gLastErr = 0;
    return FIOFwrite(handle, str, length + 1);
exit:;
    va_end(argptr);
    return -1;
}

int FIOFflush(int handle) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } * code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } * coder;

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(0xA, 4, 0);
    code->descriptor = handle;
    if (fioPacketSendPacket(1U, NULL) != 0) {
        coder = fioPacketReceiveResult(0xB, 1);
        if (coder != NULL) {
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return 1;
        }
    }
    
exit:
    return 0;
}

int FIOFstat(int handle, struct FIO_Stat *stat) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } * code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ struct FIO_Stat stat;
    } * coder;
    
    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (stat == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(0xC, 4, 0);
    code->descriptor = handle;
    if (fioPacketSendPacket(1U, NULL) != 0) {
        coder = fioPacketReceiveResult(0xD, 1);
        if (coder != NULL) {
            if (stat) {
                memcpy(stat, &coder->stat, sizeof(struct FIO_Stat));
            }
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return 1;
        }
    }
exit:;
    return 0;
}

int FIOFerror(int handle) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
    } * code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
    } * coder;

    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(0xE, 4, 0);
    code->descriptor = handle;
    if (fioPacketSendPacket(1U, NULL) != 0) {
        coder = fioPacketReceiveResult(0xF, 1);
        if (coder != NULL) {
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return gLastErr;
        }
    }
exit:;
    return gLastErr;
}

int FIOFindFirst(const char *filename, struct FIO_Finddata *finddata) {
    struct FIO_Code {
        /* 0x00 */ u8 filename; // dynamic length
    } * code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ struct FIO_Finddata findData;
    } * coder;

    if (filename == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (finddata == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(0x10U, strlen(filename) + 1, 0);
    strcpy((void*)&code->filename, filename);
    if (fioPacketSendPacket(1U, NULL) != 0) {
        coder = fioPacketReceiveResult(0x11, 1);
        if (coder != NULL) {
            if (finddata) {
                memcpy(finddata, &coder->findData, sizeof(struct FIO_Finddata));
            }
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return 1;
        }
    }
exit:;
    return 0;
}

int FIOFindNext(struct FIO_Finddata *finddata) {
    struct FIO_Code {
        /* 0x00 */ u32 reserved;
    } * code;
    struct FIO_Coder {
        /* 0x00 */ u32 result;
        /* 0x04 */ struct FIO_Finddata findData;
    } * coder;

    if (finddata == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (bAsyncBusy != 0) {
        gLastErr = 0xA1;
        goto exit;
    }
    code = fioPacketMakeHeader(0x12, 4, 0);
    code->reserved = 0;
    if (fioPacketSendPacket(1U, NULL) != 0) {
        coder = fioPacketReceiveResult(0x13, 1);
        if (coder != NULL) {
            if (finddata) {
                memcpy(finddata, &coder->findData, sizeof(struct FIO_Finddata));
            }
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return 1;
        }
    }
exit:;
    return 0;
}

u32 FIOGetAsyncBufferSize(void) {
    int nPacketSize;
    int nHeaderSize;

    if (gChID == 0) {
        return 0;
    }
    nPacketSize = gSizeOfBlocks << 0xD;
    nHeaderSize = 0x18;

    return nPacketSize - nHeaderSize;
}

int FIOFreadAsync(int handle, void * data, u32 size) {
    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (data == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (size != 0) {
        if (size > FIOGetAsyncBufferSize()) {
            gLastErr = 0xA0;
            goto exit;
        }
        if (bAsyncBusy != 0) {
            gLastErr = 0xA1;
            goto exit;
        }
        bAsyncBusy = 1;
        bAsyncBuffer = data;
        bAsyncIsRead = 1;
        if (fioPacketRead(handle, data, size, 1) >= 0) {
            return 1;
        }
    }
exit:;
    return 0;
}

int FIOFwriteAsync(int handle, void * data, u32 size) {
    if (handle == 0) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (handle == -1) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (data == NULL) {
        gLastErr = 0xB0;
        goto exit;
    }
    if (size != 0) {
        if (size > FIOGetAsyncBufferSize()) {
            gLastErr = 0xA0;
            goto exit;
        }
        if (bAsyncBusy != 0) {
            gLastErr = 0xA1;
            goto exit;
        }
        bAsyncBusy = 1;
        bAsyncBuffer = data;
        bAsyncIsRead = 0;
        if (fioPacketWrite(handle, data, size, 1) >= 0) {
            return 1;
        }
    }

exit:
    return 0;
}

int FIOCheckAsyncDone(u32 * result) {
    if (bAsyncBusy != 0) {
        if (bAsyncIsRead != 0) {
            if (result) {
                *result = fioPacketResultRead(bAsyncBuffer, gAsyncDataSize);
            }
        } else if (result) {
            *result = fioPacketResultWrite(bAsyncBuffer, gAsyncDataSize);
        }
        bAsyncBusy = 0;
        return 1;
    }
    return 0;
}

static void *fioPacketMakeHeader(u32 fioCode, u32 dataSize, int bEndianConvert) {
    MCC_Hdr *hdrDpci;
    MCC_HdrFio *hdrFio;
    char *data;

    hdrDpci = (void*)&gBuf[0];
    hdrFio = (void*)((char*)hdrDpci + 0x8);
    data = (void*)((char*)hdrFio + 0x8);
    gRequestSequenceNumber += 1;
    hdrFio->code = fioCode;
    hdrFio->number = gRequestSequenceNumber;
    hdrDpci->length = dataSize + 0x10;
    hdrDpci->rsvd = 0;
    hdrDpci->protocol = 0x120;
    if (bEndianConvert) {
        hdrFio->code = EndianConvert32(hdrFio->code);
        hdrFio->number = EndianConvert32(hdrFio->number);
        hdrDpci->length = EndianConvert32(hdrDpci->length);
        hdrDpci->protocol = EndianConvert16(hdrDpci->protocol);
    }
    return (data);
}

static int fioPacketSendPacket(u8 sizeOfBlocks, void *pTopOfSecondBlockData) {
    u32 oldMaskWrite;
    u8 indexOfBlocks;

    oldMaskWrite = MCCSetChannelEventMask(gChID, 0xA0);
    do {} while (gProcBusy != 0);
    do {} while (gProcDone == 0);
    gProcDone = 0;
    gProcBusy = 1;
    for(indexOfBlocks = 0; indexOfBlocks < sizeOfBlocks; indexOfBlocks++) {
        if (MCCWrite(gChID, ((u8)indexOfBlocks << 0xD), &gBuf, 0x2000, 0) == 0) {
            gLastErr = 0x83;
            MCCSetChannelEventMask(gChID, oldMaskWrite);
            fioErrorReport("fioPacketSendPacket.MCCWrite.NG");
            return 0;
        }
        if (sizeOfBlocks > 1U) {
            memcpy(&gBuf, pTopOfSecondBlockData, 0x2000);
            ((char*)pTopOfSecondBlockData) += 0x2000;
        }
    }
    MCCSetChannelEventMask(gChID, oldMaskWrite);
    if (MCCNotify(gChID, 0xF00000) == 0) {
        gLastErr = 0x87;
        fioErrorReport("fioPacketSendPacket.MCCNotify.NG"); // fake padding but idk whats going on here.
        return 0;
    }
    gLastErr = 0;
    return 1;
}

static void *fioPacketReceiveResult(u32 fioCode, int bDone) {
    u32 oldMaskRead;
    MCC_Hdr *hdrDpci;
    MCC_HdrFio *hdrFio;
    char *data;

    if (MPDWaiting(0xAU, &gProcDone, 1) == 0) {
        gLastErr = 0x88;
        goto exit;
    }
    oldMaskRead = MCCSetChannelEventMask(gChID, 0x50);
    if (MCCRead(gChID, 0, &gBuf, 0x2000U, 0) == 0) {
        gLastErr = 0x84;
        MCCSetChannelEventMask(gChID, oldMaskRead);
        goto exit;
    }
    hdrDpci = (void*)((char*)&gBuf[0]);
    hdrFio = (void*)((char*)hdrDpci + 0x8);
    data = (void*)((char*)hdrFio + 0x8);
    MCCSetChannelEventMask(gChID, oldMaskRead);
    if (hdrFio->code != fioCode) {
        gLastErr = 0x81;
        goto exit;
    }
    if (hdrFio->number != gRequestSequenceNumber) {
        gLastErr = 0x82;
        goto exit;
    }
    if (bDone != 0) {
        fioPacketReceiveDone();
    }
    gLastErr = 0;
    return data;
exit:;
    fioPacketReceiveDone();
    return NULL;
}

static void fioPacketReceiveDone(void) {
    gProcBusy = 0;
}

static int fioPacketRead(int fd, void *buffer, int size, int async) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 nbytes;
    } *code;

    code = fioPacketMakeHeader(4, sizeof(struct FIO_Code), 0);
    code->descriptor = fd;
    code->nbytes = size;
    gStreamReady = 0;
    if (fioPacketSendPacket(1U, NULL) != 0) {
        if (async == 0) {
            return fioPacketResultRead(buffer, size);
        }
        gAsyncDataSize = size;
        return 0;
    }
    return -1;
}

static int fioPacketWrite(int fd, void *buffer, int size, int async) {
    struct FIO_Code {
        /* 0x00 */ u32 descriptor;
        /* 0x04 */ u32 nbytes;
    } *code;

    code = fioPacketMakeHeader(6U, 0xC, 0);
    code->descriptor = fd;
    code->nbytes = size;
    if (fioPacketSendPacket(1U, NULL) != 0) {
        gStreamReady = 0U;
        if (async == 0) {
            return fioPacketResultWrite(buffer, size);
        }
        gAsyncDataSize = size;
        return 0;
    }
    return -1;
}

static int fioPacketResultRead(void *buffer, u32 dataSize) {
    int bResult;
    enum MCC_CHANNEL nChID;
    u8 nChannelBlocks;
    u32 dataBlockSize;
    u32 readDataBlocks;
    u32 nPacketSize;
    u32 nDataPacketSize;
    u32 nFraction;
    enum MCC_CONNECT state;
    int bNeedWaitDisconnect;
    u32 oldMaskWrite;
    u8 err;
    char msg[256];

    bResult = 1;
    nChID = gmChID;
    nChannelBlocks = gmSizeOfBlocks;
    dataBlockSize = (u32) (dataSize + 0x1FFF) >> 0xDU;
    nPacketSize = ((u8)nChannelBlocks << 0xD);
    nDataPacketSize = dataSize / nPacketSize;
    nFraction = dataSize - (nDataPacketSize * nPacketSize);
    nFraction = OSRoundUp32B(nFraction) & ~1;

    if (nFraction != 0) {
        do {} while ((u32) gStreamReady != 0x20U);
        MCCRead(nChID, 0, buffer, nFraction, 0);
        ((char*)buffer) += nFraction;
    }
    if (nDataPacketSize != 0) {
        bNeedWaitDisconnect = 0;
        oldMaskWrite = MCCSetChannelEventMask(nChID, 0);
        MCCSetChannelEventMask(nChID, oldMaskWrite);
        if (MCCClose(nChID) == 0) {
            fioErrorReport("fioPacketResultRead.MCCClose.NG");
            bResult = 0;
        } else {
            do {
                MCCGetConnectionStatus(nChID, &state);
            } while (state != 0);
            if (MCCStreamOpen(nChID, nChannelBlocks) == 0) {
                fioErrorReport("fioPacketResultRead.MCCStreamOpen.NG");
                bResult = 0;
            } else {
                do {
                    MCCGetConnectionStatus(nChID, &state);
                } while (state != 3);

                if ((nDataPacketSize * nChannelBlocks) != (readDataBlocks = MCCStreamRead(nChID, buffer))) {
                    err = MCCGetLastError();
                    sprintf(msg, "fioPacketResultRead.MCCStreamRead.NG(Err:%d)", err);
                    fioErrorReport(msg);
                    bResult = 0;
                }
                if (MCCStreamClose(nChID) == 0) {
                    OSReport("MCCStream:MCCStreamClose.NG\n");
                    bResult = 0;
                } else {
                    enum MCC_CONNECT state; // r1+0x10
                    do {
                        MCCGetConnectionStatus(nChID, &state);
                    } while (state != 0);
                    if (MCCOpen(nChID, nChannelBlocks, fioMccChannelEvent) == 0) {
                        OSReport("MCCStream:MCCOpen.NG\n");
                        bResult = 0;
                    } else {
                        do {
                            MCCGetConnectionStatus(nChID, &state);
                        } while (state != 3);
                    }
                }
            }
        }
        MCCSetChannelEventMask(gChID, oldMaskWrite);
    }
    // scope for variable?
    {
        struct FIO_Coder {
            /* 0x00 */ u32 result;
            /* 0x04 */ u32 nbytes;
            /* 0x08 */ char data;
        } * coder;

        coder = fioPacketReceiveResult(5U, 0);
        if (coder == NULL) {
            bResult = 0;
        } else if (coder->result != 0) {
            gLastErr = coder->result;
            bResult = 0;
        } else {
            gLastErr = 0;
        }
        fioPacketReceiveDone();
        if (bResult == 1) {
            return dataSize;
        }
        goto exit;
    }
exit:;
    return -1;
    
}

static int fioPacketResultWrite(void *buffer, u32 dataSize) {
    register int nResult = 0;
    enum MCC_CHANNEL nChID;
    u8 nChannelBlocks = 0;
    u32 dataBlockSize;
    enum MCC_CONNECT state;
    int bNeedWaitDisconnect;
    u32 oldMaskWrite;

    nChID = gmChID;
    nChannelBlocks = gmSizeOfBlocks; // needed to match. dumb.
    dataBlockSize = (dataSize + 0x1FFF) >> 0xD;
    bNeedWaitDisconnect = 0;
    oldMaskWrite = MCCSetChannelEventMask(nChID, 0);
    MCCSetChannelEventMask(nChID, oldMaskWrite);
    if (MCCClose(nChID) == 0) {
        fioErrorReport("fioPacketResultWrite.MCCClose.NG");
    } else {
loop:;
        MCCGetConnectionStatus(nChID, &state);
        if (state != 0) {
            goto loop;
        }
        if (MCCStreamOpen(nChID, nChannelBlocks) == 0) {
            fioErrorReport("fioPacketResultWrite.MCCStreamOpen.NG");
            goto loop;
        }
        
        do {
            MCCGetConnectionStatus(nChID, &state);
        } while (state != 3);
        if (MCCStreamWrite(nChID, buffer, dataBlockSize) == 0) {
            fioErrorReport("fioPacketResultWrite.MCCStreamWrite.NG");
        }
        {
            enum MCC_CONNECT state; // r1+0x10
            do {
                MCCGetConnectionStatus(nChID, &state);
            } while (state == 3);
            if (MCCStreamClose(nChID) == 0) {
                OSReport("MCCStream:MCCStreamClose.NG\n");
            } else {
                do {
                    MCCGetConnectionStatus(nChID, &state);
                } while (state == 0);
                if (MCCOpen(nChID, nChannelBlocks, fioMccChannelEvent) == 0) {
                    OSReport("MCCStream:MCCOpen.NG\n");
                }
            }
        }
        goto exit_loop;
    }
exit_loop:;
    {
        struct FIO_Coder {
            /* 0x00 */ u32 result;
            /* 0x04 */ u32 nbytes;
        } * coder;
    
        oldMaskWrite = MCCSetChannelEventMask(gChID, oldMaskWrite);
        coder = fioPacketReceiveResult(7U, 1);
        if (coder == NULL) {
            (void)0;
        } else {
            if (coder->result) {
                gLastErr = coder->result;
                goto exit;
            }
            gLastErr = 0;
            return coder->nbytes;
        }
    }
exit:
    return -1;
}
