#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ft_0D14.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallAerial.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_JumpAerial.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
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

static void fn_800D9CE8(Fighter_GObj* arg0);
static void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1);

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
    if (fp->x2220_flag.b5) {
        fp->x2008 = p_ftCommonData->x688;
        return false;
    }
    if (fp->x2220_flag.b6) {
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
    fp->x2220_flag.b5 = true;
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

int Fighter_SuperMushroomEnd(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fn_800D2818(fp)) {
        return 0;
    }
    if (fp->ground_or_air == GA_Ground) {
        ftCo_800D1BA0(gobj, 0);
    } else {
        ftCo_800D1D10(gobj, 0);
    }
    return 1;
}

void ftCo_800D1B04(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2BF8(gobj);
    fp->x2220_flag.b5 = 0;
    ftCo_800D2770(gobj, fp->x34_scale.x);
    if (fp->mv.co.mushroom.x8) {
        ftCommon_8007E2FC(gobj);
        fp->mv.co.mushroom.x8 = 0;
    }
    if (fp->ground_or_air == GA_Ground) {
        ft_8008A324(gobj);
        return;
    }
    fp->mv.co.mushroom.x0(gobj);
}

static inline void ftCo_800D1BA0_inline(Fighter_GObj* gobj, int id, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2B30(gobj);
    fn_800D2890(gobj, id);
    fp->mv.co.mushroom.x8 = arg1;
    fn_800D299C(gobj, 1, fp->x34_scale.y, fp->x34_scale.x);
    fn_800D2B04(fp);
    fp->mv.co.mushroom.x4 = ftCo_800D1B04;
}

void ftCo_800D1BA0(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantEnd, 0x91, 0.0F, 1.0F,
                              0.0F, NULL);
    ftCo_800D1BA0_inline(gobj, id, arg1);
    fp->take_dmg_cb = ftCo_800D1B04;
}

void fn_800D1C40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CA0(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantEnd, 0xC4C5081,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D1B04;
}

#pragma push
#pragma dont_inline on
void ftCo_KinokoGiantEnd_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1B04(gobj);
    }
}
#pragma pop

void ftCo_KinokoGiantEnd_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800D1DB0);
}

void ftCo_800D1D10(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantEndAir, 0x91, 0.0F,
                              1.0F, 0.0F, NULL);
    ftCo_800D1BA0_inline(gobj, id, arg1);
    fp->take_dmg_cb = ftCo_800D1B04;
}

void fn_800D1DB0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fn_800D2CD4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoGiantEndAir, 0xC4C5081,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D1B04;
}

#pragma push
#pragma dont_inline on
void ftCo_KinokoGiantEndAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1B04(gobj);
    }
}
#pragma pop

void ftCo_KinokoGiantEndAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D1C40);
}

#pragma push
#pragma dont_inline on
bool Fighter_PoisonMushroomApply(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!ftCo_800D27C4(fp)) {
        return false;
    }
    if (fp->motion_id >= ftCo_MS_KinokoGiantStart &&
        fp->motion_id <= ftCo_MS_KinokoSmallEndAir)
    {
        fp->mv.co.mushroom.x4(gobj);
    }
    if (fp->x2220_flag.b6) {
        fp->x2008 = p_ftCommonData->x688;
        return false;
    }
    if (fp->x2220_flag.b5) {
        if (fp->ground_or_air == GA_Ground) {
            ftCo_800D1BA0(gobj, 1);
        } else {
            ftCo_800D1D10(gobj, 1);
        }
        return true;
    }
    if (fp->ground_or_air == GA_Ground) {
        ftCo_800D1FFC(gobj);
    } else {
        ftCo_800D21BC(gobj);
    }
    return true;
}
#pragma pop

void ftCo_800D1F6C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2BF8(gobj);
    fp->x2220_flag.b6 = true;
    fp->x2008 = p_ftCommonData->x688;
    ftCo_800D2770(gobj, fp->mv.co.walk.fast_anim_frame);
    ftCommon_8007E2FC(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ft_8008A324(gobj);
        return;
    }
    fp->mv.co.mushroom.x0(gobj);
}

static inline void ftCo_800D1FFC_inline(Fighter_GObj* gobj, int id)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float var_f2;
    fn_800D2B30(gobj);
    fn_800D2890(gobj, id);
    if (fp->x34_scale.x < 1.0F) {
        var_f2 = fp->x34_scale.y * p_ftCommonData->x684;
    } else {
        var_f2 = fp->x34_scale.y * p_ftCommonData->x680;
    }
    fn_800D299C(gobj, 0, fp->x34_scale.y, var_f2);
    fn_800D2B04(fp);
    ftCommon_8007EBAC(fp, 12, 0);
    fp->mv.co.mushroom.x4 = ftCo_800D1F6C;
}

