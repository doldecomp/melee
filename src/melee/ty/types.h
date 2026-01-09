#ifndef MELEE_TY_TYPES_H
#define MELEE_TY_TYPES_H

#include "platform.h"

#include <placeholder.h>

#include "ty/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <dolphin/mtx.h>

typedef struct TyModeState {
    s8 x0;
    u8 x1;
    u16 x2;
    s8 x4;
    u8 x5;
    u16 x6;
    u16 x8;
    u16 xA;
} TyModeState;

/* Located at un_804A26B8 + 0x3F0 */
typedef struct ToyAnimState {
    /* 0x00 */ struct HSD_GObj* gobj;
    /* 0x04 */ struct HSD_JObj* jobj[2];
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s8 x0E;
    /* 0x0F */ s8 x0F;
    /* 0x10 */ s8 x10;
    /* 0x11 */ s8 x11;
} ToyAnimState;

/* Used by un_803109A0 for table lookup */
typedef struct ToyEntry {
    s32 id;
    union {
        s32 value;
        s8 value_byte;
    };
} ToyEntry;

/* Used by un_803060BC for trophy data lookup. 0x24 bytes per entry. */
typedef struct TrophyData {
    s32 id;  /* 0x00 - trophy ID, -1 for end sentinel */
    s32 x04; /* 0x04 - category (case 8) */
    f32 x08; /* 0x08 - field 0 */
    f32 x0C; /* 0x0C - field 1 */
    f32 x10; /* 0x10 - field 2 */
    f32 x14; /* 0x14 - field 3 */
    f32 x18; /* 0x18 - field 4 */
    f32 x1C; /* 0x1C - field 5 */
    s8 x20;  /* 0x20 - field 6 */
    s8 x21;  /* 0x21 - field 7 */
    s8 x22;  /* 0x22 - padding */
    s8 x23;  /* 0x23 - padding */
} TrophyData;

struct Toy {
    /*   +0 */ char pad_0[0x4];
    /*   +4 */ int x4;
    /*   +8 */ int x8;
    /*   +C */ char pad_C[0x40 - 0xC];
    /*  +40 */ Vec3 translate;
    /*  +4C */ Vec3 offset;
    /*  +58 */ char pad_58[0x194 - 0x58];
    /* +194 */ s32 x194;
    /* +198 */ char pad_198[0x19A - 0x198];
    /* +19A */ u16 x19A;
    /* +19C */ u16 x19C;
    /* +19E */ u16 trophyTable[0x125]; /* Trophy unlock states (0x24A bytes) */
    /* +3E8 */ char pad_3E8[0x3EC - 0x3E8];
    /* +3EC */ s16 trophyCount;
};

#endif
