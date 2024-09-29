#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_LandingAir.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

void ftCo_LandingAir_EnterWithLag(ftCo_GObj* gobj)
{
    u8 _[20] = { 0 };
    float lag;
    FtMotionId msid = ftCo_MS_None;
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        switch (fp->motion_id) {
        case ftCo_MS_AttackAirN:
            lag = fp->co_attrs.landingairn_lag;
            msid = ftCo_MS_LandingAirN;
            break;
        case ftCo_MS_AttackAirF:
            lag = fp->co_attrs.landingairf_lag;
            msid = ftCo_MS_LandingAirF;
            break;
        case ftCo_MS_AttackAirB:
            lag = fp->co_attrs.landingairb_lag;
            msid = ftCo_MS_LandingAirB;
            break;
        case ftCo_MS_AttackAirHi:
            lag = fp->co_attrs.landingairhi_lag;
            msid = ftCo_MS_LandingAirHi;
            break;
        case ftCo_MS_AttackAirLw:
            msid = ftCo_MS_LandingAirLw;
            lag = fp->co_attrs.landingairlw_lag;
            break;
        }
        if (msid != ftCo_MS_None && fp->x67F < p_ftCommonData->xE4) {
            float div_lag = lag / p_ftCommonData->xE8;
            int int_lag = div_lag;
            if ((int) div_lag == 0) {
                int_lag = 1;
            }
            lag = int_lag;
        }
    }
    if (msid != ftCo_MS_None) {
        ftCo_LandingAir_EnterWithMsidLag(gobj, msid, lag);
    } else {
        ftCo_800D5BF8(gobj);
    }
}

void ftCo_LandingAir_EnterWithMsidLag(ftCo_GObj* gobj, FtMotionId msid,
                                      float lag)
{
    u8 _[8] = { 0 };
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_SetAnimRate(gobj, (ftAnim_8006F484(gobj) + 0.1f) / lag);
}

void ftCo_LandingAir_Anim(ftCo_GObj* gobj)
{
    ftCo_Landing_Anim(gobj);
}

void ftCo_LandingAir_IASA(ftCo_GObj* gobj) {}

void ftCo_LandingAir_Phys(ftCo_GObj* gobj)
{
    ftCo_Landing_Phys(gobj);
}

void ftCo_LandingAir_Coll(ftCo_GObj* gobj)
{
    ftCo_Landing_Coll(gobj);
}
