#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CliffJump.h"

#include "ftCo_09C4.h"
#include "ftCo_FallSpecial.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"

/* 09B1B8 */ static void ftCo_8009B1B8(ftCo_GObj* gobj);
/* 09B2F8 */ static void ftCo_8009B2F8(ftCo_GObj* gobj);

bool ftCo_8009B170(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (ftCo_800CAE80(gobj)) {
        ftCo_8009B1B8(gobj);
        return true;
    }
    return false;
}

void ftCo_8009B1B8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    FtMotionId msid = (float) fp->dmg.x1830_percent < p_ftCommonData->x488
                          ? ftCo_MS_CliffJumpQuick1
                          : ftCo_MS_CliffJumpSlow1;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 32);
    fp->x221D_b7 = true;
    ftCo_CliffCatch_Phys(gobj);
}

void ftCo_CliffJump1_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_8009B2F8(gobj);
    }
}

void ftCo_CliffJump1_IASA(ftCo_GObj* gobj) {}

void ftCo_CliffJump1_Phys(ftCo_GObj* gobj)
{
    ftCo_CliffCatch_Phys(gobj);
}

void ftCo_CliffJump1_Coll(ftCo_GObj* gobj)
{
    ftCo_CliffClimb_Coll(gobj);
}

void ftCo_8009B2F8(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    FtMotionId msid = fp->motion_id == ftCo_MS_CliffJumpQuick1
                          ? ftCo_MS_CliffJumpQuick2
                          : ftCo_MS_CliffJumpSlow2;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.cliffjump.x0 = false;
    fp->self_vel.x +=
        fp->facing_dir * fp->co_attrs.ledge_jump_horizontal_velocity;
    fp->self_vel.y = fp->co_attrs.ledge_jump_vertical_velocity;
}

void ftCo_8009B390(ftCo_GObj* gobj, float force_mul)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    FtMotionId msid = fp->motion_id == ftCo_MS_CliffJumpQuick1
                          ? ftCo_MS_CliffJumpQuick2
                          : ftCo_MS_CliffJumpSlow2;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.cliffjump.x0 = false;
    fp->self_vel.y = fp->co_attrs.ledge_jump_vertical_velocity * force_mul;
}

void ftCo_CliffJump2_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftCo_CliffJump2_IASA(ftCo_GObj* gobj) {}

void ftCo_CliffJump2_Phys(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!fp->mv.co.cliffjump.x0) {
        fp->mv.co.cliffjump.x0 = true;
    } else {
        ft_80084DB0(gobj);
    }
}

void ftCo_CliffJump2_Coll(ftCo_GObj* gobj)
{
    ft_800835B0(gobj, ftCo_80096CC8, ft_80082B1C);
}
