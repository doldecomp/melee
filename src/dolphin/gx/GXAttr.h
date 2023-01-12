#ifndef DOLPHIN_GX_GXATTR_H
#define DOLPHIN_GX_GXATTR_H

#include <Runtime/platform.h>

void GXSetNumTexGens(s8);
void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);
void GXInvalidateVtxCache(void);
void GXSetArray(s32, s32, s8);
void GXSetVtxAttrFmt(s8 vertex_format, s32, s32, s32, s8);
void GXClearVtxDesc(void);
void GXSetVtxDesc(u32, s32);
void __GXSetVCD(void);
void __GXSetVAT(void);

#endif
