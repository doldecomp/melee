#ifndef DOLPHIN_OS_OSRTC
#define DOLPHIN_OS_OSRTC

#include <dolphin/types.h>

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

typedef struct OSSramEx {
    u8 flashID[2][12];
    u32 wirelessKeyboardID;
    u16 wirelessPadID[4];
    u8 dvdErrorCode;
    u8 _padding0;
    u8 flashIDCheckSum[2];
    u16 gbs;
    u8 _padding1[2];
} OSSramEx;

OSSram* __OSLockSram(void);
OSSramEx* __OSLockSramEx(void);
void __OSUnlockSram(BOOL commit);
void __OSUnlockSramEx(BOOL commit);
BOOL __OSSyncSram(void);
u32 OSGetWirelessID(u32 chan);
void OSSetWirelessID(u32 chan, u16 id);

#endif // DOLPHIN_OS_OSRTC
