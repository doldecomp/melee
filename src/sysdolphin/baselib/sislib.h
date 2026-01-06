#ifndef SYSDOLPHIN_BASELIB_SISLIB_H
#define SYSDOLPHIN_BASELIB_SISLIB_H

#include <placeholder.h>
#include <platform.h>

#include "baselib/archive.h"
#include "baselib/cobj.h"

#include "baselib/forward.h"

#include "dolphin/gx/GXStruct.h"

#include <dolphin/mtx.h>

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

/// @todo: this is the same as above, but just more generic...
/// proper types will have to be sorted out later, as well as merging the two
/// structs.
typedef struct sisLib_803A7664_t {
    void* x0;
    void* x4;
    u32 x8; ///< alloc size
    u32 xC;
} sisLib_803A7664_t;

struct HSD_Text {
    // these get passed to the text initializer HSD_SisLib_803A5ACC
    f32 pos_x;      ///< world position x
    f32 pos_y;      ///< world position y
    f32 pos_z;      ///< world position z
    f32 box_size_x; ///< text box size x
    f32 box_size_y; ///< text box size y
    Vec4 x14;
    Vec2 font_size; ///< font size, 1.0 being 100% of the screen?
    GXColor bg_color;
    GXColor text_color;
    Vec2 x34;
    Vec2 x3C;
    u16 x44;              ///< render flags?
    u16 x46;              ///< more flags?
    u8 default_fitting;   ///< sets fitting below
    u8 default_kerning;   ///< sets kerning below
    u8 default_alignment; ///< sets alignment below
    u8 x4B;
    u8 x4C;    // whether to test for Z depth?
    u8 hidden; ///< visibility flag
    u8 x4E;
    u8 font_idx; ///< which font to select from the array HSD_SisLib_804D1124
    HSD_Text* next;
    HSD_GObj* entity;
    void (*render_callback)(
        void*);      ///< callback in the text renderer (HSD_SisLib_803A84BC)
    SIS* sis_buffer; ///< SIS text buffer
    UNK_T x60;       ///< position in text buffer
    sislib_UnkAllocData* alloc_data;
    char* string_buffer; ///< raw string buffer
    u16 x6C;             ///< string length?
    u16 x6E;             ///< alloc size?
    f32 current_width;
    f32 current_height;
    Vec2 x78;
    Vec2 x80;
    f32 x88;
    GXColor active_color; ///< the texts current color
    u16 x90;              ///< set by x44
    u16 x92;              ///< set by x46
    u32 x94;
    u32 x98;
    u8 fitting;
    u8 kerning;
    u8 alignment;
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
extern u32 lbl_8040C8C0[144];
extern u32 HSD_SisLib_8040C680[144];

extern sislib_UnkAllocData* HSD_SisLib_804D7970;
extern sislib_UnkAllocData* HSD_SisLib_804D7974;
extern HSD_Text* HSD_SisLib_804D7978;
extern sislib_UnkAlloc3* HSD_SisLib_804D797C;

void HSD_SisLib_803A6048(size_t);
UNK_T func_804A70A0(UNK_T, s32, u32, s32, s32, s32, s32, s32, f64, f64, f64,
                    f64, f64, f64, f64, f64);
void HSD_SisLib_803A947C(HSD_Archive*);
HSD_Archive* HSD_SisLib_803A945C(char*);
void HSD_SisLib_803A84BC(HSD_GObj*, int);
s32 HSD_SisLib_803A7F0C(HSD_Text*, s32);
void HSD_SisLib_803A8134(void*, HSD_Text*, f32*, f32*);
void HSD_SisLib_803A7684(UNK_T, u8, u8);
void HSD_SisLib_803A7664(HSD_Text*);
void HSD_SisLib_803A75E0(HSD_Text*, s32);
void HSD_SisLib_803A7548(HSD_Text*, int, float, float);
void HSD_SisLib_803A74F0(HSD_Text*, s32 arg1, u8* arg2);
void HSD_SisLib_803A746C(HSD_Text*, s32, f32, f32);
s32 HSD_SisLib_803A70A0(HSD_Text*, ...);
u32 lbl_803A6FEC(s32, s32, bool);
int HSD_SisLib_803A6B98(HSD_Text* arg0, float, float, const char*, ...);
s32 HSD_SisLib_803A67EC(u8*, u8*);
HSD_Text* HSD_SisLib_803A6754(int arg0, s32 arg1);
void HSD_SisLib_803A660C(s32, s32, s32);
void HSD_SisLib_803A6530(s32, s32, s32);
u8* HSD_SisLib_803A6478(u8*, u8*);
void HSD_SisLib_803A6368(HSD_Text*, s32);
void HSD_SisLib_803A62A0(s32, char*, char*);
s32 HSD_SisLib_803A611C(int, HSD_GObj*, u16, u8, u8, u8, u8, u32);
void lbl_803A60EC(void);
HSD_Text* HSD_SisLib_803A5ACC(int, s32, f32, f32, f32, f32, f32);
void* HSD_SisLib_803A5798(s32);
void HSD_SisLib_803A594C(void*);
void HSD_SisLib_803A5CC4(HSD_Text*);
void HSD_SisLib_803A5A2C(void*);
void HSD_SisLib_803A5D30(void);
void HSD_SisLib_803A5DA0(s32);
void HSD_SisLib_803A5E70(void);
void HSD_SisLib_803A5F50(s32);
void HSD_SisLib_803A5FBC(void);
void fn_803A60EC(void*);
u8* fn_803A6FEC(u8*, s32, s32*);
// void *HSD_SisLib_803A84BC(HSD_GObj *, s32);

#endif
