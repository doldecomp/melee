#ifndef INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H
#define INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H

#include <platform.h>
#include "baselib/forward.h"
#include <dolphin/mtx/forward.h>

#include "baselib/jobj.h"
#include "baselib/objalloc.h"

#define DOBJ_TRSP_SHIFT 1
#define JOBJ_TRSP_SHIFT 18

#define JOBJ_OPA 0x40000
#define JOBJ_XLU 0x80000
#define JOBJ_TEXEDGE 0x100000

void _HSD_DispForgetMemory(void* lo, void* hi);
void HSD_ZListInitAllocData(void);

void HSD_EraseRect(f32 top_res, f32 bottom_res, f32 left_res, f32 right_res,
                   f32 neg_z_val, int enable_color, int enable_alpha,
                   int enable_depth);

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);
void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr, HSD_TrspMask flags, u32 rendermode);

void HSD_StateInitDirect(int vtxfmt, u32 rendermode);

void _HSD_ZListSort(void);
void _HSD_ZListDisp(void);
void _HSD_ZListClear(void);

void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*));

void HSD_SetEraseColor(u8 r, u8 g, u8 b, u8 a);

#endif
