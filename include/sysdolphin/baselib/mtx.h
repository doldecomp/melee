#ifndef _mtx_h_
#define _mtx_h_

#include <global.h>
#include <sysdolphin/baselib/objalloc.h>
#include <math.h>

#include <melee/lb/lbrefract.h>

void func_80379310(Mtx src, Mtx dest);
void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest);
void func_80379A20(Mtx src, Mtx dest);
void func_80379C24(Mtx m, Vec* vec);
void func_80379F6C(Mtx mat, Vec* vec);
void func_80379F88(Mtx arg0, Vec* arg1);
void func_8037A120(Mtx arg0, Vec* arg1);
void func_8037A230(Mtx arg0, Quaternion* arg1);
void func_8037A250(Mtx m, Vec* vec1, Vec* vec2, Vec* vec3, Vec* vec4);
void func_8037A43C(Mtx arg0, Vec* arg1, Quaternion* arg2, Vec* arg3, Vec* arg4);
void func_8037A54C(Mtx arg0, Mtx arg1, Mtx arg2, f32 arg3);
void* func_8037A610(void);
void func_8037A65C(void* arg0);
void* func_8037A68C(void);
void func_8037A6D8(void* arg0);
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
