#include "ftYs_SpecialHi.static.h"

#include "placeholder.h"

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
#include "it/items/ityoshieggthrow.h"
#include "it/items/ityoshitongue.h"
#include "lb/lb_00B0.h"

#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>

static void setDamageCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.ys.x2238 != NULL) {
        fp->take_dmg_cb = ftYs_Init_8012BA8C;
        fp->death2_cb = ftYs_Init_8012BA8C;
    }
}

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

void ftYs_SpecialS_8012DF8C(Fighter_GObj* gobj, Vec3* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYs_DatAttrs* da = fp->dat_attrs;
    float temp_f4;
    {
        float temp = ABS(fp->input.lstick.x) / da->xEC;
        float mag = MAX(temp, 1.0f) * da->xF0;
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

static inline void ftYs_SpecialS_8012DF8C_outline(Fighter_GObj* gobj,
                                                  Vec3* vec)
{
    ftYs_SpecialS_8012DF8C(gobj, vec);
}

void fn_8012E110(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYs_DatAttrs* da = fp->dat_attrs;
    bool var_r0;

    if (fp->throw_flags_b0) {
        fp->throw_flags_b0 = 0;
        var_r0 = true;
    } else {
        var_r0 = false;
    }

    if (var_r0) {
        Vec3 sp30;
        PAD_STACK(4);
        lb_8000B1CC(fp->parts[31].joint, NULL, &sp30);
        fp->x1984_heldItemSpec = fp->fv.ys.x2238 =
            it_802B2A10(gobj, &sp30, 0x1F, fp->facing_dir);
        setDamageCallbacks(gobj);
    }

    if (fp->cmd_vars[0] != 0U && fp->fv.ys.x2238 != NULL) {
        Vec3 sp24;
        Vec3 sp18;
        PAD_STACK(4);
        fp->cmd_vars[0] = 0;
        fp->mv.ys.specialhi.x0 = 1;
        sp24.x = da->x104 * fp->facing_dir;
        sp24.y = da->x108;
        sp24.z = 0.0F;
        ftYs_SpecialS_8012DF8C_outline(gobj, &sp18);
        it_802B28C8(fp->fv.ys.x2238, &sp18, &sp24,
                    fp->mv.ys.specialhi.x4 * da->x110 + da->x10C,
                    fp->mv.ys.specialhi.x4);
        fp->fv.ys.x2238 = NULL;
        fp->take_dmg_cb = NULL;
        fp->death2_cb = NULL;
    }
}

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

void ftYs_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    u8 _[24];

    fp->mv.ys.specialhi.x0 = 0;
    fp->mv.ys.specialhi.x4 = 0;
    fp->fv.ys.x2238 = NULL;
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialHi, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8012E110;
    ftAnim_8006EBA4(gobj);
}

void ftYs_SpecialAirHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    u8 _[24];

    fp->mv.ys.specialhi.x0 = 0;
    fp->mv.ys.specialhi.x4 = 0;
    fp->fv.ys.x2238 = NULL;
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirHi, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8012E110;
    ftAnim_8006EBA4(gobj);
}

static void setAccessory4Callback(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8012E110;
}

static u32 const motion_flags = (1 << 1) | (1 << 7) | (1 << 12) | (1 << 14) |
                                (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                                (1 << 27);

void fn_8012E3B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirHi, motion_flags,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    setDamageCallbacks(gobj);
    setAccessory4Callback(gobj);
    ftCommon_ClampAirDrift(fp);
}

void fn_8012E44C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16C, motion_flags, fp->cur_anim_frame, 1,
                              0, NULL);
    setDamageCallbacks(gobj);
    setAccessory4Callback(gobj);
}

void ftYs_SpecialHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->input.held_inputs & HSD_PAD_B) {
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

    if (fp->input.held_inputs & HSD_PAD_B) {
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
        ft_80083A48(gobj, fn_8012E44C);
    } else {
        ft_80082C74(gobj, fn_8012E44C);
    }
}
