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
void ftCa_SpecialHi_Anim(HSD_GObj*);
void ftCa_SpecialHi_IASA(HSD_GObj*);
void ftCa_SpecialHi_Phys(HSD_GObj*);
void ftCa_SpecialHi_Coll(HSD_GObj*);
void ftCa_SpecialAirHi_Anim(HSD_GObj*);
void ftCa_SpecialAirHi_IASA(HSD_GObj*);
void ftCa_SpecialAirHi_Phys(HSD_GObj*);
void ftCa_SpecialAirHi_Coll(HSD_GObj*);
void ftCa_SpecialHiCatch_Anim(HSD_GObj*);
void ftCa_SpecialHiCatch_IASA(HSD_GObj*);
void ftCa_SpecialHiCatch_Phys(HSD_GObj*);
void ftCa_SpecialHiCatch_Coll(HSD_GObj*);
void ftCa_SpecialHiThrow_Anim(HSD_GObj*);
void ftCa_SpecialHiThrow_IASA(HSD_GObj*);
void ftCa_SpecialHiThrow_Phys(HSD_GObj*);
void ftCa_SpecialHiThrow_Coll(HSD_GObj*);
void ftCa_SpecialLw_Anim(HSD_GObj*);
void ftCa_SpecialLw_Phys(HSD_GObj*);
void ftCa_SpecialLwColl(HSD_GObj*);
void ftCa_SpecialLwGroundEnd_Anim(HSD_GObj*);
void ftCa_SpecialLwGroundEnd_Phys(HSD_GObj*);
void ftCa_SpecialLwGroundEnd_Coll(HSD_GObj*);
void ftCa_SpecialAirLw_Anim(HSD_GObj*);
void ftCa_SpecialAirLw_Phys(HSD_GObj*);
void ftCa_SpecialAirLwColl(HSD_GObj*);
void ftCa_SpecialAirLwGroundEnd_Anim(HSD_GObj*);
void ftCa_SpecialAirLwGroundEnd_Phys(HSD_GObj*);
void ftCa_SpecialAirLwGroundEnd_Coll(HSD_GObj*);
void ftCa_SpecialAirLwAirEnd_Anim(HSD_GObj*);
void ftCa_SpecialAirLwAirEnd_Phys(HSD_GObj*);
void ftCa_SpecialAirLwAirEnd_Coll(HSD_GObj*);
void ftCa_SpecialLwAirEnd_Anim(HSD_GObj*);
void ftCa_SpecialLwAirEnd_Phys(HSD_GObj*);
void ftCa_SpecialLwAirEnd_Coll(HSD_GObj*);
void ftCa_SpecialLwRebound_Anim(HSD_GObj*);
void ftCa_SpecialLwRebound_Phys(HSD_GObj*);
void ftCa_SpecialLwRebound_Coll(HSD_GObj*);

#endif
