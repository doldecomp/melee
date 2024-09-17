#ifndef DOLPHIN_CARD_CARDBLOCK_H
#define DOLPHIN_CARD_CARDBLOCK_H

#include <platform.h>

#include <dolphin/card/forward.h>

#include <dolphin/card.h>

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback);

s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback);
s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);

#endif
