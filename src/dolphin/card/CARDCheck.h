#ifndef DOLPHIN_CARD_CARDCHECK_H
#define DOLPHIN_CARD_CARDCHECK_H

#include <dolphin/types.h>

void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv);

#endif
