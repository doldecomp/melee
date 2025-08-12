#include "sobjlib.h"

#include "objalloc.h"

/* 004DB670 */ extern const s32 HSD_SObjLib_804DEA90;
/* 004DB66C */ extern const s32 HSD_SObjLib_804DEA8C;
/* 004DB668 */ extern const s32 HSD_SObjLib_804DEA88;
/* 004DB664 */ extern const s32 HSD_SObjLib_804DEA84;
/* 004DB660 */ extern const s32 HSD_SObjLib_804DEA80;
/* 004D4540 */ extern u8 HSD_SObjLib_804D7960;
/* 004CDCC0 */ extern HSD_ObjAllocData HSD_SObjLib_804D10E0;
/* 00408F90 */ extern s8 HSD_SObjLib_8040C3B0[10];
/* 00408F80 */ extern UNK_T HSD_SObjLib_8040C3A0;
/* 003B6244 */ extern Vec3 HSD_SObjLib_803B9664;
/* 003B6238 */ extern Vec3 HSD_SObjLib_803B9658;

HSD_ObjAllocData HSD_SObjLib_804D10E0;

void HSD_SObjLib_803A44A4(void)
{
    HSD_ObjAllocInit(&HSD_SObjLib_804D10E0, 0x9C, 4);
}
