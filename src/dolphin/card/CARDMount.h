#ifndef DOLPHIN_CARD_CARDMOUNT_H
#define DOLPHIN_CARD_CARDMOUNT_H

#include <Runtime/platform.h>

s32 CARDUnmount(s32 chan);
void __CARDMountCallback(s32 chan, s32 result);

#endif
