#ifndef DOLPHIN_CARD_H
#define DOLPHIN_CARD_H

#include <platform.h>

#include <dolphin/card/forward.h>

#include <dolphin/dsp/dsp.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSThread.h>

#define CARD_FAT_CHECKSUM 0
#define CARD_FAT_CHECKSUMINV 1
#define CARD_FAT_CHECKCODE 2
#define CARD_FAT_FREEBLOCKS 3
#define CARD_FAT_LASTSLOT 4
#define CARD_FAT_AVAIL 0

#define CARD_RESULT_UNLOCKED 1
#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY -1
#define CARD_RESULT_WRONGDEVICE -2
#define CARD_RESULT_NOCARD -3
#define CARD_RESULT_NOFILE -4
#define CARD_RESULT_IOERROR -5
#define CARD_RESULT_BROKEN -6
#define CARD_RESULT_EXIST -7
#define CARD_RESULT_NOENT -8
#define CARD_RESULT_INSSPACE -9
#define CARD_RESULT_NOPERM -10
#define CARD_RESULT_LIMIT -11
#define CARD_RESULT_NAMETOOLONG -12
#define CARD_RESULT_ENCODING -13
#define CARD_RESULT_CANCELED -14
#define CARD_RESULT_FATAL_ERROR -128

#define CARD_NUM_SYSTEM_BLOCK 5

#define CARD_WORKAREA_SIZE (5 * 8 * 1024)
#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024)
#define CARD_READ_SIZE 512
#define CARD_MAX_FILE 127
#define CARD_COMMENT_SIZE 64
#define CARD_FILENAME_MAX 32
#define CARD_ICON_MAX 8
#define CARD_ICON_WIDTH 32
#define CARD_ICON_HEIGHT 32
#define CARD_BANNER_WIDTH 96
#define CARD_BANNER_HEIGHT 32

#define CARD_STAT_ICON_NONE 0
#define CARD_STAT_ICON_C8 1
#define CARD_STAT_ICON_RGB5A3 2
#define CARD_STAT_ICON_MASK 3

#define CARD_STAT_BANNER_NONE 0
#define CARD_STAT_BANNER_C8 1
#define CARD_STAT_BANNER_RGB5A3 2
#define CARD_STAT_BANNER_MASK 3

#define CARD_STAT_ANIM_LOOP 0x00
#define CARD_STAT_ANIM_BOUNCE 0x04
#define CARD_STAT_ANIM_MASK 0x04

#define CARD_STAT_SPEED_END 0
#define CARD_STAT_SPEED_FAST 1
#define CARD_STAT_SPEED_MIDDLE 2
#define CARD_STAT_SPEED_SLOW 3
#define CARD_STAT_SPEED_MASK 3

#define CARD_MAX_MOUNT_STEP (CARD_NUM_SYSTEM_BLOCK + 2)

#define CARD_PAGE_SIZE 128
#define CARD_SEG_SIZE 512

#define CARD_STAT_SPEED_END 0
#define CARD_STAT_SPEED_FAST 1
#define CARD_STAT_SPEED_MIDDLE 2
#define CARD_STAT_SPEED_SLOW 3
#define CARD_STAT_SPEED_MASK 3

#define CARD_ATTR_PUBLIC 0x04
#define CARD_ATTR_NO_COPY 0x08
#define CARD_ATTR_NO_MOVE 0x10
#define CARD_ATTR_GLOBAL 0x20
#define CARD_ATTR_COMPANY 0x40

struct CARDFileInfo {
    s32 chan;
    s32 fileNo;

    s32 offset;
    s32 length;
    u16 iBlock;
    u16 __padding;
};

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 _padding0;
    u8 bannerFormat;
    u8 fileName[CARD_FILENAME_MAX];
    u32 time;     // seconds since 01/01/2000 midnight
    u32 iconAddr; // 0xffffffff if not used
    u16 iconFormat;
    u16 iconSpeed;
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 _padding1[2];
    u32 commentAddr; // 0xffffffff if not used
} CARDDir;

typedef struct CARDDirCheck {
    u8 padding0[64 - 2 * 4];
    u16 padding1;
    s16 checkCode;
    u16 checkSum;
    u16 checkSumInv;
} CARDDirCheck;

typedef struct CARDControl {
    bool attached;
    s32 result;
    u16 size;
    u16 pageSize;
    s32 sectorSize;
    u16 cBlock;
    u16 vendorID;
    s32 latency;
    u8 id[12];
    union {
        int mountStep;
        int formatStep;
    };
    u32 scramble;
    DSPTaskInfo task;
    void* workArea;
    CARDDir* currentDir;
    u16* currentFat;
    OSThreadQueue threadQueue;
    u8 cmd[9];
    s32 cmdlen;
    vu32 mode;
    int retry;
    int repeat;
    u32 addr;
    void* buffer;
    u32 xferred;
    u16 freeNo;
    u16 startBlock;
    CARDFileInfo* fileInfo;
    CARDCallback extCallback;
    CARDCallback txCallback;
    CARDCallback exiCallback;
    CARDCallback apiCallback;
    CARDCallback xferCallback;
    CARDCallback eraseCallback;
    CARDCallback unlockCallback;
    OSAlarm alarm;
    u32 cid;
    const DVDDiskID* diskID;
} CARDControl;

extern CARDControl __CARDBlock[2];

typedef struct CARDID {
    u8 serial[32]; // flashID[12] + timebase[8] + counterBias[4] + language[4]
                   // +
                   // XXX[4]
    u16 deviceID;
    u16 size;
    u16 encode; // character set -- 0: S-JIS, 1: ANSI

    u8 padding[512 - 32 - 5 * 2];

    u16 checkSum;
    u16 checkSumInv;
} CARDID;

s32 CARDClose(CARDFileInfo*);
int CARDWrite(CARDFileInfo*, void* buf, s32 length, s32 offset);
int CARDRead(CARDFileInfo*, void* buf, u32 length, u32 offset);
s32 __CARDClearStatus(s32 chan);
s32 __CARDReadStatus(s32 chan, u8* status);
static s32 Retry(s32 chan);
CARDDir* __CARDGetDirBlock(CARDControl*);
u16* __CARDGetFatBlock(CARDControl* card);
s32 __CARDUpdateFatBlock(s32 chan, u16* fat, CARDCallback);
void __CARDDefaultApiCallback(s32 chan, s32 result);
void __CARDSyncCallback(s32, s32);

#define __CARDGetDirCheck(dir) ((CARDDirCheck*) &(dir)[CARD_MAX_FILE])

#define CARDIsValidBlockNo(card, iBlock)                                      \
    (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)

#endif