void ftCo_800D1FFC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallStart, 0x90, 0.0F, 1.0F,
                              0.0F, NULL);
    ftCo_800D1FFC_inline(gobj, id);
    fp->take_dmg_cb = ftCo_800D1F6C;
}

void fn_800D20EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CA0(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallStart, 0xC4C5080,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D1F6C;
}

#pragma push
#pragma dont_inline on
void ftCo_KinokoSmallStart_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1F6C(gobj);
    }
}
#pragma pop

void ftCo_KinokoSmallStart_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800D22AC);
}

void ftCo_800D21BC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallStartAir, 0x90, 0.0F,
                              1.0F, 0.0F, NULL);
    ftCo_800D1FFC_inline(gobj, id);
    fp->take_dmg_cb = ftCo_800D1F6C;
}

void fn_800D22AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CD4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallStartAir, 0xC4C5080,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D1F6C;
}

#pragma push
#pragma dont_inline on
void ftCo_KinokoSmallStartAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1F6C(gobj);
    }
}
#pragma pop

void ftCo_KinokoSmallStartAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D20EC);
}

bool Fighter_PoisonMushroomEnd(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fn_800D2818(fp)) {
        return false;
    }
    if (fp->ground_or_air == GA_Ground) {
        ftCo_800D2490(gobj, 0);
    } else {
        ftCo_800D2600(gobj, 0);
    }
    return true;
}

void ftCo_800D23F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2BF8(gobj);
    fp->x2220_flag.b6 = false;
    ftCo_800D2770(gobj, fp->x34_scale.x);
    if (fp->mv.co.mushroom.x8) {
        ftCommon_8007E2FC(gobj);
        fp->mv.co.mushroom.x8 = 0;
    }
    if (fp->ground_or_air == GA_Ground) {
        ft_8008A324(gobj);
        return;
    }
    fp->mv.co.mushroom.x0(gobj);
}

static inline void ftCo_800D2490_inline(Fighter_GObj* gobj, int id, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2B30(gobj);
    fn_800D2890(gobj, id);
    fp->mv.co.mushroom.x8 = arg1;
    fn_800D299C(gobj, 0, fp->x34_scale.y, fp->x34_scale.x);
    fn_800D2AD8(fp);
    fp->mv.co.mushroom.x4 = ftCo_800D23F4;
}

void ftCo_800D2490(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallEnd, 0x91, 0.0F, 1.0F,
                              0.0F, NULL);
    ftCo_800D2490_inline(gobj, id, arg1);
    fp->take_dmg_cb = ftCo_800D23F4;
}

void fn_800D2530(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CA0(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallEnd, 0xC4C5081,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D23F4;
}

#pragma push
#pragma dont_inline on
void ftCo_KinokoSmallEnd_Anim(Fighter_GObj* gobj)
{
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D23F4(gobj);
    }
}
#pragma pop

void ftCo_KinokoSmallEnd_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800D26A0);
}

void ftCo_800D2600(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int id = fp->motion_id;
    fn_800D290C(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallEndAir, 0x91, 0.0F,
                              1.0F, 0.0F, NULL);
    ftCo_800D2490_inline(gobj, id, arg1);
    fp->take_dmg_cb = ftCo_800D23F4;
}

void fn_800D26A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2CD4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_KinokoSmallEndAir, 0xC4C5081,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0F,
                              NULL);
    fp->take_dmg_cb = ftCo_800D23F4;
}

#pragma push
#pragma dont_inline on
void ftCo_KinokoSmallEndAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D23F4(gobj);
    }
}
#pragma pop

void ftCo_KinokoSmallEndAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D2530);
}

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
            ftCo_800DC750(victim);
        } else {
            HSD_GObj* tmp = victim;
            ftCo_800DC750(gobj);
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
    ft_80088148(fp, ftCo_MS_CaptureDamageKoopaAir, 0x7F, 0x40);
}

void fn_800D2B04(Fighter* fp)
{
    ft_80088148(fp, ftCo_MS_CaptureWaitKoopaAir, 0x7F, 0x40);
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

void ftCo_ItemScrew_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScrew, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftCo_800CB110(gobj, false, p_ftCommonData->x800);
    fp->x2227_b0 = true;
}

void ftCo_ItemScrew_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_ItemScrew_IASA(Fighter_GObj* gobj)
{
    ftCo_Jump_IASA(gobj);
}

void ftCo_ItemScrew_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftCo_ItemScrew_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

void ft_800D2E7C(Fighter_GObj* gobj, Vec3* arg1)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    arg1->x *= p_ftCommonData->x800;
    arg1->y *= p_ftCommonData->x800;
    *(volatile f32*) &arg1->z;
    ftCommon_8007D5D4(fp);
    ftCo_800CBAC4(gobj, ftCo_MS_ItemScrewAir, arg1, 1);
}

