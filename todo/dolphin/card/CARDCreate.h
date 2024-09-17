#ifndef DOLPHIN_CARD_CARDCREATE_H
#define DOLPHIN_CARD_CARDCREATE_H

#include <platform.h>

#include <dolphin/card/forward.h>

s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size,
                    CARDFileInfo* fileInfo, CARDCallback callback);
void CreateCallbackFat(s32 chan, s32 result);

#endif
