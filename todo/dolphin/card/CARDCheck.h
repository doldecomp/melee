#ifndef DOLPHIN_CARD_CARDCHECK_H
#define DOLPHIN_CARD_CARDCHECK_H

#include <platform.h>

#include <dolphin/card/forward.h>

#include <dolphin/card.h>

void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv);
s32 __CARDVerify(CARDControl* card);

void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv);
s32 __CARDVerify(CARDControl* card);
s32 CARDCheckExAsync(s32 chan, s32* xferBytes, CARDCallback callback);
s32 CARDCheckAsync(s32 chan, CARDCallback callback);

#endif
