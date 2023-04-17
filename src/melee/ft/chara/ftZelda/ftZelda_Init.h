#ifndef MELEE_FT_CHARA_FTZELDA_FTZELDA_H
#define MELEE_FT_CHARA_FTZELDA_FTZELDA_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftZd_Init_MotionStateTable[];
extern char ftZd_Init_DatFilename[];
extern char ftZd_Init_DataName[];
extern Fighter_CostumeStrings ftZd_Init_CostumeStrings[];
extern char ftZd_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftZd_Init_DemoMotionFilenames;

// ftzelda 1
void ftZd_Init_OnDeath(HSD_GObj* gobj);
void ftZd_Init_OnLoad(HSD_GObj* gobj);
void ftZd_Init_801393AC(HSD_GObj* gobj);
void ftZd_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftZd_Init_OnItemInvisible(HSD_GObj* gobj);
void ftZd_Init_OnItemVisible(HSD_GObj* gobj);
void ftZd_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftZd_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftZd_Init_801395C8(HSD_GObj* gobj);
void ftZd_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftZd_Init_OnKnockbackExit(HSD_GObj* gobj);

// ftzelda 2
void ftZd_SpecialHi_801396AC(HSD_GObj* gobj);
void ftZd_SpecialHi_801396E0(HSD_GObj* gobj);
void ftZd_SpecialHi_8013979C(HSD_GObj* gobj);
void ftZd_SpecialHi_Enter(HSD_GObj* gobj);
void ftZd_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftZd_SpecialHiStart_Anim(HSD_GObj* arg0);
void ftZd_SpecialAirHiStart_Anim(HSD_GObj* arg0);
void ftZd_SpecialHiStart_IASA(HSD_GObj* arg0);
void ftZd_SpecialAirHiStart_IASA(HSD_GObj* arg0);
void ftZd_SpecialHiStart_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirHiStart_Phys(HSD_GObj* gobj);
void ftZd_SpecialHiStart_Coll(HSD_GObj* arg0);
void ftZd_SpecialAirHiStart_Coll(HSD_GObj* gobj);
void ftZd_SpecialHi_80139B44(HSD_GObj* gobj);
void ftZd_SpecialHi_80139BB0(HSD_GObj* gobj);
void ftZd_SpecialHi_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftZd_SpecialHi_IASA(HSD_GObj* arg0);
void ftZd_SpecialAirHi_IASA(HSD_GObj* arg0);
void ftZd_SpecialHi_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirHi_Phys(HSD_GObj* arg0);
void ftZd_SpecialHi_Coll(HSD_GObj* gobj);
void ftZd_SpecialAirHi_Coll(HSD_GObj* gobj);
void ftZd_SpecialHi_80139F6C(HSD_GObj* gobj);
void ftZd_SpecialHi_80139FE8(HSD_GObj* gobj);
void ftZd_SpecialHi_8013A058(HSD_GObj* gobj);
void ftZd_SpecialHi_8013A244(HSD_GObj* gobj);
void ftZd_SpecialHiEnd_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirHiEnd_Anim(HSD_GObj* gobj);
void ftZd_SpecialHiEnd_IASA(HSD_GObj* arg0);
void ftZd_SpecialAirHiEnd_IASA(HSD_GObj* arg0);
void ftZd_SpecialHiEnd_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirHiEnd_Phys(HSD_GObj* gobj);
void ftZd_SpecialHiEnd_Coll(HSD_GObj* arg0);
void ftZd_SpecialAirHiEnd_Coll(HSD_GObj* gobj);
void ftZd_SpecialHi_8013A648(HSD_GObj* gobj);
void ftZd_SpecialHi_8013A6A8(HSD_GObj* gobj);
void ftZd_SpecialHi_8013A764(HSD_GObj* gobj);

// ftzelda 3
void ftZd_SpecialN_8013A830(HSD_GObj* gobj);
void ftZd_SpecialN_8013A8AC(HSD_GObj* gobj);
void ftZd_SpecialN_Enter(HSD_GObj* gobj);
void ftZd_SpecialAirN_Enter(HSD_GObj* gobj);
void ftZd_SpecialN_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirN_Anim(HSD_GObj* gobj);
void ftZd_SpecialN_IASA(HSD_GObj* gobj);
void ftZd_SpecialAirN_IASA(HSD_GObj* gobj);
void ftZd_SpecialN_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirN_Phys(HSD_GObj* gobj);
void ftZd_SpecialN_Coll(HSD_GObj* gobj);
void ftZd_SpecialAirN_Coll(HSD_GObj* gobj);
void ftZd_SpecialN_8013AC88(HSD_GObj* gobj);
void ftZd_SpecialN_8013AD1C(HSD_GObj* gobj);
void ftZd_SpecialN_8013ADB0(HSD_GObj* gobj);