void ftCo_ItemScrewAir_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_FallAerial_Enter(gobj);
    }
}

void ftCo_ItemScrewAir_IASA(Fighter_GObj* gobj)
{
    ftCo_JumpAerial_IASA(gobj);
}

void ftCo_ItemScrewAir_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_ItemScrewAir_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

bool ftCo_800D2FA4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->dmg.x1860_element == 0xE) {
        int x = fp->x2070.x2071_b0_3;
        switch (x) {
        case 11:
        case 12:
            return 0;
        }
        ftCo_800D3004(gobj);
        return 1;
    }
    return 0;
}

void ftCo_800D3004(Fighter_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->cmd_vars[0] = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageScrew, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageScrewAir, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
    }
    fp->self_vel.x = 0.0F;
    fp->self_vel.y = fp->co_attrs.x128;
    fp->self_vel.z = 0.0F;
}

void ftCo_DamageScrew_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800968C8(gobj);
    }
}

void ftCo_DamageScrew_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageScrew_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_DamageScrew_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        ftCo_AirCatchHit_Coll(gobj);
        return;
    }
    ft_80083B68(gobj);
}

bool ftCo_800D3158(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int* temp_r29 = &p_ftCommonData->x520;

    if (fp->x222A_flag.b1 || fp->x2228_b5 || fp->x2228_b2) {
        return false;
    }
    if (fp->x2219_b2) {
        return false;
    }
    if (fp->x2219_b1) {
        return false;
    }
    if (fp->cur_pos.x > Stage_GetBlastZoneRightOffset()) {
        ftCo_800D3950(gobj);
        return true;
    }
    if (fp->cur_pos.x < Stage_GetBlastZoneLeftOffset()) {
        ftCo_800D3680(gobj);
        return true;
    }
    if (fp->cur_pos.y > Stage_GetBlastZoneTopOffset() &&
        (fp->ground_or_air == GA_Ground || fp->x2222_b3 ||
         fp->x8c_kb_vel.y > p_ftCommonData->x4F0))
    {
        if (Player_GetMoreFlagsBit5(fp->player_id)) {
            ftCo_800D3E40(gobj);
        } else {
            int temp_r28 = HSD_Randi(100) + 1;
            if (!Camera_8003010C() && *temp_r29 >= temp_r28) {
                if (fp->motion_id == ftCo_MS_DamageIce) {
                    ftCo_800D47B8(gobj);
                } else {
                    ftCo_800D4780(gobj);
                }
            } else if (fp->motion_id == ftCo_MS_DamageIce) {
                ftCo_800D41C4(gobj);
            } else {
                ftCo_800D40B8(gobj);
            }
        }
        return true;
    }
    if (fp->cur_pos.y < Stage_GetBlastZoneBottomOffset()) {
        ftCo_800D3BC8(gobj);
        return true;
    }
    return false;
}

void ftCo_800D331C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->victim_gobj != NULL) {
        if (fp->x221B_b5) {
            Fighter* temp_r3_2 = GET_FIGHTER(fp->victim_gobj);
            if (!temp_r3_2->x221F_b4) {
                temp_r3_2->x2180 = fp->player_id;
            }
        } else if (!fp->x221F_b4) {
            pl_8004065C((u8) ftLib_80086BE0(fp->victim_gobj),
                        ftLib_800874BC(fp->victim_gobj));
        }
    }
    if (fp->x2180 != 6) {
        pl_8004065C(fp->x2180, 0);
    }
    if (fp->death2_cb != NULL) {
        fp->death2_cb(gobj);
    }
    if (fp->death3_cb != NULL) {
        fp->death3_cb(gobj);
    }
    if (fp->death1_cb != NULL) {
        fp->death1_cb(gobj);
    }
    ftCo_800DD100(gobj);
    ftCommon_8007E2FC(gobj);
    if (fp->item_gobj != NULL) {
        Item_8026A8EC(fp->item_gobj);
        fp->item_gobj = NULL;
        pl_8003EA08(fp->player_id, fp->x221F_b4);
        pl_8003EA74(fp->player_id, fp->x221F_b4);
    }
    if (fp->x197C != NULL) {
        ftCommon_8007F8E8(gobj);
        Item_8026A8EC(fp->x197C);
        ftCommon_8007F9B4(gobj);
    }
    if (fp->x1980 != NULL) {
        ftCommon_8007F8E8(gobj);
        Item_8026A8EC(fp->x1980);
        ftCommon_8007FF74(gobj);
    }
    if (fp->x2223_b7) {
        ftCo_800C8540(gobj);
    }
    if (fp->x2226_b4) {
        ftCo_800C8A64(gobj);
    }
    ftCommon_8007DB24(gobj);
    fp->mv.co.unk_800D331C.x6C = fp->motion_id;
    fp->mv.co.unk_800D331C.x70 = fp->x2070.x2073;
}

