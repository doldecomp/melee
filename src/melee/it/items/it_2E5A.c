#include "it_2E5A.h"

#include "types.h"

#include "db/db.h"
#include "gm/gm_unsplit.h"
#include "it/inlines.h"
#include "it/it_266F.h"
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

bool it_802E5AC4(Item_GObj* item_gobj, bool arg_check)
{
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Item* item;
    f32 temp_f1;
    f32 temp_f1_10;
    f32 temp_f2;
    f32 vel_x;
    f32 vel_y;
    f32 var_f31;
    f32 var_f4;
    bool check1;
    bool check2;
    CollData* coll_data;
    ItemAttr* comm_attr;
    it_2E5A_DatAttrs_1* spec_attr;
    PAD_STACK(4);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    coll_data = &item->x378_itemColl;
    comm_attr = item->xCC_item_attr;
    spec_attr = item->xC4_article_data->x4_specialAttributes;
    it_80276214(item_gobj);
    temp_f1 = coll_data->cur_pos.y;
    coll_data->cur_pos.y = temp_f1 - item->xC1C.bottom;
    check1 = mpColl_80048844(coll_data, temp_f1);
    coll_data->cur_pos.y = coll_data->cur_pos.y + item->xC1C.bottom;
    item->pos = coll_data->cur_pos;

    // Rounds item velocities to 0 if they are close to it
    if (check1 && arg_check) {
        vel_x = item->x40_vel.x;
        if (item->x40_vel.x < 0.0f) {
            vel_x = -vel_x;
        }
        if (vel_x <= 0.00001f) {
            item->x40_vel.x = 0.0f;
        }
        vel_y = item->x40_vel.y;
        if (vel_y < 0.0f) {
            vel_y = -vel_y;
        }
        if (vel_y <= 0.00001f) {
            item->x40_vel.y = 0.0f;
        }
        vel_x = item->x40_vel.x;
        if (vel_x < 0.0f) {
            vel_x = -vel_x;
        }
        temp_f2 = comm_attr->x5c;
        if (vel_x <= temp_f2) {
            vel_y = item->x40_vel.y;
            if (vel_y < 0.0f) {
                vel_y = -vel_y;
            }
            if (!(vel_y <= temp_f2)) {
                goto block_16;
            }
            goto block_18;
        }
    block_16:
        if (item->xDCD_flag.b4 || (comm_attr->x58 == 0.0f)) {
        block_18:
            item->x40_vel.z = 0.0f;
            item->x40_vel.y = 0.0f;
            item->x40_vel.x = 0.0f;
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
                var_f4 = sqrtf(SQ(sp28.x) + SQ(sp28.y) + SQ(sp28.z));

                if (var_f4 < 0.01f) {
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
                item->xD84 = spec_attr->x4C; // or spec_attr[1]->x20
            }
            item->x40_vel.x *= spec_attr->x14; // or spec_attr[0]->x14
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
    // HSD_GObj* it_802E5EF4(Item_GObj* item_gobj) {
    return GET_ITEM((HSD_GObj*) item_gobj)->xDD4_itemVar.it_2E5A.x0;
}

void it_802E5F00(Item_GObj* item_gobj, Vec3* pos, Vec3* vel, s32 arg3)
{
    // void it_802E5F00(Item_GObj* parent_gobj1, Item_GObj* parent_gobj2, Vec3*
    // pos, Vec3* vel, s32 arg3) {
    it_802E5FXX_struct vars;
    SpawnItem sp1C;
    f32 unused1;

    it_802E614C(NULL, item_gobj, &sp1C, pos, vel);
    // sp68 = item_gobj;
    // sp6C = 0.0f;
    // sp70 = 0.0f;
    // sp74 = arg3;
    // sp78 = 0;
    // sp7C = 1;
    // sp54 = -1.0f;
    // sp80 = 0;
    vars.x0 = (HSD_GObj*) item_gobj;
    vars.x4 = 0.0f;
    vars.x8 = 0.0f;
    vars.xC = arg3;
    vars.x10 = 0;
    vars.x14 = 1;
    sp1C.facing_dir = -1.0f;
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
    it_802E614C(NULL, item_gobj, &sp2C, pos, &vel);
    angle = M_PI_2 + arg4;
    while (angle < 0.0f) {
        angle += 2 * M_PI;
    }
    while (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    if (angle > M_PI) {
        dir = -1.0f;
    } else {
        dir = 1.0f;
    }
    // sp78 = item_gobj;
    // sp7C = angle;
    // sp80 = arg5;
    // sp84 = arg2;
    // sp88 = 1;
    // sp64 = dir;
    // sp8C = arg3;
    vars.x0 = (HSD_GObj*) item_gobj;
    vars.x4 = angle;
    vars.x8 = arg5;
    vars.xC = arg2;
    vars.x10 = 1;
    sp2C.facing_dir = dir;
    vars.x14 = arg3;
    vars.x18 = gm_8016C6C0(item_gobj);
    return it_802E609C(&vars, &sp2C);
}

// s32 it_802E609C(Fighter* fighter, SpawnItem* spawn) {
s32 it_802E609C(it_802E5FXX_struct* vars, SpawnItem* spawn)
{
    Item_GObj* spawn_gobj;
    s32 temp_r3_2;
    s32 var_r30;
    s32 var_r29 = 0;

    // var_r30 = saved_reg_r30;
    // var_r30 = 0;
    // var_r29 = 0;
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
            db_80225DD8(spawn_gobj, (Fighter_GObj*) vars->x0);
            it_802750F8(spawn_gobj);
        }
        // goto loop_6;
    }
    return var_r30;
}

// void it_802E614C(Item_GObj* arg0, Item_GObj* arg1, Vec3* arg2, f32* arg3,
// void* arg4) {
inline void it_802E614C(Item_GObj* parent_gobj1, Item_GObj* parent_gobj2,
                        SpawnItem* spawn, Vec3* pos, Vec3* vel)
{
    spawn->kind = It_Kind_Unk4;
    spawn->prev_pos = *pos;
    spawn->pos = spawn->prev_pos;
    spawn->x3C_damage = 0;
    spawn->vel = *vel;
    spawn->x0_parent_gobj = (HSD_GObj*) parent_gobj1;
    spawn->x4_parent_gobj2 = (HSD_GObj*) parent_gobj2;
    spawn->x44_flag.b0 = 1;
    spawn->x40 = 0;
}

s32 it_802E61C4(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    // s32 it_802E61C4(SpawnItem* spawn, s32 arg1, s32 arg2) {
    f32 temp_r29;
    s32 var_r29;
    // it_2E5A_DatAttrs_1* attr;
    it_2E5A_DatAttrs_2* attr;
    Item* item;
    // void* temp_r3;
    // f32 temp_f0;
    // u32 num;
    // s32 temp_r0;

    s32 unused1;
    s32 unused2;
    // s32 unused3;
    // s32 unused4;
    f64 unused5;
    // PAD_STACK(10);

    // temp_r30 = arg0->user_data->xC4_article_data->x4_specialAttributes;
    // temp_r29 = (s32) ((f32) arg1 * (attr[arg2 * 4 + 1]->x0);
    // var_r29 = (s32) ((f32) temp_r29 * ((0.01f * (temp_r30->unk24 *
    // HSD_Randf())) + 1.0f));

    // num = arg2 * 4;
    // temp_r29 = arg2 * 4;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    attr = item->xC4_article_data->x4_specialAttributes;

    // temp_r29 = arg1 * attr[arg2 * 4 + 1].x0;
    // var_r29 = temp_r29 * ((0.01f * (attr->x24 * HSD_Randf())) + 1.0f);
    var_r29 = arg1 * attr[arg2 * 4 + 1].x0 *
              ((0.01f * (attr->x24 * HSD_Randf())) + 1.0f);

    // item = &attr + arg2 * 4;
    // temp_f0 = attr->x2C;
    // temp_f0 = (float) ((HSD_GObj*) item)->x2C;
    // temp_f0 = (float) ((it_2E5A_ItemVars*) item)->x2C;
    // temp_r0 = arg2 * 4;
    // temp_f0 *= 4;
    // temp_f0 += temp_r0;
    // temp_f0 += arg2 * 4;
    // temp_r29 = temp_f0;
    // temp_r29 = (s32) ((f32) arg1 * (attr + (arg2 * 4))->unk2C);
    // temp_r29 = (arg1 * (attr + (arg2 * 4)));
    // num = arg2 * 4;
    // // temp_r29 = arg1 * attr[num].x2C->top;
    // temp_r29 = arg1 * attr[num + 1].x0;
    // // var_r29 = (temp_f0 * ((0.01f * (attr->x24 * HSD_Randf())) + 1.0f));
    // var_r29 = (temp_r29 * ((0.01f * (attr->x24 * HSD_Randf())) + 1.0f));
    if (var_r29 < 1) {
        var_r29 = 1;
        // var_r29 = true;
    }
    return var_r29;
}

// void it_802E628C(Item_GObj* item_gobj, f64 arg8, f32 arg9) {
void it_802E628C(Item_GObj* item_gobj, f32 arg8, f32 arg9)
{
    Item* item;
    f32 temp_f31;
    f32 temp_f2;
    f32 temp_f1;
    f32 temp_f0;
    f32 var_f30;
    it_2E5A_DatAttrs_1* attr;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    attr = item->xC4_article_data->x4_specialAttributes;
    temp_f31 = HSD_Randf();
    temp_f1 = M_PI_2;
    temp_f2 = attr->xC;
    temp_f0 = M_PI_3;
    temp_f1 = arg8 - M_PI_2;
    // var_f30 = temp_f31 * attr->xC * item->facing_dir;
    var_f30 = temp_f31 * temp_f2;
    var_f30 *= item->facing_dir;
    if (((arg8 >= M_PI_3) && (arg8 <= 2 * M_PI_3)) ||
        ((arg8 >= 2 * M_PI_3) && (arg8 <= 5 * M_PI_3)))
    {
        var_f30 += attr->x10 * cosf((temp_f1));
    }
    item->x40_vel.x = var_f30;
    temp_f0 = attr->x20;
    temp_f1 = attr->x18;
    temp_f0 = temp_f31 * temp_f0;
    temp_f0 += arg9;
    temp_f1 += temp_f0;
    // item->x40_vel.y = temp_f31 * attr->x20 + arg9 + attr->x18;
    item->x40_vel.y = temp_f1;
    item->x40_vel.z = 0.0f;
}

s32 it_802E6380(Item_GObj* item_gobj, it_802E5FXX_struct* arg1)
{
    // Item* temp_r30_2;
    // s32 temp_r25;
    // s32 temp_r26;
    // s32 temp_r4;
    // u8 temp_r0;
    // it_2E5A_DatAttrs_1* attr;
    Item* item;
    s32 var_r31;
    it_2E5A_DatAttrs_2* attr;
    it_2E5A_ItemVars_struct* temp_r29_2;

    // it_2E5A_DatAttrs_2* temp_r4_2;
    // void* temp_r5;
    // u32 num;
    PAD_STACK(14);

    var_r31 = 2;
    item = item_gobj->user_data;
    // temp_r4 = arg1->xC;
    attr = item->xC4_article_data->x4_specialAttributes;
    // if (arg1->xC < attr->xA8) {
    if (arg1->xC < attr[3].x24) {
        var_r31 = 1;
        // if (arg1->xC < (s32) (attr + 0x58)->unk24) {
        if (arg1->xC < attr[2].x24) {
            var_r31 = 0;
        }
    }
    // temp_r26 = var_r31 * 0x2C;
    item->xDD4_itemVar.it_2E5A.x4 = var_r31;
    // temp_r4_2 = attr[var_r31];

    // arg1->xC -= attr[var_r31 + 1].x50;
    arg1->xC -= attr[var_r31 + 1].x24;

    // item->xDD4_itemVar.it_2E5A.x0 = attr[var_r31].x50;
    item->xDD4_itemVar.it_2E5A.x0 = attr[var_r31 + 1].x24;

    if (arg1->x10 == 1) {
        arg1->x8 *= attr->x1C;
        it_802E628C(item_gobj, arg1->x4, arg1->x8);
    }
    it_80275158(item_gobj, attr->x0);
    // temp_r25 = var_r31 * 0x2C;
    item->xDD4_itemVar.it_2E5A.x10 = attr->x4;
    // temp_r5 = attr + temp_r26;
    item->xDD4_itemVar.it_2E5A.x14 = attr->x8;
    item->xDD4_itemVar.it_2E5A.x8 = arg1->x14;
    item->xDCD_flag.b01 |= 2;

    // item->xD84 = temp_r5->unk4C;
    // item->xD84 = attr[var_r31].x4C;
    item->xD84 = attr[var_r31 + 1].x20;

    // item->scl = attr[var_r31]->unk54;
    // item->scl = attr[var_r31].x54;
    item->scl = attr[var_r31 + 1].x28;

    // it_80273318(item_gobj, (attr + temp_r25)->unk3C, (s32) temp_r5);
    // it_80273318(item_gobj, attr[var_r31].x3C, var_r31);
    // it_80273318(item_gobj, attr[var_r31].x3C, (s32) &attr[var_r31]);
    it_80273318(item_gobj, attr[var_r31].x10, (s32) &attr[var_r31]);

    // it_80275D5C(item_gobj, attr + (temp_r25 + 0x58));
    // it_80275D5C(item_gobj, attr[var_r31].x58);
    // it_80275D5C(item_gobj, attr[var_r31 + 1].x2C);
    it_80275D5C(item_gobj, (itECB*) &attr[var_r31 + 2].x0);

    // item->xC0C.top = item->xC1C.top;
    // item->xC0C.bottom = item->xC1C.bottom;
    // item->xC0C.right = item->xC1C.right;
    // item->xC0C.left = item->xC1C.left;
    item->xC0C = item->xC1C;

    item->xC1C.bottom *= item->scl;
    item->xDD4_itemVar.it_2E5A.xC = 0;
    item = item_gobj->user_data;

    // temp_r0 = item->xDD4_itemVar.it_2E5A.x18 & ~0x40;
    // temp_r0 = item->xDD4_itemVar.it_2E5A.x18.b0 & ~0x40;
    // item->xDD4_itemVar.it_2E5A.x18.b0 = temp_r0;
    item->xDD4_itemVar.it_2E5A.x18.b1 = 0;
    // temp_r0 = item->xDD4_itemVar.it_2E5A.x18.b1;

    // item->xDD4_itemVar.it_2E5A.x18.b0 = (item->xDD4_itemVar.it_2E5A.x18.b0 &
    // ~0x80) | ((((temp_r0 >> 6U) & 1) << 7) & 0x80);
    // item->xDD4_itemVar.it_2E5A.x18.b0 = (item->xDD4_itemVar.it_2E5A.x18.b0 &
    // ~0x80) | (temp_r0 & 0x80); item->xDD4_itemVar.it_2E5A.x18.b0 =
    // item->xDD4_itemVar.it_2E5A.x18.b0 | item->xDD4_itemVar.it_2E5A.x18.b1;
    item->xDD4_itemVar.it_2E5A.x18.b0 = item->xDD4_itemVar.it_2E5A.x18.b1 | 1;

    if (item->xDD4_itemVar.it_2E5A.x8 != 0) {
        temp_r29_2 = item->xDD4_itemVar.it_2E5A.x1C;
        item->xDD4_itemVar.it_2E5A.x1C->x4 = item_gobj->hsd_obj;
        item->xDD4_itemVar.it_2E5A.x1C->x0 =
            (0.003906f * ((it_2E5A_DatAttrs_2*)
                              item->xC4_article_data->x4_specialAttributes)
                             ->x28) /
            item->scl;
        item->x3C = item->xDD4_itemVar.it_2E5A.x1C->x0;
        lb_8000B1CC(item->xDD4_itemVar.it_2E5A.x1C->x4, NULL,
                    (Vec3*) &temp_r29_2->x8);
        temp_r29_2->x14 = temp_r29_2->x8;
        if (db_ShowCoinPickupRange() != 0) {
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

    item = GET_ITEM((HSD_GObj*) item_gobj);
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
    if ((u32) Item_804A0C64.x50 >= it_804D6D28->x20 - 2)
    { // HSD_ObjAllocUnk.x50 >= ItemCommonData->x20 - 2
        Item_8026A8EC((Item_GObj*) it_80272828(It_Kind_Unk4));
    }
}

void it_802E66A0(HSD_GObj* item_gobj)
{
    Item* item;
    HSD_JObj* item_jobj;
    // HSD_JObj* item_jobj2;
    // u32 num;
    // u32 index;
    // it_2E5A_DatAttrs_2* attr;
    PAD_STACK(30);

    item = item_gobj->user_data;
    if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
        if (item->xDD4_itemVar.it_2E5A.xC != 0) {
            // Item_80268E5C(item_gobj, 0, 0x11);
            Item_80268E5C(item_gobj, 0, ITEM_HIT_PRESERVE | ITEM_UNK_0x1);
        } else {
            Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
            item->xDD4_itemVar.it_2E5A.xC = 1;
            item = item_gobj->user_data;
            item_jobj = item_gobj->hsd_obj;
            // item->xD0_itemStateDesc = (ItemStateDesc* )
            // (item->xC4_article_data->x4_specialAttributes +
            // ((item->xDD4_itemVar.it_2E5A.x4 * 0x2C) + 0x40)); num =
            // item->xDD4_itemVar.it_2E5A.x4 + 1; // index = 0x14; (0x40 - 0x2C
            // = 0x14) attr = item->xC4_article_data->x4_specialAttributes;
            // item->xD0_itemStateDesc = attr[num].x14;
            item->xD0_itemStateDesc =
                ((it_2E5A_DatAttrs_2*) item->xC4_article_data
                     ->x4_specialAttributes)[item->xDD4_itemVar.it_2E5A.x4 + 1]
                    .x14; // index = 0x14; (0x40 - 0x2C = 0x14)

            Item_80268D34(item_gobj, item->xD0_itemStateDesc);
            HSD_JObjAnimAll(item_jobj);
            // HSD_JObjAnimAll(item_gobj->hsd_obj);
        }
        item->on_accessory = it_802E6A74;
        return;
    }
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    // item->xD0_itemStateDesc = (ItemStateDesc* )
    // (item->xC4_article_data->x4_specialAttributes +
    // ((item->xDD4_itemVar.it_2E5A.x4 * 0x2C) + 0x40)); num =
    // item->xDD4_itemVar.it_2E5A.x4 + 1; // index = 0x14; (0x40 - 0x2C = 0x14)
    item->xD0_itemStateDesc =
        ((it_2E5A_DatAttrs_2*) item->xC4_article_data
             ->x4_specialAttributes)[item->xDD4_itemVar.it_2E5A.x4 + 1]
            .x14; // index = 0x14; (0x40 - 0x2C = 0x14)
    Item_80268D34(item_gobj, item->xD0_itemStateDesc);
    HSD_JObjAnimAll(item_jobj);
    // HSD_JObjAnimAll(item_gobj->hsd_obj);
}

bool it_2E5A_UnkMotion1_Anim(HSD_GObj* item_gobj)
{
    f32 var_f2;
    Item* item;

    item = GET_ITEM(item_gobj);
    var_f2 = item->x40_vel.y;
    if (var_f2 < 0.0f) {
        var_f2 = -var_f2;
    }
    item->x5D0_animFrameSpeed = (0.1 * var_f2) + 1.0;
    return it_802E657C((Item_GObj*) item_gobj);
}

void it_2E5A_UnkMotion1_Phys(HSD_GObj* item_gobj)
{
    ItemAttr* comm_attr;

    comm_attr = GET_ITEM(item_gobj)->xCC_item_attr;
    it_80272860((Item_GObj*) item_gobj, comm_attr->x10_fall_speed,
                comm_attr->x14_fall_speed_max);
}

bool it_2E5A_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(10);

    item = GET_ITEM(item_gobj);
    if (it_802E5AC4((Item_GObj*) item_gobj, 1)) {
        it_802E6888(item_gobj);
        item->xD50_landNum = 0;
        item->xDCF_flag.b0 = 0;
    }
    return false;
}

void it_802E6888(HSD_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    item->x5D0_animFrameSpeed = 1.0f;
    Item_80268E5C(item_gobj, 2, ITEM_HIT_PRESERVE | ITEM_UNK_0x1);
    if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
        item->on_accessory = it_802E6A74;
    }
}

