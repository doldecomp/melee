#ifndef DOLPHIN_GX_GXTEXTURE_H
#define DOLPHIN_GX_GXTEXTURE_H

#include <dolphin/gx/forward.h>
#include <Runtime/platform.h>

void __GXSetSUTexSize(void);
void GXLoadTexObjPreLoaded(unk_t, unk_t, s32);

void GXInvalidateTexAll(GXContext*, s32, u8*);
GXTexRegionCallback GXSetTlutRegionCallback(GXTexRegionCallback arg0);
void __SetSURegs(s32, s32);
void GXInitTexObj(unk_t, u32, u16, u16, s32, s32, s32, s8);
s32 GXGetTexObjWidth(GXTexObj* tex_obj);
s32 GXGetTexObjHeight(GXTexObj* tex_obj);
GXTexFmt GXGetTexObjFmt(GXTexObj* tex_obj);
void GXLoadTexObj(unk_t arg0, s32 arg1);
void GXInitTlutRegion(s32* arg0, s32 arg1, s32 arg2);
s32 GXGetTexBufferSize(u16, u16, u32, u8, u8);
void GXInitTexObjCI(unk_t, s32, u16, u16, s32, s32, s32, s8);
void GXInitTexObjLOD(unk_t, s32, s32, s32, s8, s32, f32, f32, f32);
void GXInitTlutObj(unk_t, u32, s32, u16);
void GXLoadTlut(unk_t, s32);
void __GXSetTmemConfig(s32);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback arg0);
void GXInitTexCacheRegion(unk_t, s8, u32, s32, u32, s32, s32);
void __GetImageTileCount(u32, s16, s16, s32*, s32*, s32*);
#endif
