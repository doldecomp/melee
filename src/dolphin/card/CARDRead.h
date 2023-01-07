#ifndef DOLPHIN_CARD_CARDREAD_H
#define DOLPHIN_CARD_CARDREAD_H

#include <dolphin/card.h>

s32 __CARDSeek(CARDFileInfo* fileInfo, s32 length, s32 offset,
               CARDControl** pcard);

#endif
