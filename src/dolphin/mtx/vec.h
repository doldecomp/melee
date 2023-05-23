#ifndef DOLPHIN_MTX_VEC_H
#define DOLPHIN_MTX_VEC_H

#include <platform.h>

#include <dolphin/mtx/types.h>

#define VEC2_SQ_MAG(v) ((SQ((v).x) + SQ((v).y)))
#define VEC3_SQ_MAG(v) ((SQ((v).x) + SQ((v).y) + SQ((v).z)))

void PSVECAdd(Vec3* a, Vec3* b, Vec3* result);
void PSVECScale(Vec3* src, Vec3* dst, f32 scale);
f32 PSVECMag(Vec3* v);
f32 PSVECDotProduct(Vec3* a, Vec3* b);

#endif
