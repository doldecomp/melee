#include <platform.h>
#include "ft/forward.h"

#include "ftCo_Pass.h"

#include "ftCo_AttackAir.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "mp/mpcoll.h"

bool ft_80099F1C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.lstick.y <= -p_ftCommonData->x464 &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x468 &&
        mpColl_8004CBC0(&fp->coll_data))
    {
        return true;
    }
    return false;
}

bool ftCo_80099F9C(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (ft_800C5240(gobj)) {
        return ftCo_800C60C8(gobj);
    }
    if (!fp->mv.co.pass.x0 && ft_80099F1C(gobj)) {
        fp->mv.co.pass.x0 = true;
        fp->mv.co.pass.x4 = p_ftCommonData->x470;
        return true;
    }
    return false;
}

bool ft_8009A080(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.held_inputs & HSD_PAD_LR && ft_80099F1C(gobj)) {
        ftCo_8009A228(gobj);
        return true;
    }
    return false;
}

bool ft_8009A134(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    CollData* coll = &fp->coll_data;
    if (mpColl_8004CBC0(coll)) {
        mpColl_8004CBE8(coll);
        return true;
    }
    return false;
}

void ft_8009A184(ftCo_GObj* gobj, FtMotionId msid, MotionFlags mf,
                 float anim_start)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    ftCommon_8007D468(fp);
    fp->self_vel.y = p_ftCommonData->x46C;
    Fighter_ChangeMotionState(gobj, msid, mf, NULL, anim_start, 1, 0);
    mpColl_8004CBE8(&fp->coll_data);
    fp->x671_timer_lstick_tilt_y = 0xFE;
}

void ftCo_8009A228(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    ftCommon_8007D468(fp);
    fp->self_vel.y = p_ftCommonData->x46C;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Pass, Ft_MF_None, NULL, 0, 1, 0);
    mpColl_8004CBE8(&fp->coll_data);
    fp->x671_timer_lstick_tilt_y = 0xFE;
}

void ftCo_Pass_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftCo_Pass_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj))
    RETURN_IF(ft_80095328(gobj, NULL))
    RETURN_IF(ftCo_800D7100(gobj))
    RETURN_IF(ftCo_800C3B10(gobj))
    RETURN_IF(ftCo_80099A58(gobj))
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj))
    RETURN_IF(ftCo_800D705C(gobj))
    RETURN_IF(ft_800CB870(gobj))
}

void ftCo_Pass_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_Pass_Coll(ftCo_GObj* gobj)
{
    ft_80082F28(gobj);
}
