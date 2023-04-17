#ifndef MELEE_FT_CHARA_FTYOSHI_FTYOSHI1_H
#define MELEE_FT_CHARA_FTYOSHI_FTYOSHI1_H

#include "forward.h"
#include "ft/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftYs_Init_MotionStateTable[];

void ftYs_Init_8012B8A4(HSD_GObj* gobj);
void ftYs_Init_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg);
void ftYs_Init_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                        f32 start_frame);
void ftYs_Shield_8012C49C(HSD_GObj* gobj);
void ftYs_Init_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                        f32 start_frame);

unk_t ftYs_Init_8012BECC(void);
void ftYs_Shield_8012C850(HSD_GObj* gobj);

void ftYs_Init_8012B918(HSD_GObj* gobj);
void ftYs_Init_OnDeath(HSD_GObj* gobj);
void ftYs_Init_OnLoad(HSD_GObj* gobj);
void ftYs_Init_8012BA8C(HSD_GObj* gobj);
f32 ftYs_Init_8012BAC0(Fighter* fp);
void ftYs_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftYs_Init_OnItemInvisible(HSD_GObj* gobj);
void ftYs_Init_OnItemVisible(HSD_GObj* gobj);
void ftYs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftYs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftYs_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftYs_Init_OnKnockbackExit(HSD_GObj* gobj);
unk_t ftYs_Init_8012BDA0(void);
void ftYs_Init_8012BE3C(HSD_GObj* gobj);

