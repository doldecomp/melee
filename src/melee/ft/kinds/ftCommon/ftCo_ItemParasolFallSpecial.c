#include "ftCo_ItemParasolFallSpecial.h"

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

#include "forward.h"

#include "ftCo_FallSpecial.h"
#include "ftCo_JumpAerial.h"
#include "ftCo_Landing.h"
#include "inlines.h"

#include <melee/ft/kinds/ftPeach/forward.h>

void ftCo_800CF3C8(Fighter_GObj* gobj)
{
    Fighter* temp_r4;
    s32 var_r4;

    temp_r4 = gobj->user_data;
    Fighter_ChangeMotionState(
        gobj,
        ftCo_ItemParasolGetFallMotionId(gobj, ftPe_MS_ItemParasolFall,
                                        ftCo_MS_ItemParasolFallSpecial),
        Ft_MF_SkipHit | Ft_MF_SkipParasol, 0.0f, 1.0f, 0.0f, NULL);
}

void ftCo_ItemParasolFallSpecial_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemParasolFallSpecial_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y <= p_ftCommonData->close_parasol_threshold &&
        ft_80087988(gobj))
    {
        ftCo_800968C8(gobj);
    } else {
        RETURN_IF(ftCo_800CB870(gobj));
    }
}

void ftCo_ItemParasolFallSpecial_Phys(Fighter_GObj* gobj)
{
    ftCo_ItemParasol_Phys(gobj);
}

void ftCo_ItemParasolFallSpecial_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, ftCo_LandingFallSpecial_Enter_Basic);
}
