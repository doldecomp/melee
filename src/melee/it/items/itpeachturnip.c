#include "itpeachturnip.h"

#include "ft/chara/ftPeach/ftPe_SpecialLw.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"

#include <baselib/random.h>

ItemStateTable it_803F74A8[] = {
    {
        1,
        itPeachturnip_UnkMotion4_Anim,
        itPeachturnip_UnkMotion4_Phys,
        NULL,
    },
    {
        -1,
        itPeachturnip_UnkMotion1_Anim,
        itPeachturnip_UnkMotion1_Phys,
        NULL,
    },
    {
        2,
        itPeachturnip_UnkMotion3_Anim,
        itPeachturnip_UnkMotion3_Phys,
        itPeachturnip_UnkMotion3_Coll,
    },
    {
        2,
        itPeachturnip_UnkMotion3_Anim,
        itPeachturnip_UnkMotion3_Phys,
        itPeachturnip_UnkMotion3_Coll,
    },
    {
        -1,
        itPeachturnip_UnkMotion4_Anim,
        itPeachturnip_UnkMotion4_Phys,
        NULL,
    },
};

static bool decrease_lifetimer(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    item->xD44_lifeTimer--;
    if (item->xD44_lifeTimer <= 0.0F) {
        return true;
    }
    return false;
}

// Peach_TurnipTypeDecide - Weighted random selection
s32 it_802BD32C(Item_GObj* item_gobj)
{
    s32 i, rand, sum, tmp, cum_odds, ret;
    Item* item;
    itPeachTurnipAttributes* attr;

    item = GET_ITEM(item_gobj);
    attr = item->xC4_article_data->x4_specialAttributes;

    sum = 0;
    for (i = 0; i < attr->x4_length; i++) {
        sum += attr->x8[i].x0_odds;
    }

    rand = HSD_Randi(sum);

    cum_odds = attr->x8[0].x0_odds;
    tmp = -1;
    ret = tmp;
    for (i = 0; i < attr->x4_length && ret == tmp; i++) {
        if (rand < cum_odds) {
            ret = i;
        }
        cum_odds += attr->x8[i + 1].x0_odds;
    }

    return ret;
}

void it_802BD45C(Item_GObj* item_gobj)
{
    Item_8026A8EC(item_gobj);
}

void it_2725_Logic56_Destroyed(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->xDD4_itemVar.peachturnip.xDE4_owner != NULL) {
        ftPe_SpecialLw_UnsetVeg(item->xDD4_itemVar.peachturnip.xDE4_owner);
    }
}

// Peach_SpawnAndGiveTurnip
Item_GObj* it_802BD4AC(Item_GObj* item_gobj, Vec3* pos, Fighter_Part part,
                       ItemKind kind, f32 fdir)
{
    SpawnItem spawn;
    Item_GObj* spawn_gobj;
    Item* item;
    itPeachTurnipAttributes* attr;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = fdir;
    spawn.x3C_damage = 0.0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = item_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;

    spawn_gobj = Item_80268B18(&spawn);
    if (spawn_gobj != NULL) {
        item = GET_ITEM(spawn_gobj);
        if (kind == It_Kind_Peach_Turnip) {
            attr = item->xC4_article_data->x4_specialAttributes;
            it_80275158(spawn_gobj, attr->x0_lifetime);
            item->xDD4_itemVar.peachturnip.xDD8 = it_802BD32C(spawn_gobj);
            item->xDD4_itemVar.peachturnip.xDDC_damage =
                attr->x8[item->xDD4_itemVar.peachturnip.xDD8].x4_damage;
            item->xDD4_itemVar.peachturnip.xDD4.b0 = 0;
            item->xDD4_itemVar.peachturnip.xDE4_owner = item->owner;
            it_8026BD0C(spawn_gobj);
        }

        Item_8026AB54(spawn_gobj, item_gobj, part);
        if (kind != It_Kind_Sword) {
            it_80274594(spawn_gobj);
            item = GET_ITEM(spawn_gobj);
            switch (item->kind) {
            case It_Kind_BombHei:
                item->xDD4_itemVar.peachturnip.xDE8_scl = item->scl;
                break;
            case It_Kind_Dosei:
                item->xDD4_itemVar.peachturnip.xDE0_scl = item->scl;
                break;
            case It_Kind_Peach_Turnip:
                item->xDD4_itemVar.peachturnip.xDE0_scl = item->scl;
                break;
            default:;
            }
        }
    }
    return spawn_gobj;
}

