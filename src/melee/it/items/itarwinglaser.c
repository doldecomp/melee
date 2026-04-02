#include "itarwinglaser.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/efsync.h"
#include "ft/ftlib.h"
#include "gr/grcorneria.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <trigf.h>
#include <MSL/math.h>
#include <baselib/jobj.h>

typedef struct ArwingLaserAttr {
    /* +0 */ ItemAttr* x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
} ArwingLaserAttr;

static void itArwinglaser_UnkMotion2_Anim(Item_GObj*);
static void itArwinglaser_UnkMotion3_Anim(Item_GObj*);
static void itArwinglaser_UnkMotion2_Phys(Item_GObj*);
static void itArwinglaser_UnkMotion3_Phys(Item_GObj*);
static bool itArwinglaser_UnkMotion2_Coll(Item_GObj*);
static bool itArwinglaser_UnkMotion3_Coll(Item_GObj*);
static bool itArwinglaser_UnkMotion5_Coll(Item_GObj*);

ItemStateTable it_803F8DE8[] = {
    { 0, (HSD_GObjPredicate) itArwinglaser_UnkMotion2_Anim,
      (HSD_GObjEvent) itArwinglaser_UnkMotion2_Phys,
      itArwinglaser_UnkMotion2_Coll },
    { 1, (HSD_GObjPredicate) itArwinglaser_UnkMotion3_Anim,
      (HSD_GObjEvent) itArwinglaser_UnkMotion3_Phys,
      itArwinglaser_UnkMotion3_Coll },
    { 2, (HSD_GObjPredicate) itArwinglaser_UnkMotion2_Anim,
      (HSD_GObjEvent) itArwinglaser_UnkMotion2_Phys,
      itArwinglaser_UnkMotion2_Coll },
    { 3, (HSD_GObjPredicate) itArwinglaser_UnkMotion3_Anim,
      (HSD_GObjEvent) itArwinglaser_UnkMotion3_Phys,
      itArwinglaser_UnkMotion3_Coll },
    { 4, NULL, NULL, itArwinglaser_UnkMotion5_Coll },
    { 5, NULL, NULL, itArwinglaser_UnkMotion5_Coll },
};

static Vec2 it_803F8E48[] = {
    { 0.0f, 200.0f },
    { 0.0f, -200.0f },
    { -200.0f, 0.0f },
    { 200.0f, 0.0f },
};

s32 it_802E70BC(Item_GObj* gobj)
{
    int sp44;
    u32 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);
    s32 hit_count;
    s32 i;
    Vec2* offsets;

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp10);
    sp28 = sp10;
    sp1C = ip->xDD4_itemVar.arwinglaser.xE18;
    sp1C.z = 0.0f;
    sp28.z = 0.0f;
    if (it_8026EA9C(gobj, &sp1C, &sp28, &sp34, &sp44, &sp40,
                    ip->xDD4_itemVar.arwinglaser.xE48) != 0)
    {
        mpGetSpeed(sp44, &ip->pos, &ip->x40_vel);
        return 1;
    }
    i = 0;
    offsets = it_803F8E48;
    hit_count = 0;
    for (i = 0; i < 4; i++) {
        sp1C = sp10;
        sp28 = sp1C;
        sp28.x += offsets->x;
        sp28.y += offsets->y;
        sp1C.z = 0.0f;
        sp28.z = 0.0f;
        if (it_8026EA9C(gobj, &sp1C, &sp28, &sp34, &sp44, &sp40,
                        ip->xDD4_itemVar.arwinglaser.xE48) != 0)
        {
            sp1C = sp10;
            sp1C.z = 0.0f;
            sp28.z = 0.0f;
            if (it_8026EA9C(gobj, &sp28, &sp1C, &sp34, &sp44, &sp40,
                            ip->xDD4_itemVar.arwinglaser.xE48) != 0 &&
                !(mpLineGetFlags(sp44) & 0x100))
            {
                hit_count++;
            }
        } else if (it_8026EA9C(gobj, &sp28, &sp1C, &sp34, &sp44, &sp40,
                                ip->xDD4_itemVar.arwinglaser.xE48) != 0 &&
                   !(mpLineGetFlags(sp44) & 0x100))
        {
            hit_count++;
        }
        offsets++;
    }
    if (hit_count != 0) {
        return 1;
    }
    return 0;
}

