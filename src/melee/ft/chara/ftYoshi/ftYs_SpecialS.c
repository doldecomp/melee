#include "ftYs_SpecialS.h"

#include "ftYs_SpecialHi.h"
#include "math.h"
#include "placeholder.h"

#include "ft/fighter.h"

#include "baselib/forward.h"
#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
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

inline void ftYoshi_SpecialS_SetCall(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = fn_8012EC7C;
    fp->take_dmg_cb = fn_8012EDE8;
    fp->deal_dmg_cb = fn_8012EFF4;
    fp->x21F8 = fn_8013295C;
}

/// #ftYs_SpecialS_8012EB48

inline void fn_8012EC7C_inline(Fighter_GObj *gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    FtMotionId motion = fp->motion_id;
    if ((motion != 0x16B) && ((motion >= 0x16B) || (motion != 0x167))) {
        ftParts_80074B0C(gobj, 0, 0);
    }
    HSD_JObjSetScale(jobj,&fp->fv.ys.x222C);
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    ftPartSetRotZ(fp, 2, 0.0f);
    if (fp->mv.ys.specials.x24 != 0.0f) {
        fp->facing_dir = fp->mv.ys.specials.x24;
    }
    fp->mv.ys.specials.x24 = 0.0f;
    ftCommon_8007F5CC(gobj, 1);
    fp->x221E_b4 = 1;
}

void fn_8012EC7C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    FtMotionId motion = fp->motion_id;
    if ((motion != 0x16B) && ((motion >= 0x16B) || (motion != 0x167))) {
        ftParts_80074B0C(gobj, 0, 0);
    }
    HSD_JObjSetScale(jobj,&fp->fv.ys.x222C);
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    ftPartSetRotZ(fp, 2, 0.0f);
    if (fp->mv.ys.specials.x24 != 0.0f) {
        fp->facing_dir = fp->mv.ys.specials.x24;
    }
    fp->mv.ys.specials.x24 = 0.0f;
    ftCommon_8007F5CC(gobj, 1);
    fp->x221E_b4 = 1;
}

void fn_8012EDE8(Fighter_GObj* gobj)
{
    Point3d sp18;
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId motion = fp->motion_id;
    if ((motion != 0x16B) && ((motion >= 0x16B) || (motion != 0x167))) {
        lb_8000B1CC(fp->parts->joint, NULL, &sp18);
        efSync_Spawn(0x4CF, gobj, &sp18, &fp->co_attrs.xBC);
        ft_PlaySFX(fp, 0x44618, 0x7FU, 0x40U);
    }
    fn_8012EC7C_inline(gobj);
}

void fn_8012EFC0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

void fn_8012EFF4(Fighter_GObj* gobj)
{
    f32 temp_f2;
    FtMotionId motion;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.xC = 0;
    motion = fp->motion_id;
    if((motion != 0x16a )) {
        if(motion >= 0x16a ) {
            return;
        }
        if(motion != 0x165 ) {
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

void ftYs_SpecialS_Enter(Fighter_GObj* gobj)
{
    int i;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(16);
    fp->facing_dir = fp->input.lstick.x > 0.0F ? 1.0F : -1.0F;
    Fighter_ChangeMotionState(gobj, 0x168, 0U, 0.0F, 1.0F, 0.0F, NULL);
    for (i=3; i >= 0; i--) {
        fp->cmd_vars[i] = 0;
    }
    ftCommon_8007D5D4(fp);
    ftAnim_8006EBA4(gobj);
    ftYs_SpecialS_8012F35C(gobj);
    fp->self_vel.x = fp->mv.ys.specials.x1C * fp->facing_dir;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.y = attributes->x5C;
    fp->x74_anim_vel.y = attributes->specials_start_gravity;
}

void ftYs_SpecialAirS_Enter(Fighter_GObj* gobj)
{
    int i;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(16);
    fp->facing_dir = fp->input.lstick.x > 0.0F ? 1.0F : -1.0F;
    Fighter_ChangeMotionState(gobj, 0x168, 0U, 0.0F, 1.0F, 0.0F, NULL);
    for (i=3; i >= 0; i--) {
        fp->cmd_vars[i] = 0;
    }
    ftAnim_8006EBA4(gobj);
    ftYs_SpecialS_8012F35C(gobj);
    fp->self_vel.x = fp->mv.ys.specials.x1C * fp->facing_dir;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.y = attributes->x5C;
    fp->x74_anim_vel.y = attributes->specials_start_gravity;
}

void ftYs_SpecialAirSStart_0_Anim(Fighter_GObj* gobj)
{
    f32 temp_f0;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x24 = 0.0F;
    ftYs_SpecialS_8012EB48();
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x169, 0x440012U, 0.0F, 0.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);
        fp->cur_anim_frame = 0.0F;
        ftAnim_SetAnimRate(gobj, 0.0F);
        temp_f0 = fp->mv.ys.specials.x1C * fp->facing_dir;
        fp->self_vel.x = temp_f0;
        fp->gr_vel = temp_f0;
        fp->x74_anim_vel.x = 0.0F;
        fp->xE4_ground_accel_1 = 0.0F;
        fp->self_vel.y = attributes->x5C;
        fp->x74_anim_vel.y = attributes->specials_start_gravity;
    }
}

/// #ftYs_SpecialAirSLoop_0_Anim

/// #ftYs_SpecialAirSLoop_1_Anim

/// #ftYs_SpecialAirSEnd_Anim

void ftYs_SpecialAirSStart_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.specials.x24 = 0.0F;
    fp->mv.ys.specials.x30 = 0;
    PAD_STACK(8);
    ftYs_SpecialS_8012EB48();
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter_ChangeMotionState(gobj, 0x169, 0x440012U, 0.0F, 0.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);
        fp->cur_anim_frame = 0.0F;
        ftAnim_SetAnimRate(gobj, 0.0F);

    }
}

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

void ftYs_SpecialAirSLoop_2_Phys(Fighter_GObj* gobj)
{
    f32 var_f0;
    f32 var_f2;
    f32 temp;

    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    temp = fp->input.lstick.x * attributes->xE0;
    fp->self_vel.x += temp;
    var_f0 = fp->self_vel.x < 0.0f ? -fp->self_vel.x : fp->self_vel.x;
    var_f2 = attributes->x90;
    if (var_f0 > var_f2) {
        if (fp->self_vel.x < 0.0f) {
            var_f2 = -var_f2;
        }
        fp->self_vel.x = var_f2;
    }
    ftCommon_Fall(fp, attributes->specials_start_gravity, attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSLoop_3_Phys(Fighter_GObj* gobj)
{
    f32 var_f0;
    f32 var_f2;
    f32 temp;
    
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x30 = 0;
    temp = fp->input.lstick.x * attributes->xE0;
    fp->self_vel.x += temp;
    var_f0 = fp->self_vel.x < 0.0f ? -fp->self_vel.x : fp->self_vel.x;
    var_f2 = attributes->x90;
    if (var_f0 > var_f2) {
        if (fp->self_vel.x < 0.0f) {
            var_f2 = -var_f2;
        }
        fp->self_vel.x = var_f2;
    }
    ftCommon_Fall(fp, attributes->specials_start_gravity, attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSLanding_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSStart_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 360, 0x0C4C5092U, fp->cur_anim_frame, 1.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);
    }
}

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
        ftYoshi_SpecialS_SetCall(gobj);

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
    
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
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
