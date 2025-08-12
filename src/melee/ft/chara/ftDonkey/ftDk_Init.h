#ifndef GALE01_10D740
#define GALE01_10D740

#include "ft/types.h"

#include "ftDonkey/forward.h"

/* 10D740 */ void ftDk_Init_OnDeath(HSD_GObj* gobj);
/* 10D774 */ void ftDk_Init_8010D774(HSD_GObj* gobj);
/* 10D7A8 */ void ftDk_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 10D888 */ void ftDk_Init_OnItemInvisible(HSD_GObj* gobj);
/* 10D8D0 */ void ftDk_Init_OnItemVisible(HSD_GObj* gobj);
/* 10D918 */ void ftDk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
/* 10D96C */ void ftDk_Init_UnkMotionStates4(HSD_GObj* gobj);
/* 10D9AC */ void ftDk_Init_OnLoad(HSD_GObj* gobj);
/* 10DA74 */ void ftDk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 10DAB4 */ void ftDk_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 10DAF8 */ void ftDk_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 10DB3C */ void ftDk_Init_8010DB3C(HSD_GObj* gobj);
/* 3CB838 */ extern MotionState ftDk_Init_MotionStateTable[ftDk_MS_SelfCount];
/* 3CBDF8 */ extern Fighter_CostumeStrings ftDk_Init_CostumeStrings[];
/* 3CBE04 */ extern char ftDk_Init_DatFilename[];
/* 3CBF88 */ extern char ftDk_Init_AnimDatFilename[];
/* 3CC010 */ extern Fighter_DemoStrings ftDk_Init_DemoMotionFilenames;
/* 3CC020 */ extern char ftDk_Init_DataName[];

#endif
