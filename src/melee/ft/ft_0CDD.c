#include "ft_0CDD.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftpickupitem.h"
#include "it/it_26B1.h"
#include "it/items/itfflower.h"
#include "it/items/itlgun.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

void ftCo_800CE0CC(HSD_GObj*); /* extern */
void ftCo_800CE14C(HSD_GObj*); /* extern */
void ftCo_800CE1D4(HSD_GObj*); /* extern */
void ftCo_800CE620(HSD_GObj*); /* extern */
void ftCo_800CE650(HSD_GObj*); /* extern */
void it_8028E938(Item_GObj*);  /* extern */

/// grounded
void ftCo_Attack_800CDD14(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    if (ftpickupitem_80094790(fighter_gobj) == false) {
        switch (itGetKind(fighter->item_gobj)) {
        case It_Kind_L_Gun:
            ftCo_800CDF5C(fighter_gobj);
            return;
        case It_Kind_F_Flower:
            ftCo_800CE3E0(fighter_gobj);
            return;
        case It_Kind_S_Scope:
            ft_800D76B8(fighter_gobj);
            break;
        }
    }
}

/// in air
void ftCo_800CDDA0(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    switch (itGetKind(fighter->item_gobj)) {
    case It_Kind_L_Gun:
        ftCo_800CE010(fighter_gobj);
        return;
    case It_Kind_F_Flower:
        ftCo_800CE480(fighter_gobj);
        return;
    case It_Kind_S_Scope:
        ft_800D7770(fighter_gobj);
        return;
    }
}

#pragma push
#pragma dont_inline on
void ftCo_800CDE18(Fighter_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == false) {
        ftCommon_8007D92C(fighter_gobj);
    }
}

void ftCo_800CDE54(Fighter_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftCo_800CDE74(Fighter_GObj* fighter_gobj)
{
    ft_80084DB0(fighter_gobj);
}
#pragma pop

void ftCo_800CDE94(Fighter* fighter, Vec3* arg1, Vec3* arg2)
{
    Vec3 pos;
    HSD_JObj* fighterbone_jobj;
    f32 scale;
    f32 inverse_scale;

    fighterbone_jobj = fighter->parts[fighter->ft_data->x8->x10].joint;
    pos = *arg1;

    scale = fighter->x34_scale.y;
    if (scale != 1.0f) {
        inverse_scale = 1.0f / scale;
        pos.x *= inverse_scale;
        pos.y *= inverse_scale;
        pos.z *= inverse_scale;
    }
    MTXMultVec(HSD_JObjGetMtxPtr(fighterbone_jobj), &pos, arg2);
}

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

inline void ftCo_800CE650_inline(HSD_GObj* gobj, int temp_r3_4, int temp_r4_2)
{
    int div = temp_r3_4 / temp_r4_2;
    if (temp_r4_2 - 1 == temp_r3_4 - div * temp_r4_2) {
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