void ftCo_800D34E0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Player_SetFallsByIndex(
        fp->player_id, fp->x221F_b4,
        Player_GetFallsByIndex(fp->player_id, fp->x221F_b4) + 1);
    plStale_ResetStaleMoveTableForPlayer(fp->player_id);
    if ((gm_8016B094() || gm_8016B0E8()) &&
        Player_GetEntity(fp->player_id) == gobj)
    {
        Player_LoseStock(fp->player_id);
    }
    if (gm_8016B094() && Player_GetStocks(fp->player_id) <= 0) {
        Player_UpdateMatchFrameCount(fp->player_id, fp->x221F_b4);
    }
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_UpdateKOsBySlot(fp->dmg.x18c4_source_ply, fp->x221F_b4,
                               fp->player_id);
    } else {
        Player_IncSuicideCount(fp->player_id, fp->x221F_b4);
    }
    pl_8003D644(fp->player_id, fp->x221F_b4, fp->mv.co.unk_800D34E0.x6C,
                fp->mv.co.unk_800D34E0.x70);
    Player_SetHPByIndex(fp->player_id, fp->x221F_b4, 0);
}

void ftCo_800D35FC(Fighter* fp)
{
    u8 _[8];
    HSD_GObj* cur_gobj;

    ftCommon_8007EBAC(fp, 5, p_ftCommonData->x4F8);
    cur_gobj = HSD_GObj_Entities->fighters;
    while (cur_gobj != NULL) {
        Fighter* cur_fp = GET_FIGHTER(cur_gobj);
        if (cur_fp != fp && !cur_fp->x221F_b3) {
            ftCommon_8007EBAC(cur_fp, 6, p_ftCommonData->x4FC);
        }
        cur_gobj = cur_gobj->next;
    }
}

#pragma push
#pragma dont_inline on

void ftCo_800D3680(Fighter_GObj* gobj)
{
    Vec3 sp2C;
    f32 sp24;
    Fighter* temp_r27;
    Fighter* temp_r27_2;
    Fighter* temp_r28;
    Fighter* temp_r28_3;
    Fighter* temp_r31;
    FtSFX* temp_r28_2;
    f32 temp_f1;
    f32 temp_f31;
    s32 temp_r29;
    s32 temp_r6;
    s32 temp_ret;
    s32 var_r3;
    u8* temp_r8;
    u8 temp_r3;
    u8 temp_r4;
    u8 temp_r5;
    u8 temp_r7;
    u8 temp_r8_2;
    u8* temp_r9;

    temp_r27 = gobj->user_data;
    temp_r31 = temp_r27;
    ftCo_800D331C(gobj);
    temp_r27->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, 1, 0U, 0.0F, 1.0F, 0.0F, NULL);
    temp_r28 = gobj->user_data;
    if (((u8) temp_r28->x221D >> 1U) & 1) {
        ft_800880D8(temp_r28);
        temp_r28->x2004 = 0;
    }
    temp_r28->x2219_b1 = 1;
    temp_r28->x221E_b1 = 1;
    temp_r28->x221E_b2 = 1;
    pl_8003DF44(temp_r27->player_id, temp_r27->x221F_b2);

    temp_r27_2 = gobj->user_data;
    temp_r28_2 = temp_r27_2->ft_data->x4C_sfx;
    temp_r27_2->x221E_b0 = 1;
    temp_r27_2->x221F_b1 = 1;
    Camera_80030E44(4, &temp_r27_2->cur_pos);
    ftCo_800D35FC(temp_r27_2);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x4);
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x8);

    ft_80088148(temp_r31, 0x88, 0x7F, 0x40);
    ft_8008805C(temp_r31, 0x88);
    sp2C = temp_r31->cur_pos;
    temp_f31 = Stage_GetBlastZoneTopOffset();
    temp_f1 = Stage_GetBlastZoneBottomOffset();
    if (sp2C.y > temp_f31) {
        sp2C.y = temp_f31;
    }
    if (sp2C.y < temp_f1) {
        sp2C.y = temp_f1;
    }
    sp24 = -1.5707964f;
    temp_r28_3 = gobj->user_data;
    temp_r3 = Player_GetUnk45(temp_r28_3->player_id);
    temp_r8 = &Fighter_804D650C[temp_r3];
    temp_r9 = &Fighter_804D6508[temp_r3];
    temp_r7 = temp_r8[0];
    temp_r4 = temp_r9[0];
    temp_r6 = ((temp_r8[1] << 8) & ~0xFF0000) | ((temp_r7 << 0x10) & 0xFF0000);
    temp_r8_2 = temp_r8[2];
    temp_r5 = temp_r9[2];
    temp_r29 = temp_r5 | (((temp_r9[1] << 8) & ~0xFF0000) |
                          ((temp_r4 << 0x10) & 0xFF0000));
    temp_ret = gm_801693BC(temp_r28_3->player_id);
    if (temp_ret != 0) {
        var_r3 = 0x42C;
    } else {
        var_r3 = 0x42B;
    }
    efSync_Spawn(var_r3, gobj, &sp2C, &sp24, &p_ftCommonData->x4F4,
                 temp_r8_2 | temp_r6, temp_r29);
    sp2C.x = Stage_GetBlastZoneLeftOffset();
    ftCo_800D4E50(temp_r31, &sp2C, 1, 0.0F);
}