Item_GObj* it_802E72E0(Item_GObj* parent, HSD_JObj* bone, s32 type,
                       f32 scale, f32 scale_mult)
{
    SpawnItem spawn;
    Vec3 sp24;
    Item_GObj* new_gobj;

    lb_8000B1CC(bone, NULL, &sp24);
    switch (type) {
    case 2:
    case 0:
        sp24.z = 0.0f;
        break;
    case 4:
    case 5: {
        f32 z;
        if (type == 4) {
            z = sp24.z;
            if (z < 0.0f) {
                z = -z;
            }
        } else {
            z = sp24.z;
            if (z < 0.0f) {
                z = -z;
            }
            z = -z;
        }
        sp24.z = z;
        break;
    }
    }
    spawn.pos = sp24;
    spawn.prev_pos = sp24;
    spawn.kind = 0xEA;
    spawn.facing_dir = scale;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x44_flag.b0 = false;
    spawn.x40 = 0;
    new_gobj = Item_80268B18(&spawn);
    if (new_gobj != NULL) {
        Item* ip = GET_ITEM(new_gobj);
        HSD_JObj* jobj = GET_JOBJ(new_gobj);
        it_80275158(new_gobj, 300.0f);
        ip->xDD4_itemVar.arwinglaser.xE24 = sp24;
        ip->xDD4_itemVar.arwinglaser.xE18 =
            ip->xDD4_itemVar.arwinglaser.xE24;
        ip->xDD4_itemVar.arwinglaser.xE30 = 0;
        ip->xDD4_itemVar.arwinglaser.xDFC = Ground_801C0498();
        ip->xDD4_itemVar.arwinglaser.xDF4 = parent;
        ip->xDD4_itemVar.arwinglaser.xDF8 = bone;
        ip->xDD4_itemVar.arwinglaser.xE34 = scale_mult;
        ip->xDD4_itemVar.arwinglaser.xE38 = type;
        ip->xDD4_itemVar.arwinglaser.xE3C = 0;
        ip->xDD4_itemVar.arwinglaser.xE4C = 0;
        HSD_JObjSetRotationY(
            jobj,
            (f32) (1.5707963267948966 * (f64) ip->facing_dir));
        switch (ip->xDD4_itemVar.arwinglaser.xE38) {
        case 0:
        case 2:
            ip->xDD4_itemVar.arwinglaser.xE00 = 0.0f;
            ip->xDD4_itemVar.arwinglaser.xE04 = 0.0f;
            ip->xDD4_itemVar.arwinglaser.xE08 = 0.0f;
            it_802E7A4C(new_gobj);
            switch (ip->xDD4_itemVar.arwinglaser.xE38) {
            case 0:
                HSD_JObjSetFlagsAll(jobj, 0x10U);
                ip->xDD4_itemVar.arwinglaser.xE40 =
                    it_802E72E0(new_gobj, bone, 4, scale, scale_mult);
                ip->xDD4_itemVar.arwinglaser.xE44 =
                    it_802E72E0(new_gobj, bone, 5, scale, scale_mult);
                break;
            case 2:
                ip->xDD4_itemVar.arwinglaser.xE40 = NULL;
                ip->xDD4_itemVar.arwinglaser.xE44 = NULL;
                break;
            }
            break;
        case 4:
        case 5: {
            f32 z;
            ip->xDD4_itemVar.arwinglaser.xE40 = NULL;
            ip->xDD4_itemVar.arwinglaser.xE44 = NULL;
            ip->xDD4_itemVar.arwinglaser.xE00 = 0.0f;
            ip->xDD4_itemVar.arwinglaser.xE04 = 0.0f;
            if (ip->xDD4_itemVar.arwinglaser.xE38 == 4) {
                z = ip->pos.z;
                if (z < 0.0f) {
                    z = -z;
                }
            } else {
                z = ip->pos.z;
                if (z < 0.0f) {
                    z = -z;
                }
                z = -z;
            }
            ip->xDD4_itemVar.arwinglaser.xE08 = z;
            it_802E7A4C(new_gobj);
            break;
        }
        }
    }
    return new_gobj;
}

