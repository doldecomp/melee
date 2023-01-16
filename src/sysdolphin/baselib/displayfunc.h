#ifndef INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H
#define INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H

#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/objalloc.h>

void _HSD_DispForgetMemory(any_t low, any_t high);
void HSD_ZListInitAllocData(void);

void HSD_EraseRect(f32 top_res, f32 bottom_res, f32 left_res, f32 right_res,
                   f32 neg_z_val, bool enable_color, bool enable_alpha,
                   bool enable_depth);

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);
void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr, u32 flags, u32 rendermode);

#endif
