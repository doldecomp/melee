#ifndef __DOLPHIN_DVD_H_
#define __DOLPHIN_DVD_H_

#include <platform.h>

#include <dolphin/dvd/forward.h>

#include <dolphin/os/OSThread.h>

struct bb2struct {
    u32 _00;
    u32 _04;
    s32 _08; // size?
    u32 FSTMaxLength;
    void* FSTLocationInRam;
};

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct DVDBuffer {
    void* bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
    void* FSTAddress;
    u32 userPosition;
    u32 userLength;
    u32 padding0;
} DVDBuffer;

struct DVDCommandBlock {
    /*0x00*/ DVDCommandBlock* next;
    /*0x04*/ DVDCommandBlock* prev;
    /*0x08*/ u32 command;
    /*0x0C*/ s32 state;
    /*0x10*/ u32 offset;
    /*0x14*/ u32 length;
    /*0x18*/ void* addr;
    /*0x1C*/ u32 currTransferSize;
    /*0x20*/ u32 transferredSize;
    /*0x24*/ DVDDiskID* id;
    /*0x28*/ DVDCBCallback callback;
    /*0x2C*/ void* userData;
};

typedef struct DVDFileInfo DVDFileInfo;
typedef void (*DVDCallback)(s32 result, DVDFileInfo* fileInfo);
struct DVDFileInfo {
    /*0x00*/ DVDCommandBlock cb;
    /*0x30*/ u32 startAddr;
    /*0x34*/ u32 length;
    /*0x38*/ DVDCallback callback;
};

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 padding[24];
} DVDDriveInfo;

// Minimum transfer size.
#define DVD_MIN_TRANSFER_SIZE 32

// DVD states.
#define DVD_STATE_FATAL_ERROR -1
#define DVD_STATE_END 0
#define DVD_STATE_BUSY 1
#define DVD_STATE_WAITING 2
#define DVD_STATE_COVER_CLOSED 3
#define DVD_STATE_NO_DISK 4
#define DVD_STATE_COVER_OPEN 5
#define DVD_STATE_WRONG_DISK 6
#define DVD_STATE_MOTOR_STOPPED 7
#define DVD_STATE_PAUSING 8
#define DVD_STATE_IGNORED 9
#define DVD_STATE_CANCELED 10
#define DVD_STATE_RETRY 11

// File info states.
#define DVD_FILEINFO_READY 0
#define DVD_FILEINFO_BUSY 1

// DVD results.
#define DVD_RESULT_GOOD 0
#define DVD_RESULT_FATAL_ERROR -1
#define DVD_RESULT_IGNORED -2
#define DVD_RESULT_CANCELED -3

#define DVD_AIS_SUCCESS 0

extern OSThreadQueue __DVDThreadQueue;

typedef void (*DVDLowCallback)(u32 intType);
DVDLowCallback DVDLowClearCallback(void);

void DVDInit(void);
bool DVDOpen(char*, DVDFileInfo*);
bool DVDClose(DVDFileInfo*);
bool DVDChangeDir(char*);
bool DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo);
bool DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length,
                      s32 offset, DVDCallback callback, s32 prio);
s32 DVDConvertPathToEntrynum(const char* pathPtr);
void DVDReset(void);
s32 DVDCancel(DVDCommandBlock* block);
s32 DVDGetDriveStatus(void);
void __CARDSetDiskID(const DVDDiskID* id);

bool DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length,
                          s32 offset, DVDCBCallback callback);

bool DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID,
                   DVDCBCallback callback);
bool DVDCheckDisk(void);
void __DVDPrepareResetAsync(DVDCBCallback callback);
bool DVDSetAutoInvalidation(bool autoInval);

#define DVDReadAsync(fileInfo, addr, length, offset, callback)                \
    DVDReadAsyncPrio((fileInfo), (addr), (length), (offset), (callback), 2)

s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block);
bool DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback);
int DVDCancelAll(void);
DVDDiskID* DVDGetCurrentDiskID(void);
u32 CategorizeError(u32 error);
bool DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback);
int DVDCancelStream(DVDCommandBlock* block);
bool DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback);
bool DVDInquiryAsync(DVDCommandBlock* block, void* addr,
                     DVDCBCallback callback);
bool DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length,
                         s32 offset, DVDCBCallback callback, s32 prio);
bool DVDSeekAbsAsyncPrio(DVDCommandBlock* block, u32 offset,
                         DVDCBCallback callback, s32 prio);
bool DVDPrepareStreamAbsAsync(DVDCommandBlock* block, u32 length, u32 offset,
                              DVDCBCallback callback);

#endif
