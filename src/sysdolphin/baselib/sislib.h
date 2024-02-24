#ifndef SYSDOLPHIN_BASELIB_SISLIB_H
#define SYSDOLPHIN_BASELIB_SISLIB_H

#include <platform.h>
#include "baselib/forward.h"

#include "baselib/archive.h"

typedef struct {
    UNK_T x0;
    UNK_T x4;
    UNK_T x8;
    f32 xC;
    UNK_T x10;
} sislib_UnknownType001;

typedef struct _TextGlyphTexture {
    /*0x00*/ u8 data[512];
} TextGlyphTexture;

struct TextKerning {
    /*0x00*/ u8 left;
    /*0x01*/ u8 right;
};

typedef struct _SIS {
    /*0x00*/ TextKerning* kerning;
    /*0x04*/ TextGlyphTexture* textures;
} SIS;

extern s8 HSD_SisLib_804D6390[4];
extern SIS* HSD_SisLib_804D1124[5];
extern HSD_Archive* HSD_SisLib_804D1110[5];
extern u32 lbl_8040C8C0[144];
extern u32 HSD_SisLib_8040C680[144];
extern UNK_T HSD_SisLib_8040C4B8;

extern sislib_UnknownType001 HSD_SisLib_8040C4A4;
extern sislib_UnknownType001 HSD_SisLib_8040C490;

void HSD_SisLib_803A6048(size_t);
UNK_T func_804A70A0(UNK_T, s32, u32, s32, s32, s32, s32, s32, f64, f64, f64,
                    f64, f64, f64, f64, f64);
void HSD_SisLib_803A947C(void);
void HSD_SisLib_803A945C(void);
void HSD_SisLib_803A84BC(void);
void HSD_SisLib_803A8134(void);
s32 HSD_SisLib_803A7F0C(UNK_T, s32);
void HSD_SisLib_803A7684(UNK_T, u8, u8);
void HSD_SisLib_803A7664(UNK_T);
void HSD_SisLib_803A75E0(UNK_T, s32);
void HSD_SisLib_803A7548(UNK_T, f32, f32);
void HSD_SisLib_803A74F0(UNK_T, UNK_T);
void HSD_SisLib_803A746C(UNK_T, s32, f32, f32);
s32 HSD_SisLib_803A70A0(s32, UNK_T, UNK_T);
u32 lbl_803A6FEC(s32, s32, bool);
void HSD_SisLib_803A6B98(UNK_T, u32, s32, s32, s32, s32, s32, s32, f64, f64,
                         f64, f64, f64, f64, f64, f64);
s32 HSD_SisLib_803A67EC(UNK_T, UNK_T);
UNK_T HSD_SisLib_803A6754(void);
void HSD_SisLib_803A660C(s32, s32, s32);
void HSD_SisLib_803A6530(s32, s32, s32);
void HSD_SisLib_803A6478(u8*, u8*);
void HSD_SisLib_803A6368(UNK_T, int);
void HSD_SisLib_803A62A0(s32, s32, s8*);
s32 HSD_SisLib_803A611C(s16, u32, s16, s8, s8, s8, s8, u32);
void lbl_803A60EC(void);
UNK_T HSD_SisLib_803A5ACC(char, int, f32, f32, f32, f32, f32);
void HSD_SisLib_803A594C(u8*);

#endif
