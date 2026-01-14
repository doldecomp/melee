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
    u8 x2;
    u8 x3;
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

/* Trophy metadata entry. Size: 0x24 bytes. */
typedef struct TrophyData {
    s32 id;
    s32 x04;
    f32 x08;
    f32 x0C;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    s8 x20;
    s8 x21;
    s8 x22;
    s8 x23;
} TrophyData;

/* Trophy list entry. Size: 0x34 bytes. */
typedef struct TyListArg {
    /* 0x00 */ struct TyListArg* x0;
    /* 0x04 */ struct TyListArg* x4;
    /* 0x08 */ void* x8;
    /* 0x0C */ struct HSD_JObj* xC;
    /* 0x10 */ struct HSD_JObj* x10;
    /* 0x14 */ struct HSD_JObj* x14;
    /* 0x18 */ u8 pad_18[0x26 - 0x18];
    /* 0x26 */ s16 idx;
    /* 0x28 */ u8 pad_28[0x2C - 0x28];
    /* 0x2C */ float x2C;
    /* 0x30 */ float x30;
} TyListArg;

/* Trophy list UI state. Size: 0x2D8 bytes. */
typedef struct TyListState {
    /* 0x000 */ TyListArg entries[12]; /* 12 * 0x34 = 0x270 */
    /* 0x270 */ u8 pad_270[0xC];
    /* 0x27C */ struct HSD_GObj* gobj;
    /* 0x280 */ u8 pad_280[0xC];
    /* 0x28C */ struct HSD_JObj* jobj;
    /* 0x290 */ u8 pad_290[8];
    /* 0x298 */ s16 selectedIdx;
    /* 0x29A */ s8 entryCount;
    /* 0x29B */ u8 x29B;
    /* 0x29C */ u8 x29C;
    /* 0x29D */ u8 pad_29D;
    /* 0x29E */ u8 x29E;
    /* 0x29F */ u8 x29F;
    /* 0x2A0 */ u8 pad_2A0;
    /* 0x2A1 */ u8 x2A1;
    /* 0x2A2 */ u8 pad_2A2[2];
    /* 0x2A4 */ float x2A4;
    /* 0x2A8 */ float x2A8;
    /* 0x2AC */ struct HSD_GObj* gobj_2AC;
    /* 0x2B0 */ struct HSD_GObj* gobj_2B0;
    /* 0x2B4 */ u8 pad_2B4[4];
    /* 0x2B8 */ u8 x2B8;
    /* 0x2B9 */ u8 pad_2B9[0xB];
    /* 0x2C4 */ struct HSD_GObj* gobj_2C4;
    /* 0x2C8 */ u8 pad_2C8[0x10];
} TyListState;

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
    /* +19E */ u16 trophyTable[0x125];
    /* +3E8 */ char pad_3E8[0x3EC - 0x3E8];
    /* +3EC */ s16 trophyCount;
};

#endif
