#ifndef __MTX_H__
#define __MTX_H__

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

void C_MTXOrtho( Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);

void PSVECCrossProduct(VecPtr a, VecPtr b, VecPtr axb);

#endif
