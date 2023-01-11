#ifndef _vi_h_
#define _vi_h_

#include <Runtime/platform.h>

s32 VIGetTvFormat(void);
void VIConfigure(s32);
void VIFlush(void);
void VISetNextFrameBuffer(s32);
void VIWaitForRetrace(void);
void VIInit(void);

#endif