#pragma pop

void ftCo_800D38B8(Fighter* fp, int arg1)
{
    ft_800881D8(fp, arg1, 0x7F, 0x40);
    if (!fp->x2225_b6) {
        ft_8008805C(fp, arg1);
    }
}

void ftCo_DeadLeft_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadLeft_Cam(Fighter_GObj* gobj) {}

/// #ftCo_800D3950

void ftCo_DeadRight_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadRight_Cam(Fighter_GObj* gobj) {}

/// #ftCo_800D3BC8

void ftCo_DeadDown_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadDown_Cam(Fighter_GObj* gobj) {}

/// #ftCo_800D3E40

void ftCo_DeadUp_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadUp_Cam(Fighter_GObj* gobj) {}

static inline void ftCo_800D40B8_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221D_b6) {
        ft_800880D8(fp);
        fp->x2004 = false;
    }
    fp->x2219_b1 = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    ft_80088C5C(gobj);
}

void ftCo_800D40B8(Fighter_GObj* gobj)
{
    u8 _[8];
    int* temp_r31 = &p_ftCommonData->x504;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800D331C(gobj);
    fp->mv.co.unk_deadup.x40 = *temp_r31;
    fp->mv.co.unk_deadup.x44 = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStar, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftCo_800D40B8_inline(gobj);
    ftCommon_8007EFC0(fp, true);
    ft_800881D8(fp, fp->ft_data->x4C_sfx->xC, 127, 64);
    pl_8003DF44(fp->player_id, fp->x221F_b4);
    fp->mv.co.unk_deadup.x68 = 0;
}

/// #ftCo_800D41C4

/// #ftCo_DeadUpStar_Anim

void ftCo_DeadUpStar_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

/// #ftCo_800D4580

void ftCo_800D4780(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800D4580(gobj, 6);
    fp->mv.co.unk_deadup.x68 = 0;
}

void ftCo_800D47B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2227_b6 = true;
    ftCo_800D4580(gobj, 9);
    ftCo_80090AC0(fp);
    ftCommon_8007EBAC(fp, 1, 0);
    fp->mv.co.unk_deadup.x68 = 1;
}

/// #ftCo_800D481C

/// #ftCo_DeadUpFall_Anim

/// #ftCo_DeadUpFall_Phys

/// #fn_800D4DD4

void ftCo_DeadUpFall_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

void ftCo_800D4E50(Fighter* fp, Vec3* arg1, int arg2, float arg8)
{
    if (gm_8016B0B4() && !fp->x221F_b4) {
        int coins = Player_GetCoins(fp->player_id);
        int var_r31 = coins / 2;
        Player_SetCoins(fp->player_id, coins - var_r31);
        Player_SetUnk9C(fp->player_id,
                        var_r31 + Player_GetUnk9C(fp->player_id));
        if (var_r31 > p_ftCommonData->x5C8) {
            var_r31 = p_ftCommonData->x5C8;
        }
        it_802E5F8C(fp->gobj, arg1, var_r31, arg2, arg8, p_ftCommonData->x5CC);
    }
}

static inline void ftCo_800D4F24_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    if (temp_r31->x221D_b6) {
        ft_800880D8(temp_r31);
        temp_r31->x2004 = 0;
    }
    temp_r31->x2219_b1 = 1;
    temp_r31->x221E_b1 = 1;
    temp_r31->x221E_b2 = 1;
    ftMaterial_800BFD04(gobj);
}

void ftCo_800D4F24(Fighter_GObj* gobj, int index)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221F_b3) {
        return;
    }
    if (index != 0) {
        f32 sp1C = fp->ft_data->x0->x168 * fp->x34_scale.y;
        u8 _[4];
        efSync_Spawn(0x43F, 0, &fp->cur_pos, &sp1C);
    }
    ftCo_800D331C(gobj);
    ftCo_800D4F24_inline(gobj);
}

/// #ftCo_800D4FF4

/// #ftCo_Rebirth_Anim

void ftCo_Rebirth_IASA(Fighter_GObj* gobj) {}

/// #ftCo_Rebirth_Phys

/// #ftCo_Rebirth_Coll

/// #fn_800D54A4

