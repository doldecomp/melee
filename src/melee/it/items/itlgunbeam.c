#include "itlgunbeam.h"

#include "db/db_2253.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/types.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>

UNK_RET it_80272940(Item_GObj*);              /* extern */
void it_802998A0(Item_GObj*, HSD_GObj*, s32); /* static */
int it_8029999C(HSD_GObj*);                   /* static */
void it_802999E4(HSD_GObj*);                  /* static */
int it_80299A68(HSD_GObj*);                   /* static */

static f32 it_804DCC20 = 0.0f;
static double it_804DCC28 = 2 * M_PI;
static double it_804DCC30 = -M_PI;
static double it_804DCC38 = M_PI;
static double it_804DCC40 = M_PI_2;
static double it_804DCC48 = 0.02;
static double it_804DCC50 = 0.5;
static f32 it_804DCC58 = 1.0f;
static f32 it_804DCC5C = 3.0f;

ItemStateTable it_803F6630[1] = {
    { 0, it_8029999C, it_802999E4, it_80299A68 },
};

void it_802993E0(Item_GObj* item_gobj, s32 arg1)
{
    // f32 sp1C;
    // f32 sp18;
    // f32 sp14;
    Vec3 pos;
    Item* item;

    item = item_gobj->user_data;
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    // sp14 = 0.0f;
    // sp18 = 0.0f;
    // sp1C = 0.0f;
loop_2:
    if (item->xDD4_itemVar.lgunbeam.angle0 < -3.141592653589793) {
        item->xDD4_itemVar.lgunbeam.angle0 =
            item->xDD4_itemVar.lgunbeam.angle0 + 6.283185307179586;
        goto loop_2;
    }
loop_5:
    if (item->xDD4_itemVar.lgunbeam.angle0 > 3.141592653589793) {
        item->xDD4_itemVar.lgunbeam.angle0 =
            item->xDD4_itemVar.lgunbeam.angle0 - 6.283185307179586;
        goto loop_5;
    }
#if 0
    switch (arg1) {
    case 1:
        pos.x += item->x378_itemColl.floor.normal.x;
        pos.y += item->x378_itemColl.floor.normal.y;
    case 2:
        pos.x += item->x378_itemColl.ceiling.normal.x;
        pos.y += item->x378_itemColl.ceiling.normal.y;
    case 4:
        pos.x += item->x378_itemColl.right_wall.normal.x;
        pos.y += item->x378_itemColl.right_wall.normal.y;
    case 8:
        pos.x += item->x378_itemColl.left_wall.normal.x;
        pos.y += item->x378_itemColl.left_wall.normal.y;
    }
    lbVector_Normalize(&pos);
    item->xDD4_itemVar.lgunbeam.xDE0.x = pos.x;
    item->xDD4_itemVar.lgunbeam.xDE0.y = pos.y;
    item->xDD4_itemVar.lgunbeam.xDE0.z = pos.z;
#elif 1
    if (arg1 & 1) {
        pos.x += item->x378_itemColl.floor.normal.x;
        pos.y += item->x378_itemColl.floor.normal.y;
        // sp14 += item->x378_itemColl.floor.normal.x;
        // sp18 += item->x378_itemColl.floor.normal.y;
    }
    if (arg1 & 2) {
        pos.x += item->x378_itemColl.ceiling.normal.x;
        pos.y += item->x378_itemColl.ceiling.normal.y;
        // sp14 += item->x378_itemColl.ceiling.normal.x;
        // sp18 += item->x378_itemColl.ceiling.normal.y;
    }
    if (arg1 & 4) {
        pos.x += item->x378_itemColl.right_wall.normal.x;
        pos.y += item->x378_itemColl.right_wall.normal.y;
        // sp14 += item->x378_itemColl.right_wall.normal.x;
        // sp18 += item->x378_itemColl.right_wall.normal.y;
    }
    if (arg1 & 8) {
        pos.x += item->x378_itemColl.left_wall.normal.x;
        pos.y += item->x378_itemColl.left_wall.normal.y;
        // sp14 += item->x378_itemColl.left_wall.normal.x;
        // sp18 += item->x378_itemColl.left_wall.normal.y;
    }
    lbVector_Normalize(&pos);
    item->xDD4_itemVar.lgunbeam.position1.x = pos.x;
    item->xDD4_itemVar.lgunbeam.position1.y = pos.y;
    item->xDD4_itemVar.lgunbeam.position1.z = pos.z;
#else
    if (arg1 & 1) {
        sp14 += item->x378_itemColl.floor.normal.x;
        sp18 += item->x378_itemColl.floor.normal.y;
    }
    if (arg1 & 2) {
        sp14 += item->x378_itemColl.ceiling.normal.x;
        sp18 += item->x378_itemColl.ceiling.normal.y;
    }
    if (arg1 & 4) {
        sp14 += item->x378_itemColl.right_wall.normal.x;
        sp18 += item->x378_itemColl.right_wall.normal.y;
    }
    if (arg1 & 8) {
        sp14 += item->x378_itemColl.left_wall.normal.x;
        sp18 += item->x378_itemColl.left_wall.normal.y;
    }
    lbVector_Normalize((Vec3*) &sp14);
    item->xDD4_itemVar.lgunbeam.xDE0.x = sp14;
    item->xDD4_itemVar.lgunbeam.xDE0.y = sp18;
    item->xDD4_itemVar.lgunbeam.xDE0.z = sp1C;
#endif
}

