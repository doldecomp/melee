#include "ftCo_FallAerial.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"

void ftCo_FallAerial_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallAerial, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.fallaerial.smid = ftCo_SM_FallAerial;
    fp->mv.co.fallaerial.x4 = 0.0F;
}

void ftCo_FallAerial_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_Fall_Anim_Inner(gobj, &fp->mv.co.fallaerial.x4, ftCo_SM_FallAerial,
                         ftCo_SM_FallAerialF, ftCo_SM_FallAerialB);
    ftCo_800CC988(gobj, fp->mv.co.fallaerial.x4);
}

void ftCo_FallAerial_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_Fall_IASA_Inner(gobj));
}

void ftCo_FallAerial_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}