/// #fn_800D55B4

/// #ftCo_800D5600

/// #ftCo_RebirthWait_Anim

/// #ftCo_RebirthWait_IASA

/// #ftCo_RebirthWait_Phys

/// #ftCo_RebirthWait_Coll

/// #fn_800D5A30

/// #ftCo_Rebirth_Cam

/// #ftCo_800D5AEC

/// #ftCo_800D5BF8

/// #ft_800D5C54

/// #ftCo_800D5CB0

/// #ftCo_Landing_Anim

/// #ftCo_Landing_IASA

/// #ftCo_Landing_Phys

/// #ftCo_Landing_Coll

/// #ftCo_Squat_CheckInput

/// #fn_800D5F84

/// #ftCo_800D5FB0

/// #fn_800D600C

/// #ftCo_Squat_Anim

/// #ftCo_Squat_IASA

/// #ftCo_Squat_Phys

/// #ftCo_Squat_Coll

/// #fn_800D627C

/// #fn_800D62C4

/// #ftCo_800D638C

/// #ftCo_SquatWait_Anim

/// #ftCo_SquatWait_IASA

/// #ftCo_SquatWait_Phys

/// #ftCo_SquatWait_Coll

/// #fn_800D65D8

/// #fn_800D6620

/// #ftCo_SquatRv_Anim

/// #ftCo_SquatRv_IASA

/// #ftCo_SquatRv_Phys

/// #ftCo_SquatRv_Coll

/// #ftCo_800D67C4

/// #ftCo_800D6824

/// #ftCo_800D688C

/// #ftCo_800D68C0

/// #ftCo_800D6928

/// #ftCo_Attack100_CheckInput

/// #ftCo_800D69C4

/// #ftCo_Attack_800D6A50

/// #fn_800D6AC4

/// #ftCo_800D6B00

/// #fn_800D6B8C

/// #ftCo_Attack100Start_Anim

/// #ftCo_800D6C60

/// #ftCo_Attack100Loop_Anim

/// #ftCo_Attack100End_Anim

/// #ftCo_Attack100Loop_IASA

/// #ftCo_Attack100Start_Phys

/// #ftCo_Attack100Loop_Phys

/// #ftCo_Attack100End_Phys

/// #ftCo_Attack100Start_Coll

/// #ftCo_Attack100Loop_Coll

/// #ftCo_Attack100End_Coll

/// #fn_800D6F58

/// #ftCo_800D705C

/// #ftCo_800D7100

/// #ftCo_800D71D8

/// #ftCo_800D7268

/// #ftCo_800D72A0

/// #ftCo_800D730C

/// #ftCo_800D74A4

/// #ftCo_JumpAerialF1_Anim

/// #ftCo_JumpAerialF1_IASA

/// #ftCo_JumpAerialF1_Phys

/// #ftCo_JumpAerialF1_Coll

/// #fn_800D769C

/// #ft_800D76B8

/// #ft_800D7770

/// #fn_800D7830

/// #fn_800D78B0

/// #fn_800D7938

void ftCo_ItemScopeStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirStart_Anim(Fighter_GObj* gobj) {}

/// #fn_800D79B4

/// #ftCo_ItemScopeStart_IASA

/// #ftCo_ItemScopeAirStart_IASA

/// #ftCo_ItemScopeStart_Phys

/// #ftCo_ItemScopeAirStart_Phys

/// #ftCo_ItemScopeStart_Coll

/// #ftCo_ItemScopeAirStart_Coll

/// #fn_800D7BDC

/// #fn_800D7C60

/// #fn_800D7CEC

/// #fn_800D7D70

/// #ftCo_ItemScopeRapid_Anim

/// #ftCo_ItemScopeAirRapid_Anim

/// #ftCo_ItemScopeRapid_IASA

/// #ftCo_ItemScopeAirRapid_IASA

/// #ftCo_ItemScopeRapid_Phys

/// #ftCo_ItemScopeAirRapid_Phys

/// #ftCo_ItemScopeRapid_Coll

/// #ftCo_ItemScopeAirRapid_Coll

/// #fn_800D80F4

/// #fn_800D8140

/// #fn_800D81D0

/// #fn_800D8268

/// #fn_800D82EC

/// #fn_800D8378

void ftCo_ItemScopeFire_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeAirFire_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeFire_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirFire_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

/// #ftCo_ItemScopeFire_Coll

/// #ftCo_ItemScopeAirFire_Coll

/// #fn_800D84D4

/// #fn_800D86B8

/// #fn_800D86E0

/// #fn_800D874C

/// #fn_800D87C0

/// #fn_800D8838

#pragma push
#pragma dont_inline on

void ftCo_ItemScopeEnd_Anim(Fighter_GObj* gobj)
{
    ftCo_ItemScopeFire_Anim(gobj);
}

