#include "ftCo_KinokoGiantEnd.h"

#include "platform.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D27.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

/* 0D1C40 */ static void fn_800D1C40(Fighter_GObj* gobj);

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
    fp->x2220_b5 = 0;
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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftCo_KinokoGiantEnd_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1B04(gobj);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftCo_KinokoGiantEndAir_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!fn_800D2A3C(gobj)) {
        ftCo_800D1B04(gobj);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void ftCo_KinokoGiantEndAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D1C40);
}
