#include "ftYs_SpecialHi.static.h"

#include "baselib/forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftYoshi/forward.h"

#include "ftYoshi/ftYs_Init.h"
#include "ftYoshi/types.h"
#include "it/items/it_2F2B.h"
#include "it/items/ityoshieggthrow.h"

#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>

void ftYs_SpecialS_8012DF18(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->target_item_gobj != NULL) {
        ftYoshi_MotionState msid = fp->motion_id;
        bool clear_destroy_type = false;
        if (msid == ftYs_MS_SpecialN1_1 || msid == ftYs_MS_SpecialN2_1 ||
            msid == ftYs_MS_SpecialAirN1_2 || msid == ftYs_MS_SpecialAirN2_1)
        {
            clear_destroy_type = true;
        }
        it_802F2CE0(fp->target_item_gobj, clear_destroy_type);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
    }
}

static inline float max(float a, float b)
{
    return a > b ? b : a;
}

void ftYs_SpecialS_8012DF8C(Fighter_GObj* gobj, Vec3* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYs_DatAttrs* da = fp->dat_attrs;
    float temp_f4;
    {
        float temp = ABS(fp->input.lstick.x) / da->xEC;
        float mag = max(temp, 1.0f) * da->xF0;
        if (mag < da->xF4) {
            mag = 0.0f;
        }
        temp_f4 = mag * getStickDirX(fp);
    }
    {
        float angle;
        if (fp->facing_dir == +1.0f) {
            angle = da->specialhi_base_angle - temp_f4;
        } else {
            angle = M_PI - da->specialhi_base_angle - temp_f4;
        }
        arg1->x = (fp->mv.ys.specialhi.x4 * da->x100 + da->xFC) * cosf(angle);
        arg1->y = (fp->mv.ys.specialhi.x4 * da->x100 + da->xFC) * sinf(angle);
        arg1->z = 0.0f;
    }
}

/// #fn_8012E110

void ftYs_SpecialS_8012E270(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ys.x2238 != NULL && fp->mv.ys.specials.x0 == 0) {
        it_802B2890(fp->fv.ys.x2238);
    }
    fp->fv.ys.x2238 = NULL;
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

/// #ftYs_SpecialHi_Enter

/// #ftYs_SpecialAirHi_Enter

static void setAccessory4Callback(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8012E110;
}

static void setDamageCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ys.x2238 != NULL) {
        fp->take_dmg_cb = ftYs_Init_8012BA8C;
        fp->death2_cb = ftYs_Init_8012BA8C;
    }
}

static u32 const motion_flags = (1 << 1) | (1 << 7) | (1 << 12) | (1 << 14) |
                                (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                                (1 << 27);

void fn_8012E3B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirHi, motion_flags,
                              fp->cur_anim_frame, 0.0f, 1.0f, NULL);
    setDamageCallbacks(gobj);
    setAccessory4Callback(gobj);
    ftCommon_8007D468(fp);
}

void fn_8012E44C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16C, motion_flags, fp->cur_anim_frame, 0,
                              1, NULL);
    setDamageCallbacks(gobj);
    setAccessory4Callback(gobj);
}

void ftYs_SpecialHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & 0x200) {
        fp->mv.ys.specialhi.x4 += 1;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftYs_SpecialAirHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & 0x200) {
        fp->mv.ys.specialhi.x4 += 1;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftYs_SpecialHi_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialAirHi_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialHi_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, (void(*)) fn_8012E3B4);
}

void ftYs_SpecialAirHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ys.specialhi.x0 != 0) {
        // ft_80083A48(NULL, fn_8012E44C);
        ft_80083A48(gobj, fn_8012E44C);
        // return;
    } else {
        ft_80082C74(gobj, fn_8012E44C);
    }
}
