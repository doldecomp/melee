#ifndef HSD_3915_H
#define HSD_3915_H

#include <placeholder.h>

#include <dolphin/gx/GXStruct.h>
#include <sysdolphin/baselib/list.h>

/// One cell of the debug console's ASCII font: 14 rows of 4 bytes, 2 bits per
/// pixel, 12 of the 16 pixels used.
typedef struct DebugFontGlyph {
    /*0x00*/ u8 data[56];
} DebugFontGlyph;

/* 391580 */ void DrawRectangle(float x, float y, float w, float h,
                                GXColor* color);
/* 391664 */ f32 DrawASCII(int chr, float x, float y, GXColor* color);
/* 391A04 */ void hsd_80391A04(float scale_x, float scale_y, int line_width);
/* 391AC8 */ s32 hsd_80391AC8(char*, GXColor*, f32, f32);
/* 391E18 */ void hsd_80391E18(const u8* list, f32 x1, f32 y1, f32 x2, f32 y2);
/* 391F28 */ void hsd_80391F28(GXColor*, f32, f32, f32, f32, f32);
/* 392194 */ void hsd_80392194(u8* dst, s32 flags, s32 unused1, s32 unused2,
                               const u8* src);
/* 3921B8 */ void hsd_803921B8(void*, s32, s32, s32, s32, s32, s32, void*);
/* 3922FC */ void hsd_803922FC(void*, s32, s32, s32, s32, s32, s32, s32,
                               void*);
/* 4088B8 */ extern DebugFontGlyph HSD_DebugFontAtlas[];

#endif
