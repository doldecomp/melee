#include "ftCo_CargoTurn.h"

#include "ftCo_CargoJump.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_CargoWait.h"
#include "ftCo_Shouldered.h"

#include <Runtime/platform.h>

#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/types.h>
#include "ftCo_Turn.h"
#include "types.h"
#include <melee/ft/kinds/ftDonkey/types.h>

bool ftCo_8009B818(Fighter_GObj* gobj)
{
    if (ftCo_800C97A8(gobj)) {
        ftCo_8009B860(gobj);
        return true;
    }
    return false;
}

void ftCo_8009B860(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* fp_x2CC = fp->x2CC;
    ftCo_Turn_Enter(gobj, fp_x2CC->x4_motion_state + 4, 0, 0,
                    fp_x2CC->cargo_hold.x20_TURN_SPEED, 0);
    ftCo_8009C5A4(fp->victim_gobj, ftCo_MS_ShoulderedTurn);
}

void ftCo_CargoTurn_Anim(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.walk.fast_anim_frame > 0) {
        fp->mv.co.walk.fast_anim_frame -= 1;
    } else if (!fp->mv.co.cargoturn.x0) {
        Fighter_GObj* other_gobj = fp->victim_gobj;
        Fighter* other_fp = other_gobj->user_data;
        fp->mv.co.cargoturn.x0 = true;
        fp->facing_dir = -fp->facing_dir;
        other_fp->facing_dir = fp->facing_dir;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_8009B518(gobj);
    }
}

void ftCo_CargoTurn_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj));
    RETURN_IF(ftCo_8009BB1C(gobj));
}

void ftCo_CargoTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_CargoTurn_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoWait_Coll(gobj);
}
