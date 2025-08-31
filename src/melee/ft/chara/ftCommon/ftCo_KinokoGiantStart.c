#include "ftCo_KinokoGiantStart.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D27.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_KinokoSmallEnd.h"

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

/* 0D17FC */ static void fn_800D17FC(Fighter_GObj* gobj);

bool Fighter_SuperMushroomApply(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_800D27C4(fp)) {
        return false;
    }
    if (fp->motion_id >= ftCo_MS_KinokoGiantStart &&
        fp->motion_id <= ftCo_MS_KinokoSmallEndAir)
    {
        fp->mv.co.mushroom.x4(gobj);
    }
    if (fp->x2220_b5) {
        fp->x2008 = p_ftCommonData->x688;
        return false;
    }
    if (fp->x2220_b6) {
        if (fp->ground_or_air == GA_Ground) {
            ftCo_800D2490(gobj, 1);
        } else {
            ftCo_800D2600(gobj, 1);
        }
        return true;
    }
    if (fp->ground_or_air == GA_Ground) {
        ftCo_800D170C(gobj);
    } else {
        ftCo_800D18CC(gobj);
    }
    return true;
}

void ftCo_800D15D0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 percent;
    fn_800D2BF8(gobj);
    fp->x2220_b5 = true;
    fp->x2008 = p_ftCommonData->x688;
    percent = fp->dmg.x1830_percent;
    if (percent > p_ftCommonData->x68C) {
        percent -= p_ftCommonData->x68C;
        if (percent >= p_ftCommonData->x690) {
            percent = p_ftCommonData->x690;
        }
        fp->x2008 += percent;
    }
    ftCo_800D2770(gobj, fp->mv.co.walk.fast_anim_frame);
    ftCommon_8007E2FC(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ft_8008A324(gobj);
        return;
    }
    fp->mv.co.mushroom.x0(gobj);
}

static inline void ftCo_800D170C_inline(Fighter_GObj* gobj, int id)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 var_f2;
    fn_800D2B30(gobj);
    fn_800D2890(gobj, id);
    if (fp->x34_scale.x > 1.0F) {
        var_f2 = fp->x34_scale.y * p_ftCommonData->x67C;
    } else {
        var_f2 = fp->x34_scale.y * p_ftCommonData->x678;
    }
    fn_800D299C(gobj, 0, fp->x34_scale.y, var_f2);
    fn_800D2AD8(fp);
    ftCommon_8007EBAC(fp, 12, 0);
    fp->mv.co.mushroom.x4 = ftCo_800D15D0;
}

void ftCo_800D170C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    (void) 1.0f;
    (void) 0.0f;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantStart, 0x90, 0.0F, 1.0F,
                              0.0F, NULL);
    ftCo_800D170C_inline(gobj, id);
    fp->take_dmg_cb = ftCo_800D15D0;
}

void fn_800D17FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CA0(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantStart, 0xC4C5080,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D15D0;
}

void ftCo_KinokoGiantStart_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D15D0(gobj);
    }
}

void ftCo_KinokoGiantStart_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800D19BC);
}

void ftCo_800D18CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantStartAir, 0x90, 0.0F,
                              1.0F, 0.0F, NULL);
    ftCo_800D170C_inline(gobj, id);
    fp->take_dmg_cb = ftCo_800D15D0;
}

void fn_800D19BC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CD4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantStartAir, 0xC4C5080,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D15D0;
}

void ftCo_KinokoGiantStartAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D15D0(gobj);
    }
}

void ftCo_KinokoGiantStartAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D17FC);
}
