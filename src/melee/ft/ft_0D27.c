#include "ft_0D27.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallAerial.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

void ftCo_800D2770(Fighter_GObj* gobj, f32 arg8)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLib_SetScale(gobj, arg8);
    ftCo_800D105C(gobj);
    ftCamera_80076064(fp);
    ft_80081C88(gobj, fp->x34_scale.y);
}

bool ftCo_800D27C4(Fighter* fp)
{
    bool var_r0 = fp->motion_id == ftCo_MS_DamageIce ? false : true;
    if (!var_r0) {
        return false;
    }
    switch (fp->x2070.x2071_b0_3) {
    case 12:
    case 13:
        return false;
    }
    return true;
}

bool fn_800D2818(Fighter* fp)
{
    int tmp;
    bool var_r0 = fp->motion_id == ftCo_MS_DamageIce ? false : true;
    if (!var_r0) {
        return false;
    }
    if (fp->motion_id >= ftCo_MS_KinokoGiantStart &&
        fp->motion_id <= ftCo_MS_KinokoSmallEndAir)
    {
        return false;
    }
    tmp = fp->x2070.x2071_b0_3;
    if (tmp != 5 && (tmp >= 5 || tmp != 0) && !fp->x2070.x2071_b4) {
        return false;
    } else {
        return true;
    }
}

void fn_800D2890(Fighter_GObj* gobj, int ms_id)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_PEACH && ms_id == 0x172) {
        fp->mv.co.unk_800D2890.x0 = ftCo_800968C8;
        return;
    }
    switch (ms_id) {
    case ftCo_MS_FallAerial:
        fp->mv.co.unk_800D2890.x0 = ftCo_FallAerial_Enter;
        return;
    case ftCo_MS_FallSpecial:
    case ftCo_MS_ItemParasolFallSpecial:
        fp->mv.co.unk_800D2890.x0 = ftCo_800968C8;
        return;
    default:
        fp->mv.co.unk_800D2890.x0 = ftCo_Fall_Enter;
        return;
    }
}

void fn_800D290C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim;

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);

    victim = getFtVictim(fp);
    if (victim != NULL) {
        if (fp->x221B_b5) {
            ftCo_CaptureCut_Enter(victim);
        } else {
            HSD_GObj* tmp = victim;
            ftCo_CaptureCut_Enter(gobj);
            ftCo_800DA698(tmp, false);
        }
        ftCommon_8007DB58(victim);
    }
}

void fn_800D299C(Fighter_GObj* gobj, int idx, f32 arg8, f32 arg9)
{
    static HSD_Joint lbl_803C6FF0 = {
        NULL,
        8,
        NULL,
        NULL,
        { NULL },
        { 0.0F, 0.0F, 0.0F },
        { 1.0F, 1.0F, 1.0F },
        { 0.0F, 0.0F, 0.0F },
    };

    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2184 == NULL) {
        fp->x2184 = HSD_JObjLoadJoint(&lbl_803C6FF0);
    }
    fp->mv.co.walk.middle_anim_frame = arg8;
    fp->mv.co.walk.fast_anim_frame = arg9;
    HSD_JObjAddAnim(fp->x2184, it_80293660(idx), NULL, NULL);
    ftAnim_80070734(fp->x2184, 0.0F);
    HSD_JObjAnim(fp->x2184);
}

bool fn_800D2A3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObjAnim(fp->x2184);
    {
        f32 scale = HSD_JObjGetScaleX(fp->x2184);
        f32 mid = fp->mv.co.walk.middle_anim_frame;
        f32 fast = fp->mv.co.walk.fast_anim_frame;
        ftLib_SetScale(gobj, (fast - mid) * scale + mid);
    }
    if (HSD_AObjGetFlags(fp->x2184->aobj) & 0x40000000) {
        return false;
    } else {
        return true;
    }
}

void fn_800D2AD8(Fighter* fp)
{
    ft_PlaySFX(fp, ftCo_MS_CaptureDamageKoopaAir, 0x7F, 0x40);
}

void fn_800D2B04(Fighter* fp)
{
    ft_PlaySFX(fp, ftCo_MS_CaptureWaitKoopaAir, 0x7F, 0x40);
}

void fn_800D2B30(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.common.x14 = fp->xE4_ground_accel_1;
    fp->mv.co.common.x18 = fp->xE8_ground_accel_2;
    fp->mv.co.common.x28 = fp->x74_anim_vel;
    fp->mv.co.common.x1C = fp->gr_vel;
    fp->mv.co.common.x34 = fp->self_vel;
    fp->mv.co.common.x20 = fp->xF0_ground_kb_vel;
    fp->mv.co.common.x40 = fp->x8c_kb_vel;
    fp->mv.co.common.x24 = fp->xF4_ground_attacker_shield_kb_vel;
    fp->mv.co.common.x4C = fp->x98_atk_shield_kb;
    fp->mv.co.common.x58 = fp->xD4_unk_vel;
    ftCommon_8007E2FC(fp->gobj);
}

void fn_800D2BF8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xE4_ground_accel_1 = fp->mv.co.common.x14;
    fp->xE8_ground_accel_2 = fp->mv.co.common.x18;
    fp->x74_anim_vel = fp->mv.co.common.x28;
    fp->gr_vel = fp->mv.co.common.x1C;
    fp->self_vel = fp->mv.co.common.x34;
    fp->xF0_ground_kb_vel = fp->mv.co.common.x20;
    fp->x8c_kb_vel = fp->mv.co.common.x40;
    fp->xF4_ground_attacker_shield_kb_vel = fp->mv.co.common.x24;
    fp->x98_atk_shield_kb = fp->mv.co.common.x4C;
    fp->xD4_unk_vel = fp->mv.co.common.x58;
}

void fn_800D2CA0(Fighter* fp)
{
    ftCommon_8007D7FC(fp);
    fp->mv.co.common.x1C = fp->mv.co.common.x34.x;
}

void fn_800D2CD4(Fighter* fp)
{
    ftCommon_8007D5D4(fp);
    fp->mv.co.common.x1C = 0.0F;
    fp->mv.co.common.x28.y = 0.0F;
}

bool ft_800D2D0C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL && itGetKind(fp->item_gobj) == It_Kind_ScBall) {
        return true;
    }
    return false;
}
