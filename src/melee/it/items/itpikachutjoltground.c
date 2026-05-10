#include "itpikachutjoltground.h"

#include "baselib/jobj.h"
#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itpikachutjoltair.h"
#include "lb/lbvector.h"

#include <math.h>
#include <trigf.h>

/* 2B37F0 */ static void itPikachutjoltground_UnkMotion1_Phys(Item_GObj*);

ItemStateTable it_803F7190[] = { {
                                     0,
                                     itPikachutjoltground_UnkMotion0_Anim,
                                     itPikachutjoltground_UnkMotion0_Phys,
                                     itPikachutjoltground_UnkMotion0_Coll,
                                 },
                                 {
                                     1,
                                     itPikachutjoltground_UnkMotion1_Anim,
                                     itPikachutjoltground_UnkMotion1_Phys,
                                     itPikachutjoltground_UnkMotion1_Coll,
                                 } };

static void data_ordering(void)
{
    HSD_JObjSetRotationY(NULL, 0.0f);
    fabs(M_TAU);
    fabs(M_PI);
    HSD_JObjSetRotationY(NULL, -1.0f);
    HSD_JObjSetRotationY(NULL, 1.0f);
}

Item_GObj* it_802B3368(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->xDD4_itemVar.pikachujoltground.xDDC;
        }
    }
    return NULL;
}

Item_GObj* it_802B338C(Item_GObj* owner, Vec3* pos, f32 facing_dir, u32 kind)
{
    SpawnItem spawn;
    UNUSED u8 _pad[4];
    Vec3 coll_normal;
    Item_GObj* item_gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(owner, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        itPikachutJoltGroundAttributes* attr =
            ip->xC4_article_data->x4_specialAttributes;
        if (it_8026E9A4(item_gobj, &spawn.pos, &spawn.prev_pos,
                        &coll_normal) != 0)
        {
            ip->pos = spawn.pos;
        }
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        it_80275158(item_gobj, attr->x0);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
        ip->xDD4_itemVar.pikachujoltground.xDE4 = 0;
        ip->xDD4_itemVar.pikachujoltground.xDE8 = spawn.pos;
        ip->xDD4_itemVar.pikachujoltground.xDF4.z = 0.0f;
        ip->xDD4_itemVar.pikachujoltground.xDF4.y = 0.0f;
        ip->xDD4_itemVar.pikachujoltground.xDF4.x = 0.0f;
        it_802B3554(item_gobj, owner);
        ip->xDD4_itemVar.pikachujoltground.xDD8 = owner;
    }
    return item_gobj;
}

void it_2725_Logic106_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
}

void it_802B3544(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.pikachujoltground.xDDC = 0;
}

void it_802B3554(Item_GObj* gobj, HSD_GObj* owner)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itPikachutJoltGroundAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    f64 angle;
    PAD_STACK(4);

    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);

    if (ip->facing_dir == 1.0f) {
        angle = attr->x4;
    } else {
        angle = M_PI + ABS(attr->x4);
    }
    ip->xDD4_itemVar.pikachujoltground.xDD4 = angle;

    switch (ip->kind) {
    case It_Kind_Pikachu_TJolt_Ground:
    case It_Kind_Pichu_TJolt_Ground:
        efSync_Spawn(0x4BD, gobj, jobj);
        ip->xDD4_itemVar.pikachujoltground.xDE0 = 1;
        break;
    case It_Kind_Kirby_PikachuTJolt_Ground:
    case It_Kind_Kirby_PichuTJolt_Ground:
        efSync_Spawn(0x4AD, gobj, jobj);
        ip->xDD4_itemVar.pikachujoltground.xDE0 = 1;
        break;
    }
    db_80225DD8(gobj, owner);
}

bool itPikachutjoltground_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE8 = ip->pos;
    return it_80273130(gobj);
}

bool itPikachutjoltground_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool flag;
    if (ip->xDD4_itemVar.pikachujoltground.xDDC == NULL) {
        return true;
    }
    if ((gobj != NULL) && (ip != NULL)) {
        if (ip->xDD4_itemVar.pikachujoltground.xDDC == NULL) {
            flag = true;
        } else if (it_802B3EFC(ip->xDD4_itemVar.pikachujoltground.xDDC) !=
                   gobj)
        {
            flag = true;
        } else {
            goto block_8;
        }
    } else {
    block_8:
        flag = false;
    }
    if (flag == true) {
        return true;
    }
    if (itPikachutjoltground_UnkMotion0_Anim(gobj) == true) {
        return true;
    }
    it_802B3F20(ip->xDD4_itemVar.pikachujoltground.xDDC, &ip->pos);
    return false;
}

void itPikachutjoltground_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachutJoltGroundAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = attr->x8 * cosf(ip->xDD4_itemVar.pikachujoltground.xDD4);
    ip->x40_vel.y = attr->x8 * sinf(ip->xDD4_itemVar.pikachujoltground.xDD4);
}