void it_802E7654(s32 owner, HSD_JObj* bone, Vec3* target, s32 type,
                 s32 arg4, f32 scale)
{
    SpawnItem spawn;
    Vec3 sp28;
    HSD_JObj* jobj;
    Item* ip;
    Item_GObj* new_gobj;
    f32 rot;

    lb_8000B1CC(bone, NULL, &sp28);
    spawn.kind = 0xEA;
    spawn.prev_pos = sp28;
    spawn.facing_dir = 0.0f;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x44_flag.b0 = false;
    spawn.x40 = 0;
    new_gobj = Item_80268B18(&spawn);
    if (new_gobj != NULL) {
        ip = GET_ITEM(new_gobj);
        jobj = GET_JOBJ(new_gobj);
        it_80275158(new_gobj, 400.0f);
        ip->xDD4_itemVar.arwinglaser.xE24 = sp28;
        ip->xDD4_itemVar.arwinglaser.xE18 = ip->xDD4_itemVar.arwinglaser.xE24;
        ip->xDD4_itemVar.arwinglaser.xE30 = 0;
        ip->xDD4_itemVar.arwinglaser.xDFC = Ground_801C0498();
        ip->xDD4_itemVar.arwinglaser.xDF4 = (Item_GObj*) (s32) owner;
        ip->xDD4_itemVar.arwinglaser.xDF8 = bone;
        ip->xDD4_itemVar.arwinglaser.xE34 = scale;
        ip->xDD4_itemVar.arwinglaser.xE38 = type;
        ip->xDD4_itemVar.arwinglaser.xE3C = 0;
        ip->xDD4_itemVar.arwinglaser.xE48 = arg4;
        ip->xDD4_itemVar.arwinglaser.xE4C = 0;
        ip->xDD4_itemVar.arwinglaser.xE0C.x = target->x - sp28.x;
        ip->xDD4_itemVar.arwinglaser.xE0C.y = target->y - sp28.y;
        ip->xDD4_itemVar.arwinglaser.xE0C.z = target->z - sp28.z;
        lbVector_Normalize(&ip->xDD4_itemVar.arwinglaser.xE0C);
        ip->facing_dir =
            (ip->xDD4_itemVar.arwinglaser.xE0C.x >= 0.0f) ? 1.0f : -1.0f;
        rot = -atan2f(ip->xDD4_itemVar.arwinglaser.xE0C.y,
                      ip->xDD4_itemVar.arwinglaser.xE0C.z);
        HSD_JObjSetRotationX(jobj, rot);
        rot = atan2f(ip->xDD4_itemVar.arwinglaser.xE0C.x,
                     ip->xDD4_itemVar.arwinglaser.xE0C.z);
        HSD_JObjSetRotationY(jobj, rot);
        HSD_JObjSetRotationZ(jobj, 0.0f);
        it_802E7A4C(new_gobj);
        it_802750F8(new_gobj);
        ip->xDCC_flag.b3 = 0;
    }
}

void it_802E79C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    switch (ip->xDD4_itemVar.arwinglaser.xE38) {
    case 0:
    case 2: {
        Item* ip2;
        Item* ip3;

        ip->xDD4_itemVar.arwinglaser.xDF4 = NULL;

        if (ip->xDD4_itemVar.arwinglaser.xE40 != NULL) {
            ip2 = GET_ITEM(ip->xDD4_itemVar.arwinglaser.xE40);
            if (ip2->xDD4_itemVar.arwinglaser.xDF4 == gobj) {
                ip2->xDD4_itemVar.arwinglaser.xDF4 = NULL;
            }
        }
        ip->xDD4_itemVar.arwinglaser.xE40 = NULL;

        if (ip->xDD4_itemVar.arwinglaser.xE44 != NULL) {
            ip3 = GET_ITEM(ip->xDD4_itemVar.arwinglaser.xE44);
            if (ip3->xDD4_itemVar.arwinglaser.xDF4 == gobj) {
                ip3->xDD4_itemVar.arwinglaser.xDF4 = NULL;
            }
        }
        ip->xDD4_itemVar.arwinglaser.xE44 = NULL;
        return;
    }
    case 1:
        return;
    }
}

void it_802E7A4C(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, item->xDD4_itemVar.arwinglaser.xE38, 2);
}

static void itArwinglaser_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.arwinglaser.xE24 = ip->xDD4_itemVar.arwinglaser.xE18;
    if (it_80272C6C(gobj) == 0) {
        ip->xDD4_itemVar.arwinglaser.xE30 = 1;
    }
    it_80273130(gobj);
}

static void itArwinglaser_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.arwinglaser.xE24 = ip->xDD4_itemVar.arwinglaser.xE18;
    ip->xDD4_itemVar.arwinglaser.xE30 = 1;
    it_80273130(gobj);
}

