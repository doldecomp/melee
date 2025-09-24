#ifndef GALE01_12C030
#define GALE01_12C030

#include <platform.h>

#include "ft/types.h"

#include "ftYoshi/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 12BDA0 */ void ftYs_Init_8012BDA0(Fighter_GObj* gobj);
/* 12BE3C */ void ftYs_Init_8012BE3C(HSD_GObj* gobj);
/* 12BECC */ void ftYs_Init_8012BECC(Fighter_GObj* gobj);
/* 12C030 */ void ftYs_GuardOn_0_Anim(Fighter_GObj* gobj);
/* 12C114 */ void ftYs_GuardOn_0_IASA(Fighter_GObj* gobj);
/* 12C194 */ void ftYs_GuardOn_0_Phys(Fighter_GObj* gobj);
/* 12C1B4 */ void ftYs_GuardOn_0_Coll(Fighter_GObj* gobj);
/* 12C1D4 */ void ftYs_Shield_8012C1D4(Fighter_GObj* gobj);
/* 12C2F4 */ void ftYs_GuardHold_Anim(Fighter_GObj* gobj);
/* 12C3EC */ void ftYs_GuardHold_IASA(Fighter_GObj* gobj);
/* 12C45C */ void ftYs_GuardHold_Phys(Fighter_GObj* gobj);
/* 12C47C */ void ftYs_GuardHold_Coll(Fighter_GObj* gobj);
/* 12C49C */ void ftYs_Shield_8012C49C(Fighter_GObj* gobj);
/* 12C54C */ void ftYs_GuardOff_Anim(Fighter_GObj* gobj);
/* 12C59C */ void ftYs_GuardOff_IASA(Fighter_GObj* gobj);
/* 12C5C0 */ void ftYs_GuardOff_Phys(Fighter_GObj* gobj);
/* 12C5E0 */ void ftYs_GuardOff_Coll(Fighter_GObj* gobj);
/* 12C600 */ void ftYs_Shield_8012C600(Fighter_GObj* gobj, bool);
/* 12C7A4 */ void ftYs_GuardDamage_Anim(Fighter_GObj* gobj);
/* 12C80C */ void ftYs_GuardDamage_IASA(Fighter_GObj* gobj);
/* 12C810 */ void ftYs_GuardDamage_Phys(Fighter_GObj* gobj);
/* 12C830 */ void ftYs_GuardDamage_Coll(Fighter_GObj* gobj);
/* 12C850 */ void ftYs_Shield_8012C850(Fighter_GObj* gobj);
/* 12C914 */ void ftYs_Shield_8012C914(Fighter_GObj* gobj);
/* 12CACC */ void ftYs_Shield_8012CACC(Fighter_GObj* gobj);
/* 12CAD0 */ void ftYs_GuardOn_1_Anim(Fighter_GObj* gobj);
/* 12CBBC */ void ftYs_GuardOn_1_IASA(Fighter_GObj* gobj);
/* 12CBDC */ void ftYs_GuardOn_1_Phys(Fighter_GObj* gobj);
/* 12CBFC */ void ftYs_GuardOn_1_Coll(Fighter_GObj* gobj);
/* 12CC1C */ bool ftYs_Shield_8012CC1C(Fighter_GObj* gobj);
/* 3CEA98 */ extern char ftYs_Init_DatFilename[];
/* 3CEAA4 */ extern char ftYs_Init_DataName[];
/* 3CEC70 */ extern char ftYs_Init_AnimDatFilename[];
/* 3CECEC */ extern Fighter_DemoStrings ftYs_Init_DemoMotionFilenames;
/* 3CECFC */ extern Fighter_CostumeStrings ftYs_Init_CostumeStrings[];

#endif
