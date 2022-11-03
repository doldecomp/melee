#ifndef DOLPHIN_MTX_VEC_H
#define DOLPHIN_MTX_VEC_H

#include <dolphin/mtx/types.h>

f32 PSVECDotProduct(VecPtr a, VecPtr b);
void PSVECAdd(Vec* a, Vec* b, Vec* result);
void PSVECScale(Vec* src, Vec* dst, f32 scale);
f32 PSVECMag(Vec* v);

#endif
