#ifndef _mtx_h_
#define _mtx_h_

#include <math.h>
#include <sysdolphin/baselib/objalloc.h>
#include <melee/lb/lbrefract.h>

void HSD_MtxInverse(Mtx src, Mtx dest);
void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest);
void HSD_MtxInverseTranspose(Mtx src, Mtx dest);
void HSD_MtxGetRotation(Mtx m, Vec3* vec);
void HSD_MtxGetTranslate(Mtx mat, Vec3* vec);
void HSD_MtxGetScale(Mtx arg0, Vec3* arg1);
void HSD_MkRotationMtx(Mtx arg0, Vec3* arg1);
void func_8037A230(Mtx arg0, Quaternion* arg1);
void HSD_MtxSRT(Mtx m, Vec3* vec1, Vec3* vec2, Vec3* vec3, Vec3* vec4);
void HSD_MtxSRTQuat(Mtx arg0, Vec3* arg1, Quaternion* arg2, Vec3* arg3,
                    Vec3* arg4);
void HSD_MtxScaledAdd(Mtx arg0, Mtx arg1, Mtx arg2, f32 arg3);
void* HSD_VecAlloc(void);
void HSD_VecFree(void* arg0);
void* HSD_MtxAlloc(void);
void HSD_MtxFree(void* arg0);
HSD_ObjAllocData* HSD_VecGetAllocData(void);
void HSD_VecInitAllocData(void);
HSD_ObjAllocData* HSD_MtxGetAllocData(void);
void HSD_MtxInitAllocData(void);

static inline f32 fabsf_bitwise(f32 v)
{
    *(u32*) &v &= ~0x80000000;
    return v;
}

#endif
