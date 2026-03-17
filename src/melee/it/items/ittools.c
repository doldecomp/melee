#include "ittools.h"

#include "math.h"

#include "it/inlines.h"
#include "it/item.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

#include <baselib/jobj.h>

/// #it_802EEFA8

bool itTools_Logic22_DmgDealt(Item_GObj* gobj)
{
    it_802EF320(gobj);
    return false;
}

void it_802EF098(Item_GObj* gobj, s32 idx)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.tools.x0 = idx;
    it_80275158(gobj, entry->x0);
    ip->xD5C = 0;
    ip->x40_vel.x = 0.0f;
    entry += ip->xDD4_itemVar.tools.x0;
    ip->x40_vel.y = -entry->x10;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0, 2);
}

/// #itTools_UnkMotion4_Anim

void itTools_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    entry += ip->xDD4_itemVar.tools.x0;
    it_80272860(gobj, entry->x14, entry->x18);
}

bool itTools_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->x40_vel.x != 0.0f || ip->x40_vel.y != 0.0f) {
        if (it_8026DAA8(gobj) & 3) {
            it_802EF320(gobj);
        }
    }
    return false;
}

void it_802EF320(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (f32) ((s32) entry->x4 & ~1);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, 2);
}

bool itTools_UnkMotion9_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        ip->xD44_lifeTimer = 0.0f;
        return true;
    }
    if ((s32) ip->xD44_lifeTimer & 2) {
        it_8026BB20(gobj);
        it_80273670(gobj, ip->xDD4_itemVar.tools.x0 + 5, 0.0f);
    } else {
        it_8026BB44(gobj);
    }
    return false;
}

void itTools_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itTools_UnkMotion9_Coll

/// #it_802EF548

bool itTools_Logic22_DmgReceived(Item_GObj* gobj)
{
    it_802EF548(gobj);
    return false;
}

bool it_2725_Logic22_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (f32) ((s32) entry->x4 & ~1);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, 2);
    return false;
}

bool it_2725_Logic22_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (f32) ((s32) entry->x4 & ~1);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, 2);
    return false;
}

bool it_2725_Logic22_Absorbed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (f32) ((s32) entry->x4 & ~1);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, 2);
    ip->xD44_lifeTimer = 0.0f;
    return false;
}

bool itTools_Logic22_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itTools_Logic22_Reflected(Item_GObj* gobj)
{
    const f32 PI_2 = M_PI / 2;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    it_80273030(gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * ip->facing_dir);
    return false;
}

void it_802EFA24(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
