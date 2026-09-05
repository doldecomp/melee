#include "ftCo_ItemParasolDamageFall.h"

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

#include "forward.h"

#include "ftCo_DamageFall.h"
#include "ftCo_DamageIce.h"

void ftCo_800CF4DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_ItemParasolDamageFall,
                              Ft_MF_KeepFastFall, 0.0f, 1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
}

void ftCo_ItemParasolDamageFall_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemParasolDamageFall_IASA(Fighter_GObj* gobj)
{
    ftCo_DamageFall_IASA(gobj);
}

void ftCo_ItemParasolDamageFall_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_ItemParasolDamageFall_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, (HSD_GObjEvent) ftCo_80090984);
}
