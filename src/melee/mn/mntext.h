#ifndef _mntext_h_
#define _mntext_h_

#include <common_structs.h>
#include <Runtime/platform.h>

typedef struct _TextGlyphTexture {
    /*0x00*/ u8 data[512];
} TextGlyphTexture;

typedef struct _TextKerning {
    /*0x00*/ u8 left;
    /*0x01*/ u8 right;
} TextKerning;

typedef struct _SIS {
    /*0x00*/ TextKerning* kerning;
    /*0x04*/ TextGlyphTexture* textures;
} SIS;

#endif