void it_80299528(Item_GObj* item_gobj, s32 arg1)
{
    Item* item;
    f32 temp_f1;
    f32 temp_f31;
    f32 var_f0;
    f32 var_f1;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f31;
    f32 var_f3;
    f32 var_f3_2;

    item = item_gobj->user_data;
    if (arg1 != 0) {
        temp_f31 = atan2f(item->xDD4_itemVar.lgunbeam.position1.x,
                          item->xDD4_itemVar.lgunbeam.position1.y);
        var_f31 = atan2f(item->xDD4_itemVar.lgunbeam.position2.x,
                         item->xDD4_itemVar.lgunbeam.position2.y) -
                  temp_f31;
    loop_3:
        if (var_f31 > 3.141592653589793) {
            var_f31 = var_f31 - 6.283185307179586;
            goto loop_3;
        }
    loop_6:
        if (var_f31 < -3.141592653589793) {
            var_f31 = var_f31 + 6.283185307179586;
            goto loop_6;
        }
        if (var_f31 == 0.0f) {
            var_f1 = 0.0f;
        } else {
            temp_f1 = lbVector_Angle(&item->xDD4_itemVar.lgunbeam.position1,
                                     &item->xDD4_itemVar.lgunbeam.position2);
            if (var_f31 < 0.0f) {
                var_f2 = -var_f31;
            } else {
                var_f2 = var_f31;
            }
            if (var_f2 < 1.5707963267948966) {
                if (var_f31 < 0.0f) {
                    var_f3 = -var_f31;
                } else {
                    var_f3 = var_f31;
                }
                var_f2_2 =
                    (0.019999999552965164 * (var_f3 / 3.141592653589793));
            } else {
                if (var_f31 < 0.0f) {
                    var_f3_2 = -var_f31;
                } else {
                    var_f3_2 = var_f31;
                }
                var_f2_2 = (0.5 * (var_f3_2 / 3.141592653589793));
            }
            if (var_f31 < 0.0f) {
                var_f0 = -var_f2_2;
            } else {
                var_f0 = var_f2_2;
            }
            var_f1 = temp_f1 * var_f0;
        }
        item->xDD4_itemVar.lgunbeam.angle0 -= var_f1;
    loop_27:
        if (item->xDD4_itemVar.lgunbeam.angle0 < -3.141592653589793) {
            item->xDD4_itemVar.lgunbeam.angle0 =
                item->xDD4_itemVar.lgunbeam.angle0 + 6.283185307179586;
            goto loop_27;
        }
    loop_30:
        if (item->xDD4_itemVar.lgunbeam.angle0 > 3.141592653589793) {
            item->xDD4_itemVar.lgunbeam.angle0 =
                item->xDD4_itemVar.lgunbeam.angle0 - 6.283185307179586;
            goto loop_30;
        }
    }
}

