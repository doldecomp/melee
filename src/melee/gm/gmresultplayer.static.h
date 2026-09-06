#ifndef MELEE_GM_GMRESULTPLAYER_STATIC_H
#define MELEE_GM_GMRESULTPLAYER_STATIC_H

#include <melee/gm/types.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/tobj.h>

typedef struct {
    /* 0x00 */ f32 x0[8];
    /* 0x20 */ f32 x20[4];
} CharScaleEntry;

typedef struct {
    GObj_RenderFunc funcs[4];
} ResultsRenderFuncs;

typedef struct {
    /* 0x00 */ f32 x00[9];
    /* 0x24 */ Vec3 x24;
    /* 0x30 */ Vec3 x30;
    /* 0x3C */ ResultsRenderFuncs x3C;
    /* 0x4C */ Vec3 x4C;
    /* 0x58 */ Vec3 x58;
    /* 0x64 */ ResultsRenderFuncs x64;
    /* 0x74 */ f32 x74;
    /* 0x78 */ f32 x78;
    /* 0x7C */ f32 x7C;
    /* 0x80 */ f32 x80;
    /* 0x84 */ f32 x84;
    /* 0x88 */ f32 x88;
    /* 0x8C */ f32 x8C;
    /* 0x90 */ f32 x90;
    /* 0x94 */ f32 x94;
    /* 0x98 */ f32 x98;
    /* 0x9C */ f32 x9C;
} ResultsPlayerConfig;

typedef struct {
    /* 0x00 */ f32 x_off[4];   // indexed by variant (clamped to 3)
    /* 0x10 */ f32 y_off[4];   // indexed by variant (clamped to 3)
    /* 0x20 */ f32 z_scale[4]; // indexed by variant (clamped to 3)
} CameraKindParams;            // size = 0x30

typedef struct {
    /* 0x000 */ u8 pad[0x10];
    /* 0x010 */ CameraKindParams kind[(0x6D0 - 0x10) / 0x30];
    /* 0x6D0 */ f32 slot_off[(0xF00 - 0x6D0) / 0x30][3][4];
    /* 0xEE0 */ u8 pad_EE0[0xF08 - 0xEE0];
    /* 0xF08 */ HSD_CObjDesc cobj_desc;
} CameraKindData;

typedef union {
    s16 h[4];
    u32 w[2];
} PackedS16x4;

typedef struct {
    u32 lo;
    u32 hi;
} U32Pair;

typedef struct {
    /* 0x00:0 */ u8 x0_0 : 4;
    /* 0x00:4 */ u8 x0_4 : 2;
    /* 0x00:6 */ u8 x0_6 : 2;

    /* 0x01 */ u8 player_flags[4];
    /* 0x05 */ u8 pad_x5;
    /* 0x06 */ u16 x6[4];
    /* 0x0E */ u8 variant[4];
    /* 0x12 */ u8 pad_12[0x02];
    /* 0x14 */ s32 char_kind[4];
    /* 0x24 */ u8 costume_override[4];
    /* 0x28 */ MatchEnd match_end;

    /* 0x22A4 */ u16 scissor_x[4];
    /* 0x22AC */ u16 scissor_y[4];
    /* 0x22B4 */ u16 dim_w1[4];
    /* 0x22BC */ u16 dim_w2[4];
    /* 0x22C4 */ u16 dim_h1[4];
    /* 0x22CC */ u16 dim_h2[4];
    /* 0x22D4 */ PackedS16x4 score_tbl[4];
    /* 0x22F4 */ PackedS16x4 x22F4[4];
} lbl_8046E3AC_t;

typedef struct ResultsDisplayData {
    /* 0x000 */ u8 pad_000[0x104];
    /* 0x104 */ HSD_ImageDesc player_img1[4];
    /* 0x164 */ HSD_ImageDesc player_img2[4];
    /* 0x1C4 */ HSD_ImageDesc shared_img;
} ResultsDisplayData;

typedef struct ResultsDisplayLayout {
    /* 0x000 */ u8 pad_000[0x104];
    /* 0x104 */ HSD_ImageDesc player_img1[4];
    /* 0x164 */ HSD_ImageDesc player_img2[4];
    /* 0x1C4 */ HSD_ImageDesc shared_img;
    /* 0x1DC */ HSD_GObj* gobjs[4];
    /* 0x1EC */ HSD_JObj* jobjs[4];
    /* 0x1FC */ lbl_8046E3AC_t state;
} ResultsDisplayLayout;

typedef struct {
    /* 0x000 */ f32 scale[32];
    /* 0x080 */ f32 slot_off[32][3][4];
    /* 0x680 */ u8 x680[27][0x10];
    /* 0x830 */ u8 pad_830[0x60];
} ResultsCharacterData;

extern ResultsPlayerConfig const lbl_803B7B68;

extern u32 gmResultPlayerColors[4];
extern CharScaleEntry gmResultCharacterScaleData[];
extern u32 gmResultX22F4Init[0x20 / sizeof(u32)];
extern u32 gmResultScoreTableInit[0x20 / sizeof(u32)];
extern ResultsCharacterData gmResultCharacterData;
extern HSD_CameraDescPerspective gmResultCameraDesc;

extern ResultsDisplayData lbl_8046E1B0;
extern HSD_GObj* lbl_8046E38C[4];
extern HSD_JObj* lbl_8046E39C[4];
extern lbl_8046E3AC_t lbl_8046E3AC;

#endif
