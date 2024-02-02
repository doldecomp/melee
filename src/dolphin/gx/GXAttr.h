#ifndef DOLPHIN_GX_GXATTR_H
#define DOLPHIN_GX_GXATTR_H

#include <platform.h>

#include <dolphin/gx/GXEnum.h>

#define GXSetTexCoordGen(dst_coord, func, src_param, mtx)                     \
    GXSetTexCoordGen2(dst_coord, func, src_param, mtx, GX_DISABLE,            \
                      GX_PTIDENTITY)

void GXSetNumTexGens(u8 num);
void GXSetTexCoordGen2(GXTexCoordID, GXTexGenType, GXTexGenSrc, u32, GXBool,
                       u32);
void GXInvalidateVtxCache(void);
void GXSetArray(GXAttr attr, s32 base_ptr, u8 stride);
void GXSetVtxAttrFmt(size_t vtxfmt, GXAttr attr, enum_t count, GXCompType type,
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
