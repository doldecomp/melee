#include "ft_0CDD.h"

#include <sysdolphin/baselib/gobj.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/items/itlgun.h>

void ftCo_800CE1D4(HSD_GObj*); /* extern */

/// grounded
void ftCo_800CDF5C(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;
    fighter = fighter_gobj->user_data;
    fighter->throw_flags = 0;
    if (it_8026B594(fighter->item_gobj) == false) {
        Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_LGunShoot, 0U, 0.0f,
                                  1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_LGunShootEmpty, 0U,
                                  0.0f, 1.0f, 0.0f, NULL);
    }
    ftAnim_8006EBA4(fighter_gobj);
    fighter->accessory4_cb = ftCo_800CE1D4;
    if ((Item_GObj*) fighter->item_gobj != NULL) {
        it_8028E938((Item_GObj*) fighter->item_gobj);
    }
}

/// in air
void ftCo_800CE010(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    fighter->throw_flags = 0;
    if (it_8026B594(fighter->item_gobj) == false) {
        Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_LGunShootAir, 0U, 0.0f,
                                  1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_LGunShootAirEmpty, 0U,
                                  0.0f, 1.0f, 0.0f, NULL);
    }
    ftAnim_8006EBA4(fighter_gobj);
    ftCommon_ClampAirDrift(fighter);
    fighter->accessory4_cb = ftCo_800CE1D4;
    if ((Item_GObj*) fighter->item_gobj != NULL) {
        it_8028E938((Item_GObj*) fighter->item_gobj);
    }
}

/// landing?
void ftCo_800CE0CC(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    int id;
    f32 f1;
    f32 f2;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D7FC(fighter);
    if (fighter->motion_id == ftCo_MS_LGunShootAir) {
        id = ftCo_MS_LGunShoot;
    } else {
        id = ftCo_MS_LGunShootEmpty;
    }
    f1 = fighter->cur_anim_frame;
    f2 = fighter->frame_speed_mul;
    Fighter_ChangeMotionState(fighter_gobj, id, 0x0C4C5080, f1, f2, 0.0f,
                              NULL);
    fighter->accessory4_cb = ftCo_800CE1D4;
}

/// Entering air?
void ftCo_800CE14C(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    int id;
    f32 f1;
    f32 f2;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D5D4(fighter);
    if (fighter->motion_id == ftCo_MS_LGunShoot) {
        id = ftCo_MS_LGunShootAir;
    } else {
        id = ftCo_MS_LGunShootAirEmpty;
    }
    f1 = fighter->cur_anim_frame;
    f2 = fighter->frame_speed_mul;
    Fighter_ChangeMotionState(fighter_gobj, id, 0x0C4C5080, f1, f2, 0.0f,
                              NULL);
    ftCommon_ClampAirDrift(fighter);
    fighter->accessory4_cb = ftCo_800CE1D4;
}

/// LGun accessory4 callback function (ran after fire input already processed)
#pragma push
#pragma dont_inline on
void ftCo_800CE1D4(HSD_GObj* fighter_gobj)
{
    f32 f0;
    Vec3 pos2;
    Vec3 pos1;
    u8 _[4];
    Fighter* fighter;
    bool var_r0;

    fighter = fighter_gobj->user_data;

    if (fighter->item_gobj != NULL) {
        var_r0 = fighter->throw_flags_b0;
        if (var_r0) {
            var_r0 = true;
            fighter->throw_flags_b0 = false;
        } else {
            var_r0 = false;
        }
        if (var_r0) {
            it_8028E774(fighter->item_gobj, &pos1);
            ftCo_800CDE94(fighter, &pos1, &pos2);
            if (!it_8026B594(fighter->item_gobj)) {
                it_8028E79C(fighter->item_gobj, &pos2, fighter->facing_dir);
                pos2.z = 0.0f;
                efSync_Spawn(1073, fighter_gobj, &pos2, &fighter->facing_dir);
                if (fighter->facing_dir == 1) {
                    ft_PlaySFX(fighter, 228, 127, 64);
                } else {
                    ft_PlaySFX(fighter, 229, 127, 64);
                }
            } else {
                efSync_Spawn(1029, fighter_gobj, &pos2);
                ft_PlaySFX(fighter, 230, 127, 64);
            }
        }
    }
}
#pragma pop

void ftCo_LGunShoot_Anim(Fighter_GObj* fighter_gobj)
{
    ftCo_800CDE18(fighter_gobj);
}

void ftCo_LGunShootAir_Anim(Fighter_GObj* fighter_gobj)
{
    ftCo_800CDE18(fighter_gobj);
}

void ftCo_LGunShoot_IASA(Fighter_GObj* fighter_gobj) {}

void ftCo_LGunShootAir_IASA(Fighter_GObj* fighter_gobj) {}

void ftCo_LGunShoot_Phys(Fighter_GObj* fighter_gobj)
{
    ftCo_800CDE54(fighter_gobj);
}

void ftCo_LGunShootAir_Phys(Fighter_GObj* fighter_gobj)
{
    ftCo_800CDE74(fighter_gobj);
}

void ftCo_LGunShoot_Coll(Fighter_GObj* fighter_gobj)
{
    ft_800841B8(fighter_gobj, ftCo_800CE14C);
}

void ftCo_LGunShootAir_Coll(Fighter_GObj* fighter_gobj)
{
    ft_80082C74(fighter_gobj, ftCo_800CE0CC);
}
