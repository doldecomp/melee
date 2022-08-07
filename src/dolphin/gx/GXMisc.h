#ifndef _GXMISC_H_
#define _GXMISC_H_

#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/os/OSContext.h>

void GXPixModeSync();
void __GXPEInit();
void GXPokeAlphaMode(GXColor, s8);
void GXPokeAlphaRead(GXColor);
void GXPokeAlphaUpdate(GXColor);
void GXPokeColorUpdate(GXColor);
void GXPokeDstAlpha(GXColor, GXColor);
void GXPokeDither(GXColor);
void GXPokeBlendMode(GXColor, GXColor, GXColor, GXColor);
void GXPokeZMode(GXColor, GXColor, u32);
void GXSetCurrentMtx(s32);

#endif