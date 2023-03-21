#ifndef DOLPHIN_CARD_FORWARD_H
#define DOLPHIN_CARD_FORWARD_H

#include <dolphin/os/forward.h>

#include <platform.h>

typedef struct CARDFileInfo CARDFileInfo;
typedef struct CARDStat CARDStat;

typedef void (*CARDCallback)(EXIChannel chan, s32 result);

#endif
