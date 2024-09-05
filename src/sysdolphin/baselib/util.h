#ifndef _UTIL_H_
#define _UTIL_H_

#include <platform.h>
#include <dolphin/gx/forward.h>

#include <dolphin/mtx/vec.h>

// functions
void HSD_MulColor(GXColor* arg0, GXColor* arg1, GXColor* dest);
u32 HSD_GetNbBits(u32 arg0);
s32 HSD_Index2PosNrmMtx(u32 arg0);

// variables
extern float HSD_identityMtx[];

#define FLT_MIN 1.17549435e-38f

static inline float fabsf(float x)
{
    *(u32*) &x &= 0x7FFFFFFF;
    return x;
}

static inline int vec_normalize_check(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (fabsf(src->x) <= FLT_MIN && fabsf(src->y) <= FLT_MIN &&
        fabsf(src->z) <= FLT_MIN)
    {
        return -1;
    } else {
        PSVECNormalize(src, dst);
        return 0;
    }
}

#endif // _UTIL_H_
