#ifndef DOLPHIN_GX_GXATTR_H
#define DOLPHIN_GX_GXATTR_H

#include <platform.h>

#include <dolphin/gx/GXEnum.h>

void GXSetNumTexGens(u8 num);
void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);
void GXInvalidateVtxCache(void);
void GXSetArray(GXAttr attr, s32 base_ptr, u8 stride);
void GXSetVtxAttrFmt(size_t vtxfmt, GXAttr attr, enum_t count, GXAttrType type,
                     u8 frac);
void GXClearVtxDesc(void);
void GXSetVtxDesc(GXAttr attr, s32 type);
void __GXSetVCD(void);
void __GXSetVAT(void);
void __GXSetVCD(void);
void GXClearVtxDesc(void);
void __GXXfVtxSpecs(void);
void __GXSetVAT(void);
void GXInvalidateVtxCache(void);

#endif
