#ifndef DOLPHIN_GX_GXTRANSFORM_H
#define DOLPHIN_GX_GXTRANSFORM_H

#include <dolphin/mtx/mtxtypes.h>

void GXProject(f32 x, // model coordinates
               f32 y, f32 z,
               Mtx mtx, // model-view matrix
               f32* pm, // projection matrix, as returned by GXGetProjectionv
               f32* vp, // viewport, as returned by GXGetViewportv
               f32* sx, // screen coordinates
               f32* sy, f32* sz);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz,
                         u32 field);
void GXSetViewport(f32, f32, f32, f32, f32, f32);
void GXLoadTexMtxImm(void* arg0, u32 arg1, s32 arg2);
void GXSetCurrentMtx(s32 arg0);
void GXLoadNrmMtxImm(unk_t, s32);
void GXLoadPosMtxImm(unk_t, s32);
void GXSetScissor(s32 left, s32 top, s32 width, s32 height);
void GXSetScissorBoxOffset(u32 x_off, u32 y_off);

#endif
