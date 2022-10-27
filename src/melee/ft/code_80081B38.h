#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

HSD_GObj* func_80082E3C(HSD_GObj* fighter_gobj);
f32 Stage_GetGroundFrictionMultiplier(Fighter* fp);
BOOL func_8008239C(HSD_GObj* fighter_gobj, s32 facing_direction, f32* height_attributes);
void func_80084DB0(HSD_GObj* fighter_gobj);
void func_80082C74(HSD_GObj* fighter_gobj, void cb_OnLand(HSD_GObj*));
void func_80084EEC(HSD_GObj* fighter_gobj);
unk_t func_80081DD4();
unk_t func_80081DD4();
unk_t func_8008370C();
unk_t func_800848DC();
unk_t func_80082638();
BOOL func_800824A0(HSD_GObj* fighter_gobj, ftCollisionBox*);

#endif
