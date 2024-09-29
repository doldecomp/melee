#ifndef DOLPHIN_CARD_CARDMOUNT_H
#define DOLPHIN_CARD_CARDMOUNT_H

#include <platform.h>

#include <dolphin/card/forward.h>

#include <dolphin/os.h>
#include <dolphin/os/OSExi.h>

s32 CARDUnmount(s32 chan);
void __CARDMountCallback(s32 chan, s32 result);

s32 CARDProbe(EXIChannel chan);
s32 CARDProbeEx(EXIChannel chan, s32* memSize, s32* sectorSize);
s32 DoMount(EXIChannel chan);
s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback,
                   CARDCallback attachCallback);

#endif
