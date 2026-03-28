#include "itflipper.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

/* 0x802910B8 */ void itFlipper_Logic20_Thrown(Item_GObj* gobj);

HSD_GObj* it_80290938(HSD_JObj* jobj)
{
    SpawnItem spawn;
    Vec3 pos;
    Item_GObj* gobj = NULL;

    if (jobj != NULL) {
        lb_8000B1CC(jobj, NULL, &pos);
        spawn.kind = It_Kind_Flipper;
        spawn.prev_pos = pos;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = 1.0f;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = 0;
        spawn.x40 = 0;
        gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Item* ip = GET_ITEM(gobj);
            ip->xDD4_itemVar.flipper.xDE8 = 1;
            ip->xDD4_itemVar.flipper.xDEC = jobj;
            it_80291254(gobj);
        }
    }
    return gobj;
}

void itFlipper_Logic20_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->xDD4_itemVar.flipper.xDD4 = 0;
    ip->xDD4_itemVar.flipper.xDD8 = 0;
    ip->xDD4_itemVar.flipper.xDDC = 0;
    ip->xDD4_itemVar.flipper.xDE0 = 0.0F;
    ip->xDD4_itemVar.flipper.xDE4 = 0.0F;
    ip->xDD4_itemVar.flipper.xDE8 = 0;
    ip->xDD4_itemVar.flipper.xDEC = 0;
    it_802756D0(gobj);
    it_80290F00(gobj);
}

/// #it_80290A7C

void it_80290C38(Item_GObj* gobj, Vec3* pos, f32 angle)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 speed = angle + attrs->x1C;

    if (pos->x > ip->pos.x) {
        if (pos->y > ip->pos.y) {
            ip->xDD4_itemVar.flipper.xDE4 += speed;
        } else {
            ip->xDD4_itemVar.flipper.xDE4 -= speed;
        }
    } else {
        if (pos->y > ip->pos.y) {
            ip->xDD4_itemVar.flipper.xDE4 -= speed;
        } else {
            ip->xDD4_itemVar.flipper.xDE4 += speed;
        }
    }

    if (ip->xDD4_itemVar.flipper.xDE4 > attrs->x24) {
        ip->xDD4_itemVar.flipper.xDE4 = attrs->x24;
    }
    if (ip->xDD4_itemVar.flipper.xDE4 < -attrs->x24) {
        ip->xDD4_itemVar.flipper.xDE4 = -attrs->x24;
    }
}

/// #it_80290CE8

void it_80290DD4(Item_GObj* gobj, s32 kind, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 vec;

    vec.z = 0.0f;
    vec.y = 0.0f;
    vec.x = 0.0f;

    if (kind == 0x14) {
        vec.x = ip->pos.x - pos->x;
        vec.y = ip->pos.y - pos->y;
        lbVector_NormalizeXY(&vec);
        vec.x *= 0.2f;
        vec.y *= 0.2f;
        ip->x40_vel.x += vec.x;
        ip->x40_vel.y += vec.y;
    }
}

void it_80290E78(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itFlipper_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80290F00);
    return false;
}

void it_80290F00(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFlipper_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80290E78);
    return false;
}

void itFlipper_Logic20_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion2_Phys(Item_GObj* gobj) {}

void itFlipper_Logic20_Dropped(Item_GObj* gobj)
{
    itFlipper_Logic20_Thrown(gobj);
}

void itFlipper_Logic20_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->owner != NULL) {
        if (ftLib_80087284(ip->owner)) {
            ip->xDD4_itemVar.flipper.xDD4 = attrs->x4;
        } else {
            ip->xDD4_itemVar.flipper.xDD4 = attrs->x0;
        }
    }
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

bool itFlipper_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.flipper.xDD4--;
    if (ip->xDD4_itemVar.flipper.xDD4 <= 0) {
        it_80291254(gobj);
    }
    return false;
}

/// #itFlipper_UnkMotion3_Anim

