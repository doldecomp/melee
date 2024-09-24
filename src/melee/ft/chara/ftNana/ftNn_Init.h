#ifndef GALE01_122EDC
#define GALE01_122EDC

#include "ftPopo/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 122EDC */ void ftNn_Init_OnLoad(Fighter_GObj* gobj);
/* 122F28 */ void ftNn_Init_OnDeath(Fighter_GObj* gobj);
/* 122FAC */ void ftNn_Init_80122FAC(Fighter_GObj* gobj);
/* 122FCC */ void ftNn_Init_LoadSpecialAttrs(Fighter_GObj* gobj);
/* 123348 */ void ftPp_SpecialHi_0_Anim(Fighter_GObj* gobj);
/* 123384 */ void ftPp_SpecialHi_3_Anim(Fighter_GObj* gobj);
/* 123388 */ void ftPp_SpecialHi_0_IASA(Fighter_GObj* gobj);
/* 12338C */ void ftPp_SpecialHi_3_IASA(Fighter_GObj* gobj);
/* 123390 */ void ftPp_SpecialHi_0_Phys(Fighter_GObj* gobj);
/* 1233EC */ void ftPp_SpecialHi_3_Phys(Fighter_GObj* gobj);
/* 1233F0 */ void ftPp_SpecialHi_0_Coll(Fighter_GObj* gobj);
/* 1233F4 */ void ftPp_SpecialHi_3_Coll(Fighter_GObj* gobj);
/* 123448 */ void ftPp_SpecialHi_1_Anim(Fighter_GObj* gobj);
/* 123484 */ void ftPp_SpecialHi_4_Anim(Fighter_GObj* gobj);
/* 1234E4 */ void ftPp_SpecialHi_1_IASA(Fighter_GObj* gobj);
/* 1234E8 */ void ftPp_SpecialHi_4_IASA(Fighter_GObj* gobj);
/* 1234EC */ void ftPp_SpecialHi_1_Phys(Fighter_GObj* gobj);
/* 12350C */ void ftPp_SpecialHi_4_Phys(Fighter_GObj* gobj);
/* 1235BC */ void ftPp_SpecialHi_1_Coll(Fighter_GObj* gobj);
/* 1235F8 */ void ftPp_SpecialHi_4_Coll(Fighter_GObj* gobj);
/* 123954 */ bool ftNn_Init_80123954(Fighter_GObj* gobj, GroundOrAir pp_ga);
/* 123B10 */ bool ftNn_Init_80123B10(Fighter_GObj*);
/* 123CA4 */ void ftPp_SpecialS_0_Anim(Fighter_GObj* gobj);
/* 123D68 */ void ftPp_SpecialS_1_Anim(Fighter_GObj* gobj);
/* 123E58 */ void ftPp_SpecialS_0_IASA(Fighter_GObj* gobj);
/* 123E5C */ void ftPp_SpecialS_1_IASA(Fighter_GObj* gobj);
/* 123E60 */ void ftPp_SpecialS_0_Phys(Fighter_GObj* gobj);
/* 123EFC */ void ftPp_SpecialS_1_Phys(Fighter_GObj* gobj);
/* 123F98 */ void ftPp_SpecialS_0_Coll(Fighter_GObj* gobj);
/* 1241A0 */ void ftPp_SpecialS_1_Coll(Fighter_GObj* gobj);
/* 3CD838 */ extern MotionState ftNn_Init_MotionStateTable[ftPp_MS_SelfCount];
/* 3CDB78 */ extern char ftNn_Init_DatFilename[];
/* 3CDB84 */ extern char ftNn_Init_DataName[];
/* 3CDCA0 */ extern char ftNn_Init_AnimDatFilename[];
/* 3CDD1C */ extern Fighter_DemoStrings ftNn_Init_DemoMotionFilenames;
/* 3CDD2C */ extern Fighter_CostumeStrings ftNn_Init_CostumeStrings[];

#endif
