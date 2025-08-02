#include <platform.h>

#include "ft/forward.h"

#include "ftCo_CargoFall.h"

#include "ftCo_CargoLanding.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_Shouldered.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ftDonkey/types.h"

#include <common_structs.h>

void ftCo_8009BC58(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fp->x2CC->x4_motion_state + 6,
                              Ft_MF_KeepFastFall, 0, 1, 0, NULL);
    ftAnim_SetAnimRate(gobj, 0);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
    ftCo_8009C5A4(fp->victim_gobj, ftCo_MS_ShoulderedWait);
}

void ftCo_CargoFall_Anim(Fighter_GObj* gobj) {}

void ftCo_CargoFall_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj));
}

void ftCo_CargoFall_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_CargoFall_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_8009BD4C);
}
