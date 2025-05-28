#ifndef SYSDOLPHIN_BASELIB_SISLIB_H
#define SYSDOLPHIN_BASELIB_SISLIB_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/archive.h"
#include "baselib/cobj.h"

#include <dolphin/mtx/types.h>

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

typedef struct SIS {
    /*0x00*/ TextKerning* kerning;
    /*0x04*/ TextGlyphTexture* textures;
} SIS;

// @todo: give actual names?
struct sislib_UnkAllocData {
    sislib_UnkAllocData* data_0;
    HSD_Text* data_1;
    u32 size;
};

struct HSD_Text {
    // these get passed to the text initializer HSD_SisLib_803A5ACC
    f32 x0;  // global x position, 0,0 at center
    f32 x4;  // global y position
    f32 x8;  // scale that happens from the origin after the translation of x0,
             // x4
    f32 xC;  // scale that happens on the X axis from the left side of the text
    f32 x10; // unknown, no effect observed so far

    Vec4 x14;
    Vec2 x24; // font size, 1.0 being 100% of the screen?
    U8Vec4 x2C;
    U8Vec4 x30;
    Vec2 x34;
    Vec2 x3C;
    u16 x44;
    u16 x46;
    u8 x48;
    u8 x49;
    u8 x4A;
    u8 x4B;
    u8 x4C; // whether to test for Z depth?
    u8 x4D;
    u8 x4E;
    u8 x4F; // which font to select from the array HSD_SisLib_804D1124
    HSD_Text* x50;
    HSD_GObj* x54;
    void (*x58)(void*); // callback in the text renderer (HSD_SisLib_803A84BC)
    SIS* x5C;           // could just be a byte pointer?
    UNK_T x60;
    sislib_UnkAllocData* x64;
    void* x68;
    u16 x6C;
    u16 x6E;
    f32 x70;
    f32 x74;
    Vec2 x78;
    Vec2 x80;
    f32 x88;
    U8Vec4 x8C;
    u16 x90;
    u16 x92;
    u32 x94;
    u32 x98;
    u8 x9C;
    u8 x9D;
    u8 x9E;
    u8 x9F;
};

struct sislib_UnkAlloc3 {
    sislib_UnkAlloc3* x0;
    HSD_GObj* x4;
    u16 x8;
    u16 xA;
    u8 xC;
    u8 xD;
    u8 xE;
    u8 xF;
};

extern s8 HSD_SisLib_804D6390[4];
extern SIS* HSD_SisLib_804D1124[5];
extern HSD_Archive* HSD_SisLib_804D1110[5];
extern u32 lbl_8040C8C0[144];
extern u32 HSD_SisLib_8040C680[144];
extern HSD_CObjDesc HSD_SisLib_8040C4B8;

extern u32 HSD_SisLib_804D7968;
extern sislib_UnkAllocData* HSD_SisLib_804D796C;
extern sislib_UnkAllocData* HSD_SisLib_804D7970;
extern sislib_UnkAllocData* HSD_SisLib_804D7974;
extern HSD_Text* HSD_SisLib_804D7978;
extern sislib_UnkAlloc3* HSD_SisLib_804D797C;

extern sislib_UnknownType001 HSD_SisLib_8040C4A4;
extern sislib_UnknownType001 HSD_SisLib_8040C490;

void HSD_SisLib_803A6048(size_t);
UNK_T func_804A70A0(UNK_T, s32, u32, s32, s32, s32, s32, s32, f64, f64, f64,
                    f64, f64, f64, f64, f64);
void HSD_SisLib_803A947C(HSD_Archive*);
void HSD_SisLib_803A945C(void);
void HSD_SisLib_803A84BC(HSD_GObj*, HSD_Text*);
s32 HSD_SisLib_803A7F0C(HSD_Text*, s32);
void HSD_SisLib_803A8134(void*, HSD_Text*, f32*, f32*);
void HSD_SisLib_803A7684(UNK_T, u8, u8);
void HSD_SisLib_803A7664(UNK_T);
void HSD_SisLib_803A75E0(UNK_T, s32);
void HSD_SisLib_803A7548(UNK_T, f32, f32);
void HSD_SisLib_803A74F0(HSD_Text*, s32 arg1, u8* arg2);
void HSD_SisLib_803A746C(HSD_Text*, s32, f32, f32);
s32 HSD_SisLib_803A70A0(s32, UNK_T, UNK_T);
u32 lbl_803A6FEC(s32, s32, bool);
void HSD_SisLib_803A6B98(HSD_Text* arg0, void* arg1, ...);
s32 HSD_SisLib_803A67EC(u8*, u8*);
HSD_Text* HSD_SisLib_803A6754(s8 arg0, s32 arg1);
void HSD_SisLib_803A660C(s32, s32, s32);
void HSD_SisLib_803A6530(s32, s32, s32);
void HSD_SisLib_803A6478(u8*, u8*);
void HSD_SisLib_803A6368(HSD_Text*, s32);
void HSD_SisLib_803A62A0(s32, HSD_Archive*, char*);
s32 HSD_SisLib_803A611C(u16, u32, u16, u8, u8, u8, u8, u32);
void lbl_803A60EC(void);
HSD_Text* HSD_SisLib_803A5ACC(s8, s32, f32, f32, f32, f32, f32);
void* HSD_SisLib_803A5798(s32);
void HSD_SisLib_803A594C(void*);
void HSD_SisLib_803A5CC4(HSD_Text*);
void HSD_SisLib_803A5A2C(HSD_Text*);
void HSD_SisLib_803A5D30(void);
void HSD_SisLib_803A5DA0(s32);
void HSD_SisLib_803A5E70(void);
void HSD_SisLib_803A5F50(s32);
void HSD_SisLib_803A5FBC(void);
void fn_803A60EC(void*);
u8* fn_803A6FEC(u8*, s32, s32*);
// void *HSD_SisLib_803A84BC(HSD_GObj *, s32);

#endif
