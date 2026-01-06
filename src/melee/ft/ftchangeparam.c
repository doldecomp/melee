#include "ftchangeparam.h"

#include "placeholder.h"

#include <melee/ft/fighter.h>
#include <melee/ft/inlines.h>

float ftCo_CalcYScaledKnockback(float arg0, float scale, float arg2)
{
    if (scale == 0.0F) {
        __assert("ftchangeparam.c", 0x1E, "scale != 0.0F");
    }
    if (arg2 == 0.0F) {
        return arg0;
    }
    if (arg2 < 0.0F) {
        return arg0 / ftCo_CalcYScaledKnockback(1.0F, scale, -arg2);
    }
    if (scale >= 1.0F || arg2 <= 1.0F) {
        return (scale - 1.0F) * arg0 * arg2 + arg0;
    }
    return arg0 * scale / arg2;
}

void ftCo_800CF6E8(ftCo_DatAttrs* attr, f32 scale)
{
    PAD_STACK(4);

    if (scale != 1.0f) {
        attr->slow_walk_max = ftCo_CalcYScaledKnockback(
            attr->slow_walk_max, scale, Fighter_804D6524->x10);
        attr->mid_walk_point = ftCo_CalcYScaledKnockback(
            attr->mid_walk_point, scale, Fighter_804D6524->x14);
        attr->fast_walk_min = ftCo_CalcYScaledKnockback(
            attr->fast_walk_min, scale, Fighter_804D6524->x18);
        attr->dash_run_terminal_velocity = ftCo_CalcYScaledKnockback(
            attr->dash_run_terminal_velocity, scale, Fighter_804D6524->x1C);
        attr->run_animation_scaling = ftCo_CalcYScaledKnockback(
            attr->run_animation_scaling, scale, Fighter_804D6524->x20);
        attr->jump_startup_time = ftCo_CalcYScaledKnockback(
            attr->jump_startup_time, scale, Fighter_804D6524->x24);
        attr->jump_v_initial_velocity = ftCo_CalcYScaledKnockback(
            attr->jump_v_initial_velocity, scale, Fighter_804D6524->x28);
        attr->hop_v_initial_velocity = ftCo_CalcYScaledKnockback(
            attr->hop_v_initial_velocity, scale, Fighter_804D6524->x2C);
        attr->grav = ftCo_CalcYScaledKnockback(attr->grav, scale,
                                               Fighter_804D6524->x30);
        attr->terminal_vel = ftCo_CalcYScaledKnockback(
            attr->terminal_vel, scale, Fighter_804D6524->x34);
        attr->air_drift_stick_mul = ftCo_CalcYScaledKnockback(
            attr->air_drift_stick_mul, scale, Fighter_804D6524->x38);
        attr->aerial_drift_base = ftCo_CalcYScaledKnockback(
            attr->aerial_drift_base, scale, Fighter_804D6524->x3C);
        attr->air_drift_max = ftCo_CalcYScaledKnockback(
            attr->air_drift_max, scale, Fighter_804D6524->x40);
        attr->fast_fall_velocity = ftCo_CalcYScaledKnockback(
            attr->fast_fall_velocity, scale, Fighter_804D6524->x44);
        attr->weight = ftCo_CalcYScaledKnockback(attr->weight, scale,
                                                 Fighter_804D6524->x48);
        attr->shield_break_initial_velocity = ftCo_CalcYScaledKnockback(
            attr->shield_break_initial_velocity, scale, Fighter_804D6524->x4C);
        attr->ledge_jump_horizontal_velocity =
            ftCo_CalcYScaledKnockback(attr->ledge_jump_horizontal_velocity,
                                      scale, Fighter_804D6524->x50);
        attr->ledge_jump_vertical_velocity = ftCo_CalcYScaledKnockback(
            attr->ledge_jump_vertical_velocity, scale, Fighter_804D6524->x54);
        attr->item_throw_velocity_multiplier =
            ftCo_CalcYScaledKnockback(attr->item_throw_velocity_multiplier,
                                      scale, Fighter_804D6524->x58);
        attr->xB4 =
            ftCo_CalcYScaledKnockback(attr->xB4, scale, Fighter_804D6524->x5C);
        attr->xBC.size = ftCo_CalcYScaledKnockback(attr->xBC.size, scale,
                                                   Fighter_804D6524->x60);
        attr->xDC =
            ftCo_CalcYScaledKnockback(attr->xDC, scale, Fighter_804D6524->x64);
        attr->kirby_b_star_damage = ftCo_CalcYScaledKnockback(
            attr->kirby_b_star_damage, scale, Fighter_804D6524->x68);
        attr->normal_landing_lag = ftCo_CalcYScaledKnockback(
            attr->normal_landing_lag, scale, Fighter_804D6524->x6C);
        attr->landingairn_lag = ftCo_CalcYScaledKnockback(
            attr->landingairn_lag, scale, Fighter_804D6524->x70);
        attr->landingairf_lag = ftCo_CalcYScaledKnockback(
            attr->landingairf_lag, scale, Fighter_804D6524->x74);
        attr->landingairb_lag = ftCo_CalcYScaledKnockback(
            attr->landingairb_lag, scale, Fighter_804D6524->x78);
        attr->landingairhi_lag = ftCo_CalcYScaledKnockback(
            attr->landingairhi_lag, scale, Fighter_804D6524->x7C);
        attr->landingairlw_lag = ftCo_CalcYScaledKnockback(
            attr->landingairlw_lag, scale, Fighter_804D6524->x80);
        attr->name_tag_height = ftCo_CalcYScaledKnockback(
            attr->name_tag_height, scale, Fighter_804D6524->x84);
        attr->x140 = ftCo_CalcYScaledKnockback(attr->x140, scale,
                                               Fighter_804D6524->x88);
        attr->damageicejump_vel_y = ftCo_CalcYScaledKnockback(
            attr->damageicejump_vel_y, scale, Fighter_804D6524->x8C);
        attr->damageicejump_vel_x_mult = ftCo_CalcYScaledKnockback(
            attr->damageicejump_vel_x_mult, scale, Fighter_804D6524->x90);
        attr->x170.x = ftCo_CalcYScaledKnockback(attr->x170.x, scale,
                                                 Fighter_804D6524->x94);
        attr->x170.y = ftCo_CalcYScaledKnockback(attr->x170.y, scale,
                                                 Fighter_804D6524->x94);
        attr->x170.z = ftCo_CalcYScaledKnockback(attr->x170.z, scale,
                                                 Fighter_804D6524->x94);
        attr->x17C = ftCo_CalcYScaledKnockback(attr->x17C, scale,
                                               Fighter_804D6524->x98);
    }
}

