#ifndef _mtx_h_
#define _mtx_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>
#include <sysdolphin/baselib/objalloc.h>

HSD_ObjAllocData* HSD_VecGetAllocData(void);
HSD_ObjAllocData* HSD_MtxGetAllocData(void);

void func_80379310(Mtx, Mtx);
void HSD_MtxInverseConcat(Mtx, Mtx, Mtx);
void func_80379A20(Mtx, Mtx);

#define FABSF(x) *(u32*)&x &= ~0x80000000;

#endif
