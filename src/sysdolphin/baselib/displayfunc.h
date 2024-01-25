#ifndef INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H
#define INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H

#include <platform.h>
#include "baselib/forward.h"
#include <dolphin/mtx/forward.h>

#include "baselib/jobj.h"
#include "baselib/objalloc.h"

void _HSD_DispForgetMemory(void* low, void* high);
void HSD_ZListInitAllocData(void);

void HSD_EraseRect(f32 top_res, f32 bottom_res, f32 left_res, f32 right_res,
                   f32 neg_z_val, bool enable_color, bool enable_alpha,
                   bool enable_depth);

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);
void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr, u32 flags, u32 rendermode);

void HSD_StateInitDirect(int vtxfmt, u32 param_2);

void _HSD_ZListSort(void);
void _HSD_ZListDisp(void);
void _HSD_ZListClear(void);

void HSD_SetEraseColor(int, int, int, int);

#endif
