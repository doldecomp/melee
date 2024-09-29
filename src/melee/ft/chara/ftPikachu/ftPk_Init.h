#ifndef GALE01_1243AC
#define GALE01_1243AC

#include <platform.h>

#include "ftPikachu/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 1243AC */ void ftPk_Init_OnLoad(HSD_GObj* gobj);
/* 1243E4 */ void ftPk_Init_OnLoadForPichu(Fighter* fp);
/* 124474 */ void ftPk_Init_OnDeath(HSD_GObj* gobj);
/* 1244B8 */ void ftPk_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
/* 124598 */ void ftPk_Init_OnItemInvisible(HSD_GObj* gobj);
/* 1245E0 */ void ftPk_Init_OnItemVisible(HSD_GObj* gobj);
/* 124628 */ void ftPk_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
/* 12467C */ void ftPk_Init_UnkMotionStates1(HSD_GObj* gobj);
/* 1246C0 */ void ftPk_Init_UnkMotionStates2(HSD_GObj* gobj);
/* 124704 */ void ftPk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 1247A8 */ void ftPk_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 1247EC */ void ftPk_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3CDD78 */ extern MotionState ftPk_Init_MotionStateTable[ftPk_MS_SelfCount];
/* 3CE0B8 */ extern char ftPk_Init_DatFilename[];
/* 3CE0C4 */ extern char ftPk_Init_DataName[];
/* 3CE204 */ extern char ftPk_Init_AnimDatFilename[];
/* 3CE290 */ extern Fighter_DemoStrings ftPk_Init_DemoMotionFilenames;
/* 3CE2A0 */ extern Fighter_CostumeStrings ftPk_Init_CostumeStrings[];

#endif
