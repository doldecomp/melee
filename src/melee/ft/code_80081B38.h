#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include <sysdolphin/baselib/gobj.h>

HSD_GObj* func_80082E3C(HSD_GObj* fighter_gobj);
f32 Stage_GetGroundFrictionMultiplier(Fighter* fp);
BOOL func_8008239C(HSD_GObj* fighter_gobj, s32 facing_direction, f32* height_attributes);
void func_80084DB0(HSD_GObj* fighter_gobj);
void func_80082C74(HSD_GObj* fighter_gobj, void cb_OnLand(HSD_GObj*));

#endif
