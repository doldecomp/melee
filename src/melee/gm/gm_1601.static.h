#ifndef __GALE01_1601C4
#define __GALE01_1601C4

#include "platform.h"

#include <placeholder.h>

#include "ft/forward.h"

#include "gm/gm_1601.h"
#include "gm/types.h"
#include "mn/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/// struct ResultsData {
///     /*  +0 */ char pad_0[0x94];
///     /* +94 */ int x94;
///     /* +98 */ char pad_98[0x5A8 - 0x98];
/// };
/// STATIC_ASSERT(sizeof(struct ResultsData) == 0x5A8);

struct lbl_80473700_t {
    /* +0 */ char pad_0[0x114];
};
STATIC_ASSERT(sizeof(struct lbl_80473700_t) == 0x114);

struct UnlockableCharacterData {
    /* 0x0 */ u8 idx;
    /* 0x1 */ u8 selkind;
    /* 0x2 */ u8 notification_id;
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
/* 3B7888 */ static const u8 selkind_to_ckind_map[0x1C] = {
    CKIND_CAPTAIN, CKIND_DONKEY,  CKIND_FOX,      CKIND_GAMEWATCH,
    CKIND_KIRBY,   CKIND_KOOPA,   CKIND_LINK,     CKIND_LUIGI,
    CKIND_MARIO,   CKIND_MARS,    CKIND_MEWTWO,   CKIND_NESS,
    CKIND_PEACH,   CKIND_PIKACHU, CKIND_POPONANA, CKIND_PURIN,
    CKIND_SAMUS,   CKIND_YOSHI,   CKIND_ZELDA,    CKIND_FALCO,
    CKIND_CLINK,   CKIND_DRMARIO, CKIND_EMBLEM,   CKIND_PICHU,
    CKIND_GANON,
};

/* 3B78A4 */ static const u8 ckind_to_selkind_map[CHKIND_MAX] = {
    /* 00 */ SELKIND_CAPTAIN,
    /* 01 */ SELKIND_DONKEY,
    /* 02 */ SELKIND_FOX,
    /* 03 */ SELKIND_GAMEWATCH,
    /* 04 */ SELKIND_KIRBY,
    /* 05 */ SELKIND_KOOPA,
    /* 06 */ SELKIND_LINK,
    /* 07 */ SELKIND_LUIGI,
    /* 08 */ SELKIND_MARIO,
    /* 09 */ SELKIND_MARS,
    /* 0A */ SELKIND_MEWTWO,
    /* 0B */ SELKIND_NESS,
    /* 0C */ SELKIND_PEACH,
    /* 0D */ SELKIND_PIKACHU,
    /* 0E */ SELKIND_POPONANA,
    /* 0F */ SELKIND_PURIN,
    /* 10 */ SELKIND_SAMUS,
    /* 11 */ SELKIND_YOSHI,
    /* 12 */ SELKIND_ZELDA_SEAK,
    /* 13 */ SELKIND_ZELDA_SEAK,
    /* 14 */ SELKIND_FALCO,
    /* 15 */ SELKIND_CLINK,
    /* 16 */ SELKIND_DRMARIO,
    /* 17 */ SELKIND_EMBLEM,
    /* 18 */ SELKIND_PICHU,
    /* 19 */ SELKIND_GANON,
    /* 1A */ SELKIND_MARIO,
    /* 1B */ SELKIND_MARIO,
    /* 1C */ SELKIND_MARIO,
    /* 1D */ SELKIND_COUNT,
    /* 1E */ SELKIND_MARIO,
    /* 1F */ SELKIND_MARIO,
    /* 20 */ SELKIND_CAPTAIN
};

/* 3B78C8 */ static const struct UnlockableCharacterData
    lbl_803B78C8[NUM_UNLOCKABLE_CHARACTERS] = {
        {
            0,
            SELKIND_GAMEWATCH,
            4,
            0,
            0x116,
        },
        {
            1,
            SELKIND_LUIGI,
            2,
            0,
            0x114,
        },
        {
            2,
            SELKIND_MARS,
            3,
            0,
            0x115,
        },
        {
            3,
            SELKIND_MEWTWO,
            1,
            0,
            0x113,
        },
        {
            4,
            SELKIND_PURIN,
            0,
            0,
            0x112,
        },
        {
            5,
            SELKIND_FALCO,
            8,
            0,
            0x11A,
        },
        {
            6,
            SELKIND_CLINK,
            7,
            0,
            0x119,
        },
        {
            7,
            SELKIND_DRMARIO,
            5,
            0,
            0x117,
        },
        {
            8,
            SELKIND_EMBLEM,
            0xA,
            0,
            0x11C,
        },
        {
            9,
            SELKIND_PICHU,
            9,
            0,
            0x11B,
        },
        {
            0xA,
            SELKIND_GANON,
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
/* 46B378 */ static struct lbl_8046B378_t lbl_8046B378;
/* 46B488 */ static struct lbl_8046B488_t lbl_8046B488;
/* 46B668 */ static struct lbl_8046B668_t lbl_8046B668;
/* 4D6598 */ static s8 lbl_804D6598;
/* 4D659A */ static u16 lbl_804D659A;
#endif
