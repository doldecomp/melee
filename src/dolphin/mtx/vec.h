#ifndef DOLPHIN_MTX_VEC_H
#define DOLPHIN_MTX_VEC_H

#include <dolphin/mtx/types.h>

void PSVECAdd(Vec3* a, Vec3* b, Vec3* result);
void PSVECScale(Vec3* src, Vec3* dst, f32 scale);
f32 PSVECMag(Vec3* v);
f32 PSVECDotProduct(Vec3* a, Vec3* b);

#endif
