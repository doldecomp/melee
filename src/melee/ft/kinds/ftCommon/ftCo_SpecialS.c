#include "ftCo_SpecialS.h"

#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

/* 0960CC */ static void doEnter(Fighter_GObj* gobj);

/// Check @c SpecialS input without entering the state.
bool ftCo_SpecialS_HasInput(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_B &&
        ABS(fp->input.lstick.x) >= p_ftCommonData->x218)
    {
        return true;
    }
    return false;
}

bool ftCo_SpecialS_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ftData_SpecialS[fp->kind] == NULL) {
        return false;
    }
    if (fp->x688 == 0) {
        if (fp->input.lstick.x * fp->facing_dir < -p_ftCommonData->x220) {
            ftCommon_UpdateFacing(fp);
        }
        doEnter(gobj);
        return true;
    }
    return false;
}

static void doEnter(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    fp->gr_vel +=
        -(fp->gr_vel * (1 - fp->co_attrs.specials_ground_speed_retention)) *
        ft_GetGroundFrictionMultiplier(fp);
    ftData_SpecialS[fp->kind](gobj);
}
