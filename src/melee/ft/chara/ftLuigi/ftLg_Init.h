#ifndef MELEE_FT_CHARA_FTLUIGI_FTLG_INIT_H
#define MELEE_FT_CHARA_FTLUIGI_FTLG_INIT_H

#include "it/forward.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <common_structs.h>

extern MotionState ftLg_Init_MotionStateTable[];
extern MotionState ftLg_Init_UnkMotionStates0[];
extern char ftLg_Init_DatFilename[];
extern char ftLg_Init_DataName[];
extern Fighter_CostumeStrings ftLg_Init_CostumeStrings[];
extern char ftLg_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftLg_Init_DemoMotionFilenames;

void ftLg_Init_OnLoad(HSD_GObj* gobj);
void ftLg_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
void ftLg_Init_OnItemInvisible(HSD_GObj* gobj);
void ftLg_Init_OnItemVisible(HSD_GObj* gobj);
void ftLg_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
void ftLg_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftLg_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftLg_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftLg_Init_UnkDemoCallbacks0(s32 arg0, s32* arg1, s32* arg2);
void ftLg_Init_OnDeath(HSD_GObj* gobj);
char* ftLg_Init_GetMotionFileString(enum_t demoMotionArg);

#endif
