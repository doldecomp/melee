#ifndef _vi_h_
#define _vi_h_

#include <platform.h>

#include <placeholder.h>

#define VIPadFrameBufferWidth(width) ((u16) (((u16) (width) + 15) & ~15))

s32 VIGetTvFormat(void);
void VIConfigure(s32);
void VIFlush(void);
void VISetNextFrameBuffer(void*);
void VIWaitForRetrace(void);
void VIInit(void);
u32 VIGetNextField(void);

#endif
