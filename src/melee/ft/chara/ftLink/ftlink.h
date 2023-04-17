#ifndef MELEE_FT_CHARA_FTLINK_FTLINK_H
#define MELEE_FT_CHARA_FTLINK_FTLINK_H

#include <platform.h>

#include "ft/ftcommon.h"
#include "ft/types.h"

#include <baselib/gobj.h>

typedef struct _ftLinkAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    u8 x14_filler[0x2C - 0x18];
    f32 x28;
    s32 x2C;
    u8 x30_filler[0x48 - 0x30];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    u8 x58_filler[0xBC - 0x58];
    s32 xBC;
    u8 xC0_filler[0xD8 - 0xC0];
    f32 xD8;
} ftLinkAttributes;

extern MotionState ftLk_Init_MotionStateTable[];
extern char ftLk_Init_DatFilename[];
extern char ftLk_Init_DataName[];
extern Fighter_CostumeStrings ftLk_Init_CostumeStrings[];
extern char ftLk_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftLk_Init_DemoMotionFilenames;

void ftLk_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
void ftLk_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftLk_800EC06C(void);
void ftLk_800ECD04(HSD_GObj*);
void ftLk_800ECD58(HSD_GObj*);
void ftLk_Init_OnLoadForCLink(Fighter* fp);
void ftLk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftLk_800EAF58(HSD_GObj*);
bool ftLk_800EAD64(HSD_GObj* gobj);
void ftLk_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftLk_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftLk_800EB334(HSD_GObj* gobj);
void ftLk_Init_OnDeath(HSD_GObj* gobj);
void ftLk_Init_OnLoad(HSD_GObj* gobj);
void ftLk_800EAF38(void);
void ftLk_Init_OnItemPickupExt(HSD_GObj* gobj, int arg1);
void ftLk_Init_OnItemInvisible(HSD_GObj* gobj);
void ftLk_Init_OnItemVisible(HSD_GObj* gobj);
void ftLk_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1);
void ftLk_SpecialNCharge_Phys(HSD_GObj*);
void ftLk_SpecialNCharge_Coll(HSD_GObj*);
void ftLk_SpecialNCharge_Anim(HSD_GObj*);
void ftLk_SpecialNFullyCharged_Anim(HSD_GObj*);
void ftLk_SpecialNFullyCharged_IASA(HSD_GObj*);
void ftLk_SpecialNFire_IASA(HSD_GObj*);
void ftLk_SpecialNFire_Anim(HSD_GObj*);
void ftLk_SpecialNFire_Coll(HSD_GObj*);
void ftLk_SpecialNFire_Phys(HSD_GObj*);
void ftLk_SpecialNFullyCharged_Phys(HSD_GObj*);
void ftLk_SpecialNFullyCharged_Coll(HSD_GObj*);
void ftLk_SpecialAirNCharge_Anim(HSD_GObj*);
void ftLk_SpecialAirNCharge_Phys(HSD_GObj*);
void ftLk_SpecialAirNCharge_Coll(HSD_GObj*);
void ftLk_SpecialAirNFullyCharged_Anim(HSD_GObj*);
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
void ftLk_SpecialAirNFullyCharged_IASA(HSD_GObj*);
void ftLk_SpecialAirNCharge_IASA(HSD_GObj*);
void ftLk_SpecialNCharge_IASA(HSD_GObj*);
void ftLk_SpecialSThrowEmpty_Phys(HSD_GObj*);
void ftLk_SpecialAirSThrow_Phys(HSD_GObj*);
void ftLk_SpecialAirSThrow_Anim(HSD_GObj*);
void ftLk_SpecialSThrowEmpty_Coll(HSD_GObj*);
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
void ftLk_SpecialS_Enter(HSD_GObj*);
void ftLk_SpecialAirHi_Enter(HSD_GObj*);
void ftLk_SpecialAirLw_Enter(HSD_GObj*);
void ftLk_SpecialAirS_Enter(HSD_GObj*);
void ftLk_SpecialAirN_Enter(HSD_GObj*);
void ftLk_SpecialN_Enter(HSD_GObj*);
void ftLk_SpecialN_Enter(HSD_GObj*);
void ftLk_SpecialLw_Enter(HSD_GObj*);
void ftLk_SpecialHi_Enter(HSD_GObj*);

#endif