static void itPikachutjoltground_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itPikachutjoltground_UnkMotion0_Coll(Item_GObj* gobj)
{
    f32 ground_angle;
    f32 angle_diff;
    f32 facing_dir;
    Item* ip = GET_ITEM(gobj);
    Item* ip2;
    PAD_STACK(8);

    ip->xDD4_itemVar.pikachujoltground.xE00 =
        ip->xDD4_itemVar.pikachujoltground.xDF4;
    if (it_8026E9A4(gobj, &ip->xDD4_itemVar.pikachujoltground.xDE8, &ip->pos,
                    &ip->xDD4_itemVar.pikachujoltground.xDF4) != 0)
    {
        ip2 = GET_ITEM(gobj);
        efLib_DestroyAll(gobj);
        ip2->xDD4_itemVar.pikachujoltground.xDE0 = 0;
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip2 = GET_ITEM(gobj);
        ground_angle = atan2f(ip2->xDD4_itemVar.pikachujoltground.xDF4.y,
                              ip2->xDD4_itemVar.pikachujoltground.xDF4.x);
        angle_diff = atan2f(ip2->x40_vel.y, ip2->x40_vel.x) - ground_angle;

        while (angle_diff < 0.0f) {
            angle_diff += M_TAU;
        }
        while (angle_diff > M_TAU) {
            angle_diff -= M_TAU;
        }
        if (angle_diff < M_PI) {
            facing_dir = -1.0f;
        } else {
            facing_dir = 1.0f;
        }
        ip2->xDD4_itemVar.pikachujoltground.xDDC = it_802B4224(
            ip2->owner, gobj, &ip2->pos, ip2->kind + 1, facing_dir);
        ip->xDD4_itemVar.pikachujoltground.xE00 =
            ip->xDD4_itemVar.pikachujoltground.xDF4;
        if (ip->xDD4_itemVar.pikachujoltground.xDDC == NULL) {
            return true;
        }
        it_802B3F88(ip->xDD4_itemVar.pikachujoltground.xDDC, &ip->pos,
                    &ip->x378_itemColl,
                    &ip->xDD4_itemVar.pikachujoltground.xDF4);
        ip->xDD4_itemVar.pikachujoltground.xDE4 = 0;
        it_802725D4(gobj);
    }
    return false;
}

bool itPikachutjoltground_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    if (ip->xDD4_itemVar.pikachujoltground.xDE4 >= 0) {
        ip->xDD4_itemVar.pikachujoltground.xE00 =
            ip->xDD4_itemVar.pikachujoltground.xDF4;
        if (it_8026E9A4(gobj, &ip->xDD4_itemVar.pikachujoltground.xDE8,
                        &ip->pos,
                        &ip->xDD4_itemVar.pikachujoltground.xDF4) != 0)
        {
            Item* ip2 = GET_ITEM(gobj);
            itPikachutJoltGroundAttributes* attr =
                ip2->xC4_article_data->x4_specialAttributes;
            bool flag;

            if (0.0f == attr->xC) {
                flag = false;
            } else {
                f32 angle =
                    lbVector_Angle(&ip2->xDD4_itemVar.pikachujoltground.xDF4,
                                   &ip2->xDD4_itemVar.pikachujoltground.xE00);
                f32 limit = attr->xC;
                if (limit < 0.0f) {
                    limit = -limit;
                }
                if (angle > limit) {
                    flag = true;
                } else {
                    flag = false;
                }
            }

            if (flag == true) {
                return true;
            }

            if (ip->xDD4_itemVar.pikachujoltground.xDDC == NULL) {
                return true;
            }
            it_802B3F88(ip->xDD4_itemVar.pikachujoltground.xDDC, &ip->pos,
                        &ip->x378_itemColl,
                        &ip->xDD4_itemVar.pikachujoltground.xDF4);
            ip->xDD4_itemVar.pikachujoltground.xDE4 = 0;
        }
    }
    ip->xDD4_itemVar.pikachujoltground.xDE4++;
    return false;
}

bool it_2725_Logic106_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

bool it_2725_Logic106_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->facing_dir = -ip->facing_dir;
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    ip->xDD4_itemVar.pikachujoltground.xDD4 += M_PI;

    while (ip->xDD4_itemVar.pikachujoltground.xDD4 < 0.0f) {
        ip->xDD4_itemVar.pikachujoltground.xDD4 += M_TAU;
    }
    while (ip->xDD4_itemVar.pikachujoltground.xDD4 > M_TAU) {
        ip->xDD4_itemVar.pikachujoltground.xDD4 -= M_TAU;
    }
    return false;
}

bool it_2725_Logic106_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

bool it_2725_Logic106_Absorbed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

bool it_2725_Logic106_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

bool it_2725_Logic106_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.pikachujoltground.xDD4 =
        atan2f(ip->x40_vel.y, ip->x40_vel.x);

    while (ip->xDD4_itemVar.pikachujoltground.xDD4 < 0.0f) {
        ip->xDD4_itemVar.pikachujoltground.xDD4 += M_TAU;
    }
    while (ip->xDD4_itemVar.pikachujoltground.xDD4 > M_TAU) {
        ip->xDD4_itemVar.pikachujoltground.xDD4 -= M_TAU;
    }

    {
        f32 dir;
        if (ip->x40_vel.x >= 0.0f) {
            dir = 1.0f;
        } else {
            dir = -1.0f;
        }
        ip->facing_dir = dir;
    }
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    return false;
}

void itPikachuTJoltGround_Logic106_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