void ftCo_800D0CBC(Fighter_GObj* fgp)
{
    Fighter* fp;
    struct Fighter_x2D0_t* temp_r30;
    f32 scale;
    s32 i;
    s32 count;
    PAD_STACK(16);

    fp = fgp->user_data;
    scale = fp->x34_scale.y;
    temp_r30 = fp->x2D0;
    count = temp_r30->x28;

    if (scale != 1.0f) {
        /// @todo figure out the correct args
        scale = ftCo_CalcYScaledKnockback(1.0f, scale, Fighter_804D6524->x28);
    }

    if (fp->x197C != NULL) {
        scale *= Fighter_804D6520->x14;
    }

    if (fp->is_metal) {
        scale *= Fighter_804D651C->x4;
    }

    for (i = 0; i < count; i++) {
        temp_r30->x14[i] *= scale;
    }
}

float ftCo_800D0EC8(Fighter* fp)
{
    return -ftCo_CalcYScaledKnockback(Fighter_804D6524->x30, fp->x34_scale.y,
                                      p_ftCommonData->x310);
}

void ftCo_800D0FA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->co_attrs = *fp->ft_data->x0;
    {
        fp->x294_itPickup = *fp->ft_data->x40;
        fp->x2C4 = *fp->ft_data->x50;
    }
}

extern HSD_GObjEvent ftKindCalcIndiviParamTable[];

