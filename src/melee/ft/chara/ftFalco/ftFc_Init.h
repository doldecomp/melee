#ifndef _ftfalco_h_
#define _ftfalco_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftFc_Init_MotionStateTable[];
extern char ftFc_Init_DatFilename[];
extern char ftFc_Init_DataName[];
extern Fighter_CostumeStrings ftFc_Init_CostumeStrings[];
extern char ftFc_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftFc_Init_DemoMotionFilenames;

void ftFc_Init_OnDeath(HSD_GObj*);
void ftFc_Init_OnItemPickup(HSD_GObj*, bool);
void ftFc_Init_OnItemInvisible(HSD_GObj*);
void ftFc_Init_OnItemVisible(HSD_GObj*);
void ftFc_Init_OnItemDrop(HSD_GObj*, bool);
void ftFc_Init_OnLoad(HSD_GObj*);
void ftFc_Init_LoadSpecialAttrs(HSD_GObj*);
void ftFc_Init_OnKnockbackEnter(HSD_GObj*);
void ftFc_Init_OnKnockbackExit(HSD_GObj*);

#endif
