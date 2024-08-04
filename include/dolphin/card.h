#ifndef _DOLPHIN_CARD_H_
#define _DOLPHIN_CARD_H_

#include <dolphin/os.h>
#include <dolphin/dsp.h>
#include <dolphin/dvd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CARD_FILENAME_MAX 32
#define CARD_MAX_FILE 127
#define CARD_ICON_MAX 8

typedef void (*CARDCallback)(s32 chan, s32 result);

// todo: sort into headers
typedef struct CARDFileInfo
{
    /*0x00*/ s32 chan;
    /*0x04*/ s32 fileNo;
    /*0x08*/ s32 offset;
    /*0x0C*/ s32 length;
    /*0x10*/ u16 iBlock;
} CARDFileInfo;

typedef struct CARDDir
{
    /*0x00*/ u8 gameName[4];
    /*0x04*/ u8 company[2];
    /*0x06*/ u8 _padding0;
    /*0x07*/ u8 bannerFormat;
    /*0x08*/ u8 fileName[CARD_FILENAME_MAX];
    /*0x28*/ u32 time;     // seconds since 01/01/2000 midnight
    /*0x2C*/ u32 iconAddr; // 0xffffffff if not used
    /*0x30*/ u16 iconFormat;
    /*0x32*/ u16 iconSpeed;
    /*0x34*/ u8 permission;
    u8 copyTimes;
    /*0x36*/ u16 startBlock;
    u16 length;
    u8 _padding1[2];
    u32 commentAddr; // 0xffffffff if not used
} CARDDir;

typedef struct CARDControl
{
    /*0x00*/ BOOL attached;
    /*0x04*/ s32 result;
    /*0x08*/ u16 size;
    /*0x0A*/ u16 pageSize;
    /*0x0C*/ s32 sectorSize;
    /*0x10*/ u16 cBlock;
    /*0x12*/ u16 vendorID;
    /*0x14*/ s32 latency;
    /*0x18*/ u8 id[12];
    /*0x24*/ int mountStep;
    /*0x28*/ u32 scramble;
    /*0x2C*/ int formatStep;
    DSPTaskInfo task;
    void *workArea;
    /*0x84*/ CARDDir *currentDir;
    u16 *currentFat;
    OSThreadQueue threadQueue;
    u8 cmd[9];
    s32 cmdlen;
    volatile u32 mode;
    int retry;
    int repeat;
    u32 addr;
    void *buffer;
    s32 xferred;
    u16 freeNo;
    u16 startBlock;
    /*0xC0*/ CARDFileInfo *fileInfo;
    CARDCallback extCallback;
    CARDCallback txCallback;
    CARDCallback exiCallback;
    CARDCallback apiCallback;
    CARDCallback xferCallback;
    CARDCallback eraseCallback;
    CARDCallback unlockCallback;
    OSAlarm alarm;
} CARDControl;

typedef struct CARDDecParam {
    /* 0x00 */ u8 * inputAddr;
    /* 0x04 */ u32 inputLength;
    /* 0x08 */ u32 aramAddr;
    /* 0x0C */ u8 * outputAddr;
} CARDDecParam;

typedef struct CARDID {
    /* 0x000 */ u8 serial[32];
    /* 0x020 */ u16 deviceID;
    /* 0x022 */ u16 size;
    /* 0x024 */ u16 encode;
    /* 0x026 */ u8 padding[470];
    /* 0x1FC */ u16 checkSum;
    /* 0x1FE */ u16 checkSumInv;
} CARDID;

#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDCheck.h>
#include <dolphin/card/CARDCreate.h>
#include <dolphin/card/CARDDelete.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDFormat.h>
#include <dolphin/card/CARDMount.h>
#include <dolphin/card/CARDOpen.h>
#include <dolphin/card/CARDRdwr.h>
#include <dolphin/card/CARDRead.h>
#include <dolphin/card/CARDRename.h>
#include <dolphin/card/CARDStat.h>
#include <dolphin/card/CARDWrite.h>

#define CARD_ATTR_PUBLIC  0x04u
#define CARD_ATTR_NO_COPY 0x08u
#define CARD_ATTR_NO_MOVE 0x10u
#define CARD_ATTR_GLOBAL  0x20u
#define CARD_ATTR_COMPANY 0x40u

#define CARD_FAT_AVAIL 0x0000u
#define CARD_FAT_CHECKSUM 0x0000u
#define CARD_FAT_CHECKSUMINV 0x0001u
#define CARD_FAT_CHECKCODE 0x0002u
#define CARD_FAT_FREEBLOCKS 0x0003u
#define CARD_FAT_LASTSLOT 0x0004u

#define CARD_WORKAREA_SIZE (5 * 8 * 1024)

#define CARD_SEG_SIZE 0x200u
#define CARD_PAGE_SIZE 0x80u
#define CARD_MAX_SIZE 0x01000000U

#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)

#define CARD_MAX_MOUNT_STEP (CARD_NUM_SYSTEM_BLOCK + 2)

#define CARD_STAT_SPEED_END 0
#define CARD_STAT_SPEED_FAST 1
#define CARD_STAT_SPEED_MIDDLE 2
#define CARD_STAT_SPEED_SLOW 3
#define CARD_STAT_SPEED_MASK 3

#define CARD_RESULT_UNLOCKED       1
#define CARD_RESULT_READY          0
#define CARD_RESULT_BUSY          -1
#define CARD_RESULT_WRONGDEVICE   -2
#define CARD_RESULT_NOCARD        -3
#define CARD_RESULT_NOFILE        -4
#define CARD_RESULT_IOERROR       -5
#define CARD_RESULT_BROKEN        -6
#define CARD_RESULT_EXIST         -7
#define CARD_RESULT_NOENT         -8
#define CARD_RESULT_INSSPACE      -9
#define CARD_RESULT_NOPERM       -10
#define CARD_RESULT_LIMIT        -11
#define CARD_RESULT_NAMETOOLONG  -12
#define CARD_RESULT_ENCODING     -13
#define CARD_RESULT_CANCELED     -14
#define CARD_RESULT_FATAL_ERROR -128

#define CARDIsValidBlockNo(card, blockNo) ((blockNo) >= CARD_NUM_SYSTEM_BLOCK && (blockNo) < (card)->cBlock)

#define CARD_READ_SIZE 512
#define CARD_COMMENT_SIZE 64

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

#define CARDGetBannerFormat(stat) (((stat)->bannerFormat) & CARD_STAT_BANNER_MASK)
#define CARDGetIconFormat(stat, n) (((stat)->iconFormat >> (2 * (n))) & CARD_STAT_ICON_MASK)
#define CARDGetDirCheck(dir) ((CARDDirCheck *)&(dir)[CARD_MAX_FILE])

void CARDInit(void);
s32 CARDGetResultCode(s32 chan);
s32 CARDCheckAsync(s32 chan, CARDCallback callback);
s32 CARDFreeBlocks(s32 chan, s32 *byteNotUsed, s32 *filesNotUsed);
s32 CARDRenameAsync(s32 chan, const char *oldName, const char *newName, CARDCallback callback);

#ifdef __cplusplus
}
#endif

#endif
