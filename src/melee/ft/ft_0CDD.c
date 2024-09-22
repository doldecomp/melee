#include "it/forward.h"

#include "ft_0CDD.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftpickupitem.h"
#include "it/it_26B1.h"
#include "it/items/itfflower.h"
#include "it/items/itlgun.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/mtxvec.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

void ftCo_800CE0CC(HSD_GObj*);      /* extern */
void ftCo_800CE14C(HSD_GObj*);      /* extern */
void ftCo_800CE1D4(HSD_GObj*);      /* extern */
void ftCo_800CE620(HSD_GObj*);      /* extern */
void ftCo_800CE650(HSD_GObj*);      /* extern */
void it_8028E938(Item_GObj*);       /* extern */
UNK_RET ft_800D76B8(Fighter_GObj*); /* extern */
UNK_RET ft_800D7770(Fighter_GObj*); /* extern */
static s8 L_804D3CC0[7] = "jobj.h";
static s8 L_804D3CC8[5] = "jobj";

static f32 L_804D8F18 = 1.0f;
static f32 L_804D8F20 = 0.0f;
static f32 L_804D8F24 = 1.0f;
static f32 L_804D8F28 = 0.0f;
static f32 L_804D8F2C = 1.0f;

void ftCo_Attack_800CDD14(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;
    ItemKind kind;

    fighter = fighter_gobj->user_data;
    if (ftpickupitem_80094790((HSD_GObj*) fighter_gobj) == 0) {
        kind = itGetKind(fighter->item_gobj);
        switch (kind) { /* irregular */
        case 16:
            ftCo_800CDF5C(fighter_gobj);
            return;
        case 25:
            ftCo_800CE3E0(fighter_gobj);
            return;
        case 21:
            ft_800D76B8(fighter_gobj);
            break;
        }
    }
}

void ftCo_800CDDA0(Fighter_GObj* fighter_gobj)
{
    ItemKind kind;

    kind = itGetKind(((Fighter*) fighter_gobj->user_data)->item_gobj);
    switch (kind) { /* irregular */
    case 16:
        ftCo_800CE010(fighter_gobj);
        return;
    case 25:
        ftCo_800CE480(fighter_gobj);
        return;
    case 21:
        ft_800D7770(fighter_gobj);
        return;
    }
}

void ftCo_800CDE18(Fighter_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
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

void ftCo_800CDE94(Fighter* fighter, Vec3* arg1, Vec3* arg2)
{
    // void ftCo_800CDE94(Fighter* fighter, Vec3* arg1) {
    // f32 sp20;
    // f32 sp1C;
    // f32 sp18;
    Vec3 pos;
    HSD_JObj* fighterbone_jobj;
    f32 scale;
    f32 inverse_scale;
    f32 unused1;
    f32 unused2;

    // fighter->ft_data->x8 is a model lookup, but not exactly sure how to use
    // temp_r31 = *(arg0->unk5E8 + (arg0->unk10C->unk8->unk10 * 0x10));
    // temp_r31 = *(fighter->parts->joint + (fighter->ft_data->x8->x10 *
    // 0x10));
    // fighterbone_jobj = fighter->parts[fighter->ft_data->x8->x10 *
    // 0x10].joint;
    fighterbone_jobj = fighter->parts[fighter->ft_data->x8->x10].joint;
    // sp18 = arg1->unk0;
    // sp1C = arg1->unk4;
    // sp20 = arg1->unk8;
    pos = *arg1;
    // pos->x = arg1->x;
    // pos->y = arg1->y;
    // pos->z = arg1->z;

    scale = fighter->x34_scale.y;
    if (scale != 1.0f) {
        inverse_scale = 1.0f / scale;
        // sp18 *= temp_f1_2;
        // sp1C *= temp_f1_2;
        // sp20 *= temp_f1_2;
        pos.x *= inverse_scale;
        pos.y *= inverse_scale;
        pos.z *= inverse_scale;
    }
    if (fighterbone_jobj == NULL) {
        HSD_JObjGetMtxPtr(fighterbone_jobj);
        // __assert("jobj.h", 0x478U, "jobj");
    }
    // lbColl_JObjSetupMatrix(fighterbone_jobj);
    // PSMTXMUltiVec((f32 (*)[4]) fighterbone_jobj->mtx[0], (Vec3* ) &sp18,
    // arg2);
    PSMTXMUltiVec(fighterbone_jobj->mtx, &pos, arg2);
    // PSMTXMUltiVec(fighterbone_jobj->mtx, pos, arg1);
}

void ftCo_800CDF5C(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    fighter->throw_flags = 0;
    if (it_8026B594(fighter->item_gobj) == 0) {
        Fighter_ChangeMotionState(fighter_gobj, 0x94, 0U, 0.0f, 1.0f, 0.0f,
                                  NULL);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, 0x96, 0U, 0.0f, 1.0f, 0.0f,
                                  NULL);
    }
    ftAnim_8006EBA4(fighter_gobj);
    fighter->accessory4_cb = ftCo_800CE1D4;
    if ((Item_GObj*) fighter->item_gobj != NULL) {
        it_8028E938((Item_GObj*) fighter->item_gobj);
    }
}