void it_802996D0(HSD_GObj* owner_gobj, Vec3* pos, u32 arg2, f32 dir)
{
    // u8 sp64;
    // u32 sp60;
    // s16 sp5C;
    // f32 sp58;
    // f32 sp54;
    // f32 sp50;
    // f32 sp4C;
    // f32 sp48;
    // s32 sp44;
    // s32 sp40;
    // Vec3 sp34;
    // s32 sp28;
    // HSD_GObj* sp24;
    // HSD_GObj* sp20;
    Item* item;
    Item_GObj* item_gobj;
    SpawnItem spawn;
    f32 unused1;
    f32 unused2;
    // f32 temp_f2_2;
    f32 var_f0;
    ItLGunBeamAttr* item_spec_attr;

    spawn.kind = 0x27;
    spawn.prev_pos = *pos;
    // spawn.prev_pos.x = pos->x;
    // spawn.prev_pos.y = pos->y;
    // spawn.prev_pos.z = pos->z;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68((Item_GObj*) owner_gobj, &spawn.pos);
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = owner_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    // sp64 |= 0x80;
    spawn.x40 = arg2;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        item_spec_attr = item->xC4_article_data->x4_specialAttributes;
        item->xDB8_itcmd_var3 = 0;
        item->xDB4_itcmd_var2 = 0;
        item->xDB0_itcmd_var1 = 0;
        item->xDAC_itcmd_var0 = 0;
        item->xDD4_itemVar.lgunbeam.lifetime = item_spec_attr->x0;
        it_80275158((HSD_GObj*) item_gobj, item_spec_attr->x0);
        item->xDD4_itemVar.lgunbeam.position0 = *pos;
        item->xDD4_itemVar.lgunbeam.angle1 =
            ((item_spec_attr->x8 - item_spec_attr->x4) * HSD_Randf()) +
            item_spec_attr->x4;
        item->xDD4_itemVar.lgunbeam.angle0 =
            ((item_spec_attr->x10 - item_spec_attr->xC) * HSD_Randf()) +
            item_spec_attr->xC;
        // var_f0 = item->xDD4_itemVar.lgunbeam.xDF8;
        if (item->facing_dir == 1.0f) {
            var_f0 = item->xDD4_itemVar.lgunbeam.angle0;
        } else {
            var_f0 = -item->xDD4_itemVar.lgunbeam.angle0;
        }
        item->xDD4_itemVar.lgunbeam.angle0 = var_f0;
    loop_6:
        if (item->xDD4_itemVar.lgunbeam.angle0 < -3.141592653589793) {
            item->xDD4_itemVar.lgunbeam.angle0 =
                item->xDD4_itemVar.lgunbeam.angle0 + 6.283185307179586;
            goto loop_6;
        }
    loop_9:
        if (item->xDD4_itemVar.lgunbeam.angle0 > 3.141592653589793) {
            item->xDD4_itemVar.lgunbeam.angle0 =
                item->xDD4_itemVar.lgunbeam.angle0 - 6.283185307179586;
            goto loop_9;
        }
        item->xDD4_itemVar.lgunbeam.xE04 = 0.0f;
        // item->xDCC_flag = (u8) (item->xDCC_flag & ~0x10);
        item->xDCC_flag.b1 = 1;

        it_802998A0(item_gobj, owner_gobj, HSD_Randi(4));
    }
}

void it_802998A0(Item_GObj* item_gobj, HSD_GObj* fighter_gobj, s32 arg2)
{
    f32 sp2C;
    Vec3 pos;
    HSD_JObj* item_jobj;
    Item* item;
    f32 temp_f1;
    f32 unused1;
    f32 unused2;
    f32 unused3;

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    sp2C = 1.0f;
    it_8026B3A8(item_gobj);
    // item->unkDCA = item->unkDCA & ~0x10;
    item->xDC8_word.flags.x3 = 0;
    it_80272940(item_gobj);
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
    pos = item->pos;
    Item_802694CC((HSD_GObj*) item_gobj);
    it_802999E4((HSD_GObj*) item_gobj);
    item->pos.x -= item->x40_vel.x;
    item->pos.y -= item->x40_vel.y;
    temp_f1 = it_8026D9A0(item_gobj);
    // item->pos = pos;
    // item->pos.x = sp30;
    // item->pos.y = temp_r0;
    // item->pos.z = temp_r0_2;
    // efSync_Spawn(arg2 + 0x44E, item_gobj, item_jobj, item->0x2C, &sp2C,
    // temp_f1); efSync_Spawn(arg2 + 0x44E, item_gobj, item_jobj,
    // item->facing_dir, pos, &sp2C);
    efSync_Spawn(arg2 + 0x44E, item_gobj, item_jobj, item->facing_dir,
                 item->pos, &sp2C);
    db_80225DD8(item_gobj, (Fighter_GObj*) fighter_gobj);
}

int it_8029999C(HSD_GObj* item_gobj)
{
    f32 unused1;
    f32 unused2;
    f32 unused3;
    f32 unused4;

    if (it_80273130((Item_GObj*) item_gobj) == 1) {
        efLib_DestroyAll((HSD_GObj*) item_gobj);
        return 1;
    }
    return 0;
}

