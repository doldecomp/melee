#include <platform.h>

#include <dolphin/mtx/forward.h>

#include "ftCo_CargoLanding.h"

#include "ftCo_CargoWait.h"
#include "ftCo_Shouldered.h"

#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCaptain/types.h"
#include "ftDonkey/types.h"

void ftCo_8009BD4C(ftCo_GObj* gobj)
{
    u8 _[20] = { 0 };
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ca.specialhi.vel.x = fp->x2CC->cargo_hold.x28_LANDING_LAG;
    ftCo_800D5AEC(gobj, fp->x2CC->x4_motion_state + 8, 1, 0, 0, 1);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_8009C5A4(fp->victim_gobj, 0x10A);
}

void ftCo_CargoLanding_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.ca.specialhi.vel.x <= 0) {
        ftCo_8009B518(gobj);
    }
    fp->mv.ca.specialhi.vel.x -= 1;
}

void ftCo_CargoLanding_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_CargoLanding_Coll(ftCo_GObj* gobj)
{
    ftCo_CargoWait_Coll(gobj);
}
