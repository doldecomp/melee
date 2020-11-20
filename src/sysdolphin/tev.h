#ifndef _tev_h_
#define _tev_h_

#include "global.h"

void HSD_RenderInitAllocData(void);
void* HSD_RenderGetAllocData(void);
void* HSD_TevRegGetAllocData(void);
void* HSD_ChanGetAllocData(void);
void HSD_SetupChannel(void* ch);

#endif
