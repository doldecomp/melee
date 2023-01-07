/** @file
 * @todo Rename to @c ftUnk3.h
 */
#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

HSD_GObj* func_80082E3C(HSD_GObj* fighter_gobj);
f32 Stage_GetGroundFrictionMultiplier(struct _Fighter* fp);
BOOL func_8008239C(HSD_GObj* fighter_gobj, s32 facing_direction,
                   f32* height_attributes);
void func_80084FA8(HSD_GObj* fighter_gobj);
void func_80084EEC(HSD_GObj* fighter_gobj);
BOOL func_800827A0(HSD_GObj* fighter_gobj);
BOOL func_80081D0C(HSD_GObj* fighter_gobj);
void func_80085134(HSD_GObj* fighter_gobj);
void func_80084104(HSD_GObj* fighter_gobj);
BOOL func_80082708(HSD_GObj* fighter_gobj);
void func_80084F3C(HSD_GObj* fighter_gobj);
void func_80084280(struct _HSD_GObj*);
void func_8008403C(HSD_GObj*, HSD_GObjEvent);
void func_80084DB0(struct _HSD_GObj*);
void func_80082C74(HSD_GObj*, HSD_GObjEvent);

/// @todo Name does not follow our conventions.
BOOL EnvColl_CheckGroundAndLedge(HSD_GObj* fighter_gobj, s32 direction);

#endif
