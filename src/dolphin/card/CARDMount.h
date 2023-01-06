#ifndef DOLPHIN_CARD_CARDMOUNT_H
#define DOLPHIN_CARD_CARDMOUNT_H

#include <dolphin/types.h>

s32 CARDUnmount(s32 chan);
void __CARDMountCallback(s32 chan, s32 result);

#endif
