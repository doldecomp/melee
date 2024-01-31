#ifndef DOLPHIN_CARD_FORWARD_H
#define DOLPHIN_CARD_FORWARD_H

#include <platform.h>

#include <dolphin/os.h>
#include <dolphin/os/OSExi.h>

typedef struct CARDFileInfo CARDFileInfo;
typedef struct CARDStat CARDStat;

typedef void (*CARDCallback)(EXIChannel chan, s32 result);

#endif
