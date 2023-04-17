/// @file Forward Smash (AttackS4)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKS4_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKS4_H

#include <platform.h>
#include <baselib/forward.h>

// Item-related callbacks
void ftGw_ItemTorchSetup(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchSetFlag(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchOnDamage(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchEnterHitlag(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchExitHitlag(HSD_GObj* gobj);
bool ftGw_AttackS4_ItemCheckTorchRemove(HSD_GObj* gobj);

void ftGw_AttackS4_Enter(HSD_GObj* gobj);
void ftGw_AttackS4_Anim(HSD_GObj* gobj);
void ftGw_AttackS4_IASA(HSD_GObj* gobj);
void ftGw_AttackS4_Phys(HSD_GObj* gobj);
void ftGw_AttackS4_Coll(HSD_GObj* gobj);

#endif
