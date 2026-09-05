#ifndef GALE01_155E18
#define GALE01_155E18

#include <melee/ft/types.h>

#include <melee/ft/kinds/ftCrazyHand/forward.h>

/* 155E18 */ void ftCh_Init_OnDeath(HSD_GObj* gobj);
/* 155E1C */ void ftCh_Init_OnLoad(HSD_GObj* gobj);
/* 155F8C */ void ftCh_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/* 3D41F8 */ extern MotionState ftCh_Init_MotionStateTable[ftCh_MS_SelfCount];
/* 3D4818 */ extern char ftCh_Init_DatFilename[];
/* 3D4824 */ extern char ftCh_Init_DataName[];
/* 3D485C */ extern char ftCh_Init_AnimDatFilename[];
/* 3D4868 */ extern Fighter_CostumeStrings ftCh_Init_CostumeStrings[];
/* 45A6A8 */ extern UnkCostumeStruct ftCh_CostumeList[1];

#endif
