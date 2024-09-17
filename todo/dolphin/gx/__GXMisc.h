#ifndef DOLPHIN_GX___GXMISC_HG
#define DOLPHIN_GX___GXMISC_HG

#include <platform.h>

#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXEnum.h>

/* 00339BB0 */ extern void __GXPEInit(void);
void GXPokeZMode(bool compare_enable, GXCompare func, bool update_enable);
void GXPokeDstAlpha(bool enable, u8 alpha);
void GXPokeAlphaRead(s32 mode);
void GXPokeAlphaMode(GXCompare func, u8 threshold);
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor,
                     GXBlendFactor dst_factor, GXLogicOp op);
void GXPokeDither(s32 dither);
void GXPokeAlphaUpdate(bool update_enable);
void GXPokeColorUpdate(bool update_enable);

#endif