void ftCo_800CE010(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    fighter->throw_flags = 0;
    if (it_8026B594(fighter->item_gobj) == 0) {
        Fighter_ChangeMotionState(fighter_gobj, 0x95, 0U, 0.0f, 1.0f, 0.0f,
                                  NULL);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, 0x97, 0U, 0.0f, 1.0f, 0.0f,
                                  NULL);
    }
    ftAnim_8006EBA4(fighter_gobj);
    ftCommon_8007D468(fighter);
    fighter->accessory4_cb = ftCo_800CE1D4;
    if ((Item_GObj*) fighter->item_gobj != NULL) {
        it_8028E938((Item_GObj*) fighter->item_gobj);
    }
}

// Local function?
void ftCo_800CE0CC(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    int id;
    f32 f1;
    f32 f2;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D7FC(fighter);
    if (fighter->motion_id == 0x95) {
        id = 0x94;
    } else {
        id = 0x96;
    }
    // r5 = fighter->x914->victims_1[8].x4;
    // r5 = 0x0C4C5080;
    f1 = fighter->cur_anim_frame;
    f2 = fighter->frame_speed_mul;
    // Fighter_ChangeMotionState((Fighter_GObj*) fighter_gobj, id, 0U, f1, f2,
    // 0.0f, NULL);
    Fighter_ChangeMotionState((Fighter_GObj*) fighter_gobj, id, 0x0C4C5080, f1,
                              f2, 0.0f, NULL);
    fighter->accessory4_cb = ftCo_800CE1D4;
}

// Local function?
void ftCo_800CE14C(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    int id;
    f32 f1;
    f32 f2;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D5D4(fighter);
    if (fighter->motion_id == 0x94) {
        id = 0x95;
    } else {
        id = 0x97;
    }
    f1 = fighter->cur_anim_frame;
    f2 = fighter->frame_speed_mul;
    Fighter_ChangeMotionState((Fighter_GObj*) fighter_gobj, id, 0x0C4C5080, f1,
                              f2, 0.0f, NULL);
    ftCommon_8007D468(fighter);
    fighter->accessory4_cb = ftCo_800CE1D4;
}

