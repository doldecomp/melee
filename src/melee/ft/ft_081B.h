/** @file
 * @todo Rename to @c ftUnk3.h
 */
#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include "ft/fighter.h"
#include "ft/types.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

HSD_GObj* ft_80082E3C(HSD_GObj* gobj);
f32 ft_GetGroundFrictionMultiplier(Fighter* fp);
bool ft_8008239C(HSD_GObj* gobj, s32 facing_direction, f32* height_attributes);
void ft_80084FA8(HSD_GObj* gobj);
void ft_80084EEC(HSD_GObj* gobj);
bool ft_800827A0(HSD_GObj* gobj);
GroundOrAir ft_80081D0C(HSD_GObj* gobj);
void ft_80085134(HSD_GObj* gobj);

/// CollisionCheck_StopLedge
void ft_80084104(HSD_GObj* gobj);

GroundOrAir ft_80082708(HSD_GObj* gobj);
void ft_80084F3C(HSD_GObj* gobj);
void ft_80084280(HSD_GObj*);
void ft_8008403C(HSD_GObj*, HSD_GObjEvent);
void ft_80084DB0(HSD_GObj*);
void ft_80082C74(HSD_GObj*, void (*)(ftCo_GObj*, float lag));

/// @todo Name does not follow our conventions.
bool ft_CheckGroundAndLedge(HSD_GObj* gobj, s32 direction);

void ft_80083F88(HSD_GObj* gobj);
void ft_80085154(HSD_GObj* gobj);
void ft_80083B68(HSD_GObj* gobj);
bool ft_800824A0(HSD_GObj*, struct _ftCollisionBox*);
bool ft_80082888(HSD_GObj*, struct _ftCollisionBox*);
void ft_80085204(HSD_GObj* gobj);
void ft_80082B1C(HSD_GObj* gobj);
void ft_80081B38(HSD_GObj* gobj);
bool ft_80082A68(HSD_GObj* gobj);
void ft_800851C0(HSD_GObj*);
void ftCo_AirCatchHit_Coll(HSD_GObj*);
void ft_80085088(HSD_GObj*);
bool ft_800821DC(void);
bool ft_80084A18(HSD_GObj*);
void ft_800849EC(Fighter*, Fighter*);
void ft_80081C88(HSD_GObj* dst_gobj, f32 scl_y);
void ft_80082838(void);
void ft_800831CC(HSD_GObj*, HSD_GObjPredicate, HSD_GObjEvent);

UNK_RET ft_80082978(UNK_PARAMS);
UNK_RET ft_80082D40(UNK_PARAMS);
UNK_RET ft_80082F28(UNK_PARAMS);
UNK_RET ft_80083090(UNK_PARAMS);
UNK_RET ft_80083318(UNK_PARAMS);
UNK_RET ft_80083464(UNK_PARAMS);
UNK_RET ft_800835B0(UNK_PARAMS);
UNK_RET ft_8008370C(UNK_PARAMS);
bool ft_80081DD4(ftCo_GObj* gobj);
UNK_RET ft_80083844(UNK_PARAMS);
UNK_RET ft_80083910(UNK_PARAMS);
UNK_RET ft_80083A48(UNK_PARAMS);
UNK_RET ft_80083C00(UNK_PARAMS);
UNK_RET ft_80083CE4(UNK_PARAMS);
UNK_RET ft_80083DCC(UNK_PARAMS);
UNK_RET ft_80083E64(UNK_PARAMS);
UNK_RET ft_800841B8(UNK_PARAMS);
UNK_RET ft_800843FC(UNK_PARAMS);
UNK_RET ft_80081F2C(UNK_PARAMS);
UNK_RET ft_800844EC(UNK_PARAMS);
UNK_RET ft_800845B4(UNK_PARAMS);
UNK_RET ft_800846B0(UNK_PARAMS);
UNK_RET ft_800847D0(UNK_PARAMS);
void ft_800848DC(ftCo_GObj* goibj, HSD_GObjEvent cb);
UNK_RET ft_80084A80(UNK_PARAMS);
UNK_RET ft_80084BFC(UNK_PARAMS);
UNK_RET ft_80084C38(UNK_PARAMS);
UNK_RET ft_80084C74(UNK_PARAMS);
UNK_RET ft_80084CB0(UNK_PARAMS);
bool ft_80084CE4(Fighter* attacker, Fighter* victim);
UNK_RET ft_80084E1C(UNK_PARAMS);
UNK_RET ft_80082084(UNK_PARAMS);
UNK_RET ft_80085004(UNK_PARAMS);
UNK_RET ft_800850B4(UNK_PARAMS);
UNK_RET ft_800851D0(UNK_PARAMS);
UNK_RET ft_80082578(UNK_PARAMS);
UNK_RET ft_80082638(UNK_PARAMS);
void ft_80085030(ftCo_GObj*, ftCommonData*, float gr_friction,
                 float facing_dir);

#endif
