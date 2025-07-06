#include "ftSeak/ftSk_SpecialLw.h"

#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftZelda/ftZd_SpecialLw.h"

#include <baselib/gobj.h>

static float const ftSk_Init_804D9698 = 0.4000000059604645F;
static float const ftSk_Init_804D969C = 0.003000000026077032F;
static float const ftSk_Init_804D96A0 = 1.0471975803375244F;
static float const ftSk_Init_804D96A4 = 0.0F;
static double const ftSk_Init_804D96A8 = 0.0078125;

/// #fn_80114034

/// #fn_801140B0

void fn_8011412C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = NULL;
    ftCommon_8007EFC8(gobj, &ftZd_SpecialLw_8013B4D8);
}

// Sheik_AS_361_Transform_Grounded
/// #ftSk_SpecialLw_Enter

// Sheik_AS_363_Transform_Aerial
/// #ftSk_SpecialAirLw_Enter

// Animation_SheikTransformStartGround
/// #ftSk_SpecialLw_Anim

void ftSk_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        fp->accessory4_cb = &fn_8011412C;
    }
}

void ftSk_SpecialLw_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialAirLw_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftSk_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    ftCommon_8007D494((Fighter*) fp, attributes->x68, attributes->x6C);
    ftCommon_8007CEF4((Fighter*) fp);
}

void ftSk_SpecialLw_Coll(HSD_GObj* gobj)
{
    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        ftSk_SpecialLw_8011444C(gobj);
    }
}

void ftSk_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C((Fighter_GObj*) gobj) != GA_Ground) {
        ftSk_SpecialLw_801144B8(gobj);
    }
}

void ftSk_SpecialLw_8011444C(HSD_GObj* gobj) {}

void ftSk_SpecialLw_801144B8(HSD_GObj* gobj) {}

/// #ftSk_SpecialLw2_Anim

void ftSk_SpecialAirLw2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftCo_800CC730((Fighter_GObj*) gobj);
    }
}

void ftSk_SpecialLw2_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialAirLw2_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialLw2_Phys(HSD_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

/// #ftSk_SpecialAirLw2_Phys

/// #ftSk_SpecialLw2_Coll

void ftSk_SpecialAirLw2_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C((Fighter_GObj*) gobj) != GA_Ground) {
        ftSk_SpecialLw_801146EC(gobj);
    }
}

/// #ftSk_SpecialLw_80114680

/// #ftSk_SpecialLw_801146EC

// AS_SheikFinishTransformation
/// #ftSk_SpecialLw_80114758