void itFlipper_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* item_attr = ip->xCC_item_attr;
    it_80272860(gobj, item_attr->x10_fall_speed,
                item_attr->x14_fall_speed_max);
    if (ip->xDD4_itemVar.flipper.xDD4 <= 0xA) {
        ip->x40_vel.x *=
            (f32) ip->xDD4_itemVar.flipper.xDD4 /
            (1.0f + (f32) ip->xDD4_itemVar.flipper.xDD4);
        ip->x40_vel.y *=
            (f32) ip->xDD4_itemVar.flipper.xDD4 /
            (1.0f + (f32) ip->xDD4_itemVar.flipper.xDD4);
    }
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itFlipper_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 coll = it_8026DAA8(gobj);
    if (coll != 0) {
        if (coll & 0xC) {
            ip->x40_vel.x *= -attrs->xC;
        }
        ip->x40_vel.y *= attrs->xC;
        if (coll & 2) {
            ip->x40_vel.x *= attrs->xC;
        }
        ip->x40_vel.y *= -attrs->xC;
        if (coll & 1) {
            ip->x40_vel.x *= attrs->x10;
        }
        ip->x40_vel.y *= -attrs->x10;
    }
    return false;
}

void it_80291254(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xD5C = 0;
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->xDD1_flag.b1 = 1;
    ip->xDD4_itemVar.flipper.xDD8 = 1;
    it_80275444(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.flipper.xDE8 != 0) {
        it_8027542C(gobj);
    }
    ip->xD44_lifeTimer = (f32) attrs->x8;
    it_8026B3A8(gobj);
    it_802756E0(gobj);
    it_8029131C(gobj);
}

void it_8029131C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, 0x12);
}

/// #it_80291344

bool itFlipper_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE4 != 0.0f) {
        Item_80268E5C(gobj, 6, 0x12);
    }
    return it_80291344(gobj);
}

bool itFlipper_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE4 == 0.0F) {
        Item_80268E5C(gobj, 5, 0x12);
    }
    it_80291344(gobj);
}

void itFlipper_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE8 != 0) {
        if (ip->xDD4_itemVar.flipper.xDEC != NULL) {
            lb_8000B1CC(ip->xDD4_itemVar.flipper.xDEC, 0, &ip->pos);
        }
    }
}

bool itFlipper_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE8 == 0) {
        it_8026E0F4(gobj);
    }
    return false;
}

/// #it_3F14_Logic20_DmgDealt

#pragma dont_inline on
bool it_3F14_Logic20_Clanked(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    if (ip->xDD4_itemVar.flipper.xDD8 == 0) {
        if (ip->xDD4_itemVar.flipper.xDD4 >= 6) {
            itColl_BounceOffVictim(gobj);
        } else {
            ip->x40_vel.x = -1.0f * ip->x40_vel.x;
            ip->x40_vel.y =
                -1.0f * ip->x40_vel.y + it_804D6D28->x60_float;
        }
    } else {
        ip->xDD4_itemVar.flipper.xDDC = attrs->x14;
        it_80290CE8(gobj);
        it_80272560(gobj, 0);
        it_80272560(gobj, 1);
        it_802756D0(gobj);
        if (ip->xDD4_itemVar.flipper.xDE8 == 0) {
            it_80290DD4(gobj, ip->xC38, &ip->xCD4);
        }
    }
    return false;
}

bool it_3F14_Logic20_HitShield(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    if (ip->xDD4_itemVar.flipper.xDD8 == 0) {
        if (ip->xDD4_itemVar.flipper.xDD4 >= 6) {
            itColl_BounceOffVictim(gobj);
        } else {
            ip->x40_vel.x = -1.0f * ip->x40_vel.x;
            ip->x40_vel.y =
                -1.0f * ip->x40_vel.y + it_804D6D28->x60_float;
        }
    } else {
        ip->xDD4_itemVar.flipper.xDDC = attrs->x14;
        it_80290CE8(gobj);
        it_80272560(gobj, 0);
        it_80272560(gobj, 1);
        it_802756D0(gobj);
        if (ip->xDD4_itemVar.flipper.xDE8 == 0) {
            it_80290DD4(gobj, ip->xC38, &ip->xCD4);
        }
    }
    return false;
}

#pragma dont_inline reset
bool itFlipper_Logic20_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itFlipper_Logic20_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_3F14_Logic20_DmgReceived

void itFlipper_Logic20_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itFlipper_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80290E78, it_80290F00);
    return false;
}

void itFlipper_Logic20_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
