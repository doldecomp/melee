#ifndef MELEE_FT_CHARA_FTSAMUS_FTSAMUS1_H
#define MELEE_FT_CHARA_FTSAMUS_FTSAMUS1_H

#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

void ftSamus_OnDeath(HSD_GObj* fighter_gobj);
void ftSamus_OnLoad(HSD_GObj* fighter_gobj);
void ftSamus_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftSamus_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftSamus_OnItemVisible(HSD_GObj* fighter_gobj);
void ftSamus_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftSamus_80128628(HSD_GObj* fighter_gobj);
void ftSamus_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftSamus_80128770(HSD_AObj* fighter_gobj, f32 rate);
void ftSamus_CreateThrowGrappleBeam(HSD_GObj* fighter_gobj, s32 action_state,
                                    f32 anim_speed);

#endif
