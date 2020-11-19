#ifndef _initialize_h_
#define _initialize_h_

#include "global.h"

typedef struct _HSD_MemReport
{
    u32 total;
    u32 system;
    u32 xfb;
    u32 gxfifo;
    u32 heap;
} HSD_MemReport;

void HSD_InitComponent(void);
void HSD_GXSetFifoObj(GXFifoObj* fifo);
void HSD_DVDInit(void);

#endif
