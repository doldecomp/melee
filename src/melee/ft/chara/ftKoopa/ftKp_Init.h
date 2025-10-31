#ifndef GALE01_132A0C
#define GALE01_132A0C

#include <platform.h>

#include "ft/types.h"

#include "ftKoopa/forward.h"
#include <baselib/forward.h>

/* 132A0C */ void ftKp_Init_OnDeath(Fighter_GObj* gobj);
/* 132A64 */ void ftKp_Init_UnkMotionStates3(Fighter_GObj* gobj);
/* 132A84 */ void ftKp_Init_OnLoadForGKoopa(Fighter* fp);
/* 132ABC */ void ftKp_Init_OnLoad(Fighter_GObj* gobj);
/* 132B38 */ void ftKp_Init_80132B38(void);
/* 132B3C */ void ftKp_Init_OnItemPickup(Fighter_GObj* gobj, bool flag);
/* 132C1C */ void ftKp_Init_OnItemInvisible(Fighter_GObj* gobj);
/* 132C64 */ void ftKp_Init_OnItemVisible(Fighter_GObj* gobj);
/* 132CAC */ void ftKp_Init_OnItemDrop(Fighter_GObj* gobj, bool bool1);
/* 132D00 */ void ftKp_Init_LoadSpecialAttrs(Fighter_GObj* gobj);
/* 132D38 */ void ftKp_Init_OnKnockbackEnter(Fighter_GObj* gobj);
/* 132D7C */ void ftKp_Init_OnKnockbackExit(Fighter_GObj* gobj);
/* 132DC0 */ float ftKp_SpecialS_80132DC0(Fighter_GObj* gobj);
/* 132DD0 */ float ftKp_SpecialS_80132DD0(Fighter_GObj* gobj);
/* 132DE0 */ float ftKp_SpecialS_80132DE0(Fighter_GObj* gobj);
/* 132DF0 */ float ftKp_SpecialS_80132DF0(Fighter_GObj* gobj);
/* 132E00 */ float ftKp_SpecialS_80132E00(Fighter_GObj* gobj);
/* 132E10 */ float ftKp_SpecialS_80132E10(Fighter_GObj* gobj);
/* 132E20 */ float ftKp_SpecialS_80132E20(Fighter_GObj* gobj);
/* 132E30 */ void ftKp_SpecialS_80132E30(Fighter_GObj* gobj);
/* 132EFC */ void ftKp_SpecialS_Enter(Fighter_GObj* gobj);
/* 132F94 */ void ftKp_SpecialAirS_Enter(Fighter_GObj* gobj);
/* 13302C */ void ftKp_SpecialS_8013302C(Fighter_GObj* gobj);
/* 1330E4 */ void ftKp_SpecialS_801330E4(Fighter_GObj* gobj);
/* 13319C */ void ftKp_SpecialS_8013319C(Fighter_GObj* gobj);
/* 13322C */ void ftKp_SpecialS_8013322C(Fighter_GObj* gobj);
/* 1332C4 */ void ftKp_SpecialS_801332C4(Fighter_GObj* gobj);
/* 133324 */ void ftKp_SpecialS_80133324(Fighter_GObj* gobj);
/* 133398 */ void ftKp_SpecialS_80133398(Fighter_GObj* gobj);
/* 1333F8 */ void ftKp_SpecialS_801333F8(Fighter_GObj* gobj);
/* 133484 */ void ftKp_SpecialS_80133484(Fighter_GObj* gobj);
/* 1334E4 */ void ftKp_SpecialS_801334E4(Fighter_GObj* gobj);
/* 13359C */ void ftKp_SpecialS_8013359C(Fighter_GObj* gobj);
/* 133654 */ void ftKp_SpecialSStart_Anim(Fighter_GObj* gobj);
/* 133690 */ void ftKp_SpecialAirSStart_Anim(Fighter_GObj* gobj);
/* 1336CC */ void ftKp_SpecialSHit_Anim(Fighter_GObj* gobj);
/* 13383C */ void ftKp_SpecialAirSHit_Anim(Fighter_GObj* gobj);
/* 1339AC */ void ftKp_SpecialSWait_Anim(Fighter_GObj* gobj);
/* 1339B0 */ void ftKp_SpecialAirSWait_Anim(Fighter_GObj* gobj);
/* 1339B4 */ void ftKp_SpecialSEndF_Anim(Fighter_GObj* gobj);
/* 133A90 */ void ftKp_SpecialSEndB_Anim(Fighter_GObj* gobj);
/* 133AD4 */ void ftKp_SpecialAirSEndF_Anim(Fighter_GObj* gobj);
/* 133BB0 */ void ftKp_SpecialAirSEndB_Anim(Fighter_GObj* gobj);
/* 133BF4 */ void ftKp_SpecialSHit_IASA(Fighter_GObj* gobj);
/* 133D20 */ void ftKp_SpecialAirSHit_IASA(Fighter_GObj* gobj);
/* 133E4C */ void ftKp_SpecialSWait_IASA(Fighter_GObj* gobj);
/* 134038 */ void ftKp_SpecialAirSWait_IASA(Fighter_GObj* gobj);
/* 134224 */ void ftKp_SpecialSStart_Phys(Fighter_GObj* gobj);
/* 134244 */ void ftKp_SpecialAirSStart_Phys(Fighter_GObj* gobj);
/* 134288 */ void ftKp_SpecialSHit_Phys(Fighter_GObj* gobj);
/* 1342A8 */ void ftKp_SpecialAirSHit_Phys(Fighter_GObj* gobj);
/* 1342C8 */ void ftKp_SpecialSWait_Phys(Fighter_GObj* gobj);
/* 1342E8 */ void ftKp_SpecialAirSWait_Phys(Fighter_GObj* gobj);
/* 134308 */ void ftKp_SpecialSEndF_Phys(Fighter_GObj* gobj);
/* 134328 */ void ftKp_SpecialSEndB_Phys(Fighter_GObj* gobj);
/* 134348 */ void ftKp_SpecialAirSEndF_Phys(Fighter_GObj* gobj);
/* 134368 */ void ftKp_SpecialAirSEndB_Phys(Fighter_GObj* gobj);
/* 134388 */ void ftKp_SpecialSStart_Coll(Fighter_GObj* gobj);
/* 1343B0 */ void ftKp_SpecialAirSStart_Coll(Fighter_GObj* gobj);
/* 1343D8 */ void ftKp_SpecialSHit_Coll(Fighter_GObj* gobj);
/* 134400 */ void ftKp_SpecialAirSHit_Coll(Fighter_GObj* gobj);
/* 134428 */ void ftKp_SpecialSWait_Coll(Fighter_GObj* gobj);
/* 134450 */ void ftKp_SpecialAirSWait_Coll(Fighter_GObj* gobj);
/* 134478 */ void ftKp_SpecialSEndF_Coll(Fighter_GObj* gobj);
/* 1344A0 */ void ftKp_SpecialSEndB_Coll(Fighter_GObj* gobj);
/* 1344C8 */ void ftKp_SpecialAirSEndF_Coll(Fighter_GObj* gobj);
/* 1344F0 */ void ftKp_SpecialAirSEndB_Coll(Fighter_GObj* gobj);

/* 3CEDC0 */ extern MotionState ftKp_Init_MotionStateTable[ftKp_MS_SelfCount];
/* 3CF0A0 */ extern char ftKp_Init_DatFilename[];
/* 3CF0AC */ extern char ftKp_Init_DataName[];
/* 3CF1E0 */ extern char ftKp_Init_AnimDatFilename[];
/* 3CF25C */ extern Fighter_DemoStrings ftKp_Init_DemoMotionFilenames;
/* 3CF26C */ extern Fighter_CostumeStrings ftKp_Init_CostumeStrings[];

#endif
