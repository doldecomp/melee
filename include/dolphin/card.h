#ifndef DOLPHIN_CARD_H
#define DOLPHIN_CARD_H

#include <dolphin/dsp/dsp.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSThread.h>

#define CARD_FAT_FREEBLOCKS 0x0003U

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
#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)

#define CARD_FILENAME_MAX 32
#define CARD_MAX_FILE 127
#define CARD_MAX_MOUNT_STEP (CARD_NUM_SYSTEM_BLOCK + 2)

typedef void (*CARDCallback)(s32 chan, s32 result);

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;

    s32 offset;
    s32 length;
    u16 iBlock;
    u16 __padding;
} CARDFileInfo;

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

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u16 size;
    u16 pageSize;
    s32 sectorSize;
    u16 cBlock;
    u16 vendorID;
    s32 latency;
    u8 id[12];
    int mountStep;
    int formatStep;
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
    s32 xferred;
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

s32 CARDClose(void*);
s32 CARDOpen(s32, s32, void*);
s32 CARDWrite(void*, u8*, u32, s32);
s32 CARDRead(void*, u8*, u32, s32);
s32 CARDFastOpen(s32, s32, void*);
s32 __CARDReadStatus(s32 chan, u8* status);
s32 __CARDClearStatus(s32 chan);
s32 Retry(s32 chan);
void* __CARDGetDirBlock(CARDControl*);
void* __CARDGetFatBlock(CARDControl*);


#endif
