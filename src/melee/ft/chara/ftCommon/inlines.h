#ifndef MELEE_FT_CHARA_FTCOMMON_INLINES_H
#define MELEE_FT_CHARA_FTCOMMON_INLINES_H

#include "placeholder.h"

#include <platform.h>

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Thrown.h"
#include "ftCommon/types.h"

#include <baselib/forward.h>

#include <baselib/gobj.h>

static inline void ftCo_SpawnEf(Fighter_GObj* gobj, HSD_JObj* joint, u32 arg2,
                                enum_t arg3)
{
    Fighter* fp = gobj->user_data;
    FORCE_PAD_STACK_8;
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

static inline void ftCo_Barrel_ApplyKnockback(Fighter* fp, float kb_angle,
                                              HitCapsule* hit)
{
    if (kb_angle < 0) {
        kb_angle += 360;
    }
    kb_angle = fp->facing_dir < 0.0f ? kb_angle : 180.0f - kb_angle;
    fp->dmg.kb_applied = ftColl_80079EA8(fp, hit, hit->unk_count);
    fp->dmg.x1848_kb_angle = kb_angle;
    fp->dmg.facing_dir_1 = fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 0;
    fp->dmg.x1854_collpos = fp->cur_pos;
    fp->dmg.x1860_element = hit->element;
}

#endif
