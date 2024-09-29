#ifndef GALE01_149ACC
#define GALE01_149ACC

#include <platform.h>

#include "ftFox/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 149ACC */ void ftFc_Init_OnDeath(HSD_GObj*);
/* 149B00 */ void ftFc_Init_OnItemPickup(HSD_GObj*, bool flag);
/* 149BE0 */ void ftFc_Init_OnItemInvisible(HSD_GObj*);
/* 149C28 */ void ftFc_Init_OnItemVisible(HSD_GObj*);
/* 149C70 */ void ftFc_Init_OnItemDrop(HSD_GObj*, bool flag);
/* 149CC4 */ void ftFc_Init_OnLoad(HSD_GObj*);
/* 149D3C */ void ftFc_Init_LoadSpecialAttrs(HSD_GObj*);
/* 149D5C */ void ftFc_Init_OnKnockbackEnter(HSD_GObj*);
/* 149DC8 */ void ftFc_Init_OnKnockbackExit(HSD_GObj*);
/* 3D1848 */ extern MotionState ftFc_Init_MotionStateTable[ftFx_MS_SelfCount];
/* 3D1CA8 */ extern Fighter_CostumeStrings ftFc_Init_CostumeStrings[];
/* 3D1CB4 */ extern char ftFc_Init_DatFilename[];
/* 3D1DE8 */ extern char ftFc_Init_AnimDatFilename[];
/* 3D1E64 */ extern Fighter_DemoStrings ftFc_Init_DemoMotionFilenames;
/* 3D1E74 */ extern char ftFc_Init_DataName[];

#endif
