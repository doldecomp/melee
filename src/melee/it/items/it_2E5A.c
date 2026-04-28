#include "it_2E5A.h"

#include "types.h"

#include "db/db.h"
#include "gm/gm_unsplit.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"

#include <math.h>
#include <math_ppc.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

const Vec3 it_803B8718 = { 0.0f, 0.0f, 0.0f };
const Vec3 it_803B8724 = { 0.0f, 0.0f, 0.0f };

ItemStateTable it_803F8BD8[] = {
    { 0, it_2E5A_UnkMotion1_Anim, it_2E5A_UnkMotion1_Phys,
      it_2E5A_UnkMotion0_Coll },
    { -1, it_2E5A_UnkMotion1_Anim, it_2E5A_UnkMotion1_Phys, NULL },
    { 0, it_2E5A_UnkMotion2_Anim, it_2E5A_UnkMotion2_Phys,
      it_2E5A_UnkMotion2_Coll },
};

static inline ItemStateDesc* it_2E5A_ItemStateDesc(Item* ip)
{
    it_2E5A_Attrs* attr = ip->xC4_article_data->x4_specialAttributes;
    return (ItemStateDesc*) &attr->tiers[ip->xDD4_itemVar.it_2E5A.x4]
        .anim_joint;
}

bool it_802E5AC4(Item_GObj* item_gobj, bool arg_check)
{
    u8 _pad[4];
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Item* item;
    f32 temp_f1_10;
    f32 var_f31;
    bool check1;
    bool check2;
    CollData* coll_data;
    ItemAttr* comm_attr;
    it_2E5A_Attrs* spec_attr;
    PAD_STACK(8);

    item = GET_ITEM(item_gobj);
    coll_data = &item->x378_itemColl;
    comm_attr = item->xCC_item_attr;
    spec_attr = item->xC4_article_data->x4_specialAttributes;
    it_80276214(item_gobj);
    coll_data->cur_pos.y -= item->xC1C.bottom;
    check1 = mpColl_80048844(coll_data);
    coll_data->cur_pos.y += item->xC1C.bottom;
    item->pos = coll_data->cur_pos;

    // Rounds item velocities to 0 if they are close to it
    if (check1 && arg_check) {
        if (ABS(item->x40_vel.x) <= 0.00001f) {
            item->x40_vel.x = 0.0f;
        }
        if (ABS(item->x40_vel.y) <= 0.00001f) {
            item->x40_vel.y = 0.0f;
        }
        if (ABS(item->x40_vel.x) <= comm_attr->x5c) {
            if (!(ABS(item->x40_vel.y) <= comm_attr->x5c)) {
                goto block_16;
            }
            goto block_18;
        }
    block_16:
        if (item->xDCD_flag.b4 || (comm_attr->x58 == 0.0f)) {
        block_18:
            itResetVelocity(item);
            item->xD50_landNum = 0;
        } else {
            check2 = false;
            sp34 = it_803B8718;
            check1 = false;
            sp28 = it_803B8724;
            var_f31 =
                sqrtf_accurate(SQ(item->x40_vel.x) + SQ(item->x40_vel.y));
            if (((item->x40_vel.x * coll_data->floor.normal.x) +
                 (item->x40_vel.y * coll_data->floor.normal.y)) < 0.0f)
            {
                sp40 = item->x40_vel;
                lbVector_Mirror(&sp40, &coll_data->floor.normal);
                lbVector_Add_xy(&sp28, &sp40);
                if (mpCollGetSpeedFloor(coll_data, &sp40) != 0) {
                    lbVector_Add_xy(&sp34, &sp40);
                }
                check2 = true;
            }
            if (check2) {
                lbVector_NormalizeXY(&sp28);
                if (sqrtf(SQ(sp28.x) + SQ(sp28.y) + SQ(sp28.z)) < 0.01f) {
                    sp28.x = item->x40_vel.x;
                    sp28.y = -1.0f * item->x40_vel.y;
                }
                temp_f1_10 = var_f31 * comm_attr->x58;
                sp28.x *= temp_f1_10;
                sp28.y *= temp_f1_10;
                item->x64_vec_unk2 = sp34;
                item->x40_vel = sp28;
            }
            if (it_80276D9C(item_gobj, 1) != 0) {
                it_8027321C(item_gobj);
                it_80277C40(item_gobj, 0);
                it_80275640(item_gobj, comm_attr->x58);
            }
            if (item->xD50_landNum == 1) {
                item->xD84 = spec_attr->tiers[0].xD84_value;
            }
            item->x40_vel.x *= spec_attr->x14;
            item->xD50_landNum += 1;
            if (item->xD50_landNum >= 3U) {
                if (!(item->xDCF_flag.b0)) {
                    item->xDCF_flag.b0 = 1;
                }
            }
        }
    }
    return check1;
}

