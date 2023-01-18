#ifndef DOLPHIN_CARD_CARDFORMAT_H
#define DOLPHIN_CARD_CARDFORMAT_H

#include <dolphin/card/forward.h>
#include <Runtime/platform.h>

void FormatCallback(s32 chan, s32 result);
s32 CARDFormatAsync(s32 chan, CARDCallback callback);
s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback);

#endif
