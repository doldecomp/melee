#ifndef DOLPHIN_GX_GXTRANSFORM_H
#define DOLPHIN_GX_GXTRANSFORM_H

#include <platform.h>
#include <placeholder.h>

#include <dolphin/mtx.h>

void GXProject(f32 x, // model coordinates
               f32 y, f32 z,
               Mtx mtx, // model-view matrix
               f32* pm, // projection matrix, as returned by GXGetProjectionv
               f32* vp, // viewport, as returned by GXGetViewportv
               f32* sx, // screen coordinates
               f32* sy, f32* sz);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz,
                         f32 farz, u32 field);
void GXSetViewport(f32, f32, f32, f32, f32, f32);
void GXLoadTexMtxImm(void* arg0, u32 arg1, s32 arg2);
void GXSetCurrentMtx(s32 arg0);
void GXLoadNrmMtxImm(UNK_T, s32);
void GXLoadPosMtxImm(UNK_T, s32);
void GXSetScissor(s32 left, s32 top, s32 width, s32 height);
void GXSetScissorBoxOffset(u32 x_off, u32 y_off);
void GXGetProjectionv(f32* proj);
void GXGetViewportv(f32* viewport_v);
void GXSetProjection(Mtx44 proj, s32 projection_type);
void WriteMTXPS4x3(float* src, float* dst);
void WriteMTXPS3x3from3x4(float* src, float* dst);
void WriteMTXPS4x2(float* src, float* dst);
void __GXSetMatrixIndex(s32);
void GXSetClipMode(s32);

#endif