// ftzelda 4
void ftZd_SpecialLw_8013ADB4(HSD_GObj* gobj);
void ftZd_SpecialLw_8013AE30(HSD_GObj* gobj);
void ftZd_SpecialLw_8013AEAC(HSD_GObj* gobj);
void ftZd_SpecialLw_Enter(HSD_GObj* gobj);
void ftZd_SpecialAirLw_Enter(HSD_GObj* gobj);
void ftZd_SpecialLw_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftZd_SpecialLw_IASA(HSD_GObj* arg0);
void ftZd_SpecialAirLw_IASA(HSD_GObj* arg0);
void ftZd_SpecialLw_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftZd_SpecialLw_Coll(HSD_GObj* gobj);
void ftZd_SpecialAirLw_Coll(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B1CC(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B238(HSD_GObj* gobj);
void ftZd_SpecialLwEnd_Anim(HSD_GObj* arg0);
void ftZd_SpecialAirLwEnd_Anim(HSD_GObj* arg0);
void ftZd_SpecialLwEnd_IASA(HSD_GObj* arg0);
void ftZd_SpecialAirLwEnd_IASA(HSD_GObj* arg0);
void ftZd_SpecialLwEnd_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirLwEnd_Phys(HSD_GObj* gobj);
void ftZd_SpecialLwEnd_Coll(HSD_GObj* gobj);
void ftZd_SpecialAirLwEnd_Coll(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B400(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B46C(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B4D8(HSD_GObj* gobj);
s32 ftZd_SpecialLw_8013B540(HSD_GObj* gobj);
bool ftZd_SpecialLw_8013B574(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B5C4(HSD_GObj* gobj);
void ftZd_SpecialLw_8013B5EC(HSD_GObj* gobj);

// ftzelda 5
void ftZd_SpecialS_Enter(HSD_GObj* gobj);
void ftZd_SpecialAirS_Enter(HSD_GObj* gobj);
void ftZd_SpecialSStart_Anim(HSD_GObj* gobj);
void ftZd_SpecialSHold_Anim(HSD_GObj* gobj);
void ftZd_SpecialSEnd_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirSHold_Anim(HSD_GObj* gobj);
void ftZd_SpecialAirSEnd_Anim(HSD_GObj* gobj);
void ftZd_SpecialSStart_IASA(HSD_GObj* gobj);
void ftZd_SpecialSHold_IASA(HSD_GObj* gobj);
void ftZd_SpecialSEnd_IASA(HSD_GObj* gobj);
void ftZd_SpecialAirSStart_IASA(HSD_GObj* gobj);
void ftZd_SpecialAirSHold_IASA(HSD_GObj* gobj);
void ftZd_SpecialAirSEnd_IASA(HSD_GObj* gobj);
void ftZd_SpecialSHold_Phys(HSD_GObj* arg0);
void ftZd_SpecialSEnd_Phys(HSD_GObj* arg0);
void ftZd_SpecialAirSStart_Phys(HSD_GObj* gobj);
void ftZd_SpecialAirSHold_Phys(HSD_GObj* gobj);
void ftZd_SpecialAirSEnd_Phys(HSD_GObj* gobj);
void ftZd_SpecialSStart_Coll(HSD_GObj* arg0);
void ftZd_SpecialSHold_Coll(HSD_GObj* arg0);
void ftZd_SpecialSEnd_Coll(HSD_GObj* arg0);
void ftZd_SpecialAirSStart_Coll(HSD_GObj* arg0);
void ftZd_SpecialAirSHold_Coll(HSD_GObj* arg0);
void ftZd_SpecialAirSEnd_Coll(HSD_GObj* arg0);

void ftZd_SpecialN_Anim(HSD_GObj*);
void ftZd_SpecialN_IASA(HSD_GObj*);
void ftZd_SpecialN_Phys(HSD_GObj*);
void ftZd_SpecialN_Coll(HSD_GObj*);
void ftZd_SpecialAirN_Anim(HSD_GObj*);
void ftZd_SpecialAirN_IASA(HSD_GObj*);
void ftZd_SpecialAirN_Phys(HSD_GObj*);
void ftZd_SpecialAirN_Coll(HSD_GObj*);
void ftZd_SpecialSStart_Anim(HSD_GObj*);
void ftZd_SpecialSStart_IASA(HSD_GObj*);
void ftZd_SpecialSStart_Phys(HSD_GObj*);
void ftZd_SpecialSStart_Coll(HSD_GObj*);
void ftZd_SpecialSHold_Anim(HSD_GObj*);
void ftZd_SpecialSHold_IASA(HSD_GObj*);
void ftZd_SpecialSHold_Phys(HSD_GObj*);
void ftZd_SpecialSHold_Coll(HSD_GObj*);
void ftZd_SpecialSEnd_Anim(HSD_GObj*);
void ftZd_SpecialSEnd_IASA(HSD_GObj*);
void ftZd_SpecialSEnd_Phys(HSD_GObj*);
void ftZd_SpecialSEnd_Coll(HSD_GObj*);
void ftZd_SpecialAirSStart_Anim(HSD_GObj*);
void ftZd_SpecialAirSStart_IASA(HSD_GObj*);
void ftZd_SpecialAirSStart_Phys(HSD_GObj*);
void ftZd_SpecialAirSStart_Coll(HSD_GObj*);
void ftZd_SpecialAirSHold_Anim(HSD_GObj*);
void ftZd_SpecialAirSHold_IASA(HSD_GObj*);
void ftZd_SpecialAirSHold_Phys(HSD_GObj*);
void ftZd_SpecialAirSHold_Coll(HSD_GObj*);
void ftZd_SpecialAirSEnd_Anim(HSD_GObj*);
void ftZd_SpecialAirSEnd_IASA(HSD_GObj*);
void ftZd_SpecialAirSEnd_Phys(HSD_GObj*);
void ftZd_SpecialAirSEnd_Coll(HSD_GObj*);
void ftZd_SpecialHiStart_Anim(HSD_GObj*);
void ftZd_SpecialHiStart_IASA(HSD_GObj*);
void ftZd_SpecialHiStart_Phys(HSD_GObj*);
void ftZd_SpecialHiStart_Coll(HSD_GObj*);
void ftZd_SpecialHi_Anim(HSD_GObj*);
void ftZd_SpecialHi_IASA(HSD_GObj*);
void ftZd_SpecialHi_Phys(HSD_GObj*);
void ftZd_SpecialHi_Coll(HSD_GObj*);
void ftZd_SpecialHiEnd_Anim(HSD_GObj*);
void ftZd_SpecialHiEnd_IASA(HSD_GObj*);
void ftZd_SpecialHiEnd_Phys(HSD_GObj*);
void ftZd_SpecialHiEnd_Coll(HSD_GObj*);
void ftZd_SpecialAirHiStart_Anim(HSD_GObj*);
void ftZd_SpecialAirHiStart_IASA(HSD_GObj*);
void ftZd_SpecialAirHiStart_Phys(HSD_GObj*);
void ftZd_SpecialAirHiStart_Coll(HSD_GObj*);
void ftZd_SpecialAirHi_Anim(HSD_GObj*);
void ftZd_SpecialAirHi_IASA(HSD_GObj*);
void ftZd_SpecialAirHi_Phys(HSD_GObj*);
void ftZd_SpecialAirHi_Coll(HSD_GObj*);
void ftZd_SpecialAirHiEnd_Anim(HSD_GObj*);
void ftZd_SpecialAirHiEnd_IASA(HSD_GObj*);
void ftZd_SpecialAirHiEnd_Phys(HSD_GObj*);
void ftZd_SpecialAirHiEnd_Coll(HSD_GObj*);
void ftZd_SpecialLw_Anim(HSD_GObj*);
void ftZd_SpecialLw_IASA(HSD_GObj*);
void ftZd_SpecialLw_Phys(HSD_GObj*);
void ftZd_SpecialLw_Coll(HSD_GObj*);
void ftZd_SpecialLwEnd_Anim(HSD_GObj*);
void ftZd_SpecialLwEnd_IASA(HSD_GObj*);
void ftZd_SpecialLwEnd_Phys(HSD_GObj*);
void ftZd_SpecialLwEnd_Coll(HSD_GObj*);
void ftZd_SpecialAirLw_Anim(HSD_GObj*);
void ftZd_SpecialAirLw_IASA(HSD_GObj*);
void ftZd_SpecialAirLw_Phys(HSD_GObj*);
void ftZd_SpecialAirLw_Coll(HSD_GObj*);
void ftZd_SpecialAirLwEnd_Anim(HSD_GObj*);
void ftZd_SpecialAirLwEnd_IASA(HSD_GObj*);
void ftZd_SpecialAirLwEnd_Phys(HSD_GObj*);
void ftZd_SpecialAirLwEnd_Coll(HSD_GObj*);

#endif
