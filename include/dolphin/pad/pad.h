#ifndef DOLPHIN_PAD_PAD_H
#define DOLPHIN_PAD_PAD_H

#include <dolphin/types.h>

typedef struct PADStatus
{
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerLeft;
    u8 triggerRight;
    u8 analogA;
    u8 analogB;
    s8 err;
} PADStatus;

void PADControlMotor(int chan, u32 command);
void SISetSamplingRate(u32 rate);
void VISetBlack(BOOL);
u32 VIGetRetraceCount();
void PADClamp(u8 *);
void PADRead(u8 *);
void PADReset(u32);

#endif
