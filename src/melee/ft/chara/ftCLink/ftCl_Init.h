#ifndef MELEE_FT_CHARA_FTCLINK_FTCLINK_H
#define MELEE_FT_CHARA_FTCLINK_FTCLINK_H

#include "ft/fighter.h"
#include "it/it_27CF.h"

#include <baselib/gobj.h>

/// @todo this is #ftLinkAttributes.
typedef struct _CLinkAttributes {
    s32 x0_pad[(0xC - 0x0) / 4];
    s32 xC;
    s32 x10;
    s32 x14_pad[(0x2C - 0x14) / 4];
    s32 x2C;
    s32 x30_pad[(0x48 - 0x30) / 4];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    s32 x58_pad[(0xBC - 0x58) / 4];
    s32 xBC;
    s32 xC0;
    f32 xC4;
    s32 xC8_pad[(0xD8 - 0xC8) / 4];
    f32 xD8;
} CLinkAttributes;

extern MotionState ftCl_Init_MotionStateTable[];
extern char ftCl_Init_DatFilename[];
extern char ftCl_Init_DataName[];
extern Fighter_CostumeStrings ftCl_Init_CostumeStrings[];
extern char ftCl_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftCl_Init_DemoMotionFilenames;

void ftCl_Init_OnItemPickup(HSD_GObj*, bool);
void ftCl_Init_OnItemDrop(HSD_GObj*, bool);
void ftCl_Init_80149268(HSD_GObj*);
void ftCl_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftCl_Init_80149114(HSD_GObj* gobj);
void ftCl_Init_8014919C(HSD_GObj* gobj);
void ftCl_Init_OnDeath(HSD_GObj* gobj);
bool ftCl_Init_8014920C(HSD_GObj* gobj);
void ftCl_Init_801492C4(HSD_GObj* gobj);
u32 ftCl_Init_801492F4(HSD_GObj* gobj);
void ftCl_Init_80149318(HSD_GObj* gobj);
void ftCl_Init_OnLoad(HSD_GObj* gobj);
void ftCl_Init_OnItemPickupExt(HSD_GObj* gobj, bool arg1);
void ftCl_Init_OnItemInvisible(HSD_GObj* gobj);
void ftCl_Init_OnItemVisible(HSD_GObj* gobj);
void ftCl_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1);
void ftCl_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftCl_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftCo_AttackS42_Anim(HSD_GObj*);
void ftCo_AttackS42_IASA(HSD_GObj*);
void ftCo_AttackS42_Phys(HSD_GObj*);
void ftCo_AttackS42_Coll(HSD_GObj*);
void ftCl_Appeal_Anim(HSD_GObj*);
void ftCl_Appeal_IASA(HSD_GObj*);
void ftCl_Appeal_Phys(HSD_GObj*);
void ftCl_Appeal_Coll(HSD_GObj*);
void ftCl_Appeal_Anim(HSD_GObj*);
void ftCl_Appeal_IASA(HSD_GObj*);
void ftCl_Appeal_Phys(HSD_GObj*);
void ftCl_Appeal_Coll(HSD_GObj*);
void ftLk_SpecialNCharge_Anim(HSD_GObj*);
void ftLk_SpecialNCharge_IASA(HSD_GObj*);
void ftLk_SpecialNCharge_Phys(HSD_GObj*);
void ftLk_SpecialNCharge_Coll(HSD_GObj*);
void ftLk_SpecialNFullyCharged_Anim(HSD_GObj*);
void ftLk_SpecialNFullyCharged_IASA(HSD_GObj*);
void ftLk_SpecialNFullyCharged_Phys(HSD_GObj*);
void ftLk_SpecialNFullyCharged_Coll(HSD_GObj*);
void ftLk_SpecialNFire_Anim(HSD_GObj*);
void ftLk_SpecialNFire_IASA(HSD_GObj*);
void ftLk_SpecialNFire_Phys(HSD_GObj*);
void ftLk_SpecialNFire_Coll(HSD_GObj*);
void ftLk_SpecialAirNCharge_Anim(HSD_GObj*);
void ftLk_SpecialAirNCharge_IASA(HSD_GObj*);
void ftLk_SpecialAirNCharge_Phys(HSD_GObj*);
void ftLk_SpecialAirNCharge_Coll(HSD_GObj*);
void ftLk_SpecialAirNFullyCharged_Anim(HSD_GObj*);
void ftLk_SpecialAirNFullyCharged_IASA(HSD_GObj*);
void ftLk_SpecialAirNFullyCharged_Phys(HSD_GObj*);
void ftLk_SpecialAirNFullyCharged_Coll(HSD_GObj*);
void ftLk_SpecialAirNFire_Anim(HSD_GObj*);
void ftLk_SpecialAirNFire_IASA(HSD_GObj*);
void ftLk_SpecialAirNFire_Phys(HSD_GObj*);
void ftLk_SpecialAirNFire_Coll(HSD_GObj*);
void ftLk_SpecialSThrow_Anim(HSD_GObj*);
void ftLk_SpecialSThrow_Phys(HSD_GObj*);
void ftLk_SpecialSThrow_Coll(HSD_GObj*);
void ftLk_SpecialSCatch_Anim(HSD_GObj*);
void ftLk_SpecialSCatch_IASA(HSD_GObj*);
void ftLk_SpecialSCatch_Phys(HSD_GObj*);
void ftLk_SpecialSCatch_Coll(HSD_GObj*);
void ftLk_SpecialSThrowEmpty_Anim(HSD_GObj*);
void ftLk_SpecialSThrowEmpty_Phys(HSD_GObj*);
void ftLk_SpecialSThrowEmpty_Coll(HSD_GObj*);
void ftLk_SpecialAirSThrow_Anim(HSD_GObj*);
void ftLk_SpecialAirSThrow_Phys(HSD_GObj*);
void ftLk_SpecialAirSThrow_Coll(HSD_GObj*);
void ftLk_SpecialAirSCatch_Anim(HSD_GObj*);
void ftLk_SpecialAirSCatch_IASA(HSD_GObj*);
void ftLk_SpecialAirSCatch_Phys(HSD_GObj*);
void ftLk_SpecialAirSCatch_Coll(HSD_GObj*);
void ftLk_SpecialAirSThrowEmpty_Anim(HSD_GObj*);
void ftLk_SpecialAirSThrowEmpty_Phys(HSD_GObj*);
void ftLk_SpecialAirSThrowEmpty_Coll(HSD_GObj*);
void ftLk_SpecialHi_Anim(HSD_GObj*);
void ftLk_SpecialHi_IASA(HSD_GObj*);
void ftLk_SpecialHi_Phys(HSD_GObj*);
void ftLk_SpecialHi_Coll(HSD_GObj*);
void ftLk_SpecialAirHi_Anim(HSD_GObj*);
void ftLk_SpecialAirHi_IASA(HSD_GObj*);
void ftLk_SpecialAirHi_Phys(HSD_GObj*);
void ftLk_SpecialAirHi_Coll(HSD_GObj*);
void ftLk_SpecialLw_Anim(HSD_GObj*);
void ftLk_SpecialLw_Phys(HSD_GObj*);
void ftLk_SpecialLw_Coll(HSD_GObj*);
void ftLk_SpecialAirLw_Anim(HSD_GObj*);
void ftLk_SpecialAirLw_Phys(HSD_GObj*);
void ftLk_SpecialAirLw_Coll(HSD_GObj*);
void ftCo_Zair_Anim(HSD_GObj*);
void ftCo_Zair_IASA(HSD_GObj*);
void ftCo_Zair_Phys(HSD_GObj*);
void ftCo_Zair_Coll(HSD_GObj*);
void ftCo_ZairCatch_Anim(HSD_GObj*);
void ftCo_ZairCatch_IASA(HSD_GObj*);
void ftCo_ZairCatch_Phys(HSD_GObj*);
void ftCo_ZairCatch_Coll(HSD_GObj*);

#endif
