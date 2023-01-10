/** @file
 * @todo Rename to @c ftUnk3.h
 */
#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <melee/ft/fighter.h>

HSD_GObj* func_80082E3C(HSD_GObj* fighter_gobj);
f32 Stage_GetGroundFrictionMultiplier(struct _Fighter* fp);
BOOL func_8008239C(HSD_GObj* fighter_gobj, s32 facing_direction,
                   f32* height_attributes);
void func_80084FA8(HSD_GObj* fighter_gobj);
void func_80084EEC(HSD_GObj* fighter_gobj);
BOOL func_800827A0(HSD_GObj* fighter_gobj);
BOOL func_80081D0C(HSD_GObj* fighter_gobj);
void func_80085134(HSD_GObj* fighter_gobj);

/// CollisionCheck_StopLedge
void func_80084104(HSD_GObj* fighter_gobj);

BOOL func_80082708(HSD_GObj* fighter_gobj);
void func_80084F3C(HSD_GObj* fighter_gobj);
void func_80084280(struct _HSD_GObj*);
void func_8008403C(HSD_GObj*, HSD_GObjEvent);
void func_80084DB0(struct _HSD_GObj*);
void func_80082C74(HSD_GObj*, HSD_GObjEvent);

/// @todo Name does not follow our conventions.
BOOL EnvColl_CheckGroundAndLedge(HSD_GObj* fighter_gobj, s32 direction);

void func_80083F88(HSD_GObj* fighter_gobj);
void func_80085154(HSD_GObj* fighter_gobj);
void func_80083B68(HSD_GObj* fighter_gobj);
void func_800831CC(HSD_GObj*, s32 (*)(HSD_GObj*), HSD_GObjEvent);
BOOL func_800824A0(HSD_GObj*, struct _ftCollisionBox*);
BOOL func_80082888(HSD_GObj*, struct _ftCollisionBox*);
void func_80085204(HSD_GObj* fighter_gobj);
void func_80082B1C(HSD_GObj* fighter_gobj);
void func_80081B38(HSD_GObj* fighter_gobj);
BOOL func_80082A68(HSD_GObj* fighter_gobj);
void func_800851C0(HSD_GObj*);
void func_80082B78(HSD_GObj*);
void func_80085088(HSD_GObj*);

#endif
