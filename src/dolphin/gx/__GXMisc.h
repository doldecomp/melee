#ifndef DOLPHIN_GX___GXMISC_HG
#define DOLPHIN_GX___GXMISC_HG

#include <dolphin/gx/__types.h>

/* 00339BB0 */ extern void __GXPEInit(void);
void GXPokeZMode(BOOL compare_enable, GXCompare func, BOOL update_enable);
void GXPokeDstAlpha(BOOL enable, u8 alpha);
void GXPokeAlphaRead(s32 mode);
void GXPokeAlphaMode(GXCompare func, u8 threshold);
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor,
                     GXBlendFactor dst_factor, GXLogicOp op);
void GXPokeDither(s32 dither);
void GXPokeAlphaUpdate(BOOL update_enable);
void GXPokeColorUpdate(BOOL update_enable);

#endif
