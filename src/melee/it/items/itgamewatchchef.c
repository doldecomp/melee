#include "itgamewatchchef.h"

#include "math.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/jobj.h>

/// #it_802C837C

bool itGameWatchChef_Logic112_DmgDealt(Item_GObj* gobj)
{
    it_802C875C(gobj);
    return false;
}

void it_802C84A0(Item_GObj* gobj, s32 index)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.gamewatchchef.x4 = index;
    it_80275158(gobj, attrs->x8);
    ip->xD5C = 0;
    ip->x40_vel.x =
        attrs->entries[ip->xDD4_itemVar.gamewatchchef.x4].x0 * ip->facing_dir;
    ip->x40_vel.y = attrs->entries[ip->xDD4_itemVar.gamewatchchef.x4].x4;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

/// #itGamewatchchef_UnkMotion0_Anim

void itGamewatchchef_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    s32 index = ip->xDD4_itemVar.gamewatchchef.x4;
    it_80272860(gobj, attrs->entries[index].x8, attrs->entries[index].xC);
}

bool itGamewatchchef_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    if (0.0f != ip->x40_vel.x) {
        s32 result = it_8026DAA8(gobj);
        if (result & 0xC) {
            ip->x40_vel.x *= -attrs->x4;
        }
        if (result & 3) {
            it_802C875C(gobj);
        }
    }
    return false;
}

void it_802C875C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_80275158(gobj, attrs->xC);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itGamewatchchef_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        ip->xD44_lifeTimer = 0.0f;
        return true;
    }
    if ((s32) ip->xD44_lifeTimer & 2) {
        it_8026BB20(gobj);
    } else {
        it_8026BB44(gobj);
    }
    return false;
}

void itGamewatchchef_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itGamewatchchef_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    if (0.0f != ip->x40_vel.x) {
        s32 result = it_8026DAA8(gobj);
        if (result & 0xC) {
            ip->x40_vel.x *= -attrs->x4;
        }
        if (result & 3) {
            ip = GET_ITEM(gobj);
            attrs = ip->xC4_article_data->x4_specialAttributes;
            ip->x40_vel.y = 0.0f;
            ip->x40_vel.x = 0.0f;
            it_80275158(gobj, attrs->xC);
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        }
    }
    return false;
}

bool it_2725_Logic112_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_80275158(gobj, attrs->xC);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    return false;
}

bool it_2725_Logic112_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_80275158(gobj, attrs->xC);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    return false;
}

bool it_2725_Logic112_Absorbed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(24);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_80275158(gobj, attrs->xC);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->xD44_lifeTimer = 0.0f;
    return false;
}

bool itGameWatchChef_Logic112_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itGameWatchChef_Logic112_Reflected(Item_GObj* gobj)
{
    const f32 PI_2 = M_PI / 2;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    it_80273030(gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * ip->facing_dir);
    return false;
}

void itGameWatchChef_Logic112_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
