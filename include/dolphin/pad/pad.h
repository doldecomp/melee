#ifndef _PAD_H_
#define _PAD_H_

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
void func_80350100(BOOL);
u32 func_8035017C();
void PADClamp(u8 *);
void PADRead(u8 *);
void PADReset(u32);

#endif
