#ifndef DOLPHIN_CARD_CARDRENAME_H
#define DOLPHIN_CARD_CARDRENAME_H

#include <dolphin/card/forward.h>
#include <Runtime/platform.h>

s32 CARDRenameAsync(s32 chan, const char* old, const char* new,
                    CARDCallback callback);

#endif
