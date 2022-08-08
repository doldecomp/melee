#ifndef _GXATTR_H_
#define _GXATTR_H_

#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXFifo.h>

#pragma region unordered
void GXInvalidateVtxCache();
void GXSetNumTexGens(s8);
void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);
#pragma endregion

void GXSetVtxDesc(u32, s32);
void GXClearVtxDesc();
void GXSetVtxAttrFmt(s8 vertex_format, s32, s32, s32, s8);
#endif