#ifndef MELEE_MN_MNDIAGRAM3_STATIC_H
#define MELEE_MN_MNDIAGRAM3_STATIC_H

#include "mndiagram3.h" // IWYU pragma: export
#include <dolphin/gx/GXStruct.h>

typedef struct mnDiagram3_PosTable {
    /* 0x00 */ Vec3 x0;  ///< title_pos (3.3,0.5,0)
    /* 0x0C */ Vec3 xC;  ///< rank_name_pos (-2,0.57,0)
    /* 0x18 */ Vec3 x18; ///< value_pos (8,0.57,0)
} mnDiagram3_PosTable;

typedef struct mnDiagram3_StatTable {
    /* 0x00 */ u16 label_ids[24];      ///< SIS string ids, 0x62..0x79
    /* 0x30 */ u16 unit_glyph_ids[24]; ///< mnDiagram2 unit/icon column entries
} mnDiagram3_StatTable;

typedef struct mnDiagram3_DataTable {
    /* 0x00 */ AnimLoopSettings x0;
    /* 0x0C */ AnimLoopSettings xC;
    /* 0x18 */ mnDiagram3_PosTable positions;
    /* 0x3C */ mnDiagram3_StatTable stats;
} mnDiagram3_DataTable;

/* 3EEC10 */ extern AnimLoopSettings mnDiagram3_803EEC10;
/* 3EEC1C */ extern AnimLoopSettings mnDiagram3_803EEC1C;
/* 3EEC28 */ extern mnDiagram3_PosTable mnDiagram3_803EEC28;
/* 3EEC4C */ extern mnDiagram3_StatTable mnDiagram3_803EEC4C;
/* 4D6C20 */ extern HSD_GObj* mnDiagram3_804D6C20;
/* 4D4B64 */ extern GXColor mn_804D4B64;

#endif
