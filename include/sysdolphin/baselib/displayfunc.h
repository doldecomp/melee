#ifndef INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H
#define INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H

#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/objalloc.h>

void _HSD_DispForgetMemory(void);
void HSD_ZListInitAllocData(void);

void HSD_EraseRect(f32 top_res, f32 bottom_res, f32 left_res, f32 right_res,
                   f32 neg_z_val, BOOL enable_color, BOOL enable_alpha,
                   BOOL enable_depth);

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);

#endif
