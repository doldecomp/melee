#ifndef GALE01_40CD40
#define GALE01_40CD40

#include <platform.h>

typedef struct TextGlyphTexture {
    /*0x00*/ u8 data[512];
} TextGlyphTexture;

/* 40CD40 */ extern TextGlyphTexture HSD_SisLib_FontAtlas[287];

#endif
