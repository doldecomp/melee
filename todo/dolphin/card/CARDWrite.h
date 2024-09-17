#ifndef DOLPHIN_CARD_CARDWRITE_H
#define DOLPHIN_CARD_CARDWRITE_H

#include <platform.h>

#include <dolphin/card/forward.h>

s32 CARDWriteAsync(CARDFileInfo* fileInfo, const void* buf, u32 length,
                   s32 offset, CARDCallback callback);

#endif
