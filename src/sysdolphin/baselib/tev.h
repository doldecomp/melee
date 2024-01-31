#ifndef _tev_h_
#define _tev_h_

#include <platform.h>

#include "baselib/objalloc.h"
#include "baselib/state.h"
#include "baselib/texp.h"

void HSD_RenderInitAllocData(void);
HSD_ObjAllocData* HSD_RenderGetAllocData(void);
HSD_ObjAllocData* HSD_TevRegGetAllocData(void);
HSD_ObjAllocData* HSD_ChanGetAllocData(void);
void HSD_SetupChannel(HSD_Chan*);
void HSD_StateSetNumChans(int num);
void HSD_SetupChannelAll(HSD_Chan*);
void HSD_StateRegisterTexGen(int);
void HSD_StateSetNumTexGens(void);
void HSD_StateInitTev(void);
int HSD_StateGetNumTevStages(void);
int HSD_StateAssignTev(void);
void HSD_StateSetNumTevStages(void);
void HSD_SetupTevStage(HSD_TevDesc*);
void HSD_SetupTevStageAll(HSD_TevDesc*);
int HSD_Channel2Num(int chan);
int HSD_Index2TevStage(int idx);
int HSD_TevStage2Index(int stage);
int HSD_TevStage2Num(int stage);
void HSD_SetTevRegAll(void);
void ChanUpdateFunc(HSD_Chan*, int, f32*);
void _HSD_StateInvalidateColorChannel(void);
void _HSD_StateInvalidateTevStage(void);
void _HSD_StateInvalidateTevRegister(void);
void _HSD_StateInvalidateTexCoordGen(void);

#endif
