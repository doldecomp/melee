#ifndef MELEE_FT_CHARA_FTCOMMON_INLINES_H
#define MELEE_FT_CHARA_FTCOMMON_INLINES_H

#include <platform.h>

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/types.h"

#include <baselib/forward.h>

#include <baselib/gobj.h>

static inline void ftCo_SpawnEf(Fighter_GObj* gobj, HSD_JObj* joint, u32 arg2,
                                enum_t arg3)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    efAsync_Spawn((HSD_GObj*) gobj, &fp->x60C, arg2, arg3, joint);
}

static inline void ftCo_Thrown_Enter(Fighter_GObj* gobj, FtMotionId msid,
                                     MotionFlags mf, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = GET_FIGHTER(fp->victim_gobj)->facing_dir;
    fp->mv.co.capturekoopa.x0 = false;
    Fighter_ChangeMotionState(gobj, msid, mf, anim_start, 1, 0,
                              fp->victim_gobj);
    fp->accessory1_cb = (HSD_GObjEvent) ftCo_800DE508;
    ftCommon_8007E2F4(fp, 0x1FF);
}

#endif
