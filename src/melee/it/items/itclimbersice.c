#include "itclimbersice.h"

#include "baselib/jobj.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftPopo/ftPp_Init.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"

#include <MSL/math.h>

ItemStateTable it_803F7668[] = {
    { -1, itClimbersice_UnkMotion0_Anim, itClimbersice_UnkMotion0_Phys,
      itClimbersice_UnkMotion0_Coll },
    { -1, itClimbersice_UnkMotion1_Anim, itClimbersice_UnkMotion1_Phys,
      itClimbersice_UnkMotion1_Coll },
    { 0, itClimbersice_UnkMotion2_Anim, itClimbersice_UnkMotion2_Phys,
      itClimbersice_UnkMotion2_Coll },
    { 0, itClimbersice_UnkMotion3_Anim, itClimbersice_UnkMotion3_Phys,
      itClimbersice_UnkMotion3_Coll },
};

static void fakefunc(f32 f, u32 u, Vec3 vec)
{
    vec.x = 0;
    vec.x = f * u;
}

static inline void itClimbersIce_sub_x4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itClimbersIceAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xD44_lifeTimer -= attr->x4;
}

static inline void itClimbersice_Spawn(Item_GObj* gobj, u32 spawn1, u32 spawn2)
{
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    Item* ip = GET_ITEM(gobj);
    if (ip->kind == 0x6A) {
        f32* facing = &ip->facing_dir;
        efAsync_Spawn(gobj, &ip->xBC0, 3, spawn1, child, facing);
    } else {
        f32* facing = &ip->facing_dir;
        efAsync_Spawn(gobj, &ip->xBC0, 3, spawn2, child, facing);
    }
}
static inline void itClimbersice_Spawn2(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    HSD_JObj* other;
    Item* ip = GET_ITEM(gobj);
    if (ip->kind == 0x6A) {
        other = child;
        efAsync_Spawn(gobj, &ip->xBC0, 0, 0x4E9, other);
    } else {
        other = child;
        efAsync_Spawn(gobj, &ip->xBC0, 0, 0x4AE, other);
    }
}

Item_GObj* it_802C1590(Item_GObj* parent_gobj, Vec3* pos, enum_t kind,
                       f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    PAD_STACK(16);

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent_gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDD4_itemVar.climbersice.x0 = ip->owner;
        ip->xDD4_itemVar.climbersice.x8_b0 = false;
        ip->xDD4_itemVar.climbersice.x4 = ip->xCC_item_attr->x60_scale;
        itClimbersice_Spawn2(item_gobj);
        it_802C1A58(item_gobj);
        db_80225DD8(item_gobj, parent_gobj);
        it_8026B3A8(item_gobj);
        it_802750F8(item_gobj);
    }
    return item_gobj;
}

void it_802C16F8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    ip->x40_vel.x = sa->x10 * ip->facing_dir;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;

    it_80275158(gobj, sa->x0);

    ip->xDD4_itemVar.climbersice.x8_b0 = 1;

    it_80272980(gobj);
    itClimbersice_Spawn(gobj, 0x4ea, 0x4af);

    it_802C1AE4(gobj);
}

void it_802C17DC(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

void it_2725_Logic90_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.climbersice.x0 != NULL) {
        if (ip->kind == 0x6A) {
            ftPp_Init_8011F16C(ip->xDD4_itemVar.climbersice.x0, gobj);
        } else {
            ftKb_SpecialNIc_80108CE8(ip->xDD4_itemVar.climbersice.x0, gobj);
        }
    }
    ip->xDD4_itemVar.climbersice.x0 = NULL;
}

bool it_802C1854(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    CollData* coll = &ip->x378_itemColl;
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    bool result = false;

    if (ip->x378_itemColl.env_flags & 0x18000) {
        f32 normal_x = coll->floor.normal.x;
        s32 normal_sign = (normal_x < 0.0f) ? -1 : 1;
        s32 vel_sign = (ip->x40_vel.x < 0.0f) ? -1 : 1;
        f32 delta;

        if (vel_sign != normal_sign) {
            delta = sa->x1C * (normal_x * sa->x14);
        } else {
            delta = sa->x18 * (normal_x * sa->x14);
        }
        ip->x40_vel.x += delta;

        if (ABS(ip->x40_vel.x) < sa->x24) {
            it_8026BD84(gobj);
            it_8026BD6C(gobj);
            it_802C1950(gobj);
            efLib_DestroyAll(gobj);
            result = true;
        }
    }
    return result;
}

void it_802C1950(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* child;
    PAD_STACK(8);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    if (ip->xDD4_itemVar.climbersice.x8_b0) {
        ip->xDD4_itemVar.climbersice.x4 *= sa->x28;
        it_80272F7C(child, ip->xDD4_itemVar.climbersice.x4);
        if (ip->xDD4_itemVar.climbersice.x4 < 0.01f) {
            return true;
        }
    }
    return false;
}

void itClimbersice_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itClimbersice_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802C1A58);
    it_80276CB8(gobj);
    return false;
}

void it_802C1A58(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itClimbersice_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itClimbersice_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802C1950);
    return false;
}

void it_802C1AE4(Item_GObj* gobj)
{
    PAD_STACK(16);
    itClimbersice_Spawn(gobj, 0x4eb, 0x4b0);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

static inline void itClimbersice_Phys_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    u32 dmg = ABS(ip->x40_vel.x * sa->x30);
    dmg += sa->x2C;
    it_80272460(&ip->x5D4_hitboxes[0].hit, dmg, gobj);
}

void itClimbersice_UnkMotion2_Phys(Item_GObj* gobj)
{
    if (it_802C1854(gobj)) {
        itClimbersice_Phys_inline(gobj);
    }
}

static inline bool itClimbersice_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    if (it_80276308(gobj) != 0) {
        if (ABS(ip->x40_vel.x) <= sa->xC) {
            it_8027770C(gobj);
            it_80272980(gobj);
            itClimbersIce_sub_x4(gobj);
        } else {
            return true;
        }
    }
    return false;
}

bool itClimbersice_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, fn_802C1D44);
    it_80276CB8(gobj);
    return itClimbersice_Coll(gobj);
}

void fn_802C1D44(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    efLib_DestroyAll(gobj);
}

bool itClimbersice_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void itClimbersice_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
    itClimbersice_Phys_inline(gobj);
}

bool itClimbersice_UnkMotion3_Coll(Item_GObj* gobj)
{
    PAD_STACK(16);
    if (it_8026DAA8(gobj) & 1) {
        itClimbersice_Spawn(gobj, 0x4eb, 0x4b0);
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    }
    return itClimbersice_Coll(gobj);
}

bool itClimbersIce_Logic90_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itClimbersIce_Logic90_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itClimbersIce_Logic90_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic90_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;

    if (ABS(ip->x40_vel.x) <= sa->xC) {
        itColl_BounceOffVictim(gobj);
        it_80272980(gobj);
        {
            f32 scale = attr->x58;
            ip->x40_vel.x *= scale;
            ip->x40_vel.y *= scale;
            ip->x40_vel.z *= scale;
        }
        itClimbersIce_sub_x4(gobj);
        if (ip->xD44_lifeTimer < sa->x8) {
            return true;
        }
    } else {
        return true;
    }
    return false;
}

bool itClimbersIce_Logic90_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itClimbersIce_Logic90_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void itClimbersIce_Logic90_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.climbersice.x0 == ref_gobj) {
        ip->xDD4_itemVar.climbersice.x0 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
