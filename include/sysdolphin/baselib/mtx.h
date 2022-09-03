#ifndef _mtx_h_
#define _mtx_h_

#include <global.h>
#include <sysdolphin/baselib/objalloc.h>
#include <math.h>

#include <melee/lb/lbrefract.h>

void func_80379310(Mtx src, Mtx dest);
void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest);
void func_80379A20(Mtx src, Mtx dest);
void HSD_MtxGetRotation(Mtx m, Vec* vec);
void HSD_MtxGetTranslate(Mtx mat, Vec* vec);
void HSD_MtxGetScale(Mtx arg0, Vec* arg1);
void HSD_MkRotationMtx(Mtx arg0, Vec* arg1);
void func_8037A230(Mtx arg0, Quaternion* arg1);
void HSD_MtxSRT(Mtx m, Vec* vec1, Vec* vec2, Vec* vec3, Vec* vec4);
void HSD_MtxSRTQuat(Mtx arg0, Vec* arg1, Quaternion* arg2, Vec* arg3, Vec* arg4);
void HSD_MtxScaledAdd(Mtx arg0, Mtx arg1, Mtx arg2, f32 arg3);
void* HSD_VecAlloc(void);
void HSD_VecFree(void* arg0);
void* HSD_MtxAlloc(void);
void HSD_MtxFree(void* arg0);
HSD_ObjAllocData* HSD_VecGetAllocData(void);
void HSD_VecInitAllocData(void);
HSD_ObjAllocData* HSD_MtxGetAllocData(void);
void HSD_MtxInitAllocData(void);

inline f32 fabsf_bitwise(f32 v)
{
    *(u32*)&v &= ~0x80000000;
    return v;
}

#endif
