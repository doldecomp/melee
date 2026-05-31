#ifndef __GALE01_245BA4
#define __GALE01_245BA4

#include "mndiagram2.static.h" // IWYU pragma: export

#include "mndiagram3.h" // IWYU pragma: export

#include <placeholder.h>

#include <melee/mn/types.h>

typedef struct mnDiagram3_PosTable {
    /* 0x00 */ Vec3 x0;
    /* 0x0C */ Vec3 xC;
    /* 0x18 */ Vec3 x18;
} mnDiagram3_PosTable;

typedef struct mnDiagram3_StatTable {
    /* 0x00 */ u16 indices[0x28];
    /* 0x50 */ char x50[0x18];
    /* 0x68 */ char x68[0x10];
    /* 0x78 */ char x78[0x1C];
} mnDiagram3_StatTable;

/* 3EEC10 */ extern AnimLoopSettings mnDiagram3_803EEC10;
/* 3EEC1C */ extern AnimLoopSettings mnDiagram3_803EEC1C;
/* 3EEC28 */ extern mnDiagram3_PosTable mnDiagram3_803EEC28;
/* 3EEC4C */ extern mnDiagram3_StatTable mnDiagram3_803EEC4C;
/* 4A0844 */ extern mnDiagram_ArchiveData mnDiagram_804A0844;
/* 4A0854 */ extern mnDiagram_ArchiveData mnDiagram_804A0854;
/* 4D6C20 */ extern HSD_GObj* mnDiagram3_804D6C20;
/* 4D6C24 */ extern HSD_GObj* mnDiagram3_804D6C24;
/* 4D4B64 */ extern GXColor mn_804D4B64;
/* 4DBFF0 */ extern f64 mnDiagram3_804DBFF0;
/* 4DBFF8 */ extern f32 mnDiagram3_804DBFF8;
/* 4DBFFC */ extern f32 mnDiagram3_804DBFFC;
/* 4DC000 */ extern f64 mnDiagram3_804DC000;
/* 4DC008 */ extern f32 mnDiagram3_804DC008;
/* 4DC00C */ extern f32 mnDiagram3_804DC00C;
/* 4DC010 */ extern f32 mnDiagram3_804DC010;
/* 4DC014 */ extern f32 mnDiagram3_804DC014;

/* 2461BC */ void fn_802461BC(HSD_GObj* gobj);

#endif
