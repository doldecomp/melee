#ifndef GALE01_14EEF8
#define GALE01_14EEF8

#include "ft/types.h"

#include "ftMars/forward.h"
#include <baselib/forward.h>

/* 14EEF8 */ void ftFe_Init_OnDeath(HSD_GObj*);
/* 14EF60 */ void ftFe_Init_OnItemPickup(HSD_GObj*, bool);
/* 14F040 */ void ftFe_Init_OnItemInvisible(HSD_GObj*);
/* 14F088 */ void ftFe_Init_OnItemVisible(HSD_GObj*);
/* 14F0D0 */ void ftFe_Init_OnItemDrop(HSD_GObj*, bool);
/* 14F124 */ void ftFe_Init_OnLoad(HSD_GObj*);
/* 14F148 */ void ftFe_Init_LoadSpecialAttrs(HSD_GObj*);
/* 14F168 */ void ftFe_Init_OnKnockbackEnter(HSD_GObj*);
/* 14F1AC */ void ftFe_Init_OnKnockbackExit(HSD_GObj*);
/* 3D2E80 */ extern MotionState ftFe_Init_MotionStateTable[ftMs_MS_SelfCount];
/* 3D3280 */ extern Fighter_CostumeStrings ftFe_Init_CostumeStrings[];
/* 3D328C */ extern char ftFe_Init_DatFilename[];
/* 3D3410 */ extern char ftFe_Init_AnimDatFilename[];
/* 3D3498 */ extern Fighter_DemoStrings ftFe_Init_DemoMotionFilenames;
/* 3D34A8 */ extern char ftFe_Init_DataName[];

#endif
