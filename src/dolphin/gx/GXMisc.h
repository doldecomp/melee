#ifndef _GXMISC_H_
#define _GXMISC_H_

#include <dolphin/gx/GXFifo.h>
#include <dolphin/os/OSContext.h>

typedef u32 color_t;

void GXPixModeSync();
void __GXPEInit();
void GXPokeAlphaMode(color_t, s8);
void GXPokeAlphaRead(color_t);
void GXPokeAlphaUpdate(color_t);
void GXPokeColorUpdate(color_t);
void GXPokeDstAlpha(color_t, color_t);
void GXPokeDither(color_t);

#endif