#ifndef DOLPHIN_GX_GXGEOMETRY_H
#define DOLPHIN_GX_GXGEOMETRY_H

#include <dolphin/gx/types.h>

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXSetLineWidth(u8 width, GXTexOffset texOffsets);
void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets);
void GXEnableTexOffsets(GXTexCoordID coord, GXBool line_enable,
                        GXBool point_enable);
void GXSetCullMode(GXCullMode mode);
void GXSetCoPlanar(GXBool enable);

#endif
