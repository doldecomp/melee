#ifndef DOLPHIN_CARD_CARDSTAT_H
#define DOLPHIN_CARD_CARDSTAT_H

#include <platform.h>

#include <dolphin/card/forward.h>

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* stat);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat* stat,
                       CARDCallback callback);

#endif
