#ifndef _ftemblem_h_
#define _ftemblem_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftFe_Init_MotionStateTable[];
extern char ftFe_Init_DatFilename[];
extern char ftFe_Init_DataName[];
extern Fighter_CostumeStrings ftFe_Init_CostumeStrings[];
extern char ftFe_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftFe_Init_DemoMotionFilenames;

void ftFe_Init_OnDeath(HSD_GObj*);
void ftFe_Init_OnItemPickup(HSD_GObj*, bool);
void ftFe_Init_OnItemInvisible(HSD_GObj*);
void ftFe_Init_OnItemVisible(HSD_GObj*);
void ftFe_Init_OnItemDrop(HSD_GObj*, bool);
void ftFe_Init_OnLoad(HSD_GObj*);
void ftFe_Init_LoadSpecialAttrs(HSD_GObj*);
void ftFe_Init_OnKnockbackEnter(HSD_GObj*);
void ftFe_Init_OnKnockbackExit(HSD_GObj*);

#endif
