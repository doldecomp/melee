#include "itmewtwodisable.h"

#include <placeholder.h>
#include <platform.h>

#include <melee/it/forward.h>

#include <melee/db/db.h>
#include <melee/ft/chara/ftMewtwo/ftMt_SpecialLw.h>
#include <melee/ft/ftlib.h>
#include <melee/it/inlines.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>

ItemStateTable it_803F7750[1] = { 0, itMewtwodisable_UnkMotion0_Anim,
                                  itMewtwodisable_UnkMotion0_Phys,
                                  itMewtwodisable_UnkMotion0_Coll };

void itMewtwoDisable_Logic67_Destroy(Item_GObj* item_gobj)
{
    Item_8026A8EC(item_gobj);
}

void itMewtwoDisable_Logic67_Destroyed(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->xDD4_itemVar.mdisable.owner != NULL) {
        ftMt_SpecialLw_ClearDisableGObj(item->xDD4_itemVar.mdisable.owner);
    }
    item->xDD4_itemVar.mdisable.owner = NULL;
}

Item_GObj* itMewtwoDisable_Logic67_SpawnMewtwoDisable(Fighter_GObj* fighter_gobj,
                                              Vec3* offset, f32 facing_dir)
{
    Item_GObj* item_gobj;
    SpawnItem spawnitem;
    Vec3* vel = &spawnitem.vel;

    spawnitem.kind = It_Kind_Mewtwo_Disable;
    spawnitem.prev_pos = *offset;
    // set item position relative to fp bone
    it_8026BB68(fighter_gobj, &spawnitem.pos);
    spawnitem.facing_dir = facing_dir;
    spawnitem.x3C_damage = 0;
    vel->z = 0.0f;
    vel->y = 0.0f;
    vel->x = 0.0f;
    spawnitem.x0_parent_gobj = fighter_gobj;
    spawnitem.x4_parent_gobj2 = spawnitem.x0_parent_gobj;
    spawnitem.x44_flag.b0 = true;
    spawnitem.x40 = 0;

    if ((item_gobj = Item_80268B18(&spawnitem)) != NULL) {
        Item* item = GET_ITEM(item_gobj);
        itMDisable_ItemVars* vars = &item->xDD4_itemVar.mdisable;
        Fighter_GObj** owner;
        owner = &vars->owner;
        *owner = item->owner;
        it_802C4B38(item_gobj);
        it_8026B3A8(item_gobj);
        db_80225DD8(item_gobj, fighter_gobj);
        item->xDCC_flag.b3 = true;
    }
    return item_gobj;
}

void it_802C4B38(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    itMDisableAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    Fighter_GObj* fighter_gobj = item->xDD4_itemVar.mdisable.owner;

    // the last parameter gets the y scaling of mewtwo
    item->x40_vel.x =
        attrs->x_vel * item->facing_dir * ftLib_80086A0C(fighter_gobj);
    item->x40_vel.y = item->x40_vel.z = 0.0f;
    // set mdisable lifetime timers
    it_80275158(item_gobj, attrs->lifetime);
    it_802C4BB8(item_gobj);
}

void it_802C4BB8(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    float y_scale;

    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    y_scale = ftLib_80086A0C(item->xDD4_itemVar.mdisable.owner);
    it_802755C0(item_gobj, y_scale);
}

bool itMewtwodisable_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    item->xD44_lifeTimer -= 1.0f;
    return false;
}

void itMewtwodisable_UnkMotion0_Phys(Item_GObj* item_gobj) {}

int itMewtwodisable_UnkMotion0_Coll(Item_GObj* item_gobj)
{
    u32 coll_flags = 0;

    // coll processing
    it_8026D9A0(item_gobj);
    // report if collided with wall
    coll_flags |= it_80276308(item_gobj);
    // combine with collided with ceiling report
    coll_flags |= it_802763E0(item_gobj);
    return coll_flags;
}

bool itMewtwoDisable_Logic67_DmgDealt(Item_GObj* item_gobj)
{
    return true;
}

bool itMewtwoDisable_Logic67_Reflected(Item_GObj* item_gobj)
{
    // process being reflected
    return it_80273030(item_gobj);
}

bool itMewtwoDisable_Logic67_Clanked(Item_GObj* item_gobj)
{
    return true;
}

bool itMewtwoDisable_Logic67_HitShield(Item_GObj* item_gobj)
{
    return true;
}

bool itMewtwoDisable_Logic67_Absorbed(Item_GObj* item_gobj)
{
    return true;
}

bool itMewtwoDisable_Logic67_ShieldBounced(Item_GObj* item_gobj)
{
    return true;
}

void itMewtwoDisable_Logic67_EvtUnk(Item_GObj* item_gobj, Fighter_GObj* ref_owner)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->xDD4_itemVar.mdisable.owner == ref_owner) {
        item->xDD4_itemVar.mdisable.owner = NULL;
    }
    // remove all gobj interaction references from item
    it_8026B894(item_gobj, ref_owner);
}