void ftYs_MS_341_Anim(HSD_GObj*);
void ftYs_MS_341_IASA(HSD_GObj*);
void ftYs_MS_341_Phys(HSD_GObj*);
void ftYs_MS_341_Coll(HSD_GObj*);
void ftYs_ShieldHold_Anim(HSD_GObj*);
void ftYs_ShieldHold_IASA(HSD_GObj*);
void ftYs_ShieldHold_Phys(HSD_GObj*);
void ftYs_ShieldHold_Coll(HSD_GObj*);
void ftYs_ShieldRelease_Anim(HSD_GObj*);
void ftYs_ShieldRelease_IASA(HSD_GObj*);
void ftYs_ShieldRelease_Phys(HSD_GObj*);
void ftYs_ShieldRelease_Coll(HSD_GObj*);
void ftYs_ShieldDamage_Anim(HSD_GObj*);
void ftYs_ShieldDamage_IASA(HSD_GObj*);
void ftYs_ShieldDamage_Phys(HSD_GObj*);
void ftYs_ShieldDamage_Coll(HSD_GObj*);
void ftYs_ShieldStart_Anim(HSD_GObj*);
void ftYs_ShieldStart_IASA(HSD_GObj*);
void ftYs_ShieldStart_Phys(HSD_GObj*);
void ftYs_ShieldStart_Coll(HSD_GObj*);
void ftYs_SpecialN_Anim(HSD_GObj*);
void ftYs_SpecialN_Phys(HSD_GObj*);
void ftYs_SpecialN_Coll(HSD_GObj*);
void ftYs_SpecialNCatchStart_Anim(HSD_GObj*);
void ftYs_SpecialNCatchStart_Phys(HSD_GObj*);
void ftYs_SpecialNCatchStart_Coll(HSD_GObj*);
void ftYs_SpecialNCatch_Anim(HSD_GObj*);
void ftYs_SpecialNCatch_Phys(HSD_GObj*);
void ftYs_SpecialNCatch_Coll(HSD_GObj*);
void ftYs_SpecialAirN_Anim(HSD_GObj*);
void ftYs_SpecialAirN_Phys(HSD_GObj*);
void ftYs_SpecialAirN_Coll(HSD_GObj*);
void ftYs_SpecialAirNCatchStart_Anim(HSD_GObj*);
void ftYs_SpecialAirNCatchStart_Phys(HSD_GObj*);
void ftYs_SpecialAirNCatchStart_Coll(HSD_GObj*);
void ftYs_SpecialAirNCatch_Anim(HSD_GObj*);
void ftYs_SpecialAirNCatch_Phys(HSD_GObj*);
void ftYs_SpecialAirNCatch_Coll(HSD_GObj*);
void ftYs_SpecialSStart_Anim(HSD_GObj*);
void ftYs_SpecialSStart_Phys(HSD_GObj*);
void ftYs_SpecialSStart_Coll(HSD_GObj*);
void ftYs_SpecialS_Anim(HSD_GObj*);
void ftYs_SpecialS_Phys(HSD_GObj*);
void ftYs_SpecialS_Coll(HSD_GObj*);
void ftYs_SpecialSTurn_Anim(HSD_GObj*);
void ftYs_SpecialSTurn_Phys(HSD_GObj*);
void ftYs_SpecialSTurn_Coll(HSD_GObj*);
void ftYs_SpecialSEnd_Anim(HSD_GObj*);
void ftYs_SpecialSEnd_Phys(HSD_GObj*);
void ftYs_SpecialSEnd_Coll(HSD_GObj*);
void ftYs_SpecialAirSStart_Anim(HSD_GObj*);
void ftYs_SpecialAirSStart_IASA(HSD_GObj*);
void ftYs_SpecialAirSStart_Phys(HSD_GObj*);
void ftYs_SpecialAirSStart_Coll(HSD_GObj*);
void ftYs_SpecialAirS_Anim(HSD_GObj*);
void ftYs_SpecialAirS_IASA(HSD_GObj*);
void ftYs_SpecialAirS_Phys(HSD_GObj*);
void ftYs_SpecialAirS_Coll(HSD_GObj*);
void ftYs_SpecialAirSRebound_Anim(HSD_GObj*);
void ftYs_SpecialAirSRebound_IASA(HSD_GObj*);
void ftYs_SpecialAirSRebound_Phys(HSD_GObj*);
void ftYs_SpecialAirSRebound_Coll(HSD_GObj*);
void ftYs_SpecialAirSEnd_Anim(HSD_GObj*);
void ftYs_SpecialAirSEnd_IASA(HSD_GObj*);
void ftYs_SpecialAirSEnd_Phys(HSD_GObj*);
void ftYs_SpecialAirSEnd_Coll(HSD_GObj*);
void ftYs_SpecialHi_Anim(HSD_GObj*);
void ftYs_SpecialHi_IASA(HSD_GObj*);
void ftYs_SpecialHi_Phys(HSD_GObj*);
void ftYs_SpecialHi_Coll(HSD_GObj*);
void ftYs_SpecialAirHi_Anim(HSD_GObj*);
void ftYs_SpecialAirHi_IASA(HSD_GObj*);
void ftYs_SpecialAirHi_Phys(HSD_GObj*);
void ftYs_SpecialAirHi_Coll(HSD_GObj*);
void ftYs_SpecialLw_Anim(HSD_GObj*);
void ftYs_SpecialLw_IASA(HSD_GObj*);
void ftYs_SpecialLw_Phys(HSD_GObj*);
void ftYs_SpecialLw_Coll(HSD_GObj*);
void ftYs_SpecialLwLand_Anim(HSD_GObj*);
void ftYs_SpecialLwLand_IASA(HSD_GObj*);
void ftYs_SpecialLwLand_Phys(HSD_GObj*);
void ftYs_SpecialLwLand_Coll(HSD_GObj*);
void ftYs_SpecialAirLw_Anim(HSD_GObj*);
void ftYs_SpecialAirLw_Phys(HSD_GObj*);
void ftYs_SpecialAirLw_Coll(HSD_GObj*);
void ftYs_MS_365_Anim(HSD_GObj*);
void ftYs_MS_365_Phys(HSD_GObj*);
void ftYs_MS_365_Coll(HSD_GObj*);
void ftYs_MS_366_Anim(HSD_GObj*);
void ftYs_MS_366_Phys(HSD_GObj*);
void ftYs_MS_366_Coll(HSD_GObj*);
void ftYs_MS_367_Anim(HSD_GObj*);
void ftYs_MS_367_Phys(HSD_GObj*);
void ftYs_MS_367_Coll(HSD_GObj*);
void ftYs_MS_368_Anim(HSD_GObj*);
void ftYs_MS_368_Phys(HSD_GObj*);
void ftYs_MS_368_Coll(HSD_GObj*);
void ftYs_Shield_8012C1D4(HSD_GObj*);
void ftYs_ShieldHold_Anim(HSD_GObj* gobj);
void ftYs_ShieldHold_IASA(HSD_GObj*);
void ftYs_ShieldHold_Phys(HSD_GObj*);
void ftYs_ShieldHold_Coll(HSD_GObj*);

#endif
