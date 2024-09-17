#ifndef DOLPHIN_CARD_CARDRDWR_H
#define DOLPHIN_CARD_CARDRDWR_H

#include <platform.h>

#include <dolphin/card/forward.h>

#include <dolphin/card.h>

s32 __CARDWrite(s32 chan, u32 addr, u32 length, void* dst,
                CARDCallback callback);

s32 __CARDRead(s32 chan, u32 addr, u32 length, void* dst,
               CARDCallback callback);

u32 CARDGetXferredBytes(s32 chan);

#endif
