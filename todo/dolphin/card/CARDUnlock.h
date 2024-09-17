#ifndef DOLPHIN_CARD_CARDUNLOCK_H
#define DOLPHIN_CARD_CARDUNLOCK_H

#include <platform.h>

s32 __CARDUnlock(s32 chan, u8 flashID[12]);

s32 DummyLen(void);
u32 bitrev(u32 data);
s32 ReadArrayUnlock(s32 chan, u32 data, void* rbuf, s32 rlen, s32 mode);

#endif
