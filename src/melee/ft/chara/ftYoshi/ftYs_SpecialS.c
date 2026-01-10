#include "ftYs_SpecialS.h"

#include "math.h"
#include "placeholder.h"

#include "ft/fighter.h"

#include "baselib/forward.h"
#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftYoshi/types.h"

#include "ef/efsync.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

/* 3CED84 */ static Vec4 ftYs_Unk3_803CED84 = { 0.65, 0.7, 0.8, 1 };
/* 3CED94 */ static Vec4 ftYs_Unk3_803CED94 = { 1.1, 1.35, 1.3, 1.2 };
/* 3CEDA4 */ static Vec3 ftYs_Unk3_803CEDA4[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

/// #ftYs_SpecialS_8012EB48

void fn_8012EC7C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if ((ftGetAction(fp) != 0x16B) && ((ftGetAction(fp) >=- 0x16B) || (ftGetAction(fp) != 0x167))) {
        ftParts_80074B0C(gobj, 0, 0);
    }
    if (jobj == NULL) {
        __assert("jobj.h", 0x2F8U, "jobj");
    }
    if (&fp->fv == NULL) {
        __assert("jobj.h", 0x2F9U, "scale");
    }
}

void fn_8012EDE8(Fighter_GObj* gobj)
{
    Point3d sp18;
    HSD_JObj* jobj;
    s32 var_r3;
    union Fighter_FighterVars* temp_r29;

    Fighter* fp = GET_FIGHTER(gobj);
    if ((ftGetAction(fp) != 0x16B) && ((ftGetAction(fp) >= 0x16B) || (ftGetAction(fp) != 0x167))) {
        lb_8000B1CC(fp->parts->joint, NULL, &sp18);
        efSync_Spawn(0x4CF, gobj, &sp18, &fp->co_attrs.xBC);
        ft_PlaySFX(fp, 0x44618, 0x7FU, 0x40U);
    }
    jobj = GET_JOBJ(gobj);
    if ((ftGetAction(fp) != 0x16B) && ((ftGetAction(fp) >= 0x16B) || (ftGetAction(fp) != 0x167))) {
        ftParts_80074B0C(gobj,0, 0);
    }
    temp_r29 = &fp->fv;
    if (jobj == NULL) {
        __assert("jobj.h", 0x2F8U, "jobj");
    }
    if (temp_r29 == NULL) {
        __assert("jobj.h", 0x2F9U, "scale");
    }
    jobj->scale.x = *(f32*)&fp->fv.ys.x222C;
    jobj->scale.y = *(f32*)&fp->fv.ys.x2230;
    jobj->scale.z = *(f32*)&fp->fv.ys.x2234;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != NULL) {
            if (jobj == NULL) {
                __assert("jobj.h", 0x234U, "jobj");
            }
            var_r3 = !(jobj->flags & 0x800000) && (jobj->flags & 0x40);
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
    }
    ftPartSetRotY(fp, 0, (f32) (1.5707963267948966 * (f64) fp->facing_dir));
    ftPartSetRotZ(fp, 2, 0.0f);
    if (fp->mv.co.common.x24 != 0.0f) {
        fp->facing_dir = fp->mv.co.common.x24;
    }
    fp->mv.co.common.x24 = 0.0f;
    ftCommon_8007F5CC((Item_GObj* ) gobj, 1);
    fp->x221E_b4 = fp->x221E_b7;
}

void fn_8012EFC0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

void fn_8012EFF4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    f32 temp_f2;
    fp->mv.ys.specials.xC = 0;
    if(ftGetAction(fp) != 0x16a ) {
        if(ftGetAction(fp) >= 0x16a ) {
            return;
        }
        if(ftGetAction(fp) != 0x165 ) {
            return;
        }
    }

    fp->mv.ys.specials.x0 -= attributes->x50;
    temp_f2 = fp->ground_or_air==1 ? attributes->x8C : attributes->x7C;
    
    if ((fp->mv.ys.specials.x1C < 0.0F ? -fp->mv.ys.specials.x1C : +fp->mv.ys.specials.x1C) > temp_f2) {
        if (fp->mv.ys.specials.x1C > 0.0F) {
            fp->mv.ys.specials.x1C -= attributes->xCC;
            if (!(fp->mv.ys.specials.x1C < temp_f2)) return;
            fp->mv.ys.specials.x1C = temp_f2;
            return;
        }
        temp_f2 = -temp_f2;
        fp->mv.ys.specials.x1C += attributes->xCC;
        if (!(fp->mv.ys.specials.x1C > temp_f2)) return;
        fp->mv.ys.specials.x1C = temp_f2;
        return;
    }
    if (0.0f != fp->mv.ys.specials.x1C) return;
    fp->mv.ys.specials.x1C = fp->facing_dir * temp_f2;
}

