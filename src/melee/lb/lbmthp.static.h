#ifndef __GALE01_01E8F8
#define __GALE01_01E8F8

#include "lbmthp.h" // IWYU pragma: export

#include <dolphin/gx/GXStruct.h>

struct lbl_804333E0_t {
    /* 0x000 */ char pad_0[0x84];
    /* 0x084 */ s32 unk_84;        /* inferred */
    /* 0x088 */ char pad_88[0x80]; /* maybe part of unk_84[0x21]? */
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ s32 unk_110;
    /* 0x114 */ char pad_114[0x20]; /* maybe part of unk_110[9]? */
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ char pad_138[0xC]; /* maybe part of unk_134[4]? */
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ char pad_150[0x88]; /* maybe part of unk_14C[0x23]? */
}; /* size = 0x1D8 */
STATIC_ASSERT(sizeof(struct lbl_804333E0_t) == 0x1D8);

/* 4333E0 */ static struct lbl_804333E0_t lbl_804333E0;
/* 4D7CC0 */ static float lb_804D7CC0;

struct lbl_804335B8_t {
    /* 0x00 */ GXTexObj tex0; /* 0x00-0x20 (size 0x20) */
    /* 0x20 */ void* x20;     /* image ptr for tex0 */
    /* 0x24 */ GXTexObj tex1; /* 0x24-0x44 (size 0x20) */
    /* 0x44 */ void* x44;     /* image ptr for tex1 */
    /* 0x48 */ GXTexObj tex2; /* 0x48-0x68 (size 0x20) */
    /* 0x68 */ void* x68;     /* image ptr for tex2 */
    /* 0x6C */ u16 x6C;       /* width */
    /* 0x6E */ u16 x6E;       /* height */
    /* 0x70 */ s32 x70;
    /* 0x74 */ u16 x74;
    /* 0x76 */ u16 x76;
    /* 0x78 */ s32 x78;
    /* 0x7C */ s32 x7C;
    /* 0x80 */ float x80;
    /* 0x84 */ float x84;
    /* 0x88 */ void* x88;
    /* 0x8C */ s32 x8C;
    /* 0x90 */ struct HSD_SObj* x90;
    /* 0x94 */ char pad_94[0xA0 - 0x94];
}; /* size = 0xA0 */
STATIC_ASSERT(sizeof(struct lbl_804335B8_t) == 0xA0);

/* 4335B8 */ static struct lbl_804335B8_t lbl_804335B8;
/* 4D7CE0 */ static float lbl_804D7CE0;

#endif
