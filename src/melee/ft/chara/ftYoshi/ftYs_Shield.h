#ifndef MELEE_FT_CHARA_FTYOSHI_FTYOSHI2_H
#define MELEE_FT_CHARA_FTYOSHI_FTYOSHI2_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

#include <dolphin/mtx/types.h>

extern char ftYs_Init_DatFilename[];
extern char ftYs_Init_DataName[];
extern Fighter_CostumeStrings ftYs_Init_CostumeStrings[];
extern char ftYs_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftYs_Init_DemoMotionFilenames;

void ftYs_MS_341_Anim(HSD_GObj* gobj);
void ftYs_MS_341_IASA(HSD_GObj* gobj);
void ftYs_MS_341_Phys(HSD_GObj*);
void ftYs_MS_341_Coll(HSD_GObj*);
void ftYs_Shield_8012C1D4(HSD_GObj*);
void ftYs_ShieldHold_Anim(HSD_GObj* gobj);
void ftYs_ShieldHold_IASA(HSD_GObj*);
void ftYs_ShieldHold_Phys(HSD_GObj*);
void ftYs_ShieldHold_Coll(HSD_GObj*);
void ftYs_Shield_8012C49C(HSD_GObj*);
void ftYs_ShieldRelease_Anim(HSD_GObj*);
void ftYs_ShieldRelease_IASA(HSD_GObj*);
void ftYs_ShieldRelease_Phys(HSD_GObj*);
void ftYs_ShieldRelease_Coll(HSD_GObj*);
void ftYs_Shield_8012C600(HSD_GObj*);
void ftYs_ShieldDamage_Anim(HSD_GObj*);
void ftYs_ShieldDamage_IASA(HSD_GObj*);
void ftYs_ShieldDamage_Phys(HSD_GObj*);
void ftYs_ShieldDamage_Coll(HSD_GObj*);
void ftYs_Shield_8012CACC(HSD_GObj*);
void ftYs_Shield_8012C914(HSD_GObj*);
void ftYs_ShieldStart_Anim(HSD_GObj*);
void ftYs_ShieldStart_IASA(HSD_GObj*);
void ftYs_ShieldStart_Phys(HSD_GObj*);
void ftYs_ShieldStart_Coll(HSD_GObj*);
bool ftYs_Shield_8012CC1C(HSD_GObj*);
void ftYs_Shield_8012CC6C(HSD_GObj*);
void ftYs_Shield_8012CC94(HSD_GObj* gobj, Vec3* out);
f32 ftYs_Shield_8012CCC4(HSD_GObj*);
f32 ftYs_Shield_8012CCD0(HSD_GObj*);
f32 ftYs_Shield_8012CCE0(HSD_GObj*);
f32 ftYs_Shield_8012CCF0(HSD_GObj*);
f32 ftYs_Shield_8012CD00(HSD_GObj*);

#endif
