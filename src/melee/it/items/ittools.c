#include "ittools.h"

#include "math.h"
#include "placeholder.h"

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"

#include <baselib/jobj.h>

ItemStateTable it_803F9260[] = {
    { 0, itTools_UnkMotion4_Anim, itTools_UnkMotion4_Phys,
      itTools_UnkMotion4_Coll },
    { 1, itTools_UnkMotion4_Anim, itTools_UnkMotion4_Phys,
      itTools_UnkMotion4_Coll },
    { 2, itTools_UnkMotion4_Anim, itTools_UnkMotion4_Phys,
      itTools_UnkMotion4_Coll },
    { 3, itTools_UnkMotion4_Anim, itTools_UnkMotion4_Phys,
      itTools_UnkMotion4_Coll },
    { 4, itTools_UnkMotion4_Anim, itTools_UnkMotion4_Phys,
      itTools_UnkMotion4_Coll },
    { 5, itTools_UnkMotion9_Anim, itTools_UnkMotion9_Phys,
      itTools_UnkMotion9_Coll },
    { 6, itTools_UnkMotion9_Anim, itTools_UnkMotion9_Phys,
      itTools_UnkMotion9_Coll },
    { 7, itTools_UnkMotion9_Anim, itTools_UnkMotion9_Phys,
      itTools_UnkMotion9_Coll },
    { 8, itTools_UnkMotion9_Anim, itTools_UnkMotion9_Phys,
      itTools_UnkMotion9_Coll },
    { 9, itTools_UnkMotion9_Anim, itTools_UnkMotion9_Phys,
      itTools_UnkMotion9_Coll },
};

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
    itToolsAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.tools.x0 = arg1;
    it_80275158(gobj, attrs->x0);
    ip->xD5C = 0;
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = -attrs->motions[ip->xDD4_itemVar.tools.x0].x0;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, ip->xDD4_itemVar.tools.x0, ITEM_ANIM_UPDATE);
}

bool itTools_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itToolsAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 rz = HSD_JObjGetRotationZ(jobj);
    rz += attrs->motions[ip->xDD4_itemVar.tools.x0].xC * ip->facing_dir;
    HSD_JObjSetRotationZ(jobj, rz);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        ip->xD44_lifeTimer = 0.0f;
        it_802EF320(gobj);
    }
    return false;
}

void itTools_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_80272860(gobj, attrs->motions[ip->xDD4_itemVar.tools.x0].x4,
                attrs->motions[ip->xDD4_itemVar.tools.x0].x8);
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
    itToolsAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
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
    ip->xD44_lifeTimer = (s32) attrs->x4 & 0xFFFE;
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

void it_802EF548(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    Fighter_GObj* fighter;
    f32 new_damage;
    Vec3 fighter_pos;
    f32 dir;

    if (ABS(ip->x40_vel.x) > attrs->motions[ip->xDD4_itemVar.tools.x0].x14) {
        return;
    }

    fighter = NULL;
    ip->xD44_lifeTimer = ip->xD48_halfLifeTimer;
    if (ip->xCEC_fighterGObj != NULL) {
        fighter = ip->xCEC_fighterGObj;
    }

    new_damage = ip->xCA0;
    dir = -1.0f * ip->xCCC_incDamageDirection;
    if (fighter != NULL) {
        if (ftLib_80086960(fighter)) {
            ftLib_800866DC(fighter, &fighter_pos);
        } else {
            return;
        }
        if (ip->pos.x > fighter_pos.x) {
            dir = 1.0f;
        } else {
            dir = -1.0f;
        }
    }

    new_damage *= attrs->x8;
    new_damage += ip->x5D4_hitboxes[0].hit.damage;
    if (new_damage > (u32) attrs->xC) {
        new_damage = (u32) attrs->xC;
    }
    it_80272460(&ip->x5D4_hitboxes[0].hit, (u32) new_damage, gobj);

    ip->x40_vel.x = dir * ((1.0f + (ip->x5D4_hitboxes[0].hit.damage - 10.0f)) *
                           attrs->motions[ip->xDD4_itemVar.tools.x0].x18);
    ip->x40_vel.y = attrs->motions[ip->xDD4_itemVar.tools.x0].x10;
}

bool itTools_Logic22_DmgReceived(Item_GObj* gobj)
{
    it_802EF548(gobj);
    return false;
}

bool it_2725_Logic22_Clanked(Item_GObj* gobj)
{
    itToolsAttributes* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
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
    itToolsAttributes* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
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
    itToolsAttributes* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
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