/// @brief Initializes a fighters attributes from the DAT, then applies
/// specific modifiers such as metal, bunny hood, etc.
/// @param fighter_gobj
void ftCo_800D105C(Fighter_GObj* fgp)
{
    Fighter* fp;
    ftDonkeyAttributes* attr;
    f32 var_f1;
    f32 temp_f1;
    PAD_STACK(36); /// @todo fix stack

    fp = GET_FIGHTER(fgp);
    fp->co_attrs = *fp->ft_data->x0;
    fp->x294_itPickup = *fp->ft_data->x40;
    fp->x2C4 = *fp->ft_data->x50;

    if (fp->x34_scale.y != 1.0f) {
        ftCo_800CF6E8(&fp->co_attrs, fp->x34_scale.y);
        temp_f1 = fp->x34_scale.y;
        fp->x294_itPickup.gr_light_offset.x *= temp_f1;
        fp->x294_itPickup.gr_light_offset.y *= temp_f1;
        fp->x294_itPickup.gr_light_offset.z *= temp_f1;
        fp->x294_itPickup.gr_light_offset.w *= temp_f1;
        fp->x294_itPickup.gr_heavy_offset.x *= temp_f1;
        fp->x294_itPickup.gr_heavy_offset.y *= temp_f1;
        fp->x294_itPickup.gr_heavy_offset.z *= temp_f1;
        fp->x294_itPickup.gr_heavy_offset.w *= temp_f1;
        fp->x294_itPickup.air_light_offset.x *= temp_f1;
        fp->x294_itPickup.air_light_offset.y *= temp_f1;
        fp->x294_itPickup.air_light_offset.z *= temp_f1;
        fp->x294_itPickup.air_light_offset.w *= temp_f1;
        fp->x2C4.x *= temp_f1;
        fp->x2C4.y *= temp_f1;
    }

    /// if bunnyhood != NULL
    if (fp->x197C != NULL) {
        fp->co_attrs.dash_run_acceleration_a *= Fighter_804D6520->x4;
        fp->co_attrs.dash_run_acceleration_b *= Fighter_804D6520->x8;
        fp->co_attrs.dash_run_terminal_velocity *= Fighter_804D6520->xC;
        fp->co_attrs.jump_h_initial_velocity *= Fighter_804D6520->x10;
        fp->co_attrs.jump_v_initial_velocity *= Fighter_804D6520->x14;
        fp->co_attrs.jump_h_max_velocity *= Fighter_804D6520->x1C;
        fp->co_attrs.hop_v_initial_velocity *= Fighter_804D6520->x18;
        fp->co_attrs.grav *= Fighter_804D6520->x20;
        fp->co_attrs.terminal_vel *= Fighter_804D6520->x24;
        fp->co_attrs.fast_fall_velocity *= Fighter_804D6520->x28;
        fp->co_attrs.ledge_jump_horizontal_velocity *= Fighter_804D6520->x2C;
        fp->co_attrs.ledge_jump_vertical_velocity *= Fighter_804D6520->x30;
        fp->co_attrs.wall_jump_horizontal_velocity *= Fighter_804D6520->x34;
        fp->co_attrs.wall_jump_vertical_velocity *= Fighter_804D6520->x38;
    }
    if (fp->is_metal) {
        fp->co_attrs.jump_v_initial_velocity *= Fighter_804D651C->x4;
        fp->co_attrs.hop_v_initial_velocity *= Fighter_804D651C->x8;
        fp->co_attrs.grav *= Fighter_804D651C->xC;
        fp->co_attrs.terminal_vel *= Fighter_804D651C->x10;
        fp->co_attrs.fast_fall_velocity *= Fighter_804D651C->x14;
        fp->co_attrs.weight *= Fighter_804D651C->x18;
        fp->co_attrs.ledge_jump_vertical_velocity *= Fighter_804D651C->x1C;
        fp->co_attrs.wall_jump_vertical_velocity *= Fighter_804D651C->x20;
    }

    if (fp->x2229_b1) {
        fp->co_attrs.grav *= Fighter_804D6518->x0;
        fp->co_attrs.weight *= Fighter_804D6518->x4;
    }

    if (ftKindCalcIndiviParamTable[fp->kind] == NULL) {
        OSReport("don\'t set ftKindCalcIndiviParamTable!!\n");
        __assert("ftchangeparam.c", 0x10d,
                 "ftKindCalcIndiviParamTable[fp->kind] != NULL");
    }
    ftKindCalcIndiviParamTable[fp->kind](fgp);

    if (fp->x2D0 != NULL) {
        ftCo_800D0CBC(fgp);
    }

    if (fp->x2222_b0) {
        fp = fgp->user_data;
        var_f1 = fp->x34_scale.y;
        attr = fp->x2CC;
        if (var_f1 != 1.0f) {
            attr->x14 *= var_f1;
            attr->x18 *= fp->x34_scale.y;
            attr->x1C *= fp->x34_scale.y;
        }
    }
}