void ftCo_ItemScopeAirEnd_Anim(Fighter_GObj* gobj)
{
    ftCo_ItemScopeFire_Anim(gobj);
}

#pragma pop

void ftCo_ItemScopeEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirEnd_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ItemScopeEnd_Phys

/// #ftCo_ItemScopeAirEnd_Phys

/// #ftCo_ItemScopeEnd_Coll

/// #ftCo_ItemScopeAirEnd_Coll

/// #ftCo_Catch_CheckInput

bool ftCo_800D8A38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_80095254(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && (fp->input.x668 & HSD_PAD_A)) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    return false;
}

/// #ftCo_800D8AE0

/// #ftCo_800D8B9C

void fn_800D8BFC(Fighter_GObj* arg0)
{
    NOT_IMPLEMENTED;
}

void ftCo_800D8C54(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);

    temp_r31->x74_anim_vel.z = 0.0F;
    temp_r31->x74_anim_vel.y = 0.0F;
    temp_r31->x74_anim_vel.x = 0.0F;
    temp_r31->mv.co.catch.x0 = 0.0F;
    Fighter_ChangeMotionState(gobj, msid, 0U, 0.0F, 1.0F, 0.0F, NULL);
    ftCommon_8007E2D0(temp_r31, 1, fn_800D9CE8, fn_800D8BFC, fn_800DAADC);
}

void ftCo_Catch_Anim(Fighter_GObj* gobj)
{
    u8 _[8];

    if (fn_800D8EC8(gobj)) {
        return;
    }
    if (fn_800D9558(gobj)) {
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// #ftCo_CatchDash_Anim

void ftCo_Catch_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchDash_IASA(Fighter_GObj* gobj) {}

/// #ftCo_Catch_Phys

/// #ftCo_CatchDash_Phys

/// #ftCo_Catch_Coll

/// #fn_800D8E30

/// #ftCo_CatchDash_Coll

bool fn_800D8E94(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->kind;
    if (((kind == FTKIND_LINK) || (kind == FTKIND_CLINK)) &&
        (fp->fv.lk.xC != NULL))
    {
        return false;
    }
    return true;
}

/// #fn_800D8EC8

/// #fn_800D9228

/// #fn_800D949C

/// #ftCo_800D94D8

bool fn_800D952C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->kind == FTKIND_SAMUS) && (fp->fv.ss.x223C != NULL)) {
        return false;
    }
    return true;
}

/// #fn_800D9558

/// #fn_800D9930

/// #fn_800D9C64

/// #ftCo_800D9C98

void fn_800D9CE8(Fighter_GObj* arg0)
{
    NOT_IMPLEMENTED;
}

/// #ftCo_CatchPull_Anim

void ftCo_CatchPull_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CatchPull_Phys

/// #ftCo_CatchPull_Coll

/// #fn_800DA004

/// #fn_800DA054

/// #fn_800DA190

/// #fn_800DA1D8

/// #fn_800DA2B0

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

/// #ftCo_CatchWait_IASA

/// #ftCo_CatchWait_Phys

/// #ftCo_CatchWait_Coll

/// #fn_800DA440

void fn_800DA490(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

/// #fn_800DA4A0

/// #fn_800DA4C0

/// #fn_800DA4FC

void ftCo_CatchAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DA2B0(gobj);
    }
}

void ftCo_CatchAttack_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CatchAttack_Phys

/// #ftCo_CatchAttack_Coll

/// #fn_800DA618

void fn_800DA668(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

/// #fn_800DA678

/// #ftCo_800DA698

void ftCo_CatchCut_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CatchCut_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CatchCut_Phys

/// #ftCo_CatchCut_Coll

/// #ftCo_800DA824

/// #fn_800DA8E4

/// #fn_800DAA40

void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1)
{
    NOT_IMPLEMENTED;
}

void ftCo_CapturePulledHi_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledHi_IASA(Fighter_GObj* gobj) {}

/// #fn_800DAC78

/// #fn_800DAD18

/// #ftCo_CapturePulledHi_Phys

/// #ftCo_CapturePulledHi_Coll

/// #fn_800DAECC

/// #fn_800DAEEC

void ftCo_CapturePulledLw_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CapturePulledLw_Phys

/// #ftCo_CapturePulledLw_Coll

/// #fn_800DB230

/// #ftCo_800DB368

/// #ftCo_800DB464

/// #ftCo_800DB500

/// #fn_800DB5D8

/// #fn_800DB6C8

/// #fn_800DB790

/// #fn_800DB8A4

/// #ftCo_CaptureWaitHi_Anim

void ftCo_CaptureWaitHi_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

/// #ftCo_CaptureWaitHi_Phys

/// #ftCo_CaptureWaitHi_Coll

/// #fn_800DBAC4

/// #fn_800DBAE4

