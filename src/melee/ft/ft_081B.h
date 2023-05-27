/** @file
 * @todo Rename to @c ftUnk3.h
 */
#ifndef MELEE_FT_CODE_80081B38_H
#define MELEE_FT_CODE_80081B38_H

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include "ft/fighter.h"
#include "ft/types.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

Fighter_GObj* ft_80082E3C(Fighter_GObj* gobj);
float ft_GetGroundFrictionMultiplier(Fighter* fp);
bool ft_8008239C(Fighter_GObj* gobj, s32 facing_direction,
                 float* height_attributes);
void ft_80084FA8(Fighter_GObj* gobj);
void ft_80084EEC(Fighter_GObj* gobj);
bool ft_800827A0(Fighter_GObj* gobj);
GroundOrAir ft_80081D0C(Fighter_GObj* gobj);
void ft_80085134(Fighter_GObj* gobj);

/// CollisionCheck_StopLedge
void ft_80084104(Fighter_GObj* gobj);

GroundOrAir ft_80082708(Fighter_GObj* gobj);
void ft_80084F3C(Fighter_GObj* gobj);
void ft_80084280(Fighter_GObj*);
void ft_8008403C(Fighter_GObj*, HSD_GObjEvent);
void ft_80084DB0(Fighter_GObj*);
void ft_80082C74(Fighter_GObj*, void (*)(Fighter_GObj*, float lag));

/// @todo Name does not follow our conventions.
bool ft_CheckGroundAndLedge(Fighter_GObj* gobj, s32 direction);

void ft_80083F88(Fighter_GObj* gobj);
void ft_80085154(Fighter_GObj* gobj);
void ft_80083B68(Fighter_GObj* gobj);
bool ft_800824A0(Fighter_GObj*, ftCollisionBox*);
bool ft_80082888(Fighter_GObj*, ftCollisionBox*);
void ft_80085204(Fighter_GObj* gobj);
void ft_80082B1C(Fighter_GObj* gobj);
void ft_80081B38(Fighter_GObj* gobj);
bool ft_80082A68(Fighter_GObj* gobj);
void ft_800851C0(Fighter_GObj*);
void ftCo_AirCatchHit_Coll(Fighter_GObj*);
void ft_80085088(Fighter_GObj*);
bool ft_800821DC(void);
bool ft_80084A18(Fighter_GObj*);
void ft_800849EC(Fighter*, Fighter*);
void ft_80081C88(Fighter_GObj* dst_gobj, float scl_y);
void ft_80082838(void);
void ft_800831CC(Fighter_GObj*, bool (*)(Fighter_GObj*, enum_t),
                 HSD_GObjEvent);

UNK_RET ft_80082978(UNK_PARAMS);
UNK_RET ft_80082D40(UNK_PARAMS);
UNK_RET ft_80082F28(UNK_PARAMS);
void ft_80083090(Fighter_GObj* gobj, bool (*)(Fighter_GObj*, enum_t),
                 HSD_GObjEvent);
UNK_RET ft_80083318(UNK_PARAMS);
UNK_RET ft_80083464(UNK_PARAMS);
UNK_RET ft_800835B0(UNK_PARAMS);
void ft_8008370C(Fighter_GObj* gobj, HSD_GObjEvent cb);
bool ft_80081DD4(Fighter_GObj* gobj);
UNK_RET ft_80083844(UNK_PARAMS);
UNK_RET ft_80083910(UNK_PARAMS);
UNK_RET ft_80083A48(UNK_PARAMS);
UNK_RET ft_80083C00(UNK_PARAMS);
UNK_RET ft_80083CE4(UNK_PARAMS);
UNK_RET ft_80083DCC(UNK_PARAMS);
UNK_RET ft_80083E64(UNK_PARAMS);
void ft_800841B8(Fighter_GObj* gobj, HSD_GObjEvent cb);
UNK_RET ft_800843FC(UNK_PARAMS);
UNK_RET ft_80081F2C(UNK_PARAMS);
UNK_RET ft_800844EC(UNK_PARAMS);
void ft_800845B4(Fighter_GObj* gobj);
UNK_RET ft_800846B0(UNK_PARAMS);
UNK_RET ft_800847D0(UNK_PARAMS);
void ft_800848DC(Fighter_GObj* gobj, HSD_GObjEvent cb);
UNK_RET ft_80084A80(UNK_PARAMS);
bool ft_80084BFC(Fighter_GObj* gobj, int*, int*);
bool ft_80084C38(Fighter_GObj*, int*, int*, int*, char*);
bool ft_80084C74(Fighter_GObj*, int*, int*, int*);
UNK_RET ft_80084CB0(UNK_PARAMS);
bool ft_80084CE4(Fighter* attacker, Fighter* victim);
UNK_RET ft_80084E1C(UNK_PARAMS);
UNK_RET ft_80082084(UNK_PARAMS);
UNK_RET ft_80085004(UNK_PARAMS);
UNK_RET ft_800850B4(UNK_PARAMS);
UNK_RET ft_800851D0(UNK_PARAMS);
UNK_RET ft_80082578(UNK_PARAMS);
void ft_80082638(Fighter_GObj* gobj, ftCollisionBox*);
void ft_80085030(Fighter_GObj*, float gr_friction, float facing_dir);

#endif
