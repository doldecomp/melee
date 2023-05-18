#ifndef DOLPHIN_GX_GXATTR_H
#define DOLPHIN_GX_GXATTR_H

#include <platform.h>

void GXSetNumTexGens(u8 arg0);
void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);
void GXInvalidateVtxCache(void);
void GXSetArray(s32, s32, u8);
void GXSetVtxAttrFmt(u32, u32, s32, u32, u8);
void GXClearVtxDesc(void);
void GXSetVtxDesc(s32, s32);
void __GXSetVCD(void);
void __GXSetVAT(void);
void __GXSetVCD(void);
void GXClearVtxDesc(void);
void __GXXfVtxSpecs(void);
void __GXSetVAT(void);
void GXInvalidateVtxCache(void);

#endif
