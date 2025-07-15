#ifndef __GALE01_1601C4
#define __GALE01_1601C4

#include <placeholder.h>

#include <baselib/forward.h>

#include "gm_1601.h" // IWYU pragma: export
#include "platform.h"

#include "gm/types.h"

#include <dolphin/mtx.h>

struct lbl_8046B488_t {
    /* 0x000 */ char pad_0[0x10];
    /* 0x010:0 */ u8 unk_10_b0 : 1;
    /* 0x010:1 */ u8 unk_10_b1 : 1;
    /* 0x010:2 */ u8 unk_10_b2 : 1;
    /* 0x010:3 */ u8 unk_10_b3 : 1;
    /* 0x010:4 */ u8 unk_10_b4 : 1;
    /* 0x010:5 */ u8 unk_10_b5 : 1;
    /* 0x010:6 */ u8 unk_10_b6 : 1;
    /* 0x010:7 */ u8 unk_10_b7 : 1;
    /* 0x011 */ char pad_11[0x1CF]; /* maybe part of unk_10[0x1D0]? */
}; /* size = 0x1E0 */
STATIC_ASSERT(sizeof(struct lbl_8046B488_t) == 0x1E0);

struct fn_80166CBC_arg0_t {
    /* +0 */ char pad_0[0x5E];
    /* +5E */ u8 x5E;
    /* +5F */ char pad_5F[0xA8 - 0x5F];
};
STATIC_ASSERT(sizeof(struct fn_80166CBC_arg0_t) == 0xA8);

struct lbl_8046DBE8_t {
    /*  +0 */ char pad_0[0x94];
    /* +94 */ int x94;
    /* +98 */ char pad_98[0x5A8 - 0x98];
};
STATIC_ASSERT(sizeof(struct lbl_8046DBE8_t) == 0x5A8);

struct lbl_80472D28_t {
    /*   +0 */ char pad_0[0x104];
    /* +104 */ int x104;
};

struct lbl_80472E48_t {
    /* 0x00 */ char pad_0[4];
    /* 0x04 */ s32 unk_4;        /* inferred */
    /* 0x08 */ s32 unk_8;        /* inferred */
    /* 0x0C */ char pad_C[0x74]; /* maybe part of unk_8[0x1E]? */
}; /* size = 0x80 */
STATIC_ASSERT(sizeof(struct lbl_80472E48_t) == 0x80);

struct lbl_8046B668_t {
    /* 0x00 */ char pad_0[0x1C];
    /* 0x1C */ s8 unk_1C;         /* inferred */
    /* 0x1D */ char pad_1D[0x1B]; /* maybe part of unk_1C[0x1C]? */
}; /* size = 0x38 */
STATIC_ASSERT(sizeof(struct lbl_8046B668_t) == 0x38);

struct lbl_80473700_t {
    /* +0 */ char pad_0[0x114];
};
STATIC_ASSERT(sizeof(struct lbl_80473700_t) == 0x114);

/* 166A8C */ static f32 fn_80166A8C(Vec3*, Vec3*);
/* 166CBC */ static u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0,
                                   ssize_t index);
/* 169364 */ static UNK_T fn_80169364(void);
/* 1693A8 */ static s32 fn_801693A8(void);
/* 16A1E4 */ static s32 fn_8016A1E4(void);
/* 174274 */ static int fn_80174274(void);
/* 17F294 */ static int fn_8017F294(void);
/* 3B75F8 */ static const struct gmMainLib_8015ED8C_arg0_t lbl_803B75F8 = { 0 };
/* 3B7808 */ static const s16 lbl_803B7808[0x3C / 2] = { 0 };
/* 3B7864 */ extern const U8Vec4 lbl_803B7864[9];
/* 3B7888 */ static const u8 lbl_803B7888[0x1C] = { 0 };
/* 3B78A4 */ static const u8 lbl_803B78A4[0x24] = { 0 };
/* 3B7930 */ static Vec2 const lbl_803B7930[0x114 / sizeof(Vec2)] = { 0 };
/* 46B488 */ static struct lbl_8046B488_t lbl_8046B488;
/* 46B668 */ static struct lbl_8046B668_t lbl_8046B668;
/* 4D4190 */ static s32 lbl_804D4190 = 0xFFFFFFFF;
/* 4D6598 */ static s8 lbl_804D6598;
/* 4D659A */ static s16 lbl_804D659A;


#define NUM_UNLOCKABLE_CHARACTERS 11

#endif
