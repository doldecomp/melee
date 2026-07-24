#ifndef MELEE_GM_GMREGCLEAR_DATA_H
#define MELEE_GM_GMREGCLEAR_DATA_H

#include <platform.h>

/// Adventure mode stage data table entry (size 0x1A).
/// Table has 110 entries: 22 stages × 5 difficulty levels.
typedef struct AdventureStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct;
    /* 0x04 */ u16 scale1_pct;
    /* 0x06 */ u8 pad_6[0x14];
} AdventureStageEntry;
STATIC_ASSERT(sizeof(AdventureStageEntry) == 0x1A);

/// All-Star mode stage data table entry (size 0x1A).
/// Table has 55 entries: 11 stages × 5 difficulty levels.
typedef struct AllstarStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct;
    /* 0x04 */ u16 scale1_pct;
    /* 0x06 */ u8 pad_6[0xA];
    /* 0x10 */ u16 scale2_pct;
    /* 0x12 */ u16 scale3_pct;
    /* 0x14 */ u8 pad_14[0x6];
} AllstarStageEntry;
STATIC_ASSERT(sizeof(AllstarStageEntry) == 0x1A);

struct AdventureStageTable {
    AdventureStageEntry entries[110];
    u8 pad[4];
};

struct AllstarStageTable {
    AllstarStageEntry entries[55];
    u8 pad[2];
};

extern struct AdventureStageTable lbl_803D7AC0;
extern struct AllstarStageTable lbl_803D85F0;

#endif
