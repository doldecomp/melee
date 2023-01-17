#ifndef __DOLPHIN_DVD_H_
#define __DOLPHIN_DVD_H_

#include <dolphin/dvd/forward.h>
#include <Runtime/platform.h>

struct bb2struct {
    u32 _00;
    u32 _04;
    s32 _08; // size?
    u32 FSTMaxLength;
    void* FSTLocationInRam;
};

typedef struct {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
    void* FSTAddress;
    u32 userPosition;
    u32 userLength;
    u32 padding0;
} DVDBuffer;

struct DVDNode {
    DVDNode* next;
    DVDNode* prev;
};

struct DVDCommandBlock {
    DVDNode node;
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
};

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 padding[24];
} DVDDriveInfo;

typedef void (*DVDLowCallback)(u32 intType);
DVDLowCallback DVDLowClearCallback(void);

void DVDInit(void);
bool DVDOpen(char*, DVDFileInfo*);
bool DVDClose(DVDFileInfo*);
bool DVDChangeDir(char*);
bool DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo);
bool DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
                      DVDCallback callback, s32 prio);
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

#define DVDReadAsync(fileInfo, addr, length, offset, callback)                 \
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

#endif
