#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_AttackS3.h"

#include "ftCo_08A6.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"

#include <placeholder.h>

/* 08B788 */ static void decideAngle(ftCo_GObj* gobj);

bool ftCo_AttackS3_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A &&
        fp->input.lstick.x * fp->facing_dir >= p_ftCommonData->x98)
    {
        if (ABS(ftCo_GetLStickAngle(fp)) < p_ftCommonData->x20) {
            if (fp->item_gobj) {
                if (fp->input.held_inputs & HSD_Pad_LR ||
                    it_8026B30C(fp->item_gobj) == 0)
                {
                    ft_800957F4(gobj, ftCo_MS_LightThrowF);
                    return true;
                } else {
                    switch (it_8026B30C(fp->item_gobj)) {
                    case 2:
                        ftCo_Attack_800CCF58(gobj, 1);
                        return true;
                    case 3:
                        ftCo_Attack_800CDD14(gobj);
                        return true;
                    }
                }
            }
            decideAngle(gobj);
            return true;
        }
    }
    return false;
}

static void decideAngle(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80094790(gobj)) {
        FtMotionId msid;
        float stick_angle = ftCo_GetLStickAngle(fp);
        if (stick_angle > p_ftCommonData->x9C &&
            ftData_80085FD4(fp, ftCo_MS_AttackS3S)->x8 != NULL)
        {
            msid = ftCo_MS_AttackS3Hi;
        } else if (stick_angle > p_ftCommonData->xA0 &&
                   ftData_80085FD4(fp, ftCo_MS_AttackS3LwS)->x8 != NULL)
        {
            msid = ftCo_MS_AttackS3HiS;
        } else if (stick_angle < p_ftCommonData->xA8 &&
                   ftData_80085FD4(fp, ftCo_MS_AttackLw3)->x8 != NULL)
        {
            msid = ftCo_MS_AttackS3Lw;
        } else if (stick_angle < p_ftCommonData->xA4 &&
                   ftData_80085FD4(fp, ftCo_MS_AttackHi3)->x8 != NULL)
        {
            msid = ftCo_MS_AttackS3LwS;
        } else {
            msid = ftCo_MS_AttackS3S;
        }
        fp->allow_interrupt = false;
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, NULL, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCo_AttackS3_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_AttackS3_IASA(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackS3_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_AttackS3_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}
