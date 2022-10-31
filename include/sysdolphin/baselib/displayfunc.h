#ifndef _displayfunc_c_
#define _displayfunc_c_

#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/objalloc.h>

void _HSD_DispForgetMemory();
void HSD_ZListInitAllocData(void);
void HSD_EraseRect(f32 top_res, f32 bottom_res, f32 left_res, f32 right_res, f32 neg_z_val, BOOL enable_color, BOOL enable_alpha, BOOL enable_depth);

#endif
