#ifndef _PAD_H_
#define _PAD_H_

#include <platform.h>

#include <dolphin/pad/forward.h>

#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>

#define PAD_CHAN0 0
#define PAD_CHAN1 1
#define PAD_CHAN2 2
#define PAD_CHAN3 3
#define PAD_CHANMAX 4

#define PAD_CHAN0_BIT 0x80000000
#define PAD_CHAN1_BIT 0x40000000
#define PAD_CHAN2_BIT 0x20000000
#define PAD_CHAN3_BIT 0x10000000

#define PAD_ERR_NO_CONTROLLER -1
#define PAD_ERR_NONE 0

#define PAD_SPEC_2 2

struct PADStatus {
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
};

extern u32 __PADFixBits;

void PADControlMotor(int chan, u32 command);
void VISetBlack(bool);
u32 VIGetRetraceCount(void);
void PADClamp(PADStatus*);
void PADRead(PADStatus*);
void PADReset(u32);
void PADTypeAndStatusCallback(s32 chan, u32 type);
void PADSetSpec(s32);
void PADInit(void);
bool __PADDisableRecalibration(bool);
void PADRecalibrate(s32);

void PADOriginCallback(s32 unused0, s32 arg1);
void PADOriginUpdateCallback(s32 chan, u32 error, OSContext* context);
void PADProbeCallback(s32 chan, u32 error, OSContext* context);
void UpdateOrigin(s32 arg0);

#endif
