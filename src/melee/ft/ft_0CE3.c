#include "ft_0CDD.h"

#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/it/items/itfflower.h>
#include <melee/lb/lb_00B0.h>

void ftCo_800CE620(HSD_GObj*); /* extern */

void ftCo_800CE3E0(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    fighter->throw_flags = 0;
    fighter->mv.co.itemthrow.facing_dir = p_ftCommonData->x5A8;
    fighter->mv.co.itemthrow.x4 = p_ftCommonData->x5AC;
    fighter->mv.co.itemthrow.x8 = 0;
    fighter->mv.co.itemthrow.xC = 0;
    fighter->mv.co.itemthrow.x10 = 0.0f;
    fighter->mv.co.itemthrow.x14 = 0;
    Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_FireFlowerShoot, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

void ftCo_800CE480(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    fighter->throw_flags = 0;
    fighter->mv.co.itemthrow.facing_dir = p_ftCommonData->x5A8;
    fighter->mv.co.itemthrow.x4 = p_ftCommonData->x5AC;
    fighter->mv.co.itemthrow.x8 = 0;
    fighter->mv.co.itemthrow.xC = 0;
    fighter->mv.co.itemthrow.x10 = 0.0f;
    fighter->mv.co.itemthrow.x14 = 0;
    Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_FireFlowerShootAir, 0,
                              0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    ftCommon_ClampAirDrift(fighter);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

void ft_800CE528(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D7FC(fighter);
    Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_FireFlowerShoot,
                              0x0C4C5880U, fighter->cur_anim_frame,
                              fighter->frame_speed_mul, 0.0f, NULL);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

void ft_800CE5A0(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D5D4(fighter);
    Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_FireFlowerShootAir,
                              0x0C4C5880U, fighter->cur_anim_frame,
                              fighter->frame_speed_mul, 0.0f, NULL);
    ftCommon_ClampAirDrift(fighter);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

/// Local function?
void ftCo_800CE620(HSD_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    if (fighter->item_gobj != NULL) {
        it_80292EAC(fighter->item_gobj);
    }
}

static inline bool zero_throw_flag_b0(Fighter* fp)
{
    if (fp->throw_flags_b0) {
        fp->throw_flags_b0 = false;
        return true;
    } else {
        return false;
    }
}

void ftCo_800CE650(HSD_GObj* gobj)
{
    Vec3 effect_pos;
    Vec3 item_pos;
    f32 effect_scale;
    UNUSED u8 padA[8];
    Vec3 item_pos_start;
    Vec3 effect_pos_start;
    f32 effect_scale_start;
    Vec3 joint_pos_start;
    Vec3 shot_item_pos_start;
    Vec3 shot_pos_start;
    UNUSED u8 padB[8];
    Vec3 item_pos_repeat;
    Vec3 effect_pos_repeat;
    f32 effect_scale_repeat;
    Vec3 joint_pos_repeat;
    Vec3 shot_item_pos_repeat;
    Vec3 shot_pos_repeat;

    Fighter* fp;
    int frame;
    int interval;

    fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        if (!(fp->input.held_inputs & HSD_PAD_A)) {
            fp->mv.co.itemthrow.xC = 1;
        }
        if (fp->mv.co.itemthrow.x10 < p_ftCommonData->x5B0) {
            fp->mv.co.itemthrow.x10 += 1.0F;
        }
        if (fp->mv.co.itemthrow.x10 < p_ftCommonData->x5B0 &&
            (fp->input.x668 & HSD_PAD_A))
        {
            fp->mv.co.itemthrow.x10 = 0.0F;
        }
        if (zero_throw_flag_b0(fp)) {
            fp->mv.co.itemthrow.x14 = 1;

            {
                Fighter* fp = GET_FIGHTER(gobj);

                if (it_8026B594(fp->item_gobj) == 0) {
                    effect_scale_start = 0.0F;
                    lb_8000B1CC(fp->parts->joint, NULL, &joint_pos_start);
                    efSync_Spawn(0x3FF, gobj, &joint_pos_start,
                                 &fp->facing_dir, &effect_scale_start);
                    ft_PlaySFX(fp, 0xEE, 0x7F, 0x40);
                } else {
                    it_80292EF8(fp->item_gobj, &item_pos_start);
                    ftCo_800CDE94(fp, &item_pos_start, &effect_pos_start);
                    efSync_Spawn(0x405, gobj, &effect_pos_start);
                    ft_PlaySFX(fp, 0xEF, 0x7F, 0x40);
                }
            }

            {
                Fighter* fp = GET_FIGHTER(gobj);

                it_80292EF8(fp->item_gobj, &shot_item_pos_start);
                ftCo_800CDE94(fp, &shot_item_pos_start, &shot_pos_start);
                if (!it_8026B594(fp->item_gobj)) {
                    it_80292F14(fp->item_gobj, &shot_pos_start,
                                fp->facing_dir);
                } else {
                    ftCommon_8007ECD4(fp, 1);
                }
                fp->mv.co.itemthrow.x8++;

                frame = fp->mv.co.itemthrow.x8;
                interval = p_ftCommonData->x5B4;
                if (interval - 1 == frame % interval) {
                    ft_800892A0(gobj);
                    ft_80089824(gobj);
                }
            }

            if (it_8026B594(fp->item_gobj) == 0) {
                effect_scale = 0.0f;
                lb_8000B1CC(fp->parts->joint, NULL, &effect_pos);
                efSync_Spawn(0x3FD, gobj, &effect_pos, &fp->facing_dir,
                             &effect_scale);
                it_80292EF8(fp->item_gobj, &item_pos);
                ftCo_800CDE94(fp, &item_pos, &effect_pos);
                efSync_Spawn(0x3F3, gobj, &effect_pos);
                ftCommon_8007EBAC(fp, 1, 0);
            }
            ftAnim_SetAnimRate(gobj, 0.0f);
        }
        if (fp->mv.co.itemthrow.x14 == 1) {
            fp->mv.co.itemthrow.x4 -= 1.0f;
            if (fp->mv.ca.specialhi.vel.x <= 0.0f) {
                fp->mv.ca.specialhi.vel.x = p_ftCommonData->x5AC;

                {
                    Fighter* fp = GET_FIGHTER(gobj);

                    if (it_8026B594(fp->item_gobj) == 0) {
                        effect_scale_repeat = 0.0F;
                        lb_8000B1CC(fp->parts->joint, NULL,
                                    &joint_pos_repeat);
                        efSync_Spawn(0x3FF, gobj, &joint_pos_repeat,
                                     &fp->facing_dir, &effect_scale_repeat);
                        ft_PlaySFX(fp, 0xEE, 0x7F, 0x40);
                    } else {
                        it_80292EF8(fp->item_gobj, &item_pos_repeat);
                        ftCo_800CDE94(fp, &item_pos_repeat,
                                     &effect_pos_repeat);
                        efSync_Spawn(0x405, gobj, &effect_pos_repeat);
                        ft_PlaySFX(fp, 0xEF, 0x7F, 0x40);
                    }
                }
            }
            fp->mv.co.itemthrow.facing_dir -= 1.0f;
            if (fp->mv.co.itemthrow.facing_dir <= 0.0f) {
                fp->mv.co.itemthrow.facing_dir = p_ftCommonData->x5A8;

                {
                    Fighter* fp = GET_FIGHTER(gobj);

                    it_80292EF8(fp->item_gobj, &shot_item_pos_repeat);
                    ftCo_800CDE94(fp, &shot_item_pos_repeat,
                                 &shot_pos_repeat);
                    if (!it_8026B594(fp->item_gobj)) {
                        it_80292F14(fp->item_gobj, &shot_pos_repeat,
                                    fp->facing_dir);
                    } else {
                        ftCommon_8007ECD4(fp, 1);
                    }
                    fp->mv.co.itemthrow.x8++;

                    frame = fp->mv.co.itemthrow.x8;
                    interval = p_ftCommonData->x5B4;
                    if (interval - 1 == frame % interval) {
                        ft_800892A0(gobj);
                        ft_80089824(gobj);
                    }
                }
            }
            if (fp->mv.co.itemthrow.x8 >= p_ftCommonData->x5A4 &&
                fp->mv.co.itemthrow.xC != 0)
            {
                if (fp->mv.co.itemthrow.x10 >= p_ftCommonData->x5B0) {
                    fp->mv.co.itemthrow.x14 = 0.0f;
                    ftAnim_SetAnimRate(gobj, 1.0f);
                    ftCommon_8007ECD4(fp, 1);
                }
            }
        }
    }
}

static inline bool zero_throw_flag_b3(Fighter* fp)
{
    if (fp->throw_flags_b3) {
        fp->throw_flags_b3 = false;
        return true;
    } else {
        return false;
    }
}

static inline bool zero_throw_flag_b4(Fighter* fp)
{
    if (fp->throw_flags_b4) {
        fp->throw_flags_b4 = false;
        return true;
    } else {
        return false;
    }
}

void ftCo_FireFlowerShoot_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    if (fighter->item_gobj != NULL) {
        if (zero_throw_flag_b3(fighter)) {
            it_80292E64(fighter->item_gobj);
        }
        if (zero_throw_flag_b4(fighter)) {
            it_80292EAC(fighter->item_gobj);
        }
        ftCo_800CDE18(fighter_gobj);
    }
}

void ftCo_FireFlowerShootAir_Anim(Fighter_GObj* fighter_gobj)
{
    ftCo_FireFlowerShoot_Anim(fighter_gobj);
}

void ftCo_FireFlowerShoot_IASA(Fighter_GObj* fighter_gobj) {}

void ftCo_FireFlowerShootAir_IASA(Fighter_GObj* fighter_gobj) {}

void ftCo_FireFlowerShoot_Phys(Fighter_GObj* fighter_gobj)
{
    ftCo_800CDE54(fighter_gobj);
}

void ftCo_FireFlowerShootAir_Phys(Fighter_GObj* fighter_gobj)
{
    ftCo_800CDE74(fighter_gobj);
}

void ftCo_FireFlowerShoot_Coll(Fighter_GObj* fighter_gobj)
{
    ft_800841B8(fighter_gobj, ft_800CE5A0);
}

void ftCo_FireFlowerShootAir_Coll(Fighter_GObj* fighter_gobj)
{
    ft_80082C74(fighter_gobj, ft_800CE528);
}
