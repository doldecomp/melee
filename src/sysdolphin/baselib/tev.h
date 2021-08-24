#ifndef _tev_h_
#define _tev_h_

#include "global.h"

#include "objalloc.h"

void HSD_RenderInitAllocData(void);
HSD_ObjAllocData* HSD_RenderGetAllocData(void);
HSD_ObjAllocData* HSD_TevRegGetAllocData(void);
HSD_ObjAllocData* HSD_ChanGetAllocData(void);
void HSD_SetupChannel(void* ch);
void HSD_StateSetNumChans(s32 num);

#endif