bool it_2E5A_UnkMotion2_Anim(HSD_GObj* item_gobj)
{
    return it_802E657C((Item_GObj*) item_gobj);
}

void it_2E5A_UnkMotion2_Phys(HSD_GObj* item_gobj) {}

bool it_2E5A_UnkMotion2_Coll(HSD_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(54);

    item = item_gobj->user_data;
    if ((item->xDD4_itemVar.it_2E5A.x8 == 1) &&
        !(it_802E5AC4((Item_GObj*) item_gobj, 0)))
    {
        item = item_gobj->user_data;
        if (item->xDD4_itemVar.it_2E5A.x8 == 1) {
            if (item->xDD4_itemVar.it_2E5A.xC) {
                Item_80268E5C(item_gobj, 0, ITEM_HIT_PRESERVE | ITEM_UNK_0x1);
            } else {
                Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
                item->xDD4_itemVar.it_2E5A.xC = 1;
                item = item_gobj->user_data;
                item_jobj = item_gobj->hsd_obj;
                // item->xD0_itemStateDesc =
                // item->xC4_article_data->x4_specialAttributes + (((s32)
                // item->xDD4_itemVar.it_2E5A.x4 * 0x2C) + 0x40);
                item->xD0_itemStateDesc =
                    ((it_2E5A_DatAttrs_2*)
                         item->xC4_article_data->x4_specialAttributes)
                        [item->xDD4_itemVar.it_2E5A.x4 + 1]
                            .x14; // index = 0x14; (0x40 - 0x2C = 0x14)
                Item_80268D34(item_gobj, item->xD0_itemStateDesc);
                HSD_JObjAnimAll(item_jobj);
            }
            item->on_accessory = it_802E6A74;
        } else {
            Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
            item = item_gobj->user_data;
            item_jobj = item_gobj->hsd_obj;
            // item->xD0_itemStateDesc =
            // item->xC4_article_data->x4_specialAttributes + (((s32)
            // item->xDD4_itemVar.it_2E5A.x4 * 0x2C) + 0x40);
            item->xD0_itemStateDesc =
                ((it_2E5A_DatAttrs_2*) item->xC4_article_data
                     ->x4_specialAttributes)[item->xDD4_itemVar.it_2E5A.x4 + 1]
                    .x14; // index = 0x14; (0x40 - 0x2C = 0x14)
            Item_80268D34(item_gobj, item->xD0_itemStateDesc);
            HSD_JObjAnimAll(item_jobj);
        }
    }
    return false;
}

bool it_2725_Logic115_DmgDealt(Item_GObj* item_gobj)
{
    lbAudioAx_80023870(0x93, 0x7F, 0x40, 0x1A);
    return true;
}

void it_802E6A74(HSD_GObj* gobj)
{
    Item* item;
    // Vec3* temp_r3;
    it_2E5A_ItemVars_struct* temp_r6;

    item = gobj->user_data;
    if (item->xDD4_itemVar.it_2E5A.x8) {
        temp_r6 = item->xDD4_itemVar.it_2E5A.x1C;
        // temp_r3 = &item->xDD4_itemVar.it_2E5A.x1C->x8;
        // temp_r6->x14 = *temp_r3;
        // lb_8000B1CC(temp_r6->x4, NULL, temp_r3);
        temp_r6->x14 = temp_r6->x8;
        lb_8000B1CC(temp_r6->x4, NULL, &temp_r6->x8);
    }
}

void it_2725_Logic115_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
