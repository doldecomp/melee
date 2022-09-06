#ifndef DOLPHIN_GX_GXTRANSFORM_H
#define DOLPHIN_GX_GXTRANSFORM_H

#include <dolphin/mtx/mtxtypes.h>

void GXProject(
    f32 x, // model coordinates
    f32 y,
    f32 z,
    MtxPtr mtx, // model-view matrix
    f32* pm,    // projection matrix, as returned by GXGetProjectionv
    f32* vp,    // viewport, as returned by GXGetViewportv
    f32* sx,    // screen coordinates
    f32* sy,
    f32* sz);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field);
void GXSetViewport(f32, f32, f32, f32, f32, f32);

#endif
