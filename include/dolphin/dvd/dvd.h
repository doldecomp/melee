#ifndef __DOLPHIN_DVD_H_
#define __DOLPHIN_DVD_H_

#include <dolphin/types.h>

struct bb2struct
{
	u32 _00;
	u32 _04;
	s32 _08;  // size?
	u32 FSTMaxLength;
	void* FSTLocationInRam;
};

typedef struct
{
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);
struct DVDCommandBlock
{
    /*0x00*/ DVDCommandBlock *next;
    /*0x04*/ DVDCommandBlock *prev;
    /*0x08*/ u32 command;
    /*0x0C*/ s32 state;
    /*0x10*/ u32 offset;
    /*0x14*/ u32 length;
    /*0x18*/ void *addr;
    /*0x1C*/ u32 currTransferSize;
    /*0x20*/ u32 transferredSize;
    /*0x24*/ DVDDiskID *id;
    /*0x28*/ DVDCBCallback callback;
    /*0x2C*/ void *userData;
};

typedef struct DVDFileInfo  DVDFileInfo;
typedef void (*DVDCallback)(s32 result, DVDFileInfo *fileInfo);
struct DVDFileInfo
{
	/*0x00*/ DVDCommandBlock cb;
    /*0x30*/ u32 startAddr;
    /*0x34*/ u32 length;
    /*0x38*/ DVDCallback callback;
};

void DVDInit(void);
BOOL DVDOpen(char *, DVDFileInfo *);
BOOL DVDClose(DVDFileInfo *);
BOOL DVDChangeDir(char *);
BOOL DVDFastOpen(s32 entrynum, DVDFileInfo *fileInfo);
BOOL DVDReadAsyncPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, DVDCallback callback, s32 prio);
s32 DVDConvertPathToEntrynum(char *pathPtr);
s32 DVDCancel(DVDCommandBlock *block);
s32 DVDGetDriveStatus(void);

#define DVDReadAsync(fileInfo, addr, length, offset, callback) \
    DVDReadAsyncPrio((fileInfo), (addr), (length), (offset), (callback), 2)

#endif
