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

inline void ftCo_800CE650_inline(HSD_GObj* gobj, int frame, int interval)
{
    if (interval - 1 == frame % interval) {
        ft_800892A0(gobj);
        ft_80089824(gobj);
    }
}

inline void ftCo_800CE650_inline2(HSD_GObj* gobj)
{
    Vec3 sp30;
    Vec3 sp24;
    Fighter* fp = GET_FIGHTER(gobj);
    it_80292EF8(fp->item_gobj, &sp30);
    ftCo_800CDE94(fp, &sp30, &sp24);
    if (!it_8026B594(fp->item_gobj)) {
        it_80292F14(fp->item_gobj, &sp24, fp->facing_dir);
    } else {
        ftCommon_8007ECD4(fp, 1);
    }
    fp->mv.co.itemthrow.x8++;

    ftCo_800CE650_inline(gobj, fp->mv.co.itemthrow.x8, p_ftCommonData->x5B4);
}

inline void ftCo_800CE650_inline3(HSD_GObj* gobj)
{
    Vec3 spA0;
    Vec3 sp94;
    float sp90;
    Vec3 sp84;
    Fighter* fp = GET_FIGHTER(gobj);

    if (it_8026B594(fp->item_gobj) == 0) {
        sp90 = 0.0F;
        lb_8000B1CC(fp->parts->joint, NULL, &sp84);
        efSync_Spawn(0x3FF, gobj, &sp84, &fp->facing_dir, &sp90);
        ft_PlaySFX(fp, 0xEE, 0x7F, 0x40);
    } else {
        it_80292EF8(fp->item_gobj, &spA0);
        ftCo_800CDE94(fp, &spA0, &sp94);
        efSync_Spawn(0x405, gobj, &sp94);
        ft_PlaySFX(fp, 0xEF, 0x7F, 0x40);
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
    Vec3 spC4;
    Vec3 spB8;
    f32 spB4;

    Fighter* temp_r3;

    PAD_STACK(0x0c);

    temp_r3 = GET_FIGHTER(gobj);
    if (temp_r3->item_gobj != NULL) {
        if (!(temp_r3->input.held_inputs & HSD_PAD_A)) {
            temp_r3->mv.co.itemthrow.xC = 1;
        }
        if (temp_r3->mv.co.itemthrow.x10 < p_ftCommonData->x5B0) {
            temp_r3->mv.co.itemthrow.x10 += 1.0F;
        }
        if (temp_r3->mv.co.itemthrow.x10 < p_ftCommonData->x5B0 &&
            (temp_r3->input.x668 & HSD_PAD_A))
        {
            temp_r3->mv.co.itemthrow.x10 = 0.0F;
        }
        if (zero_throw_flag_b0(temp_r3)) {
            temp_r3->mv.co.itemthrow.x14 = 1;

            ftCo_800CE650_inline3(gobj);

            ftCo_800CE650_inline2(gobj);

            if (it_8026B594(temp_r3->item_gobj) == 0) {
                spB4 = 0.0f;
                lb_8000B1CC(temp_r3->parts->joint, NULL, &spC4);
                efSync_Spawn(0x3FD, gobj, &spC4, &temp_r3->facing_dir, &spB4);
                it_80292EF8(temp_r3->item_gobj, &spB8);
                ftCo_800CDE94(temp_r3, &spB8, &spC4);
                efSync_Spawn(0x3F3, gobj, &spC4);
                ftCommon_8007EBAC(temp_r3, 1, 0);
            }
            ftAnim_SetAnimRate(gobj, 0.0f);
        }
        if (temp_r3->mv.co.itemthrow.x14 == 1) {
            temp_r3->mv.co.itemthrow.x4 -= 1.0f;
            if (temp_r3->mv.ca.specialhi.vel.x <= 0.0f) {
                temp_r3->mv.ca.specialhi.vel.x = p_ftCommonData->x5AC;

                ftCo_800CE650_inline3(gobj);
            }
            temp_r3->mv.co.itemthrow.facing_dir -= 1.0f;
            if (temp_r3->mv.co.itemthrow.facing_dir <= 0.0f) {
                temp_r3->mv.co.itemthrow.facing_dir = p_ftCommonData->x5A8;

                ftCo_800CE650_inline2(gobj);
            }
            if (temp_r3->mv.co.itemthrow.x8 >= p_ftCommonData->x5A4 &&
                temp_r3->mv.co.itemthrow.xC != 0)
            {
                if (temp_r3->mv.co.itemthrow.x10 >= p_ftCommonData->x5B0) {
                    temp_r3->mv.co.itemthrow.x14 = 0.0f;
                    ftAnim_SetAnimRate(gobj, 1.0f);
                    ftCommon_8007ECD4(temp_r3, 1);
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
