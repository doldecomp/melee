#ifndef DOLPHIN_MTX_VEC_H
#define DOLPHIN_MTX_VEC_H

#include <platform.h>

#include <dolphin/mtx/types.h>

#define VEC2_DOT(v) ((SQ((v).x) + SQ((v).y)))
#define VEC3_DOT(v) ((SQ((v).x) + SQ((v).y) + SQ((v).z)))

void PSVECAdd(Vec3* a, Vec3* b, Vec3* result);
void PSVECScale(Vec3* src, Vec3* dst, float scale);
float PSVECMag(Vec3* v);
float PSVECDotProduct(Vec3* a, Vec3* b);

#endif
