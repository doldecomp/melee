#ifndef _tev_h_
#define _tev_h_

#include <baselib/objalloc.h>
#include <baselib/texp.h>

void HSD_RenderInitAllocData(void);
HSD_ObjAllocData* HSD_RenderGetAllocData(void);
HSD_ObjAllocData* HSD_TevRegGetAllocData(void);
HSD_ObjAllocData* HSD_ChanGetAllocData(void);
void HSD_SetupChannel(void* ch);
void HSD_StateSetNumChans(s32 num);
void HSD_StateInitTev(void);

void HSD_SetupTevStage(HSD_TevDesc*);
void HSD_SetTevRegAll(void);
int HSD_StateGetNumTevStages(void);
int HSD_StateAssignTev(void);
void HSD_StateSetNumTevStages(void);
void HSD_StateSetNumTexGens(void);
void _HSD_StateInvalidateColorChannel(void);
void _HSD_StateInvalidateTevStage(void);
void _HSD_StateInvalidateTevRegister(void);
void _HSD_StateInvalidateTexCoordGen(void);

#endif
