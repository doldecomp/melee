#include "itmball.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ef/efasync.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/types.h"

#include <dolphin/mtx.h>
#include <melee/gr/ground.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>

void it_3F14_Logic34_Destroyed(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (!(it->xDD4_itemVar.mball.b1)) {
        Item_804A0C64.x1C -= 1;
    }
}

void it_3F14_Logic34_Spawned(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);

    item->xDD4_itemVar.mball.b0 = false;
    item->xDD4_itemVar.mball.b1 = false;
    it_802979D4(arg0);
}

void it_80297944(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    HSD_JObj* jobj = GET_JOBJ(arg0);
    it_8026B390(arg0);
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
}

bool itMball_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itMball_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itMball_UnkMotion0_Coll(Item_GObj* arg0)
{
    it_8026D62C(arg0, it_802979D4);
    return 0;
}

void it_802979D4(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);

    if (!item->xDD4_itemVar.mball.b0) {
        Item_80268E5C(arg0, 1, ITEM_UNK_0x1);
        return;
    }
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
}

bool itMball_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itMball_UnkMotion1_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    it_80272860(arg0, item->xCC_item_attr->x10_fall_speed,
                item->xCC_item_attr->x14_fall_speed_max);
}

bool itMball_UnkMotion1_Coll(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    f32 previous_vel_x;

    previous_vel_x = item->x40_vel.x;
    it_8026E15C(arg0, it_80297944);
    if (item->x40_vel.x != previous_vel_x) {
        it_80272980(arg0);
    }
    return 0;
}

void it_3F14_Logic34_PickedUp(Item_GObj* arg0)
{
    Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
}

bool itMball_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itMball_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic34_Dropped(Item_GObj* arg0)
{
    Item_80268E5C(arg0, 3, 6);
}

void it_3F14_Logic34_Thrown(Item_GObj* arg0)
{
    Item_80268E5C(arg0, 3, 6);
}

void itMball_UnkMotion3_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    it_80272860(arg0, item->xCC_item_attr->x10_fall_speed,
                item->xCC_item_attr->x14_fall_speed_max);
    it_80274658(arg0, it_804D6D28->x68_float);
}

bool itMball_UnkMotion3_Coll(Item_GObj* arg0)
{
    it_8026E414(arg0, (void (*)(HSD_GObj*)) it_80297CC4);
    return 0;
}

bool it_3F14_Logic34_DmgDealt(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    it_802725D4(arg0);
    itColl_BounceOffVictim(arg0);
    return 0;
}

/// #it_3F14_Logic34_EnteredAir

bool itMball_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itMball_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itMball_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80297944, it_802979D4);
    return false;
}

void it_80297CC4(Item_GObj* arg0)
{
    f32 zero = 0.0f;
    Item* item = GET_ITEM(arg0);
    itMBallAttributes* spec_attrs =
        item->xC4_article_data->x4_specialAttributes;
    HSD_JObj* hsd_obj = arg0->hsd_obj;

    it_8026B3A8(arg0);
    it_80275D5C(arg0, &item->xC0C);
    item->xDC8_word.flags.x1A = 0;
    item->xD5C = 0;
    item->x40_vel.z = zero;
    item->x40_vel.y = zero;
    item->x40_vel.x = zero;
    it_80274740(arg0);
    if (!item->xDD4_itemVar.mball.b0) {
        item->xD44_lifeTimer = spec_attrs->x0;
        item->xDD4_itemVar.mball.b0 = true;
        efAsync_Spawn(arg0, &GET_ITEM(arg0)->xBC0, 0U, 0x449U, hsd_obj);
        Item_8026AE84(item, 0x10C, 0x7F, 0x40);
        Item_80268E5C((HSD_GObj*) arg0, 5, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C((HSD_GObj*) arg0, 5, ITEM_UNK_0x1);
    }
    item->on_accessory = it_80297DD8;
}

void it_80297DD8(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    itMBallAttributes* spec_attrs =
        item->xC4_article_data->x4_specialAttributes;

    if (item->xD44_lifeTimer == spec_attrs->x4) {
        item->xDD4_itemVar.mball.b1 = it_8027AB64(arg0);
    }
}

bool itMball_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void itMball_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itMball_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80297E8C);
    return false;
}

/// #it_80297E8C

bool itMball_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void itMball_UnkMotion6_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);

    it_80272860(arg0, item->xCC_item_attr->x10_fall_speed,
                item->xCC_item_attr->x14_fall_speed_max);
}

bool itMball_UnkMotion6_Coll(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    f32 previous_vel_x;

    previous_vel_x = item->x40_vel.x;
    it_8026E15C(arg0, (void (*)(HSD_GObj*)) it_80297CC4);
    if (item->x40_vel.x != previous_vel_x) {
        it_80272980(arg0);
    }
    return 0;
}

bool it_3F14_Logic34_Clanked(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    it_802725D4(arg0);
    itColl_BounceOffVictim(arg0);
    return 0;
}

bool it_3F14_Logic34_Reflected(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    return it_80273030(arg0);
}

bool it_3F14_Logic34_HitShield(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    it_802725D4(arg0);
    itColl_BounceOffVictim(arg0);
    return 0;
}

bool it_3F14_Logic34_ShieldBounced(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    return itColl_BounceOffShield(arg0);
}

void it_3F14_Logic34_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
