#ifndef DOLPHIN_CARD_CARDREAD_H
#define DOLPHIN_CARD_CARDREAD_H

#include <platform.h>

#include <dolphin/card/forward.h>

#include <dolphin/card.h>

s32 __CARDSeek(CARDFileInfo* fileInfo, s32 length, s32 offset,
               CARDControl** pcard);
s32 CARDReadAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset,
                  CARDCallback callback);

#endif
