#ifndef DOLPHIN_GX_GXPIXEL_H
#define DOLPHIN_GX_GXPIXEL_H

#include <dolphin/gx/types.h>

void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(s8, s32, s32);
void GXSetBlendMode(s32, s32, s32, s32);
void GXSetAlphaUpdate(s32);
void GXSetColorUpdate(s32);

#endif
