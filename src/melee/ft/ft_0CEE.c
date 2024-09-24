#include "ft_0CEE.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/types.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_DamageIce.h"

void ftCo_ItemParasolFall_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemParasolFallSpecial_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemParasolDamageFall_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemParasolFall_Phys(Fighter_GObj* gobj)
{
    ftCo_ItemParasolOpen_Phys(gobj);
}

void ftCo_ItemParasolFallSpecial_Phys(Fighter_GObj* gobj)
{
    ftCo_ItemParasolOpen_Phys(gobj);
}

void ftCo_ItemParasolDamageFall_IASA(Fighter_GObj* gobj)
{
    ftCo_DamageFall_IASA(gobj);
}

void ftCo_ItemParasolDamageFall_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_ItemParasolOpen_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, (void (*)(HSD_GObj*)) ftCo_800D5BF8);
}

void ftCo_ItemParasolFall_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, (void (*)(HSD_GObj*)) ftCo_800D5BF8);
}

void ftCo_ItemParasolFallSpecial_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, (HSD_GObjEvent) ft_800D5C54);
}

void ftCo_ItemParasolDamageFall_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, (HSD_GObjEvent) ftCo_80090984);
}

void ftCo_800CF280(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_ItemParasolFall,
                              Ft_MF_SkipHit | Ft_MF_SkipParasol, 0, 1, 0,
                              NULL);
}
