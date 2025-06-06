#ifndef GALE01_12C030
#define GALE01_12C030

#include <platform.h>

#include "ftYoshi/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

#include <dolphin/mtx.h>

/* 12C030 */ void ftYs_GuardOn_0_Anim(ftYs_GObj* gobj);
/* 12C114 */ void ftYs_GuardOn_0_IASA(ftYs_GObj* gobj);
/* 12C194 */ void ftYs_GuardOn_0_Phys(ftYs_GObj* gobj);
/* 12C1B4 */ void ftYs_GuardOn_0_Coll(ftYs_GObj* gobj);
/* 12C1D4 */ void ftYs_Shield_8012C1D4(ftYs_GObj* gobj);
/* 12C2F4 */ void ftYs_GuardHold_Anim(ftYs_GObj* gobj);
/* 12C3EC */ void ftYs_GuardHold_IASA(ftYs_GObj* gobj);
/* 12C45C */ void ftYs_GuardHold_Phys(ftYs_GObj* gobj);
/* 12C47C */ void ftYs_GuardHold_Coll(ftYs_GObj* gobj);
/* 12C49C */ void ftYs_Shield_8012C49C(ftYs_GObj* gobj);
/* 12C54C */ void ftYs_GuardOff_Anim(ftYs_GObj* gobj);
/* 12C59C */ void ftYs_GuardOff_IASA(ftYs_GObj* gobj);
/* 12C5C0 */ void ftYs_GuardOff_Phys(ftYs_GObj* gobj);
/* 12C5E0 */ void ftYs_GuardOff_Coll(ftYs_GObj* gobj);
/* 12C600 */ void ftYs_Shield_8012C600(ftYs_GObj* gobj, bool);
/* 12C7A4 */ void ftYs_GuardDamage_Anim(ftYs_GObj* gobj);
/* 12C80C */ void ftYs_GuardDamage_IASA(ftYs_GObj* gobj);
/* 12C810 */ void ftYs_GuardDamage_Phys(ftYs_GObj* gobj);
/* 12C830 */ void ftYs_GuardDamage_Coll(ftYs_GObj* gobj);
/* 12C850 */ void ftYs_Shield_8012C850(ftYs_GObj* gobj);
/* 12C914 */ void ftYs_Shield_8012C914(ftYs_GObj* gobj);
/* 12CACC */ void ftYs_Shield_8012CACC(ftYs_GObj* gobj);
/* 12CAD0 */ void ftYs_GuardOn_1_Anim(ftYs_GObj* gobj);
/* 12CBBC */ void ftYs_GuardOn_1_IASA(ftYs_GObj* gobj);
/* 12CBDC */ void ftYs_GuardOn_1_Phys(ftYs_GObj* gobj);
/* 12CBFC */ void ftYs_GuardOn_1_Coll(ftYs_GObj* gobj);
/* 12CC1C */ bool ftYs_Shield_8012CC1C(ftYs_GObj* gobj);
/* 12CC6C */ Fighter_Part ftYs_Shield_8012CC6C(ftYs_GObj* gobj);
/* 12CC94 */ void ftYs_Shield_8012CC94(ftYs_GObj* gobj, Vec3* out);
/* 12CCC4 */ float ftYs_Shield_8012CCC4(ftYs_GObj* gobj);
/* 12CCD0 */ float ftYs_Shield_8012CCD0(ftYs_GObj* gobj);
/* 12CCE0 */ float ftYs_Shield_8012CCE0(ftYs_GObj* gobj);
/* 12CCF0 */ float ftYs_Shield_8012CCF0(ftYs_GObj* gobj);
/* 12CD00 */ float ftYs_Shield_8012CD00(ftYs_GObj* gobj);
/* 3CEA98 */ extern char ftYs_Init_DatFilename[];
/* 3CEAA4 */ extern char ftYs_Init_DataName[];
/* 3CEC70 */ extern char ftYs_Init_AnimDatFilename[];
/* 3CECEC */ extern Fighter_DemoStrings ftYs_Init_DemoMotionFilenames;
/* 3CECFC */ extern Fighter_CostumeStrings ftYs_Init_CostumeStrings[];

#endif
