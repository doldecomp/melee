#ifndef _vi_h_
#define _vi_h_

#include <dolphin/types.h>

s32 VIGetTvFormat();
void VIConfigure(s32);
void VIFlush();
void VISetNextFrameBuffer(s32);
void VIWaitForRetrace(void);

#endif
