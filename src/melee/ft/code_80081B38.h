#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

HSD_GObj* func_80082E3C(HSD_GObj* fighter_gobj);
f32 Stage_GetGroundFrictionMultiplier(Fighter* fp);
BOOL func_8008239C(HSD_GObj* fighter_gobj, s32 facing_direction, ftCollisionBox* height_attributes);
void func_80084DB0(HSD_GObj* fighter_gobj);
void func_80082C74(HSD_GObj* fighter_gobj, void cb_OnLand(HSD_GObj*));
void func_80084EEC(HSD_GObj* fighter_gobj);
unk_t func_80081DD4();
unk_t func_80081DD4();
unk_t func_8008370C();
unk_t func_800848DC();
unk_t func_80082638();
BOOL func_800824A0(HSD_GObj* fighter_gobj, ftCollisionBox*);
void func_80082B1C(HSD_GObj* fighter_gobj);
void func_800831CC(HSD_GObj*, s32 (*)(HSD_GObj*), void (*)(HSD_GObj*));
unk_t func_800845B4();
unk_t func_800841B8();
BOOL func_80082708(HSD_GObj* fighter_gobj);
unk_t func_80083090();
void func_8008403C(HSD_GObj* fighter_gobj, void (*cb_Coll)(HSD_GObj* fighter_gobj));
void func_80085088(HSD_GObj* fighter_gobj);
unk_t func_80084C74();
void func_80083F88(HSD_GObj* fighter_gobj);
unk_t func_80085004();
unk_t func_800847D0();
unk_t func_80082F28();
BOOL func_800827A0(HSD_GObj* fighter_gobj);
BOOL func_800821DC();
unk_t func_800835B0();
void func_80083B68(HSD_GObj* fighter_gobj);

#endif
