#ifndef DOLPHIN_MTX_VEC_H
#define DOLPHIN_MTX_VEC_H

#include <platform.h>

#include <dolphin/mtx/types.h>

#define VEC2_SQ_LEN(v) ((SQ((v).x) + SQ((v).y)))
#define VEC3_SQ_LEN(v) ((SQ((v).x) + SQ((v).y) + SQ((v).z)))

#define VECCrossProduct PSVECCrossProduct
#define VECSubtract PSVECSubtract
#define VECNormalize PSVECNormalize
#define VECAdd PSVECAdd
#define VECScale PSVECScale
#define VECMag PSVECMag
#define VECDotProduct PSVECDotProduct

void PSVECCrossProduct(Vec3* a, Vec3* b, Vec3* axb);
void PSVECSubtract(Vec3 const* a, Vec3 const* b, Vec3* ab);
void PSVECNormalize(Vec3* a, Vec3* b);
void PSVECAdd(Vec3* a, Vec3* b, Vec3* result);
void PSVECScale(Vec3* src, Vec3* dst, float scale);
float PSVECMag(Vec3* v);
float PSVECDotProduct(Vec3* a, Vec3* b);

#endif
