#ifndef DOLPHIN_GX_GXTEXTURE_H
#define DOLPHIN_GX_GXTEXTURE_H

#include <platform.h>
#include <placeholder.h>

#include <dolphin/gx.h>
#include <dolphin/gx/GXEnum.h>

void __GXSetSUTexSize(void);
void GXLoadTexObjPreLoaded(const GXTexObj*, UNK_T, GXTexMapID);

void GXInvalidateTexAll(void);
GXTexRegionCallback GXSetTlutRegionCallback(GXTexRegionCallback arg0);
void __SetSURegs(s32, s32);
void GXInitTexObj(GXTexObj*, void*, u16, u16, GXTexFmt, GXTexWrapMode,
                  GXTexWrapMode, GXBool);
s32 GXGetTexObjWidth(GXTexObj* tex_obj);
s32 GXGetTexObjHeight(GXTexObj* tex_obj);
GXTexFmt GXGetTexObjFmt(GXTexObj* tex_obj);
void GXLoadTexObj(const GXTexObj*, GXTexMapID);
void GXInitTlutRegion(s32* arg0, s32 arg1, s32 arg2);
s32 GXGetTexBufferSize(u16, u16, u32, u8, u8);
void GXInitTexObjCI(GXTexObj*, void*, u16, u16, GXCITexFmt, GXTexWrapMode,
                    GXTexWrapMode, GXBool, u32);
void GXInitTexObjLOD(GXTexObj*, GXTexFilter, GXTexFilter, f32, f32, f32,
                     GXBool, GXBool, GXAnisotropy);
void GXInitTlutObj(GXTlutObj*, void*, GXTlutFmt, u16);
void GXLoadTlut(GXTlutObj*, s32);
void __GXSetTmemConfig(s32);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback arg0);
void GXInitTexCacheRegion(UNK_T, s8, u32, s32, u32, s32, s32);
void __GetImageTileCount(u32, s16, s16, s32*, s32*, s32*);
#endif
