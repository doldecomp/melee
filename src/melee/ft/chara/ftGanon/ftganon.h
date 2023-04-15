#ifndef _ftganon_h_
#define _ftganon_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftGn_Init_MotionStateTable[];
extern char ftGn_Init_DatFilename[];
extern char ftGn_Init_DataName[];
extern Fighter_CostumeStrings ftGn_Init_CostumeStrings[];
extern char ftGn_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftGn_Init_DemoMotionFilenames;

void ftGn_Init_OnDeath(HSD_GObj*);
void ftGn_Init_OnItemPickup(HSD_GObj*, bool);
void ftGn_Init_OnItemInvisible(HSD_GObj*);
void ftGn_Init_OnItemVisible(HSD_GObj*);
void ftGn_Init_OnItemDrop(HSD_GObj*, bool);
void ftGn_Init_OnLoad(HSD_GObj*);
void ftGn_Init_LoadSpecialAttrs(HSD_GObj*);
void ftGn_Init_OnKnockbackEnter(HSD_GObj*);
void ftGn_Init_OnKnockbackExit(HSD_GObj*);
void ftCa_SpecialLw_800E4B00(HSD_GObj*);
void ftCa_SpecialLw_800E4B60(HSD_GObj*);
void ftCa_SpecialLw_800E4BF8(HSD_GObj*);
void ftCa_SpecialLw_800E4E1C(HSD_GObj*);
void ftCa_SpecialLw_800E4EE8(HSD_GObj*);
void ftCa_SpecialLw_800E4F48(HSD_GObj*);
void ftCa_SpecialLw_800E4FDC(HSD_GObj*);
void ftCa_SpecialLw_800E50D8(HSD_GObj*);
void ftCa_SpecialLw_800E51F8(HSD_GObj*);
void ftCa_SpecialLw_800E5234(HSD_GObj*);
void ftCa_SpecialLw_800E5238(HSD_GObj*);
void ftCa_SpecialLw_800E523C(HSD_GObj*);
void ftCa_SpecialLw_800E5310(HSD_GObj*);
void ftCa_SpecialLw_800E5384(HSD_GObj*);
void ftCa_SpecialLw_800E5388(HSD_GObj*);
void ftCa_SpecialLw_800E54B8(HSD_GObj*);
void ftCa_SpecialHi_800E415C(HSD_GObj*);
void ftCa_SpecialHi_800E4408(HSD_GObj*);
void ftCa_SpecialHi_800E46B8(HSD_GObj*);
void ftCa_SpecialHi_800E4268(HSD_GObj*);
void ftCa_SpecialHi_800E449C(HSD_GObj*);
void ftCa_SpecialHi_800E47B0(HSD_GObj*);
void ftCa_SpecialHi_800E42E0(HSD_GObj*);
void ftCa_SpecialHi_800E45E4(HSD_GObj*);
void ftCa_SpecialHi_800E48BC(HSD_GObj*);
void ftCa_SpecialHi_800E4354(HSD_GObj*);
void ftCa_SpecialHi_800E4618(HSD_GObj*);
void ftCa_SpecialHi_800E493C(HSD_GObj*);
void ftCa_SpecialHi_800E4390(HSD_GObj*);
void ftCa_SpecialHi_800E4678(HSD_GObj*);
void ftCa_SpecialHi_800E495C(HSD_GObj*);
void ftCa_SpecialHi_800E42A4(HSD_GObj*);
void ftCa_SpecialHi_800E455C(HSD_GObj*);
void ftCa_SpecialHi_800E4838(HSD_GObj*);
void ftCa_SpecialHi_800E43CC(HSD_GObj*);
void ftCa_SpecialHi_800E4698(HSD_GObj*);
void ftCa_SpecialLw_800E49DC(HSD_GObj*);

#endif
