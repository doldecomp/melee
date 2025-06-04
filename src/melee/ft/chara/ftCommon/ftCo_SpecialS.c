#include <platform.h>

#include <baselib/forward.h>

#include "ftCo_SpecialS.h"

#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 0960CC */ static void doEnter(ftCo_GObj* gobj);

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

bool ftCo_SpecialS_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (ftData_SpecialS[fp->kind] == NULL) {
        return false;
    }
    if (fp->x688 == 0) {
        if (fp->input.lstick.x * fp->facing_dir < -p_ftCommonData->x220) {
            ftCommon_8007D9FC(fp);
        }
        doEnter(gobj);
        return true;
    }
    return false;
}

static void doEnter(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    fp->gr_vel += -(fp->gr_vel * (1 - fp->co_attrs.xB8)) *
                  ft_GetGroundFrictionMultiplier(fp);
    ftData_SpecialS[fp->kind](gobj);
}
