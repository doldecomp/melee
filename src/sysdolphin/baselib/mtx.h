#ifndef _mtx_h_
#define _mtx_h_

#include <platform.h>

#include "baselib/objalloc.h"

#include <dolphin/mtx.h>
#include <MSL/math.h>
#include <MSL/math_ppc.h>

#define VEC2_SQ_LEN(v) ((SQ((v).x) + SQ((v).y)))
#define VEC3_SQ_LEN(v) ((SQ((v).x) + SQ((v).y) + SQ((v).z)))

typedef Vec3 VecMtx[4];
typedef Vec3* VecMtxPtr;

void HSD_MtxInverse(Mtx src, Mtx dest);
void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest);
void HSD_MtxInverseTranspose(Mtx src, Mtx dest);
void HSD_MtxGetRotation(Mtx m, Vec3* vec);
void HSD_MtxGetTranslate(Mtx mat, Vec3* vec);
void HSD_MtxGetScale(Mtx arg0, Vec3* arg1);
void HSD_MkRotationMtx(Mtx arg0, Vec3* arg1);
void HSD_Mtx_8037A230(Mtx arg0, Quaternion* arg1);
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

static inline void HSD_MtxColVec(MtxPtr mtx, int col, Vec3* vec)
{
    vec->x = mtx[0][col];
    vec->y = mtx[1][col];
    vec->z = mtx[2][col];
}

static inline void HSD_MtxSetColVec(MtxPtr mtx, int col, Vec3* vec)
{
    mtx[0][col] = vec->x;
    mtx[1][col] = vec->y;
    mtx[2][col] = vec->z;
}

static inline f32 HSD_MtxColMag(MtxPtr mtx, int col)
{
    return sqrtf__Ff((mtx[0][col] * mtx[0][col]) +
                     (mtx[1][col] * mtx[1][col]) +
                     (mtx[2][col] * mtx[2][col]));
}

static inline f32 HSD_MtxColMagFloat(MtxPtr mtx, int col)
{
    return sqrtf((mtx[0][col] * mtx[0][col]) + (mtx[1][col] * mtx[1][col]) +
                 (mtx[2][col] * mtx[2][col]));
}

#endif
