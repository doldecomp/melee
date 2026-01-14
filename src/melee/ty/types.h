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

/**
 * Trophy metadata entry used by un_803060BC for trophy data lookup.
 * Size: 0x24 bytes per entry.
 *
 * Evidence for struct layout:
 * - un_803060BC switch statement accesses fields by index:
 *   - cases 0-5: return float fields x08-x1C
 *   - case 6: return (float) x20 (s8)
 *   - case 7: return (float) x21 (s8)
 *   - case 8: return (float) x04 (category)
 * - id (s32): compared to -1 sentinel and int trophyId in table search loops
 *   (lines 331-332, 359-360 in toy.c), matches s32 to produce correct cmpwi
 */
typedef struct TrophyData {
    s32 id;  /* 0x00 - compared to -1 sentinel and int trophyId */
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

/**
 * Entry in the trophy list UI. Size: 0x34 bytes.
 * Used in TyListState entries array.
 */
typedef struct TyListArg {
    /* 0x00 */ void* x0;
    /* 0x04 */ void* x4;
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

/**
 * Trophy list UI state. Located at un_804A2AC0.
 * Size: 0x2D8 bytes.
 *
 * Evidence from tylist.c:
 * - memzero(&data[0], 0x2AC) clears entries + fields up to 0x2AC
 * - memzero(&data[0x2AC], 0x18) clears gobj_2AC area
 * - memzero(&data[0x2C4], 0x14) clears gobj_2C4 area
 */
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
    /**
     * Trophy unlock states array. 0x125 (293) entries for each trophy ID.
     * Evidence: Trophy_SetUnlockState uses toy->trophyTable as u16 array
     * indexed by trophyId. gmMainLib_8015CC78 returns same data from save.
     * Size: 0x24A bytes (293 * 2).
     */
    /* +19E */ u16 trophyTable[0x125];
    /* +3E8 */ char pad_3E8[0x3EC - 0x3E8];
    /**
     * Count of unlocked trophies.
     * Evidence (s16): Trophy_SetUnlockState casts to s16 on assignment
     * (line 198 in toy.c: toy->trophyCount = (s16) newCount).
     * gmMainLib_8015CC90 returns s16* to same field in save data.
     */
    /* +3EC */ s16 trophyCount;
};

#endif
