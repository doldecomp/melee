#include "ftCo_ItemParasolFallSpecial.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_DamageIce.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_ItemParasolOpen.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftCommon/inlines.h"

#include "ftPeach/forward.h"

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
    ft_8008370C(gobj, (HSD_GObjEvent) ftCo_LandingFallSpecial_Enter_Basic);
}