s32 it_802E5EF4(Item_GObj* item_gobj)
{
    return GET_ITEM(item_gobj)->xDD4_itemVar.it_2E5A.x0;
}

void it_802E5F00(Item_GObj* item_gobj, Vec3* pos, Vec3* vel, s32 arg3)
{
    it_802E5FXX_struct vars;
    SpawnItem sp1C;
    f32 unused1;

    it_802E614C(NULL, item_gobj, &sp1C, pos, vel);
    vars.x0 = item_gobj;
    sp1C.facing_dir = -1.0f;
    vars.x8 = vars.x4 = 0.0f;
    vars.xC = arg3;
    vars.x10 = 0;
    vars.x14 = 1;
    vars.x18 = 0;
    it_802E609C(&vars, &sp1C);
}

s32 it_802E5F8C(Item_GObj* item_gobj, Vec3* pos, s32 arg2, s32 arg3, f32 arg4,
                f32 arg5)
{
    it_802E5FXX_struct vars;
    SpawnItem sp2C;
    f32 dir;
    f32 angle;
    Vec3 vel;

    vel.x = vel.y = vel.z = 0.0f;
    it_802E614C(item_gobj, item_gobj, &sp2C, pos, &vel);
    angle = M_PI_2 + arg4;
    while (angle < 0.0f) {
        angle += M_TAU;
    }
    while (angle > M_TAU) {
        angle -= M_TAU;
    }
    if (angle > M_PI) {
        dir = -1.0f;
    } else {
        dir = 1.0f;
    }
    vars.x0 = item_gobj;
    vars.x4 = angle;
    vars.x8 = arg5;
    vars.xC = arg2;
    vars.x10 = 1;
    sp2C.facing_dir = dir;
    vars.x14 = arg3;
    vars.x18 = gm_8016C6C0(item_gobj);
    return it_802E609C(&vars, &sp2C);
}

s32 it_802E609C(it_802E5FXX_struct* vars, SpawnItem* spawn)
{
    Item_GObj* spawn_gobj;
    s32 temp_r3_2;
    s32 var_r30;
    s32 var_r29 = 0;

    while (vars->xC) {
        it_802E6658();
        spawn_gobj = Item_80268B18(spawn);
        if (spawn_gobj != NULL) {
            if ((vars->x10 == 1) && (var_r29 == 0)) {
                temp_r3_2 = it_802E61C4(spawn_gobj, vars->xC, vars->x18);
                vars->xC = temp_r3_2;
                var_r30 = temp_r3_2;
                var_r29 = 1;
            }
            it_802E6380(spawn_gobj, vars);
            it_802E66A0(spawn_gobj);
            db_80225DD8(spawn_gobj, vars->x0);
            it_802750F8(spawn_gobj);
        }
    }
    return var_r30;
}

inline void it_802E614C(Item_GObj* parent_gobj1, Item_GObj* parent_gobj2,
                        SpawnItem* spawn, Vec3* pos, Vec3* vel)
{
    spawn->kind = It_Kind_Unk4;
    spawn->prev_pos = *pos;
    spawn->pos = spawn->prev_pos;
    spawn->x3C_damage = 0;
    spawn->vel = *vel;
    spawn->x0_parent_gobj = parent_gobj1;
    spawn->x4_parent_gobj2 = parent_gobj2;
    spawn->x44_flag.b0 = 1;
    spawn->x40 = 0;
}

s32 it_802E61C4(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    it_2E5A_Attrs* attr = item->xC4_article_data->x4_specialAttributes;
    f32 new_var;
    s32 var_r29;
    f32 temp_f1;
    var_r29 = arg1 * attr->x2C[arg2];
    new_var = HSD_Randf();
    temp_f1 = attr->x24 * new_var;
    var_r29 *= (0.01F * temp_f1) + 1.0F;
    if (var_r29 < 1) {
        do {
            var_r29 = 1;
        } while (0);
    }
    return var_r29;
}

