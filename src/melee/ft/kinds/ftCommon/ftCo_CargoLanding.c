#include "ftCo_CargoLanding.h"

#include "ftCo_CargoWait.h"
#include "ftCo_Landing.h"
#include "ftCo_Shouldered.h"

#include <dolphin/mtx.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCaptain/types.h>
#include <melee/ft/kinds/ftDonkey/types.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCo_8009BD4C(Fighter_GObj* gobj)
{
    u8 _[20] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ca.specialhi.vel.x = fp->x2CC->cargo_hold.x28_LANDING_LAG;
    ftCo_Landing_Enter(gobj, fp->x2CC->x4_motion_state + 8, true, Ft_MF_None,
                       0.0F, 1.0F);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_8009C5A4(fp->victim_gobj, 0x10A);
}

void ftCo_CargoLanding_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.ca.specialhi.vel.x <= 0) {
        ftCo_8009B518(gobj);
    }
    fp->mv.ca.specialhi.vel.x -= 1;
}

void ftCo_CargoLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_CargoLanding_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoWait_Coll(gobj);
}
