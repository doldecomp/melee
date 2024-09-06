#ifndef _UTIL_H_
#define _UTIL_H_

#include <platform.h>
#include <dolphin/gx/forward.h>

#include "mtx.h"

#include <dolphin/mtx/vec.h>

// functions
void HSD_MulColor(GXColor* arg0, GXColor* arg1, GXColor* dest);
u32 HSD_GetNbBits(u32 arg0);
s32 HSD_Index2PosNrmMtx(u32 arg0);

// variables
extern float HSD_identityMtx[];

#define FLT_MIN 1.17549435e-38f

static inline int vec_normalize_check(Vec3* src, Vec3* dst)
{
    if (!src || !dst) {
        return -1;
    }
    if (fabsf_bitwise(src->x) <= FLT_MIN && fabsf_bitwise(src->y) <= FLT_MIN &&
        fabsf_bitwise(src->z) <= FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

#endif // _UTIL_H_