void it_802E628C(Item_GObj* item_gobj, f32 arg8, f32 arg9)
{
    Item* item = GET_ITEM(item_gobj);
    f32 temp_f31;
    f32 temp_f2;
    f32 temp_f1;
    f32 temp_f0;
    f32 var_f30;
    it_2E5A_Attrs* attr = item->xC4_article_data->x4_specialAttributes;

    temp_f31 = HSD_Randf();
    temp_f1 = M_PI_2;
    temp_f2 = attr->xC;
    temp_f0 = M_PI_3;
    temp_f1 = arg8 - M_PI_2;
    temp_f0 = M_PI;
    var_f30 = temp_f31 * temp_f2;
    var_f30 *= item->facing_dir;
    if (((arg8 >= (temp_f0 / 3)) && (arg8 <= (2 * (temp_f0 / 3)))) ||
        ((arg8 >= (4 * (temp_f0 / 3))) && (arg8 <= (5 * (temp_f0 / 3)))))
    {
        var_f30 += attr->x10 * cosf((temp_f1));
    }
    item->x40_vel.x = var_f30;
    temp_f0 = attr->x20;
    temp_f1 = attr->x18;
    temp_f0 = temp_f31 * temp_f0;
    temp_f0 += arg9;
    temp_f1 += temp_f0;
    item->x40_vel.y = temp_f1;
    item->x40_vel.z = 0.0f;
}

s32 it_802E6380(Item_GObj* item_gobj, it_802E5FXX_struct* arg1)
{
    Item* item = GET_ITEM(item_gobj);
    it_2E5A_Attrs* attr = item->xC4_article_data->x4_specialAttributes;
    it_2E5A_TierEntry* tier;
    s32 off = 2;
    PAD_STACK(30);

    tier = attr->tiers;
    if (arg1->xC < tier[2].threshold) {
        off = 1;
        if (arg1->xC < tier[1].threshold) {
            off = 0;
        }
    }
    item->xDD4_itemVar.it_2E5A.x4 = off;

    arg1->xC -= attr->tiers[off].threshold;
    item->xDD4_itemVar.it_2E5A.x0 = attr->tiers[off].threshold;

    if (arg1->x10 == 1) {
        arg1->x8 *= attr->x1C;
        it_802E628C(item_gobj, arg1->x4, arg1->x8);
    }
    it_80275158(item_gobj, attr->x0);
    item->xDD4_itemVar.it_2E5A.x10 = attr->x4;
    item->xDD4_itemVar.it_2E5A.x14 = attr->x8;
    item->xDD4_itemVar.it_2E5A.x8 = arg1->x14;
    item->xDCD_flag.b6 = off;

    tier = &attr->tiers[off];
    item->xD84 = attr->tiers[off].xD84_value;
    item->scl = attr->tiers[off].scale;

    it_80273318(item_gobj, attr->tiers[off].joint);
    it_80275D5C(item_gobj, &attr->tiers[off].ecb);

    item->xC0C = item->xC1C;
    item->xC1C.bottom *= item->scl;
    item->xDD4_itemVar.it_2E5A.xC = 0;

    {
        Item* item = GET_ITEM(item_gobj);
        s8 old = item->xDD4_itemVar.it_2E5A.x18.u8;
        item->xDD4_itemVar.it_2E5A.x18.b1 = 0;
        item->xDD4_itemVar.it_2E5A.x18.b0 = (old >> 6) & 1;
    }

    if (item->xDD4_itemVar.it_2E5A.x8 != 0) {
        it_2E5A_Attrs* attr = item->xC4_article_data->x4_specialAttributes;
        it_2E5A_SubVars* sub = &item->xDD4_itemVar.it_2E5A.sub;
        sub->x4 = GET_JOBJ(item_gobj);
        sub->x0 = (0.003906f * attr->x28) / item->scl;
        item->x3C = sub->x0;
        lb_8000B1CC(sub->x4, NULL, &sub->x8);
        sub->x14 = sub->x8;
        if (db_ShowCoinPickupRange()) {
            item->xDAA_flag.b0 = 0;
        }
    }
    return arg1->xC;
}

bool it_802E657C(Item_GObj* item_gobj)
{
    Item* item;
    f32 timer;
    f32 temp_f0_2;
    f32 temp_f1;
    u8 temp_r4;

    item = GET_ITEM(item_gobj);
    timer = item->xD44_lifeTimer;
    if (timer <= 0.0f) {
        return true;
    }
    item->xD44_lifeTimer = timer - 1.0f;
    if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
        temp_f0_2 = item->xDD4_itemVar.it_2E5A.x10;
        if (temp_f0_2 <= 0.0f) {
            temp_r4 = item->xDD4_itemVar.it_2E5A.x18.b0;
            if (!temp_r4) {
                item->xDD4_itemVar.it_2E5A.x18.b0 = 1;
            }
        } else {
            item->xDD4_itemVar.it_2E5A.x10 = temp_f0_2 - 1.0f;
        }
        temp_f1 = item->xDD4_itemVar.it_2E5A.x14;
        if (temp_f1 <= 0.0f) {
            if (item->xDCD_flag.b5 != 1) {
                it_80275444(item_gobj);
                item->xDD4_itemVar.it_2E5A.x18.b1 = 1;
            }
        } else {
            item->xDD4_itemVar.it_2E5A.x14 = temp_f1 - 1.0f;
        }
    }
    return false;
}

