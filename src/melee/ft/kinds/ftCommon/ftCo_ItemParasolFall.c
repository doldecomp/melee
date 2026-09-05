#include "ftCo_ItemParasolFall.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_Fall.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_JumpAerial.h"
#include "ftCo_Landing.h"
#include "ftCo_SpecialAir.h"
#include "inlines.h"

#include "forward.h"
#include <melee/ft/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

void ftCo_800CF280(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_ItemParasolFall,
                              Ft_MF_SkipHit | Ft_MF_SkipParasol, 0, 1, 0,
                              NULL);
}

void ftCo_ItemParasolFall_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemParasolFall_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    if (fp->input.lstick.y <= p_ftCommonData->close_parasol_threshold &&
        ft_80087988(gobj))
    {
        ftCo_Fall_Enter(gobj);
    } else {
        RETURN_IF(ftCo_800CB870(gobj));
    }
}

void ftCo_ItemParasolFall_Phys(Fighter_GObj* gobj)
{
    ftCo_ItemParasol_Phys(gobj);
}

void ftCo_ItemParasolFall_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, ftCo_Landing_Enter_Basic);
}
