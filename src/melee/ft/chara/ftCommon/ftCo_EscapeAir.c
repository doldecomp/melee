#include "ftCo_EscapeAir.h"

#include "ftCo_AirCatch.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_ItemThrow.h"
#include "math.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 099D70 */ static void ftCo_80099D70(Fighter_GObj* gobj);

typedef enum cmd_var_idx {
    cmd_skip_decay,
} cmd_var_idx;

bool ftCo_80099A58(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->input.x668 & (HSD_PAD_R | HSD_PAD_L)) {
        ftCo_80099A9C(gobj, p_ftCommonData->x334);
        return true;
    }
    return false;
}

static inline void inlineA0(Fighter* fp)
{
    fp->mv.co.escapeair.self_vel = fp->self_vel;
    if (ABS(fp->input.lstick.x) < p_ftCommonData->escapeair_deadzone.x) {
        if (ABS(fp->input.lstick.y) < p_ftCommonData->escapeair_deadzone.y) {
            fp->self_vel.y = 0;
            fp->self_vel.x = 0;
            return;
        }
    }
    {
        float angle = ftCommon_8007D9D4(fp);
        fp->self_vel.x = p_ftCommonData->escapeair_force * cosf(angle);
        fp->self_vel.y = p_ftCommonData->escapeair_force * sinf(angle);
    }
}

void ftCo_80099A9C(Fighter_GObj* gobj, int timer)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    ftCo_800D705C(gobj);
    inlineA0(fp);
    fp->cmd_vars[cmd_skip_decay] = false;
    fp->mv.co.escapeair.timer = timer;
    Fighter_ChangeMotionState(gobj, ftCo_MS_EscapeAir, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007EBAC(fp, 23, 0);
}

void ftCo_EscapeAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 1, false, p_ftCommonData->x340,
                      p_ftCommonData->x344);
    }
}

void ftCo_EscapeAir_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.escapeair.timer != 0) {
        bool b;
        Vec3 self_vel = fp->mv.co.escapeair.self_vel;
        u8 _[4] = { 0 };
        if (ftCo_80095328(gobj, &b)) {
            if (b) {
                fp->self_vel = self_vel;
            }
            return;
        }
        ftCo_800D705C(gobj);
        --fp->mv.co.escapeair.timer;
    }
    if (ftCo_800C3B10(gobj)) {
        fp->self_vel.x *= 0.1f;
    }
}

void ftCo_EscapeAir_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!fp->cmd_vars[cmd_skip_decay]) {
        fp->self_vel.x *= p_ftCommonData->escapeair_decay;
        fp->self_vel.y *= p_ftCommonData->escapeair_decay;
    } else {
        ft_80084DB0(gobj);
    }
}

void ftCo_EscapeAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_80099D70);
}

void ftCo_80099D70(Fighter_GObj* gobj)
{
    ftCo_800D5CB0(gobj, 0, p_ftCommonData->x344);
}
