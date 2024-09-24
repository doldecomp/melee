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

/// #ftSk_SpecialAirLw_Anim

void ftSk_SpecialLw_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialAirLw_IASA(HSD_GObj* gobj) {}

/// #ftSk_SpecialLw_Phys

/// #ftSk_SpecialAirLw_Phys

/// #ftSk_SpecialLw_Coll

/// #ftSk_SpecialAirLw_Coll

/// #ftSk_SpecialLw_8011444C

/// #ftSk_SpecialLw_801144B8

/// #ftSk_SpecialLw2_Anim

/// #ftSk_SpecialAirLw2_Anim

void ftSk_SpecialLw2_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialAirLw2_IASA(HSD_GObj* gobj) {}

/// #ftSk_SpecialLw2_Phys

/// #ftSk_SpecialAirLw2_Phys

/// #ftSk_SpecialLw2_Coll

/// #ftSk_SpecialAirLw2_Coll

/// #ftSk_SpecialLw_80114680

/// #ftSk_SpecialLw_801146EC

// AS_SheikFinishTransformation
/// #ftSk_SpecialLw_80114758