// Local function?
void ftCo_800CE1D4(HSD_GObj* fighter_gobj)
{
    Vec3 pos1;
    Vec3 pos2;
    Fighter* fighter;
    f32 f0;
    f32 f1;
    s32 var_r0;

    fighter = fighter_gobj->user_data;

    if (fighter->item_gobj != NULL) {
        // temp_r3 = fighter->unk2210;
        // temp_r3 = fighter->throw_flags;
        // fighter->throw_flags_b1 |= 1;
        var_r0 = (u8) (fighter->throw_flags_b0 & ~0x10);
        if (var_r0) {
            var_r0 = 1;
            fighter->throw_flags_b0 = (u8) (var_r0 & ~0x7);
        } else {
            var_r0 = 0;
        }
        if (var_r0) {
            it_8028E774((Item_GObj*) fighter->item_gobj, &pos1);
            ftCo_800CDE94(fighter, &pos1, &pos2);
            // it_8026B594((Item_GObj* ) fighter->item_gobj);
            it_8026B594((Item_GObj*) fighter->item_gobj);

            if (fighter->item_gobj != NULL) {
                it_8028E79C((Item_GObj*) fighter->item_gobj, &pos1,
                            fighter->facing_dir);
                // it_8028E79C((Item_GObj* ) fighter->item_gobj, &pos2,
                // fighter->facing_dir); efSync_Spawn(1073, fighter_gobj, pos2,
                // fighter);
                f0 = 0.0f;
                // efSync_Spawn(1073, fighter, &pos2);
                efSync_Spawn(1073, fighter, &pos2, fighter->facing_dir);
                if (fighter->facing_dir != 1) {
                    ft_80088148(fighter, 228, 127, 64);
                } else {
                    ft_80088148(fighter, 229, 127, 64);
                }
            } else {
                efSync_Spawn(1029, fighter, &pos2);
                ft_80088148(fighter, 230, 127, 64);
            }
        }
    }
}

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
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    fighter->throw_flags = 0;
    // fighter->mv.ca.specials.grav = p_ftCommonData->unk5A8;
    // fighter->mv.ca.specialhi.vel.x = p_ftCommonData->unk5AC;
    // fighter->mv.ca.specialhi.vel.y = 0.0f;
    fighter->mv.co.itemthrow.facing_dir =
        (float) ((int) p_ftCommonData + 0x5A8);
    // fighter->mv.co.itemthrow.facing_dir = (float) ((u8) p_ftCommonData->x5A0
    // + 0x8);
    fighter->mv.co.itemthrow.x4 = (float) ((int) p_ftCommonData + 0x5AC);
    // fighter->mv.co.itemthrow.x4 = (float) ((u8) p_ftCommonData->x5A0 + 0xC);
    fighter->mv.co.itemthrow.x8 = 0U;
    fighter->mv.co.itemthrow.xC = 0U;
    fighter->mv.co.itemthrow.x10 = 0.0f;
    fighter->mv.co.itemthrow.x14 = 0U;
    Fighter_ChangeMotionState(fighter_gobj, 0x98, 0U, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

void ftCo_800CE480(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    fighter->throw_flags = 0;
    fighter->mv.co.itemthrow.facing_dir =
        (float) ((int) p_ftCommonData + 0x5A8);
    fighter->mv.co.itemthrow.x4 = (float) ((int) p_ftCommonData + 0x5AC);
    fighter->mv.co.itemthrow.x8 = 0U;
    fighter->mv.co.itemthrow.xC = 0U;
    fighter->mv.co.itemthrow.x10 = 0.0f;
    fighter->mv.co.itemthrow.x14 = 0U;
    Fighter_ChangeMotionState(fighter_gobj, 0x99, 0U, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    ftCommon_8007D468(fighter);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

void ft_800CE528(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D7FC(fighter);
    Fighter_ChangeMotionState(fighter_gobj, 0x98, 0x0C4C5880U,
                              fighter->cur_anim_frame,
                              fighter->frame_speed_mul, 0.0f, NULL);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

void ft_800CE5A0(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;

    fighter = fighter_gobj->user_data;
    ftCommon_8007D5D4(fighter);
    Fighter_ChangeMotionState(fighter_gobj, 0x99, 0x0C4C5880U,
                              fighter->cur_anim_frame,
                              fighter->frame_speed_mul, 0.0f, NULL);
    ftCommon_8007D468(fighter);
    fighter->accessory4_cb = ftCo_800CE650;
    fighter->take_dmg_cb = ftCo_800CE620;
}

// Local function?
void ftCo_800CE620(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    Item_GObj* item_gobj;

    fighter = fighter_gobj->user_data;
    item_gobj = (Item_GObj*) fighter->item_gobj;
    if (item_gobj != NULL) {
        it_80292EAC(item_gobj);
    }
}

// Local function?
void ftCo_800CE650(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    Item_GObj* item_gobj;
    u32 r0;
    u32 r3;
    u32 r4;
    f32 f0;
    f32 f1;
    Vec3* pos0;
    Vec3 pos1;
    Vec3 pos2;
    Vec3 pos3;
    Vec3 pos4;
    Vec3 pos5;
    Vec3 pos6;
    Vec3 pos7;
    Vec3 pos8;
    Vec3 pos9;
    Vec3 pos10;
    Vec3 pos11;
    Vec3 pos12;
    Vec3 pos13;

    fighter = fighter_gobj->user_data;
    item_gobj = (Item_GObj*) fighter->item_gobj;
    if (item_gobj != NULL) {
        // item_gobj->x5D4_hitboxes[0]->hit->victims_1[4].victim
        // fighter->input.held_inputs = fighter->input.held_inputs & 0x100;
        if (fighter->input.held_inputs & 0x100) {
            // fighter->input.held_inputs = 1;
            r0 = 1;
            r0 = fighter->mv.co.itemthrow.xC;
        }
        if (fighter->mv.co.itemthrow.x10 >=
            (float) ((int) p_ftCommonData + 0x5B0))
        {
            fighter->mv.co.itemthrow.x10 += 1.0f;
        }
        if (fighter->mv.co.itemthrow.x10 >=
            (float) ((int) p_ftCommonData + 0x5B0))
        {
            if (fighter->input.x668 & 0x100) {
                f0 = 0.0f;
                f0 = fighter->mv.co.itemthrow.x10;
            }
        }
        r3 = (u8) (fighter->throw_flags_b0 & ~0x10);
        if (r3) {
            r0 = 0;
            r3 = (u8) (r0 & ~0x7);
            fighter->throw_flags_b0 = r3;
            r0 = 1;
        } else {
            r0 = 0;
        }
        if (r0) {
            r0 = 1;
            r0 = fighter->mv.co.itemthrow.x14;
            it_8026B594(item_gobj);
            if (item_gobj) {
                f0 = 0.0f;
                lb_8000B1CC(fighter->parts->joint, 0, &pos1);
                // efSync_Spawn(1023, fighter_gobj, &pos1,
                // fighter->facing_dir);
                efSync_Spawn(1023, fighter_gobj, &pos1, fighter->facing_dir,
                             &pos0);
                ft_80088148(fighter, 238, 127, 64);
            } else {
                it_80292EF8((Item_GObj*) fighter->item_gobj, &pos2);
                // ftCo_800CDE94(fighter, &pos2, &pos3);
                efSync_Spawn(1029, fighter_gobj, &pos3);
                ft_80088148(fighter, 239, 127, 64);
            }
            fighter = fighter_gobj->user_data;
            item_gobj = (Item_GObj*) fighter->item_gobj;
            it_80292EF8(item_gobj, &pos4);
            ftCo_800CDE94(fighter, &pos4, &pos5);
            it_8026B594(item_gobj);
            if (item_gobj) {
                it_80292F14(item_gobj, &pos5, fighter->facing_dir);
            } else {
                ftCommon_8007ECD4(fighter, 1);
            }
            r3 = fighter->mv.co.itemthrow.x8;
            r0 = r3 + 1;
            fighter->mv.co.itemthrow.x8 = r0;
            r3 = fighter->mv.co.itemthrow.x8;
            r4 = ((int) p_ftCommonData + 0x5B4);
            r0 = r3 / r4;        // r0 should be the quotient
            r0 = (r0 / r4) * r0; // r0 should be the quotient*divisor
            r4 = r4 - 1;
            r0 = r0 % r3; // r0 should be the remainder
            if (r4 != r0) {
                ft_800892A0((Fighter_GObj*) fighter_gobj);
                ft_80089824((Fighter_GObj*) fighter_gobj);
            }
            it_8026B594(item_gobj);
            if (item_gobj) {
                f0 = 0.0f;
                lb_8000B1CC(fighter->parts->joint, 0, &pos6);
                efSync_Spawn(1021, fighter_gobj, &pos6, fighter->facing_dir,
                             0.0f);
                it_80292EF8(item_gobj, &pos8);
                ftCo_800CDE94(fighter, &pos8, &pos6);
                efSync_Spawn(1011, fighter_gobj, &pos6);
                ftCommon_8007EBAC(fighter, 1, 0);
            }
            ftAnim_SetAnimRate((Fighter_GObj*) fighter_gobj, 0.0f);
        }
        if (fighter->mv.co.itemthrow.x14 != 1) {
            f1 = fighter->mv.co.itemthrow.x4;
            f0 = 0.0f;
            f0 = f1 - f0;
            fighter->mv.co.itemthrow.x4 = f0;
            f1 = fighter->mv.co.itemthrow.x4;
            f0 = 0.0f;
            if (f0 <= f1) {
                fighter->mv.co.itemthrow.x4 = ((int) p_ftCommonData + 0x5AC);
                it_8026B594(item_gobj);
                if (item_gobj) {
                    f0 = 0.0f;
                    lb_8000B1CC(fighter->parts->joint, 0, &pos9);
                    efSync_Spawn(1023, fighter_gobj, &pos9,
                                 fighter->facing_dir, 0.0f);
                    ft_80088148(fighter, 238, 127, 64);
                } else {
                    item_gobj = (Item_GObj*) fighter->item_gobj;
                    it_80292EF8(item_gobj, &pos10);
                    ftCo_800CDE94(fighter, &pos10, &pos11);
                    efSync_Spawn(1029, fighter_gobj, &pos11);
                    ft_80088148(fighter, 239, 127, 64);
                }
                f1 = fighter->mv.co.itemthrow.facing_dir;
                f0 = 1.0f;
                f0 = f1 - f0;
                fighter->mv.co.itemthrow.facing_dir = f0;
                if (f1 <= f0) {
                    f0 = ((int) p_ftCommonData + 0x5A8);
                    fighter->mv.co.itemthrow.facing_dir = f0;
                    item_gobj = (Item_GObj*) fighter->item_gobj;
                    it_80292EF8(item_gobj, &pos12);
                    ftCo_800CDE94(fighter, &pos12, &pos13);
                    it_8026B594(item_gobj);
                    if (item_gobj) {
                        it_80292F14(item_gobj, &pos13, fighter->facing_dir);
                    } else {
                        ftCommon_8007ECD4(fighter, 1);
                    }
                    r3 = fighter->mv.co.itemthrow.x8;
                    r0 = r3 + 1;
                    fighter->mv.co.itemthrow.x8 = r0;
                    r3 = fighter->mv.co.itemthrow.x8;
                    r4 = ((int) p_ftCommonData + 0x5B4);
                    r0 = r3 / r4;
                    r0 = (r0 / r4) * r4;
                    r4 = r4 + (-1);
                    r0 = r0 - r3;
                    if (r4 != r0) {
                        ft_800892A0((Fighter_GObj*) fighter_gobj);
                        ft_80089824((Fighter_GObj*) fighter_gobj);
                    }
                }
                r3 = fighter->mv.co.itemthrow.x8;
                r0 = ((int) p_ftCommonData + 0x5A4);
                if (r3 != r0) {
                    r0 = fighter->mv.co.itemthrow.xC;
                    if (r0 != 0) {
                        f1 = fighter->mv.co.itemthrow.x10;
                        f0 = ((int) p_ftCommonData + 0x5B0);
                        if (f1 >= f0) {
                            r0 = 0;
                            fighter->mv.co.itemthrow.x14 = r0;
                            ftAnim_SetAnimRate((Fighter_GObj*) fighter_gobj,
                                               1.0f);
                            ftCommon_8007ECD4(fighter, 1);
                        }
                    }
                }
            }
        }
    }
}

void ftCo_FireFlowerShoot_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;
    s32 var_r0;
    s32 var_r0_2;
    u8 temp_r3;
    u8 temp_r3_2;

    fighter = fighter_gobj->user_data;
    if ((Item_GObj*) fighter->item_gobj != NULL) {
        // temp_r3 = fighter->unk2210;
        temp_r3 = fighter->throw_flags;
        if ((temp_r3 >> 4U) & 1) {
            // fighter->unk2210 = (u8) (temp_r3 & ~0x10);
            fighter->throw_flags = (u8) (temp_r3 & ~0x10);
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            it_80292E64(fighter->item_gobj);
        }
        // temp_r3_2 = fighter->unk2210;
        temp_r3_2 = fighter->throw_flags;
        if ((temp_r3_2 >> 3U) & 1) {
            // fighter->unk2210 = (u8) (temp_r3_2 & ~8);
            fighter->throw_flags = (u8) (temp_r3_2 & ~8);
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            it_80292EAC(fighter->item_gobj);
        }
        ftCo_800CDE18(fighter_gobj);
    }
}

void ftCo_FireFlowerShootAir_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter;
    s32 var_r0;
    s32 var_r0_2;
    u8 temp_r3;
    u8 temp_r3_2;
    f32 unused1;
    f32 unused2;

    fighter = fighter_gobj->user_data;
    if ((Item_GObj*) fighter->item_gobj != NULL) {
        // temp_r3 = fighter->unk2210;
        temp_r3 = fighter->throw_flags;
        if ((temp_r3 >> 4U) & 1) {
            // fighter->unk2210 = (u8) (temp_r3 & ~0x10);
            fighter->throw_flags = (u8) (temp_r3 & ~0x10);
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            it_80292E64(fighter->item_gobj);
        }
        // temp_r3_2 = fighter->unk2210;
        temp_r3_2 = fighter->throw_flags;
        if ((temp_r3_2 >> 3U) & 1) {
            // fighter->unk2210 = (u8) (temp_r3_2 & ~8);
            fighter->throw_flags = (u8) (temp_r3_2 & ~8);
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            it_80292EAC(fighter->item_gobj);
        }
        ftCo_800CDE18(fighter_gobj);
    }
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
    ft_800841B8(fighter_gobj, (void (*)(HSD_GObj*)) ft_800CE5A0);
}

void ftCo_FireFlowerShootAir_Coll(Fighter_GObj* fighter_gobj)
{
    ft_80082C74(fighter_gobj, (void (*)(HSD_GObj*)) ft_800CE528);
}
