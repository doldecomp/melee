#ifndef DOLPHIN_CARD_CARDDELETE_H
#define DOLPHIN_CARD_CARDDELETE_H

#include <platform.h>

#include <dolphin/card/forward.h>

s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback);
s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback);

#endif
