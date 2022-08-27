#ifndef DOLPHIN_GX_GXATTR_H
#define DOLPHIN_GX_GXATTR_H

#include <dolphin/types.h>

/* 00339758 */ extern void GXSetNumTexGens(s8);
/* 00339488 */ extern void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);
/* 00339478 */ extern void GXInvalidateVtxCache();
/* 003393EC */ extern void GXSetArray(s32, s32, s8);
/* 00338FF4 */ extern void GXSetVtxAttrFmt(s8 vertex_format, s32, s32, s32, s8);
/* 00338FA8 */ extern void GXClearVtxDesc();
/* 00338AE0 */ extern void GXSetVtxDesc(u32, s32);

#endif
