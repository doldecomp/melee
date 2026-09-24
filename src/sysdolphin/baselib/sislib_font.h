#ifndef GALE01_40CD40
#define GALE01_40CD40

#include <Runtime/platform.h>

typedef struct TextGlyphTexture {
    /*0x00*/ u8 data[512];
} TextGlyphTexture;

/// Per-glyph left and right margins used by proportional text rendering.
typedef struct TextGlyphMetrics {
    /*0x00*/ u8 left;
    /*0x01*/ u8 right;
} TextGlyphMetrics;

/// A big-endian SIS glyph opcode, as stored in encoded strings.
typedef struct SisGlyphCode {
    /*0x00*/ u8 hi;
    /*0x01*/ u8 lo;
} SisGlyphCode;

/// A double-byte Shift-JIS character.
typedef struct SjisChar {
    /*0x00*/ u8 lead;
    /*0x01*/ u8 trail;
} SjisChar;

/* 40C680 */ extern SisGlyphCode HSD_SisLib_8040C680[288];
/* 40C8C0 */ extern SjisChar lbl_8040C8C0[288];
/* 40CB00 */ extern TextGlyphMetrics HSD_SisLib_8040CB00[288];
/* 40CD40 */ extern TextGlyphTexture HSD_SisLib_FontAtlas[287];

#endif