static void itArwinglaser_UnkMotion2_Phys(Item_GObj* gobj)
{
    Vec3 scale_vec;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    ArwingLaserAttr* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    switch (ip->xDD4_itemVar.arwinglaser.xE38) {
    case 0:
    case 2:
        if ((s16) ip->xDD4_itemVar.arwinglaser.xE30 == 1) {
            ip->x40_vel.x =
                attrs->x0->x4_throw_speed_mul * ip->facing_dir;
            ip->x40_vel.z = 0.0f;
            ip->x40_vel.y = 0.0f;
        } else {
            lb_8000B1CC(ip->xDD4_itemVar.arwinglaser.xDF8, NULL, &ip->pos);
            ip->pos.z = 0.0f;
            ip->x40_vel.z = 0.0f;
            ip->x40_vel.y = 0.0f;
            ip->x40_vel.x = 0.0f;
        }
        break;
    }
    {
        f32 s = ip->xDD4_itemVar.arwinglaser.xDFC *
                ip->xDD4_itemVar.arwinglaser.xE34;
        scale_vec.z = s;
        scale_vec.y = s;
        scale_vec.x = s;
    }
    HSD_JObjSetScale(jobj, &scale_vec);
}

static void itArwinglaser_UnkMotion3_Phys(Item_GObj* gobj)
{
    Vec3 scale_vec;
    Vec3 corneria_offset;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    ArwingLaserAttr* attrs = ip->xC4_article_data->x4_specialAttributes;

    switch (ip->xDD4_itemVar.arwinglaser.xE38) {
    case 2:
        break;
    case 1:
    case 3:
        ip->x40_vel.x = ip->xDD4_itemVar.arwinglaser.xE0C.x *
                         (attrs->x0->x4_throw_speed_mul * attrs->x4);
        ip->x40_vel.y = ip->xDD4_itemVar.arwinglaser.xE0C.y *
                         (attrs->x0->x4_throw_speed_mul * attrs->x4);
        ip->x40_vel.z = ip->xDD4_itemVar.arwinglaser.xE0C.z *
                         (attrs->x0->x4_throw_speed_mul * attrs->x4);
        break;
    }
    {
        f32 s = ip->xDD4_itemVar.arwinglaser.xDFC *
                ip->xDD4_itemVar.arwinglaser.xE34;
        scale_vec.z = s;
        scale_vec.y = s;
        scale_vec.x = s;
        {
            f32 ratio = attrs->x8;
            scale_vec.y *= ratio;
            scale_vec.z *= ratio;
        }
    }
    HSD_JObjSetScale(jobj, &scale_vec);

    switch (Stage_8022519C(Stage_80225194())) {
    case 14:
        grCorneria_801DDCF0(&corneria_offset);
        ip->pos.x += corneria_offset.x;
        ip->pos.y += corneria_offset.y;
        /* fallthrough */
    case 15:
        return;
    }
}

static bool itArwinglaser_UnkMotion2_Coll(Item_GObj* gobj)
{
    Vec3 sp40;
    Vec3 prev_pos;
    Vec3 curr_pos;
    Vec3 sp1C;
    u32 sp18;
    int sp14;
    Item* ip = GET_ITEM(gobj);
    Item* ip2;
    int hit;

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp40);
    ip->xDD4_itemVar.arwinglaser.xE18 = sp40;
    ip2 = GET_ITEM(gobj);
    curr_pos = ip2->xDD4_itemVar.arwinglaser.xE18;
    prev_pos = ip2->xDD4_itemVar.arwinglaser.xE24;
    prev_pos.z = 0.0f;
    curr_pos.z = 0.0f;
    if (it_8026EA20(gobj, &prev_pos, &curr_pos, &sp1C, &sp14, &sp18)) {
        mpGetSpeed(sp14, &ip2->pos, &ip2->x40_vel);
        ip2->pos.x += curr_pos.x - ip2->xDD4_itemVar.arwinglaser.xE18.x;
        hit = 1;
    } else {
        hit = 0;
    }
    if (hit == 1) {
        efSync_Spawn(0x40E, gobj, &sp40);
        Item_8026AE84(ip, 0x74, 0x7FU, 0x40U);
        return true;
    }
    return false;
}

