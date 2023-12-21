#ifndef _vi_h_
#define _vi_h_

#include <platform.h>

#include <placeholder.h>

#define VIPadFrameBufferWidth(width) ((u16) (((u16) (width) + 15) & ~15))

#define VI_NTSC 0
#define VI_PAL 1
#define VI_MPAL 2
#define VI_DEBUG 3
#define VI_DEBUG_PAL 4
#define VI_EURGB60 5

u32 VIGetTvFormat(void);
void VIConfigure(s32);
void VIFlush(void);
void VISetNextFrameBuffer(void*);
void VIWaitForRetrace(void);
void VIInit(void);
u32 VIGetNextField(void);

#endif
