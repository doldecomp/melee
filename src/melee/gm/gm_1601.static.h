#ifndef __GALE01_1601C4
#define __GALE01_1601C4

#include "gm_unsplit.h" // IWYU pragma: export
#include "platform.h"

#include <placeholder.h>

#include "gm/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

#define NUM_UNLOCKABLE_CHARACTERS 11
#define NUM_UNLOCKABLE_STAGES 11

struct lbl_8046B488_t {
    /* 0x000 */ char pad_0[0x7];
    /* 0x007 */ u8 x7;
    /* 0x008 */ u8 x8;
    /* 0x009 */ char pad_9[0x0F - 0x9];
    /* 0x00F */ u8 xF;
    /* 0x010:0 */ u8 unk_10_b0 : 1;
    /* 0x010:1 */ u8 unk_10_b1 : 1;
    /* 0x010:2 */ u8 unk_10_b2 : 1;
    /* 0x010:3 */ u8 unk_10_b3 : 1;
    /* 0x010:4 */ u8 unk_10_b4 : 1;
    /* 0x010:5 */ u8 unk_10_b5 : 1;
    /* 0x010:6 */ u8 unk_10_b6 : 1;
    /* 0x010:7 */ u8 unk_10_b7 : 1;
    /* 0x011 */ char pad_11[0x20 - 0x11];
    /* 0x020 */ s8 x20[0xA2 - 0x20];
    /* 0x0A2 */ s8 xA2[0x124 - 0xA2];
    /* 0x124 */ s8 x124[0x1A6 - 0x124];
    /* 0x1A6 */ s8 x1A6[0x1B8 - 0x1A6];
    /* 0x1B8 */ int (*x1B8)(void);
    /* 0x1BC */ char pad_1BC[0x1E0 - 0x1BC];
}; /* size = 0x1E0 */
STATIC_ASSERT(sizeof(struct lbl_8046B488_t) == 0x1E0);

struct fn_80166CBC_arg0_t {
    /* +0 */ char pad_0[0x5E];
    /* +5E */ u8 x5E;
    /* +5F */ char pad_5F[0xA8 - 0x5F];
};
STATIC_ASSERT(sizeof(struct fn_80166CBC_arg0_t) == 0xA8);

// struct ResultsData {
//     /*  +0 */ char pad_0[0x94];
//     /* +94 */ int x94;
//     /* +98 */ char pad_98[0x5A8 - 0x98];
// };
// STATIC_ASSERT(sizeof(struct ResultsData) == 0x5A8);

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
    /* 0x0 */ u8 idx;
    /* 0x1 */ u8 ckind;
    /* 0x2 */ u8 x2;
    /* 0x3 */ u8 x3;
    /* 0x4 */ u16 x4;
}; /* size = 0x6 */

struct VictoryTheme {
    s8 ckind;
    s32 theme_id;
};

struct ResultAnimEntry {
    CharacterKind ckind;
    char* path;
};

/* 166A8C */ static f32 fn_80166A8C(Vec3*, Vec3*);
/* 166CBC */ static u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0,
                                   ssize_t index);
/* 1693A8 */ static s32 fn_801693A8(void);
/* 16A1E4 */ static s32 fn_8016A1E4(void);

/* 3B75F8 */ static const float lbl_803B75F8[] = {
    0.95, 0.8, 1, 0.65, 1,    1,   1, 1, 1,   1, 1, 1, 1, 1, 0.67, 1, 1,
    1,    1,   1, 1,    0.95, 0.8, 1, 1, 0.9, 1, 1, 1, 1, 1, 1,    0,
};
static const float lbl_803B767C[] = {
    0.8, 1, 1, 0.6, 1,   1,   1, 1, 1,   1,   1, 1, 1,   0.9, 0.8, 0.8, 1,
    1,   1, 1, 1,   0.7, 0.8, 1, 1, 0.8, 0.8, 1, 1, 0.8, 0.8, 1,   0,
};
static const float lbl_803B7700[] = {
    0.8, 0.9, 1, 0.8, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1,   1,   1, 1,   1, 0.9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
};
static const float lbl_803B7784[] = {
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* 3B7808 */ static const s16 lbl_803B7808[0x3C / 2] = {
    0x0004, 0x0005, 0x000D, 0x0006, 0x0008, 0x0002, 0x0007, 0x0003,
    0x000A, 0x0009, 0x0019, 0x0013, 0x000B, 0x000C, 0x000E, 0x000F,
    0x0010, 0x0011, 0x0016, 0x0017, 0x0018, 0x0012, 0x0014, 0x001B,
    0x001F, 0x0020, 0x001C, 0x001D, 0x001E, 0x0000,
};

static const u8 lbl_803B7844[] = {
    0x06, 0x0B, 0x07, 0x19, 0x14, 0x12, 0x11, 0x0E, 0x1C, 0x18, 0x08,
    0x1A, 0x04, 0x10, 0x17, 0x22, 0x20, 0x13, 0x09, 0x21, 0x0D, 0x0F,
    0x1F, 0x16, 0x15, 0x1E, 0x0A, 0x0C, 0x23, 0x05, 0x1D, 0x1B,
};

/* 3B7864 */ static const GXColor lbl_803B7864[9] = {
    { 0x99, 0x1A, 0x1A, 0xFF }, { 0x33, 0x33, 0x80, 0xFF },
    { 0x80, 0x66, 0x00, 0xFF }, { 0x1A, 0x66, 0x1A, 0xFF },
    { 0x66, 0x66, 0x66, 0xFF }, { 0x66, 0x4D, 0x4D, 0xFF },
    { 0x4D, 0x4D, 0x66, 0xFF }, { 0x66, 0x59, 0x33, 0xFF },
    { 0x4D, 0x66, 0x4D, 0xFF },
};
/* 3B7888 */ static const u8 lbl_803B7888[0x1C] = {
    CKIND_CAPTAIN, CKIND_DONKEY,  CKIND_FOX,      CKIND_GAMEWATCH,
    CKIND_KIRBY,   CKIND_KOOPA,   CKIND_LINK,     CKIND_LUIGI,
    CKIND_MARIO,   CKIND_MARS,    CKIND_MEWTWO,   CKIND_NESS,
    CKIND_PEACH,   CKIND_PIKACHU, CKIND_POPONANA, CKIND_PURIN,
    CKIND_SAMUS,   CKIND_YOSHI,   CKIND_ZELDA,    CKIND_FALCO,
    CKIND_CLINK,   CKIND_DRMARIO, CKIND_EMBLEM,   CKIND_PICHU,
    CKIND_GANON,
};
/* 3B78A4 */ static const u8 lbl_803B78A4[0x24] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x08, 0x08, 0x08, 0x19, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00
};

