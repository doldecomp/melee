#ifndef _PAD_H_
#define _PAD_H_

#include <dolphin/types.h>

#define PAD_CHANMAX 4

#define PAD_ERR_NONE 0

#define PAD_SPEC_2 2

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
void PADClamp(PADStatus*);
void PADRead(u8 *);
void PADReset(u32);

#endif
