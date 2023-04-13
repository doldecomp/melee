#ifndef DOLPHIN_CARD_CARDSTAT_H
#define DOLPHIN_CARD_CARDSTAT_H

#include <dolphin/card/forward.h>

#include <Runtime/platform.h>

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* stat);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat* stat,
                       CARDCallback callback);

#endif
