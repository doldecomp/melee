#include "ftCo_ItemParasolFall.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftCommon/inlines.h"

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
