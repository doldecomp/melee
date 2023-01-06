#ifndef _vi_h_
#define _vi_h_

#include <dolphin/types.h>

s32 VIGetTvFormat(void);
void VIConfigure(s32);
void VIFlush(void);
void VISetNextFrameBuffer(s32);
void VIWaitForRetrace(void);

#endif
