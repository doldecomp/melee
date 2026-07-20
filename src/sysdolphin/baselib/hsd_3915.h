#ifndef HSD_3915_H
#define HSD_3915_H

#include <placeholder.h>

#include <sysdolphin/baselib/list.h>

/* 391580 */ void DrawRectangle(float x, float y, float w, float h,
                                GXColor* color);
/* 391664 */ f32 DrawASCII(int chr, float x, float y, GXColor* color);
/* 391A04 */ void hsd_80391A04(float scale_x, float scale_y, int line_width);
/* 391AC8 */ s32 hsd_80391AC8(char*, GXColor*, f32, f32);
/* 391E18 */ void hsd_80391E18(u8* list, f32 x1, f32 y1, f32 x2, f32 y2);
/* 391F28 */ void hsd_80391F28(GXColor*, f32, f32, f32, f32, f32);
/* 392194 */ void hsd_80392194(u8* dst, s32 flags, void* unused1,
                               void* unused2, u8* src);
/* 3921B8 */ void hsd_803921B8(void*, s32, s32, s32, s32, s32, s32, void*);
/* 3922FC */ void hsd_803922FC(void*, s32, s32, s32, s32, s32, s32, s32,
                               void*);
/* 392474 */ UNK_RET hsd_80392474(UNK_PARAMS);
/* 392480 */ HSD_SList* fn_80392480(Event event, int priority);
/* 392528 */ void hsd_80392528(Event);
/* 39254C */ void hsd_8039254C(void);
/* 392934 */ UNK_RET fn_80392934(UNK_PARAMS);
/* 392A08 */ UNK_RET fn_80392A08(int, int, int);
/* 392A3C */ void* fn_80392A3C(void);

#endif
