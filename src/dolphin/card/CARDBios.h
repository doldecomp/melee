#ifndef DOLPHIN_CARD_CARDBIOS_H
#define DOLPHIN_CARD_CARDBIOS_H

#include <dolphin/card.h>
#include <dolphin/os/OSExi.h>

s32 __CARDPutControlBlock(struct CARDControl* card, s32 result);
s32 __CARDEraseSector(EXIChannel chan, u32 addr, CARDCallback callback);
s32 __CARDGetControlBlock(EXIChannel chan, CARDControl** pcard);
s32 __CARDEnableInterrupt(EXIChannel chan, BOOL enable);
void __CARDExiHandler(EXIChannel chan, OSContext* context);
void __CARDExtHandler(EXIChannel chan, OSContext* context);
s32 __CARDReadSegment(s32 chan, CARDCallback callback);
s32 __CARDWritePage(s32 chan, CARDCallback callback);
s32 __CARDSync(s32 i);

#endif
