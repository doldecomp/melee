#include <platform.h>

#include "ft/forward.h"

#include "ftCo_Pass.h"

#include "ftCo_0C60.h"
#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_HammerWait.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "mp/mpcoll.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_80099F1C(ftCo_GObj* gobj)
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
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCo_800C5240(gobj)) {
        return ftCo_800C60C8(gobj);
    }
    if (!fp->mv.co.pass.x0 && ftCo_80099F1C(gobj)) {
        fp->mv.co.pass.x0 = true;
        fp->mv.co.pass.x4 = p_ftCommonData->x470;
        return true;
    }
    return false;
}

bool ftCo_8009A080(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.held_inputs & HSD_PAD_LR && ftCo_80099F1C(gobj)) {
        ftCo_8009A228(gobj);
        return true;
    }
    return false;
}

bool ftCo_8009A134(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    CollData* coll = &fp->coll_data;
    if (mpColl_8004CBC0(coll)) {
        mpColl_8004CBE8(coll);
        return true;
    }
    return false;
}

void ftCo_8009A184(ftCo_GObj* gobj, FtMotionId msid, MotionFlags mf,
                   float anim_start)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    ftCommon_8007D468(fp);
    fp->self_vel.y = p_ftCommonData->x46C;
    Fighter_ChangeMotionState(gobj, msid, mf, anim_start, 1, 0, NULL);
    mpColl_8004CBE8(&fp->coll_data);
    fp->x671_timer_lstick_tilt_y = 0xFE;
}

void ftCo_8009A228(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    ftCommon_8007D468(fp);
    fp->self_vel.y = p_ftCommonData->x46C;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Pass, Ft_MF_None, 0, 1, 0, NULL);
    mpColl_8004CBE8(&fp->coll_data);
    fp->x671_timer_lstick_tilt_y = 0xFE;
}

void ftCo_Pass_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftCo_Pass_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800D7100(gobj));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
}

void ftCo_Pass_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_Pass_Coll(ftCo_GObj* gobj)
{
    ft_80082F28(gobj);
}
