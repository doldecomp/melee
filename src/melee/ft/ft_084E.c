#include "ft_084E.h"

#include <math.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcommon.h>

void ft_80084E1C(Fighter_GObj* gobj, float threshold, float drift_max,
                 float target_max)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);
    float drift;
    float target_vel;

    ftCommon_CheckFallFast(fp);
    if (fp->fall_fast) {
        ftCommon_FallFast(fp);
    } else {
        ftCommon_Fall(fp, co_attrs->grav, co_attrs->terminal_vel);
    }

    if (ABS(fp->input.lstick.x) >= threshold) {
        drift = fp->input.lstick.x * drift_max;
        target_vel = fp->input.lstick.x * target_max;
    } else {
        target_vel = 0.0F;
        drift = 0.0F;
    }
    ftCommon_8007D140(fp, drift, target_vel, co_attrs->aerial_friction);
}

void ft_80084EEC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);

    ftCommon_Fall(fp, co_attrs->grav, co_attrs->terminal_vel);
    ftCommon_ApplyFrictionAir(fp, co_attrs->aerial_friction);
}

void ft_80084F3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    f32 friction = co->gr_friction;
    PAD_STACK(8);
    if (ABS(fp->gr_vel) > co->walk_max_vel) {
        friction *= p_ftCommonData->x6C;
    }
    ftCommon_ApplyFrictionGround(fp, friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ft_80084FA8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    f32 var_f2 = fp->gr_vel;
    f32 var_f1 = co->gr_friction;
    if (var_f2 < 0.0F) {
        var_f2 = -var_f2;
    }
    if (var_f2 > co->walk_max_vel) {
        var_f1 *= p_ftCommonData->x6C;
    }
    ft_80085030(gobj, var_f1, fp->facing_dir);
}

void ft_80085004(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    co_attrs = &fp->co_attrs;

    ft_80085030(gobj, co_attrs->gr_friction, fp->facing_dir1);
}

void ft_80085030(Fighter_GObj* gobj, float gr_friction, float facing_dir)
{
    Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->xE4_ground_accel_1 =
            fp->x6A4_transNOffset.z * facing_dir - fp->gr_vel;
    } else {
        ftCommon_ApplyFrictionGround(fp, gr_friction);
    }
    ftCommon_ApplyGroundMovement(gobj);
}

void ft_80085088(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    co_attrs = &fp->co_attrs;

    ft_800850E0(gobj, co_attrs->gr_friction, fp->facing_dir);
}

void ft_800850B4(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    co_attrs = &fp->co_attrs;

    ft_800850E0(gobj, co_attrs->gr_friction, fp->facing_dir1);
}

void ft_800850E0(Fighter_GObj* gobj, float arg8, float arg9)
{
    Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->gr_vel = fp->x6A4_transNOffset.z * arg9;
    } else {
        ftCommon_ApplyFrictionGround(fp, arg8);
    }
    ftCommon_ApplyGroundMovement(gobj);
}

void ft_80085134(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir;
    fp->self_vel.y = fp->x6A4_transNOffset.y;
}

void ft_80085154(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 lstick_x = cosf(fp->lstick_angle);
    f32 lstick_y = sinf(fp->lstick_angle);
    f32 temp_f0 = fp->x6A4_transNOffset.y;
    f32 temp_f3 = fp->x6A4_transNOffset.z * fp->facing_dir;
    fp->self_vel.x = (temp_f3 * lstick_x) - (temp_f0 * lstick_y);
    fp->self_vel.y = (temp_f3 * lstick_y) + (temp_f0 * lstick_x);
}

void ft_800851C0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = fp->x6A4_transNOffset.y;
}

void ft_800851D0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x197C != NULL) {
        fp->self_vel.y =
            fp->x6A4_transNOffset.y * ((f32*) Fighter_804D6520)[5];
    } else {
        fp->self_vel.y = fp->x6A4_transNOffset.y;
    }
}

void ft_80085204(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir;
}
