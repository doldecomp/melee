#include "ftCo_CargoKneebend.h"

#include "ftCo_CargoJump.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_CargoWait.h"
#include "ftCo_KneeBend.h"
#include "ftCo_Shouldered.h"
#include "types.h"

#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/kinds/ftCaptain/types.h>
#include <melee/ft/kinds/ftDonkey/types.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCo_8009B9C8(Fighter_GObj* gobj, int arg1)
{
    u8 _[20] = { 0 };
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* fp_x2CC = fp->x2CC;
    fp->mv.co.cargokneebend.x4 = arg1;
    fp->mv.co.cargokneebend.x0 = 0;
    fp->mv.co.cargokneebend.x8 = fp_x2CC->cargo_hold.x24_JUMP_STARTUP_LAG;
    Fighter_ChangeMotionState(gobj, fp->x2CC->x4_motion_state + 5, Ft_MF_None,
                              0, 1, 0, NULL);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_8009C5A4(fp->victim_gobj, ftCo_MS_ShoulderedWait);
}

void ftCo_CargoKneebend_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.ca.specialhi.vel.y <= 0) {
        ftCo_8009BB64(gobj);
    }
    fp->mv.ca.specialhi.vel.y -= 1;
}

void ftCo_CargoKneebend_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj));
    ftCo_KneeBend_Check_ShortHop(gobj);
}

void ftCo_CargoKneebend_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_CargoKneebend_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoWait_Coll(gobj);
}
