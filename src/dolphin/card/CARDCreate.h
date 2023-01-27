#ifndef DOLPHIN_CARD_CARDCREATE_H
#define DOLPHIN_CARD_CARDCREATE_H

#include <dolphin/card/forward.h>
#include <Runtime/platform.h>

s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size,
                    CARDFileInfo* fileInfo, CARDCallback callback);

#endif
