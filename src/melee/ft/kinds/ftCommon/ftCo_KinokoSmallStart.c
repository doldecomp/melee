#include "ftCo_KinokoSmallStart.h"

#include <Runtime/platform.h>
#include <stdbool.h>

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ft_0D27.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

#include "forward.h"

#include "ftCo_KinokoGiantEnd.h"

/* 0D20EC */ static void fn_800D20EC(Fighter_GObj* gobj);

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool Fighter_PoisonMushroomApply(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    /// @todo Float hack
    (void) 1.0f;
    (void) 0.0f;

    if (!ftCo_800D27C4(fp)) {
        return false;
    }
    if (fp->motion_id >= ftCo_MS_KinokoGiantStart &&
        fp->motion_id <= ftCo_MS_KinokoSmallEndAir)
    {
        fp->mv.co.mushroom.x4(gobj);
    }
    if (fp->x2220_b6) {
        fp->x2008 = p_ftCommonData->x688;
        return false;
    }
    if (fp->x2220_b5) {
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
#ifdef MUST_MATCH
#pragma pop
#endif

void ftCo_800D1F6C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D2BF8(gobj);
    fp->x2220_b6 = true;
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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftCo_KinokoSmallStart_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1F6C(gobj);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftCo_KinokoSmallStartAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1F6C(gobj);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void ftCo_KinokoSmallStartAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D20EC);
}
