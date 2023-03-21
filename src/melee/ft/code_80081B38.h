/** @file
 * @todo Rename to @c ftUnk3.h
 */
#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include <placeholder.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <melee/ft/fighter.h>

HSD_GObj* func_80082E3C(HSD_GObj* gobj);
f32 Stage_GetGroundFrictionMultiplier(Fighter* fp);
bool func_8008239C(HSD_GObj* gobj, s32 facing_direction,
                   f32* height_attributes);
void func_80084FA8(HSD_GObj* gobj);
void func_80084EEC(HSD_GObj* gobj);
bool func_800827A0(HSD_GObj* gobj);
bool func_80081D0C(HSD_GObj* gobj);
void func_80085134(HSD_GObj* gobj);

/// CollisionCheck_StopLedge
void func_80084104(HSD_GObj* gobj);

bool func_80082708(HSD_GObj* gobj);
void func_80084F3C(HSD_GObj* gobj);
void func_80084280(HSD_GObj*);
void func_8008403C(HSD_GObj*, HSD_GObjEvent);
void func_80084DB0(HSD_GObj*);
void func_80082C74(HSD_GObj*, HSD_GObjEvent);

/// @todo Name does not follow our conventions.
bool EnvColl_CheckGroundAndLedge(HSD_GObj* gobj, s32 direction);

void func_80083F88(HSD_GObj* gobj);
void func_80085154(HSD_GObj* gobj);
void func_80083B68(HSD_GObj* gobj);
bool func_800824A0(HSD_GObj*, struct _ftCollisionBox*);
bool func_80082888(HSD_GObj*, struct _ftCollisionBox*);
void func_80085204(HSD_GObj* gobj);
void func_80082B1C(HSD_GObj* gobj);
void func_80081B38(HSD_GObj* gobj);
bool func_80082A68(HSD_GObj* gobj);
void func_800851C0(HSD_GObj*);
void func_80082B78(HSD_GObj*);
void func_80085088(HSD_GObj*);
bool func_800821DC(void);
bool func_80084A18(HSD_GObj*);
void func_800849EC(Fighter*, Fighter*);
void func_80081C88(HSD_GObj* dst_gobj, f32 scl_y);
void func_80082838(void);
void func_800831CC(HSD_GObj*, HSD_GObjPredicate, HSD_GObjEvent);

UNK_RET func_80082978(UNK_PARAMS);
UNK_RET func_80082D40(UNK_PARAMS);
UNK_RET func_80082F28(UNK_PARAMS);
UNK_RET func_80083090(UNK_PARAMS);
UNK_RET func_80083318(UNK_PARAMS);
UNK_RET func_80083464(UNK_PARAMS);
UNK_RET func_800835B0(UNK_PARAMS);
UNK_RET func_8008370C(UNK_PARAMS);
UNK_RET func_80081DD4(UNK_PARAMS);
UNK_RET func_80083844(UNK_PARAMS);
UNK_RET func_80083910(UNK_PARAMS);
UNK_RET func_80083A48(UNK_PARAMS);
UNK_RET func_80083C00(UNK_PARAMS);
UNK_RET func_80083CE4(UNK_PARAMS);
UNK_RET func_80083DCC(UNK_PARAMS);
UNK_RET func_80083E64(UNK_PARAMS);
UNK_RET func_800841B8(UNK_PARAMS);
UNK_RET func_800843FC(UNK_PARAMS);
UNK_RET func_80081F2C(UNK_PARAMS);
UNK_RET func_800844EC(UNK_PARAMS);
UNK_RET func_800845B4(UNK_PARAMS);
UNK_RET func_800846B0(UNK_PARAMS);
UNK_RET func_800847D0(UNK_PARAMS);
UNK_RET func_800848DC(UNK_PARAMS);
UNK_RET func_80084A80(UNK_PARAMS);
UNK_RET func_80084BFC(UNK_PARAMS);
UNK_RET func_80084C38(UNK_PARAMS);
UNK_RET func_80084C74(UNK_PARAMS);
UNK_RET func_80084CB0(UNK_PARAMS);
bool func_80084CE4(Fighter* attacker, Fighter* victim);
UNK_RET func_80084E1C(UNK_PARAMS);
UNK_RET func_80082084(UNK_PARAMS);
UNK_RET func_80085004(UNK_PARAMS);
UNK_RET func_800850B4(UNK_PARAMS);
UNK_RET func_800851D0(UNK_PARAMS);
UNK_RET func_80082578(UNK_PARAMS);
UNK_RET func_80082638(UNK_PARAMS);

#endif
