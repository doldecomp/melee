#ifndef _DOLPHIN_CARD_INTERNAL_H_
#define _DOLPHIN_CARD_INTERNAL_H_

#include <dolphin/card.h>
#include <dolphin/exi.h>

// CARDStatEx.c
long __CARDGetStatusEx(long chan, long fileNo, struct CARDDir * dirent);
long __CARDSetStatusExAsync(long chan, long fileNo, struct CARDDir * dirent, void (* callback)(long, long));
long __CARDSetStatusEx(long chan, long fileNo, struct CARDDir * dirent);

// CARDUnlock.c
s32 __CARDUnlock(s32 chan, u8 flashID[12]);

// CARDRead.c
s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard);

// CARDRdwr.c
long __CARDRead(long chan, unsigned long addr, long length, void * dst, void (* callback)(long, long));
long __CARDWrite(long chan, unsigned long addr, long length, void * dst, void (* callback)(long, long));

// CARDRaw.c
long __CARDRawReadAsync(long chan, void * buf, long length, long offset, void (* callback)(long, long));
long __CARDRawRead(long chan, void * buf, long length, long offset);

// CARDOpen.c
BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName);
s32 __CARDAccess(CARDDir *ent);
s32 __CARDIsPublic(CARDDir *ent);
s32 __CARDGetFileNo(CARDControl* card, const char* fileName, s32* pfileNo);
BOOL __CARDIsOpened(CARDControl *card, s32 fileNo);

// CARDMount.c
void __CARDMountCallback(s32 chan, s32 result);

// CARDFormat.c
s32 CARDFormatAsync(s32 chan, CARDCallback callback);

// CARDDir.c
CARDDir *__CARDGetDirBlock(CARDControl* card);
s32 __CARDUpdateDir(s32 chan, CARDCallback callback);

// CARDCheck.c
void __CARDCheckSum(void *ptr, int length, u16 *checksum, u16 *checksumInv);
s32 __CARDVerify(CARDControl *card);

// CARDBlock.c
void *__CARDGetFatBlock(CARDControl *card);
s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback);
s32 __CARDUpdateFatBlock(s32 chan, u16 *fat, CARDCallback callback);

// CARDBios.c
extern struct CARDControl __CARDBlock[2];

extern DVDDiskID * __CARDDiskID;
extern DVDDiskID __CARDDiskNone;

void __CARDDefaultApiCallback(s32 chan, s32 result);
void __CARDSyncCallback(s32 chan, s32 result);
void __CARDExtHandler(s32 chan, OSContext *context);
void __CARDExiHandler(s32 chan, OSContext *context);
void __CARDTxHandler(s32 chan, OSContext *context);
void __CARDUnlockedHandler(s32 chan, OSContext *context);
int __CARDReadNintendoID(s32 chan, u32 *id);
s32 __CARDEnableInterrupt(s32 chan, BOOL enable);
s32 __CARDReadStatus(s32 chan, u8 *status);
s32 __CARDClearStatus(s32 chan);
long __CARDSleep(long chan);
long __CARDWakeup(long chan);
s32 __CARDReadSegment(s32 chan, CARDCallback callback);
s32 __CARDWritePage(s32 chan, CARDCallback callback);
long __CARDErase(long chan, void (* callback)(long, long));
s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
void __CARDSetDiskID(DVDDiskID *id);
s32 __CARDGetControlBlock(s32 chan, CARDControl **pcard);
s32 __CARDPutControlBlock(CARDControl *card, s32 result);
s32 __CARDSync(s32 chan);

#endif // _DOLPHIN_CARD_INTERNAL_H_