/// #ftYs_SpecialS_8012F0DC

/// #ftYs_SpecialS_8012F35C

/// #ftYs_SpecialS_Enter

/// #ftYs_SpecialAirS_Enter

/// #ftYs_SpecialAirSStart_0_Anim

/// #ftYs_SpecialAirSLoop_0_Anim

/// #ftYs_SpecialAirSLoop_1_Anim

/// #ftYs_SpecialAirSEnd_Anim

/// #ftYs_SpecialAirSStart_1_Anim

/// #ftYs_SpecialAirSLoop_2_Anim

/// #ftYs_SpecialAirSLoop_3_Anim

/// #ftYs_SpecialAirSLanding_Anim

void ftYs_SpecialAirSStart_0_IASA(Fighter_GObj* gobj) {}

/// #ftYs_SpecialAirSLoop_0_IASA

void ftYs_SpecialAirSLoop_1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    s32 x48 = attributes->x48;
    s32 x4C = attributes->x4C;
    s32 difference = x48 - x4C;

    if ((fp->mv.ys.specials.x0 < difference) && (fp->input.x668 & HSD_PAD_B)) {
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, 0.0f);
    }
}

void ftYs_SpecialAirSEnd_IASA(Fighter_GObj* gobj) {}

void ftYs_SpecialAirSStart_1_IASA(Fighter_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

void ftYs_SpecialAirSLoop_2_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    if ((fp->mv.ys.specials.x0 < attributes->x48 - attributes->x4C) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0f);
    }
}

void ftYs_SpecialAirSLoop_3_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x30 = 0;

    if ((fp->mv.ys.specials.x0 < (attributes->x48 - attributes->x4C)) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0f);
    }
}

void ftYs_SpecialAirSLanding_IASA(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->mv.ys.specials.x30 = 0;
}

void ftYs_SpecialAirSStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->xE4_ground_accel_1 = 0.0f;
    fp->gr_vel = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    fp->x74_anim_vel.y = 0.0f;
    fp->x74_anim_vel.x = 0.0f;
}

/// #ftYs_SpecialAirSLoop_0_Phys

/// #ftYs_SpecialAirSLoop_1_Phys

void ftYs_SpecialAirSEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_ApplyFrictionGround((Fighter*) fp, fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftYs_SpecialAirSStart_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

/// #ftYs_SpecialAirSLoop_2_Phys

/// #ftYs_SpecialAirSLoop_3_Phys

void ftYs_SpecialAirSLanding_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

/// #ftYs_SpecialAirSStart_0_Coll

/// #ftYs_SpecialAirSLoop_0_Coll

/// #ftYs_SpecialAirSLoop_1_Coll

void ftYs_SpecialAirSEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, fp->cur_anim_frame);
    }
}

void ftYs_SpecialAirSStart_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.specials.x30 = 0;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 356, 0x0C4C5092U, fp->cur_anim_frame, 1.0F, 0.0F, NULL);
        fp = GET_FIGHTER(gobj);
        fp->death2_cb = fn_8012EC7C;
        fp->take_dmg_cb = fn_8012EDE8;
        fp->deal_dmg_cb = fn_8012EFF4;
        fp->x21F8 = fn_8013295C;

    }
}

/// #ftYs_SpecialAirSLoop_2_Coll

/// #ftYs_SpecialAirSLoop_3_Coll

void ftYs_SpecialAirSLanding_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.specials.x30 = 0;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x4C4092, fp->cur_anim_frame);
    }
}

void fn_8013295C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);
    
    ftPartSetRotY(fp, 0, (f32) (M_PI_2 * fp->facing_dir));
    fp->self_vel.x = -fp->self_vel.x;
    fp->gr_vel = -fp->gr_vel;
    fp->xE4_ground_accel_1 = -fp->xE4_ground_accel_1;
    fp->mv.ys.specials.x10 = -fp->mv.ys.specials.x10;
    fp->mv.ys.specials.x14 = -fp->mv.ys.specials.x14;
    fp->mv.ys.specials.x18 = -fp->mv.ys.specials.x18;
    fp->mv.ys.specials.x1C = -fp->mv.ys.specials.x1C;
    fp->mv.ys.specials.x20 = -fp->mv.ys.specials.x20;
    fp->mv.ys.specials.x24 = -fp->mv.ys.specials.x24;
}
