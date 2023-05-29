#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CargoKneebend.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftanim.h"
#include "ftDonkey/types.h"

void ftCo_8009B9C8(ftCo_GObj* gobj, int arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20] = { 0 };
#endif
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* fp_x2CC = fp->x2CC;
    fp->mv.co.cargokneebend.x4 = arg1;
    fp->mv.co.cargokneebend.x0 = 0;
    fp->mv.co.cargokneebend.x8 = fp_x2CC->cargo_hold.x24_JUMP_STARTUP_LAG;
    Fighter_ChangeMotionState(gobj, fp->x2CC->x4_motion_state + 5, Ft_MF_None,
                              NULL, 0, 1, 0);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_8009C5A4(fp->x1A58_interactedFighter, ftCo_MS_ShoulderedWait);
}

void ftCo_CargoKneebend_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.ca.specialhi.vel.y <= 0) {
        ftCo_8009BB64(gobj);
    }
    fp->mv.ca.specialhi.vel.y -= 1;
}

void ftCo_CargoKneebend_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj))
    ftCo_800CB59C(gobj);
}

void ftCo_CargoKneebend_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_CargoKneebend_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoWait_Coll(gobj);
}