void it_802999E4(HSD_GObj* item_gobj)
{
    Item* item;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 unused1;
    f32 unused2;

    item = item_gobj->user_data;
    item->xDD4_itemVar.lgunbeam.position0 = item->pos;
    temp_f0 = item->xDD4_itemVar.lgunbeam.angle1 *
              sinf(item->xDD4_itemVar.lgunbeam.angle0);
    item->x40_vel.x = temp_f0;
    // item->xDD4_itemVar.lgunbeam.xDEC = temp_f0;
    item->xDD4_itemVar.lgunbeam.position2.x = temp_f0;
    temp_f0_2 = item->xDD4_itemVar.lgunbeam.angle1 *
                cosf(item->xDD4_itemVar.lgunbeam.angle0);
    item->x40_vel.y = temp_f0_2;
    item->xDD4_itemVar.lgunbeam.position2.y = temp_f0_2;
    item->x40_vel.z = 0.0f;
    item->xDD4_itemVar.lgunbeam.position2.z = 0.0f;
    lbVector_Normalize(&item->xDD4_itemVar.lgunbeam.position2);
}

int it_80299A68(HSD_GObj* item_gobj)
{
    Item* item;
    s32 temp_r3;
    s32 var_r31;

    item = item_gobj->user_data;
loop_2:
    if (item->xDD4_itemVar.lgunbeam.angle0 < -3.141592653589793) {
        item->xDD4_itemVar.lgunbeam.angle0 =
            item->xDD4_itemVar.lgunbeam.angle0 + 6.283185307179586;
        goto loop_2;
    }
loop_5:
    if (item->xDD4_itemVar.lgunbeam.angle0 > 3.141592653589793) {
        item->xDD4_itemVar.lgunbeam.angle0 =
            item->xDD4_itemVar.lgunbeam.angle0 - 6.283185307179586;
        goto loop_5;
    }
    var_r31 = 0;
    // item->x378_itemColl.x108_joint = 3.0f;
    // item->x378_itemColl.x10C_joint[0] = 3.0f;
    // item->x378_itemColl.x10C_joint[1] = 3.0f;
    // item->x378_itemColl.x10C_joint[2] = 3.0f;
    item->x378_itemColl.x108_f32 = 3.0f;
    item->x378_itemColl.x10C_f32 = 3.0f;
    item->x378_itemColl.x110_f32 = 3.0f;
    item->x378_itemColl.x114_f32 = 3.0f;
    it_8026D9A0((Item_GObj*) item_gobj);
    temp_r3 = item->x378_itemColl.env_flags;
    if (temp_r3 & 0x18000) {
        var_r31 = 1;
    }
    if (temp_r3 & 0x6000) {
        var_r31 |= 2;
    }
    if (temp_r3 & 0x3F) {
        var_r31 |= 4;
    }
    if (temp_r3 & 0xFC0) {
        var_r31 |= 8;
    }
    if (var_r31 != 0) {
        it_802993E0((Item_GObj*) item_gobj, var_r31);
        it_80299528((Item_GObj*) item_gobj, var_r31);
    }
    return 0;
}

int it_80299B6C(Item_GObj* item_gobj)
{
    return 0;
}

int it_80299B74(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD4_itemVar.lgunbeam.angle0 =
        item->xDD4_itemVar.lgunbeam.angle0 + 3.141592653589793;
loop_2:
    if (item->xDD4_itemVar.lgunbeam.angle0 < -3.141592653589793) {
        item->xDD4_itemVar.lgunbeam.angle0 =
            item->xDD4_itemVar.lgunbeam.angle0 + 6.283185307179586;
        goto loop_2;
    }
loop_5:
    if (item->xDD4_itemVar.lgunbeam.angle0 > 3.141592653589793) {
        item->xDD4_itemVar.lgunbeam.angle0 =
            item->xDD4_itemVar.lgunbeam.angle0 - 6.283185307179586;
        goto loop_5;
    }
    item->facing_dir = -item->facing_dir;
    item->x40_vel.x = -item->x40_vel.x;
    item->x40_vel.y = -item->x40_vel.y;
    return 0;
}

int it_80299C08(Item_GObj* item_gobj)
{
    return 1;
}

int it_80299C10(Item_GObj* item_gobj)
{
    return 0;
}

int it_80299C18(Item_GObj* item_gobj)
{
    return 1;
}

int it_80299C20(Item_GObj* item_gobj)
{
    return 1;
}

void it_80299C28(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
