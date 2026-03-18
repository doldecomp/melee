#include "ittools.h"

#include "math.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/jobj.h>

Item_GObj* it_802EEFA8(Vec3* pos, s32 arg1, f32 facing_dir)
{
    Item_GObj* gobj;
    SpawnItem spawn;
    PAD_STACK(12);

    spawn.kind = It_Kind_Tools;
    spawn.prev_pos = *pos;
    spawn.pos = *pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it_802EF098(gobj, arg1);
        return gobj;
    }
    return NULL;
}

bool itTools_Logic22_DmgDealt(Item_GObj* gobj)
{
    it_802EF320(gobj);
    return false;
}

void it_802EF098(Item_GObj* gobj, s32 arg1)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* attrs =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.tools.x0 = arg1;
    it_80275158(gobj, attrs->x0);
    ip->xD5C = 0;
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = -attrs[ip->xDD4_itemVar.tools.x0].x10;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0, ITEM_ANIM_UPDATE);
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
    itToolsAttrEntry* attrs =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (s32) attrs->x4 & 0xFFFE;
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, ITEM_ANIM_UPDATE);
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

static inline void itTools_UnkMotion9_Coll_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (f32) ((s32) attrs->x4 & 0xFFFE);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, ITEM_ANIM_UPDATE);
}

bool itTools_UnkMotion9_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if ((ip->x40_vel.x != 0.0f || ip->x40_vel.y != 0.0f) &&
        (it_8026DAA8(gobj) & 3))
    {
        itTools_UnkMotion9_Coll_inline(gobj);
    }
    return false;
}

/// #it_802EF548

bool itTools_Logic22_DmgReceived(Item_GObj* gobj)
{
    it_802EF548(gobj);
    return false;
}

bool it_2725_Logic22_Clanked(Item_GObj* gobj)
{
    itToolsAttrEntry* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (s32) attrs->x4 & 0xFFFE;
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, ITEM_ANIM_UPDATE);
    return false;
}

bool it_2725_Logic22_HitShield(Item_GObj* gobj)
{
    itToolsAttrEntry* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (s32) attrs->x4 & 0xFFFE;
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, ITEM_ANIM_UPDATE);
    return false;
}

bool it_2725_Logic22_Absorbed(Item_GObj* gobj)
{
    itToolsAttrEntry* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(24);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xD44_lifeTimer = (s32) attrs->x4 & 0xFFFE;
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0 + 5, ITEM_ANIM_UPDATE);
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
