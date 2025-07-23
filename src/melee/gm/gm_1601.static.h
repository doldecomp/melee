#ifndef __GALE01_1601C4
#define __GALE01_1601C4

#include <placeholder.h>

#include <baselib/forward.h>

#include "gm_unsplit.h" // IWYU pragma: export
#include "platform.h"

#include "gm/types.h"

#include <dolphin/mtx.h>

#define NUM_UNLOCKABLE_CHARACTERS 11

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

struct lbl_803B78C8_0x6 {
    /* 0x0 */ u8 x0;      /* inferred */
    /* 0x1 */ u8 x1;      /* inferred */
    /* 0x2 */ char _2[4]; /* maybe part of unk1[5]? */
};                        /* size = 0x6 */

struct VictoryTheme {
    s8 character_id;
    s32 theme_id;
};

struct ResultAnimEntry {
    s32 character_id;
    char* path;
};

/* 166A8C */ static f32 fn_80166A8C(Vec3*, Vec3*);
/* 166CBC */ static u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0,
                                   ssize_t index);
/* 169364 */ static UNK_T fn_80169364(void);
/* 1693A8 */ static s32 fn_801693A8(void);
/* 16A1E4 */ static s32 fn_8016A1E4(void);
/* 3B75F8 */ static const struct gmMainLib_8015ED8C_arg0_t lbl_803B75F8 = { 0 };
/* 3B7808 */ static const s16 lbl_803B7808[0x3C / 2] = { 0 };
/* 3B7864 */ extern const U8Vec4 lbl_803B7864[9];
/* 3B7888 */ static const u8 lbl_803B7888[0x1C] = { 0 };
/* 3B78A4 */ static const u8 lbl_803B78A4[0x24] = { 0 };
/* 3B78C8 */ static struct lbl_803B78C8_0x6 lbl_803B78C8[NUM_UNLOCKABLE_CHARACTERS] = {
    { 0, 3, { 4, 0, 1, 0x16 } },
    { 1, 7, { 2, 0, 1, 0x14 } },
    { 2, 9, { 3, 0, 1, 0x15 } },
    { 3, 0xA, { 1, 0, 1, 0x13 } },
    { 4, 0xF, { 0, 0, 1, 0x12 } },
    { 5, 0x13, { 8, 0, 1, 0x1A } },
    { 6, 0x14, { 7, 0, 1, 0x19 } },
    { 7, 0x15, { 5, 0, 1, 0x17 } },
    { 8, 0x16, { 0xA, 0, 1, 0x1C } },
    { 9, 0x17, { 9, 0, 1, 0x1B } },
    { 0xA, 0x18, { 6, 0, 1, 0x18 } },
};
/* 3B7930 */ static Vec2 const lbl_803B7930[0x114 / sizeof(Vec2)] = { 0 };
/* 46B488 */ static struct lbl_8046B488_t lbl_8046B488;
/* 46B668 */ static struct lbl_8046B668_t lbl_8046B668;
/* 4D6598 */ static s8 lbl_804D6598;
/* 4D659A */ static s16 lbl_804D659A;



#endif
