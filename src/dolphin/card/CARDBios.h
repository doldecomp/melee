#ifndef DOLPHIN_CARD_CARDBIOS_H
#define DOLPHIN_CARD_CARDBIOS_H

#include <dolphin/card.h>
#include <dolphin/os/OSExi.h>

s32 __CARDEnableInterrupt(EXIChannel chan, bool enable);
s32 __CARDEraseSector(EXIChannel chan, u32 addr, CARDCallback callback);
s32 __CARDGetControlBlock(EXIChannel chan, CARDControl** pcard);
s32 __CARDPutControlBlock(struct CARDControl* card, s32 result);
s32 __CARDReadSegment(s32 chan, CARDCallback callback);
s32 __CARDSync(s32 i);
s32 __CARDWritePage(s32 chan, CARDCallback callback);
void __CARDExiHandler(EXIChannel chan, OSContext* context);
void __CARDExtHandler(EXIChannel chan, OSContext* context);
void CARDInit(void);
s32 __CARDStart(s32 chan, CARDCallback txCallback, CARDCallback exiCallback);
s32 CARDFreeBlocks(s32 chan, s32* byteNotUsed, s32* filesNotUsed);
s32 CARDGetResultCode(s32 chan);
s32 CARDGetSectorSize(s32 chan, u32* size);
void __CARDTxHandler(EXIChannel chan, OSContext* context);
void __CARDUnlockedHandler(EXIChannel chan, OSContext* context);

#endif
