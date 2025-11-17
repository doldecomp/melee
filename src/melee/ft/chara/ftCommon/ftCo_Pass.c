#include "ftCo_Pass.h"

#include "ftCo_0C60.h"
#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_HammerWait.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"

#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/types.h"
#include "mp/mpcoll.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_80099F1C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->input.lstick.y <= -p_ftCommonData->x464 &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x468 &&
        mpColl_IsOnPlatform(&fp->coll_data))
    {
        return true;
    }
    return false;
}

bool ftCo_80099F9C(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
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

bool ftCo_8009A080(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->input.held_inputs & HSD_PAD_LR && ftCo_80099F1C(gobj)) {
        ftCo_8009A228(gobj);
        return true;
    }
    return false;
}

bool ftCo_8009A134(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    CollData* coll = &fp->coll_data;
    if (mpColl_IsOnPlatform(coll)) {
        mpUpdateFloorSkip(coll);
        return true;
    }
    return false;
}

void ftCo_8009A184(Fighter_GObj* gobj, FtMotionId msid, MotionFlags mf,
                   float anim_start)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    ftCommon_ClampAirDrift(fp);
    fp->self_vel.y = p_ftCommonData->x46C;
    Fighter_ChangeMotionState(gobj, msid, mf, anim_start, 1, 0, NULL);
    mpUpdateFloorSkip(&fp->coll_data);
    fp->x671_timer_lstick_tilt_y = 0xFE;
}

void ftCo_8009A228(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    ftCommon_ClampAirDrift(fp);
    fp->self_vel.y = p_ftCommonData->x46C;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Pass, Ft_MF_None, 0, 1, 0, NULL);
    mpUpdateFloorSkip(&fp->coll_data);
    fp->x671_timer_lstick_tilt_y = 0xFE;
}

void ftCo_Pass_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_Pass_IASA(Fighter_GObj* gobj)
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

void ftCo_Pass_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_Pass_Coll(Fighter_GObj* gobj)
{
    ft_80082F28(gobj);
}