static bool itArwinglaser_UnkMotion3_Coll(Item_GObj* gobj)
{
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp10);
    ip->xDD4_itemVar.arwinglaser.xE18 = sp10;
    if (ip->xDD4_itemVar.arwinglaser.xE24.z > -30.0f &&
        ip->xDD4_itemVar.arwinglaser.xE24.z < 30.0f)
    {
        ip->xDD4_itemVar.arwinglaser.xE4C++;
        if (ip->xDD4_itemVar.arwinglaser.xE4C == 1) {
            if (ip->xDD4_itemVar.arwinglaser.xE48 == 3) {
                Item_8026AE84(ip, 0x5573B, 0x7FU, 0x40U);
            } else {
                Item_8026AE84(ip, 0x6B6CA, 0x7FU, 0x40U);
            }
            ip->xDD4_itemVar.arwinglaser.xE4C++;
        }
        if (it_802E70BC(gobj) == true) {
            efSync_Spawn(0x40E, gobj, &sp10);
            Item_8026AE84(ip, 0x74, 0x7FU, 0x40U);
            return true;
        }
    }
    return false;
}

static bool itArwinglaser_UnkMotion5_Coll(Item_GObj* gobj)
{
    Vec3 trans;
    Vec3 scale_vec;
    Quaternion rot;
    Item* ip = GET_ITEM(gobj);
    Item_GObj* parent_gobj = ip->xDD4_itemVar.arwinglaser.xDF4;
    Item* parent_ip;
    PAD_STACK(4);

    if (parent_gobj != NULL) {
        parent_ip = GET_ITEM(parent_gobj);
        if (parent_ip->xDD4_itemVar.arwinglaser.xE40 == gobj ||
            parent_ip->xDD4_itemVar.arwinglaser.xE44 == gobj)
        {
            HSD_JObjGetTranslation(parent_ip->xBBC_dynamicBoneTable->bones[0], &trans);
            trans.z = ip->xDD4_itemVar.arwinglaser.xE08;
            HSD_JObjSetTranslate(ip->xBBC_dynamicBoneTable->bones[0], &trans);
            ip->pos = trans;

            HSD_JObjGetScale(parent_ip->xBBC_dynamicBoneTable->bones[0], &scale_vec);
            HSD_JObjSetScale(ip->xBBC_dynamicBoneTable->bones[0], &scale_vec);

            HSD_JObjGetRotation(parent_ip->xBBC_dynamicBoneTable->bones[0], &rot);
            HSD_JObjSetRotation(ip->xBBC_dynamicBoneTable->bones[0], &rot);

            return false;
        }
    }
    return true;
}

bool it_802E838C(Item_GObj* gobj)
{
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp10);
    ip->xDD4_itemVar.arwinglaser.xE18 = sp10;
    efSync_Spawn(0x40E, gobj, &sp10);
    Item_8026AE84(ip, 0x74, 0x7FU, 0x40U);
    return true;
}

bool it_802E8418(Item_GObj* gobj)
{
    return true;
}

bool it_802E8420(Item_GObj* gobj)
{
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (!ip->xDCC_flag.b1) {
        gobj = ip->owner;
    } else {
        gobj = ip->xC64_reflectGObj;
    }
    ip->xDD4_itemVar.arwinglaser.xE3C = 1;
    switch (ip->xDD4_itemVar.arwinglaser.xE38) {
    case 0:
    case 2:
        lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp10);
        ip->pos = sp10;
        ip->xDD4_itemVar.arwinglaser.xE24 = ip->pos;
        ip->xDD4_itemVar.arwinglaser.xE18 =
            ip->xDD4_itemVar.arwinglaser.xE24;
        ip->facing_dir = -ip->facing_dir;
        ip->x40_vel.x = -ip->x40_vel.x;
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.y = 0.0f;
        HSD_JObjSetRotationY(jobj,
            (f32) (1.5707963267948966 * (f64) ip->facing_dir));
        break;
    case 1:
    case 3:
        if (ip->x40_vel.x * ftLib_800865C0(gobj) < 0.0f) {
            ip->facing_dir = -ip->facing_dir;
        }
        break;
    }
    return false;
}

bool it_802E85F4(Item_GObj* gobj)
{
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->xDD4_itemVar.arwinglaser.xE3C = 1;
    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[4], NULL, &sp10);
    ip->pos = sp10;
    ip->xDD4_itemVar.arwinglaser.xE24 = ip->pos;
    ip->xDD4_itemVar.arwinglaser.xE18 = ip->xDD4_itemVar.arwinglaser.xE24;
    switch (ip->xDD4_itemVar.arwinglaser.xE38) {
    case 0:
    case 2:
        ip->facing_dir = (ip->x40_vel.x < 0.0f) ? -1.0f : 1.0f;
        HSD_JObjSetRotationY(jobj,
            (f32) (1.5707963267948966 * (f64) ip->facing_dir));
        break;
    }
    return false;
}

bool it_802E8784(Item_GObj* gobj)
{
    return true;
}