/* 3B78C8 */ static const struct lbl_803B78C8_0x6
    lbl_803B78C8[NUM_UNLOCKABLE_CHARACTERS] = {
        {
            0,
            3,
            4,
            0,
            0x116,
        },
        {
            1,
            7,
            2,
            0,
            0x114,
        },
        {
            2,
            9,
            3,
            0,
            0x115,
        },
        {
            3,
            0xA,
            1,
            0,
            0x113,
        },
        {
            4,
            0xF,
            0,
            0,
            0x112,
        },
        {
            5,
            0x13,
            8,
            0,
            0x11A,
        },
        {
            6,
            0x14,
            7,
            0,
            0x119,
        },
        {
            7,
            0x15,
            5,
            0,
            0x117,
        },
        {
            8,
            0x16,
            0xA,
            0,
            0x11C,
        },
        {
            9,
            0x17,
            9,
            0,
            0x11B,
        },
        {
            0xA,
            0x18,
            6,
            0,
            0x118,
        },
    };

static const u8 lbl_803B790C[0xB][3] = {
    { 0x00, 0x09, 0x0B }, { 0x01, 0x11, 0x0D }, { 0x02, 0x13, 0x0E },
    { 0x03, 0x15, 0x0C }, { 0x04, 0x19, 0x0F }, { 0x05, 0x1B, 0x10 },
    { 0x06, 0x24, 0x11 }, { 0x07, 0x25, 0x12 }, { 0x08, 0x1C, 0x13 },
    { 0x09, 0x1D, 0x14 }, { 0x0A, 0x1E, 0x15 },
};

/* 3B7930 */ static Vec2 const lbl_803B7930[] = {
    0.35, 2.857143,  0.4,  2.5,       0.46, 2.173913,
    0.53, 1.8867925, 0.61, 1.6393442, 0.7,  1.4285715,
    0.8,  1.25,      0.93, 1.0752689, 1.07, 0.9345794,
};

static const s16 lbl_803B7978[] = {
    0x001B, 0x0003, 0x0012, 0x0039, 0x000F, 0x001E, 0x0006, 0x002D, 0x0000,
    0x0036, 0x0033, 0x0018, 0x0021, 0x0015, 0x0024, 0x0030, 0x0009, 0x000C,
    0x0027, 0x002A, 0x0042, 0x0045, 0x003C, 0x004B, 0x0048, 0x003F, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

static const s16 lbl_803B79BC[] = {
    0x001C, 0x0004, 0x0013, 0x003A, 0x0010, 0x001F, 0x0007, 0x002E, 0x0001,
    0x0037, 0x0034, 0x0019, 0x0022, 0x0016, 0x0025, 0x0031, 0x000A, 0x000D,
    0x0028, 0x002B, 0x0043, 0x0046, 0x003D, 0x004C, 0x0049, 0x0040, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

static const s16 lbl_803B7A00[] = {
    0x001D, 0x0005, 0x0014, 0x003B, 0x0011, 0x0020, 0x0008, 0x002F, 0x0002,
    0x0038, 0x0035, 0x001A, 0x0023, 0x0017, 0x0026, 0x0032, 0x000B, 0x000E,
    0x0029, 0x002C, 0x0044, 0x0047, 0x003E, 0x004D, 0x004A, 0x0041, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

/* 46B488 */ static struct lbl_8046B488_t lbl_8046B488;
/* 46B668 */ static struct lbl_8046B668_t lbl_8046B668;
/* 4D6598 */ static s8 lbl_804D6598;
/* 4D659A */ static u16 lbl_804D659A;

#endif
