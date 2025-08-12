#include "ftSeak/ftSk_SpecialLw.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftZelda/ftZd_SpecialLw.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <math.h>
#include <baselib/gobj.h>

static void fn_80114034(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4FC, gobj, fp->parts[FtPart_R2ndNb].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = 0;
}

static void fn_801140B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4FD, gobj, fp->parts[FtPart_HipN].joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = 0;
}

static void fn_8011412C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = NULL;
    ftCommon_8007EFC8(gobj, &ftZd_SpecialLw_8013B4D8);
}

static void ftSk_unk_inline(Vec3* v)
{
    lb_800119DC(v, 0x78, 0.4F, 0.003F, M_PI / 3);
}

// Sheik_AS_361_Transform_Grounded
void ftSk_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Vec3 sp20;
    Fighter* fp;
    ftSeakAttributes* attributes;

    u8 _[16];

    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;
    fp->cmd_vars[0] = 0;
    fp->self_vel.x /= attributes->x60;
    fp->self_vel.y /= attributes->x64;
    fp->gr_vel /= attributes->x60;
    lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &sp20);
    ftSk_unk_inline(&sp20);
    fp->accessory4_cb = &fn_80114034;
}

// Sheik_AS_363_Transform_Aerial
void ftSk_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Vec3 sp20;
    Fighter* fp;
    ftSeakAttributes* attributes;

    u8 _[16];

    Fighter_ChangeMotionState(gobj, 0x16B, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    fp->cmd_vars[0] = 0;
    fp->self_vel.x /= attributes->x60;
    fp->self_vel.y /= attributes->x64;
    fp->gr_vel /= attributes->x60;
    lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &sp20);
    ftSk_unk_inline(&sp20);
    fp->accessory4_cb = &fn_80114034;
}

// Animation_SheikTransformStartGround
void ftSk_SpecialLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->accessory4_cb = &fn_8011412C;
    }
}

void ftSk_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->accessory4_cb = &fn_8011412C;
    }
}

void ftSk_SpecialLw_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialAirLw_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialLw_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    ftCommon_8007D494(fp, attributes->x68, attributes->x6C);
    ftCommon_8007CEF4(fp);
}

void ftSk_SpecialLw_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftSk_SpecialLw_8011444C(gobj);
    }
}

void ftSk_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftSk_SpecialLw_801144B8(gobj);
    }
}

void ftSk_SpecialLw_8011444C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16B, 0xC4C508E, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    fp->accessory4_cb = fn_80114034;
}

void ftSk_SpecialLw_801144B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x169, 0xC4C508E, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    fp->accessory4_cb = fn_80114034;
}

void ftSk_SpecialLw2_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftSk_SpecialAirLw2_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftSk_SpecialLw2_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialAirLw2_IASA(Fighter_GObj* gobj) {}

void ftSk_SpecialLw2_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSk_SpecialAirLw2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    ftCommon_8007D494(fp, attributes->x68, attributes->x6C);
    ftCommon_8007CEF4(fp);
}

void ftSk_SpecialLw2_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftSk_SpecialLw_80114680(gobj);
    }
}

void ftSk_SpecialAirLw2_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftSk_SpecialLw_801146EC(gobj);
    }
}

void ftSk_SpecialLw_80114680(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x16C, 0xC4C508E, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    fp->accessory4_cb = fn_801140B0;
}

void ftSk_SpecialLw_801146EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16A, 0xC4C508E, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    fp->accessory4_cb = fn_801140B0;
}

// AS_SheikFinishTransformation
void ftSk_SpecialLw_80114758(Fighter_GObj* gobj)
{
    s32 var_r4;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    if (fp->ground_or_air == GA_Ground) {
        var_r4 = 0x16A;
    } else {
        var_r4 = 0x16C;
    }
    Fighter_ChangeMotionState(gobj, var_r4, 0, attributes->x70, 1.0F, 0.0F,
                              NULL);
    fp->accessory4_cb = fn_801140B0;
}