// ItemOnSpawn_Turnip
void it_2725_Logic56_PickedUp(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);

    it_80273670(item_gobj, 0, (f32) item->xDD4_itemVar.peachturnip.xDD8);
    if (item->xDD4_itemVar.peachturnip.xDD4.b0) {
        Item_80268E5C(item_gobj, 4, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        it_8026BCF4(item_gobj);
    }
    item->xDD4_itemVar.peachturnip.xDD4.b0 = 1;
    Item_802694CC(item_gobj);
}

bool itPeachturnip_UnkMotion4_Anim(Item_GObj* item_gobj)
{
    return false;
}

void itPeachturnip_UnkMotion4_Phys(Item_GObj* item_gobj)
{
    return;
}

bool itPeachturnip_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    return decrease_lifetimer(item_gobj);
}

void itPeachturnip_UnkMotion1_Phys(Item_GObj* item_gobj)
{
    ItemAttr* temp_r4;

    temp_r4 = GET_ITEM(item_gobj)->xCC_item_attr;
    it_80272860(item_gobj, temp_r4->x10_fall_speed,
                temp_r4->x14_fall_speed_max);
}

void it_2725_Logic56_Thrown(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hit;
    HSD_JObj* jobj;

    item = GET_ITEM(item_gobj);
    jobj = GET_JOBJ(item_gobj);

    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
    it_80273670(item_gobj, 0, (f32) item->xDD4_itemVar.peachturnip.xDD8);

    hit = &item->x5D4_hitboxes[0].hit;
    it_80272460(hit, item->xDD4_itemVar.peachturnip.xDDC_damage, item_gobj);
    it_80274484(item_gobj, jobj, item->xDD4_itemVar.peachturnip.xDE0_scl);
}

bool itPeachturnip_UnkMotion3_Anim(Item_GObj* item_gobj)
{
    return decrease_lifetimer(item_gobj);
}

// ProjectilePhysics_TurnipVelocity
void itPeachturnip_UnkMotion3_Phys(Item_GObj* item_gobj)
{
    ItemAttr* attr;

    attr = GET_ITEM(item_gobj)->xCC_item_attr;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(item_gobj, it_804D6D28->x68_float);
}

bool itPeachturnip_UnkMotion3_Coll(Item_GObj* item_gobj)
{
    s32 first_check, second_check;
    bool chk;

    first_check = 0xE;
    second_check = 0x3;

    chk = it_8026DAA8(item_gobj);
    if (chk & first_check) {
        it_80276FC4(item_gobj, chk);
        Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    } else if (chk & second_check) {
        return true;
    }
    return false;
}

void it_2725_Logic56_Dropped(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    Item_80268E5C(item_gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
    it_80273670(item_gobj, 0, (f32) item->xDD4_itemVar.peachturnip.xDD8);
}

bool it_2725_Logic56_DmgDealt(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    return false;
}

bool it_2725_Logic56_Clanked(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_2725_Logic56_Reflected(Item_GObj* item_gobj)
{
    it_80273030(item_gobj);
    return false;
}

bool it_2725_Logic56_HitShield(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_2725_Logic56_ShieldBounced(Item_GObj* item_gobj)
{
    itColl_BounceOffShield(item_gobj);
    return false;
}

void it_2725_Logic56_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->xDD4_itemVar.peachturnip.xDE4_owner == ref_gobj) {
        item->xDD4_itemVar.peachturnip.xDE4_owner = NULL;
    }
    it_8026B894(item_gobj, ref_gobj);
}
