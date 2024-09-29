#include <platform.h>

#include <dolphin/mtx/forward.h>

#include "ftCo_Down.h"

#include "ftCo_DownAttack.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

/* 097EAC */ static void ftCo_80098324(ftCo_GObj* gobj, FtMotionId msid);

static inline bool inlineA0(ftCo_Fighter* fp)
{
    if (ABS(fp->input.lstick.x) >= p_ftCommonData->x248 &&
        ftCo_GetLStickAngle(fp) < p_ftCommonData->x20)
    {
        return true;
    } else {
        return false;
    }
}

bool ftCo_Down_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    float stick_x;
    if (ftCo_800DF678(fp)) {
        stick_x = fp->input.cstick.x;
    } else if (inlineA0(fp)) {
        stick_x = fp->input.lstick.x;
    } else {
        return false;
    }
    {
        FtMotionId msid;
        if (stick_x * fp->facing_dir >= 0) {
            msid = fp->motion_id == ftCo_MS_DownWaitU ? ftCo_MS_DownFowardU
                                                      : ftCo_MS_DownFowardD;
        } else {
            msid = fp->motion_id == ftCo_MS_DownWaitU ? ftCo_MS_DownBackU
                                                      : ftCo_MS_DownBackD;
        }
        ftCo_80098324(gobj, msid);
    }
    return true;
}

void ftCo_80098324(ftCo_GObj* gobj, FtMotionId msid)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007CCE8(fp);
}

void ftCo_Down_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Down_IASA(ftCo_GObj* gobj) {}

void ftCo_Down_Phys(ftCo_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Down_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}

static inline bool inlineB0(ftCo_Fighter* fp)
{
    if (fp->x67C < p_ftCommonData->x24C || fp->x67D < p_ftCommonData->x24C) {
        return true;
    }
    return false;
}

bool ftCo_80098400(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (inlineB0(fp) || ftCo_800DF644(fp)) {
        FtMotionId msid = fp->motion_id == ftCo_MS_DownBoundU
                              ? ftCo_MS_DownAttackU
                              : ftCo_MS_DownAttackD;
        ftCo_8009856C(gobj, msid);
        return true;
    }
    return false;
}