/// #fn_800DBBF8

/// #ftCo_CaptureWaitLw_Anim

/// #ftCo_CaptureWaitLw_IASA

/// #ftCo_CaptureWaitLw_Phys

/// #ftCo_CaptureWaitLw_Coll

/// #fn_800DBED4

/// #fn_800DC014

/// #fn_800DC044

/// #fn_800DC070

/// #ftCo_CaptureJump_Anim

/// #ftCo_CaptureJump_IASA

/// #ftCo_CaptureJump_Phys

void ftCo_CaptureJump_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/// #ftCo_800DC284

void ftCo_CaptureDamageHi_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DB790(gobj);
    }
}

void ftCo_CaptureDamageHi_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CaptureDamageHi_Phys

/// #ftCo_CaptureDamageHi_Coll

/// #fn_800DC384

/// #ftCo_800DC3A4

/// #fn_800DC404

void ftCo_CaptureDamageLw_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DBAE4(gobj);
    }
}

void ftCo_CaptureDamageLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CaptureDamageLw_Phys

/// #ftCo_CaptureDamageLw_Coll

/// #fn_800DC624

/// #ftCo_800DC750

void ftCo_CaptureCut_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CaptureCut_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CaptureCut_Phys

/// #ftCo_CaptureCut_Coll

/// #fn_800DC8D8

/// #fn_800DC8FC

/// #ftCo_800DC920

/// #ftCo_800DCE34

/// #ftCo_800DCFD4

/// #ftCo_800DD100

/// #ftCo_800DD168

/// #ftCo_800DD1E4

/// #ftCo_800DD398

/// #ftCo_800DD4B0

/// #fn_800DD568

/// #fn_800DD5EC

/// #fn_800DD684

/// #fn_800DD6E4

/// #ftCo_800DD724

/// #ftCo_ThrowF_Anim

void ftCo_ThrowF_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowF_Phys

/// #ftCo_ThrowF_Coll

/// #ftCo_ThrowB_Anim

void ftCo_ThrowB_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowB_Phys

/// #ftCo_ThrowB_Coll

/// #ftCo_ThrowHi_Anim

void ftCo_ThrowHi_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowHi_Phys

/// #ftCo_ThrowHi_Coll

/// #ftCo_ThrowHi_Cam

/// #ftCo_ThrowLw_Anim

void ftCo_ThrowLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowLw_Phys

/// #ftCo_ThrowLw_Coll

/// #ftCo_800DDDE4

/// #ftCo_800DE2A8

/// #ftCo_800DE2CC

/// #ftCo_800DE2F0

/// #ftCo_800DE3FC

/// #ftCo_800DE508

/// #ftCo_800DE5A4

void ftCo_ThrownF_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownF_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownF_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownF_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownB_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownB_Coll(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownHi_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownHi_Coll(Fighter_GObj* gobj) {}

/// #ftCo_ThrownHi_Cam

void ftCo_ThrownLw_Anim(Fighter_GObj* gobj)
{
    ftCo_800DE5A4(gobj);
}

void ftCo_ThrownLw_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_Phys(Fighter_GObj* gobj) {}

void ftCo_ThrownLw_Coll(Fighter_GObj* gobj) {}

/// #fn_800DE798

/// #ftCo_800DE7C0

/// #ftCo_800DE854

/// #ftCo_800DE920

/// #ftCo_800DE974

/// #ftCo_800DE9B8

/// #ftCo_800DE9D8

/// #ftCo_800DEA28

/// #ftCo_800DEAE8

/// #ftCo_800DEBD0

/// #ftCo_AppealS_Anim

/// #ftCo_AppealS_IASA

void ftCo_AppealS_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_AppealS_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

/// #ftCo_800DEE84

void ftCo_800DEEA8(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.state = SmashState_None;
}

/// #ftCo_800DEEB8

/// #ftCo_800DEEE8

/// #ftCo_800DEF38

/// #ftCo_800DF0D0

/// #ftCo_800DF1C8

/// #ftCo_800DF21C

/// #ftCo_800DF2D8

/// #ftCo_800DF30C

/// #ftCo_800DF3A8

/// #ftCo_800DF3DC

/// #ftCo_800DF478

/// #ftCo_800DF50C

/// #ftCo_800DF608

/// #ftCo_800DF644

/// #ftCo_800DF678

/// #ftCo_800DF6F8

/// #ftCo_800DF72C

/// #ftCo_800DF79C

/// #ftCo_800DF7F4

/// #ftCo_800DF844

/// #ftCo_800DF878

/// #ftCo_800DF8B0

/// #ftCo_800DF8E8

bool ftCo_800DF910(Fighter* fp)
{
    if (fp->input.cstick.y >= p_ftCommonData->tap_jump_threshold) {
        return true;
    }
    return false;
}
