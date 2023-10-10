#ifndef MELEE_FT_CHARA_FTCOMMON_INLINES_H
#define MELEE_FT_CHARA_FTCOMMON_INLINES_H

#include <platform.h>
#include "ftCommon/forward.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <baselib/gobj.h>

static inline void ftCo_SpawnEf(ftCo_GObj* gobj, HSD_JObj* joint, uint arg2,
                                enum_t arg3)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    efAsync_Spawn((HSD_GObj*) gobj, &fp->x60C, arg2, arg3, joint);
}

static inline void ftCo_Thrown_Enter(ftCo_GObj* gobj, FtMotionId msid,
                                     MotionFlags mf, float anim_start)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = GET_FIGHTER(fp->victim_gobj)->facing_dir;
    fp->mv.co.capturekoopa.x0 = false;
    Fighter_ChangeMotionState(gobj, msid, mf, anim_start, 1, 0,
                              fp->victim_gobj);
    fp->accessory1_cb = (HSD_GObjEvent) ftCo_800DE508;
    ftCommon_8007E2F4(fp, 0x1FF);
}

#endif
