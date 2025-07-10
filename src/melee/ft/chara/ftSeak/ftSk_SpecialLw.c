#include "ftSeak/ftSk_SpecialLw.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftZelda/ftZd_SpecialLw.h"

#include <baselib/gobj.h>

static float const ftSk_Init_804D9698 = 0.4000000059604645F;
static float const ftSk_Init_804D969C = 0.003000000026077032F;
static float const ftSk_Init_804D96A0 = 1.0471975803375244F;
static f32 const ftSk_Init_804D96A4 = 0.0f;
static f32 const ftSk_Init_804D96A8 = 0.0078125f;

void fn_80114034(HSD_GObj* gobj) {}

void fn_801140B0() {}

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
void ftSk_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        fp->accessory4_cb = &fn_8011412C;
    }
}

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

void ftSk_SpecialLw_8011444C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16B, 0x0C4C508EU, fp->cur_anim_frame,
                              ftSk_Init_804D96A8, ftSk_Init_804D96A4, NULL);
    fp->accessory4_cb = fn_80114034;
}

void ftSk_SpecialLw_801144B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x169, 0x0C4C508EU, fp->cur_anim_frame,
                              ftSk_Init_804D96A8, ftSk_Init_804D96A4, NULL);
    fp->accessory4_cb = fn_80114034;
}

void ftSk_SpecialLw2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ft_8008A2BC((Fighter_GObj*) gobj);
    }
}

void ftSk_SpecialAirLw2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftCo_Fall_Enter((Fighter_GObj*) gobj);
    }
}

void ftSk_SpecialLw2_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialAirLw2_IASA(HSD_GObj* gobj) {}

void ftSk_SpecialLw2_Phys(HSD_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

void ftSk_SpecialAirLw2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    ftCommon_8007D494((Fighter*) fp, attributes->x68, attributes->x6C);
    ftCommon_8007CEF4((Fighter*) fp);
}

void ftSk_SpecialLw2_Coll(HSD_GObj* gobj)
{
    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        ftSk_SpecialLw_80114680(gobj);
    }
}

void ftSk_SpecialAirLw2_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C((Fighter_GObj*) gobj) != GA_Ground) {
        ftSk_SpecialLw_801146EC(gobj);
    }
}

void ftSk_SpecialLw_80114680(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16C, 0x0C4C508EU, fp->cur_anim_frame,
                              ftSk_Init_804D96A8, ftSk_Init_804D96A4, NULL);
    fp->accessory4_cb = fn_801140B0;
}

void ftSk_SpecialLw_801146EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16A, 0x0C4C508EU, fp->cur_anim_frame,
                              ftSk_Init_804D96A8, ftSk_Init_804D96A4, NULL);
    fp->accessory4_cb = fn_801140B0;
}

// AS_SheikFinishTransformation
void ftSk_SpecialLw_80114758(HSD_GObj* gobj)
{
    s32 var_r4;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    if ((s32) fp->ground_or_air == 0) {
        var_r4 = 0x16A;
    } else {
        var_r4 = 0x16C;
    }
    Fighter_ChangeMotionState((Fighter_GObj*) gobj, var_r4, 0U,
                              attributes->x70, ftSk_Init_804D96A8,
                              ftSk_Init_804D96A4, NULL);
    fp->accessory4_cb = &fn_801140B0;
}
