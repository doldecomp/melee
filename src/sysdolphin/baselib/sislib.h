#ifndef SYSDOLPHIN_BASELIB_SISLIB_H
#define SYSDOLPHIN_BASELIB_SISLIB_H

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/forward.h>
#include <Runtime/platform.h>

typedef struct {
    unk_t x0;
    unk_t x4;
    unk_t x8;
    f32 xC;
    unk_t x10;
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

extern s8 lbl_804D6390[4];
extern SIS* lbl_804D1124[5];
extern HSD_Archive* lbl_804D1110[5];
extern u32 lbl_8040C8C0[144];
extern u32 lbl_8040C680[144];
extern unk_t lbl_8040C4B8;

extern sislib_UnknownType001 lbl_8040C4A4;
extern sislib_UnknownType001 lbl_8040C490;

void func_803A6048(size_t);
unk_t func_804A70A0(unk_t, s32, u32, s32, s32, s32, s32, s32, f64, f64, f64,
                    f64, f64, f64, f64, f64);
void func_803A947C(void);
void func_803A945C(void);
void func_803A84BC(void);
void func_803A8134(void);
s32 func_803A7F0C(unk_t, s32);
void func_803A7684(unk_t, u8, u8);
void func_803A7684(unk_t, u8, u8);
void func_803A7664(unk_t);
void func_803A75E0(unk_t, s32);
void func_803A7548(unk_t, f32, f32);
void func_803A74F0(unk_t, unk_t);
void func_803A746C(unk_t, s32, f32, f32);
s32 func_803A70A0(s32, unk_t, unk_t);
u32 lbl_803A6FEC(s32, s32, bool);
void func_803A6B98(unk_t, u32, s32, s32, s32, s32, s32, s32, f64, f64, f64, f64,
                   f64, f64, f64, f64);
s32 func_803A67EC(unk_t, unk_t);
s32 func_803A67EC(unk_t, unk_t);
unk_t func_803A6754(void);
void func_803A660C(s32, s32, s32);
void func_803A6530(s32, s32, s32);
void func_803A6478(u8*, u8*);
void func_803A6368(unk_t, unk_t, u8*);
void func_803A62A0(s32, s32, s8*);
s32 func_803A611C(s16, u32, s16, s8, s8, s8, s8, u32);
void lbl_803A60EC(void);
unk_t func_803A5ACC(f32, f32, f32, f32, f32);
void func_803A594C(u8*);
s32 func_803A611C(s16 arg0, u32 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5,
                  s8 arg6, u32 arg7);

#endif