void it_802E6658(void)
{
    if ((u32) Item_804A0C64.x50 >= it_804D6D28->x20 - 2) {
        Item_8026A8EC(it_80272828(It_Kind_Unk4));
    }
}

static inline void it_2E5A_ApplyStateDesc(HSD_GObj* item_gobj, int idx)
{
    Item* item = item_gobj->user_data;
    HSD_JObj* item_jobj = item_gobj->hsd_obj;
    it_2E5A_Attrs* attr = item->xC4_article_data->x4_specialAttributes;
    item->xD0_itemStateDesc = (ItemStateDesc*) &attr->tiers[idx].anim_joint;
    Item_80268D34(item_gobj, item->xD0_itemStateDesc);
    HSD_JObjAnimAll(item_jobj);
}

void it_802E66A0(HSD_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    PAD_STACK(16);
    if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
        if (item->xDD4_itemVar.it_2E5A.xC != 0) {
            Item_80268E5C(item_gobj, 0, ITEM_HIT_PRESERVE | ITEM_UNK_0x1);
        } else {
            Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
            item->xDD4_itemVar.it_2E5A.xC = 1;
            it_2E5A_ApplyStateDesc(item_gobj, item->xDD4_itemVar.it_2E5A.x4);
        }
        item->on_accessory = it_802E6A74;
        return;
    }
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    it_2E5A_ApplyStateDesc(item_gobj, item->xDD4_itemVar.it_2E5A.x4);
}

bool it_2E5A_UnkMotion1_Anim(HSD_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->x5D0_animFrameSpeed = (0.1 * ABS(item->x40_vel.y)) + 1.0;
    return it_802E657C(item_gobj);
}

void it_2E5A_UnkMotion1_Phys(HSD_GObj* item_gobj)
{
    ItemAttr* comm_attr = GET_ITEM(item_gobj)->xCC_item_attr;
    it_80272860(item_gobj, comm_attr->x10_fall_speed,
                comm_attr->x14_fall_speed_max);
}

bool it_2E5A_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    PAD_STACK(10);

    if (it_802E5AC4(item_gobj, 1)) {
        it_802E6888(item_gobj);
        item->xD50_landNum = 0;
        item->xDCF_flag.b0 = 0;
    }
    return false;
}

void it_802E6888(HSD_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    itResetVelocity(item);
    item->x5D0_animFrameSpeed = 1.0f;
    Item_80268E5C(item_gobj, 2, ITEM_HIT_PRESERVE | ITEM_UNK_0x1);
    if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
        item->on_accessory = it_802E6A74;
    }
}

bool it_2E5A_UnkMotion2_Anim(HSD_GObj* item_gobj)
{
    return it_802E657C(item_gobj);
}

void it_2E5A_UnkMotion2_Phys(HSD_GObj* item_gobj) {}

bool it_2E5A_UnkMotion2_Coll(HSD_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    PAD_STACK(42);
    if ((item->xDD4_itemVar.it_2E5A.x8 == 1) && !(it_802E5AC4(item_gobj, 0))) {
        item = item_gobj->user_data;
        if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
            if (item->xDD4_itemVar.it_2E5A.xC) {
                Item_80268E5C(item_gobj, 0, ITEM_HIT_PRESERVE | ITEM_UNK_0x1);
            } else {
                Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
                item->xDD4_itemVar.it_2E5A.xC = 1;
                it_2E5A_ApplyStateDesc(item_gobj,
                                       item->xDD4_itemVar.it_2E5A.x4);
            }
            item->on_accessory = it_802E6A74;
        } else {
            Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
            it_2E5A_ApplyStateDesc(item_gobj, item->xDD4_itemVar.it_2E5A.x4);
        }
    }
    return false;
}

bool it_2E5A_Logic115_DmgDealt(Item_GObj* item_gobj)
{
    lbAudioAx_80023870(0x93, 0x7F, 0x40, 0x1A);
    return true;
}

void it_802E6A74(HSD_GObj* gobj)
{
    Item* item = gobj->user_data;
    if (item->xDD4_itemVar.it_2E5A.x8) {
        it_2E5A_SubVars* sub = &item->xDD4_itemVar.it_2E5A.sub;
        sub->x14 = sub->x8;
        lb_8000B1CC(sub->x4, NULL, &sub->x8);
    }
}

void it_2E5A_Logic115_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
