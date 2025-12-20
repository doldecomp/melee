#include "itnesspkfirepillar.h"

#include "db/db.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"


/**
 * <rei wolf> i do know 1.0f and 0.0 are swapped but idk how to get a 1.0 in the higher functions x_x
 * <Altafen#6776> itll get dead stripped by the linker should still match
 * <rei wolf> oh wow rly
 * <Altafen#6776> yea (i didn't know linkers could do that especially linkers from 1998)
 * <Altafen#6776> (i should write a linker)
 * <rei wolf> i have never heard of that being a thing at all
*/

float get_min_life(void);
float get_min_life(void) {
    return 1.0F;
}

/**
 * <rei wolf> lol is there a way to hide the function from objdiff
 * <Altafen#6776> i dont think so :(
 * <rei wolf> cries
*/

ItemStateTable itNesspkfirepillar_ItemStateTable[1] = {
    0,
    itNesspkfirepillar_UnkMotion0_Anim,
    itNesspkfirepillar_UnkMotion0_Phys,
    itNesspkfirepillar_UnkMotion0_Coll
};

inline void itNesspkfirepillar_INLINE_SpawnItem_Init(SpawnItem* spawnitem, Vec3* offset, f32 facing_dir, HSD_GObj* parent1_gobj, HSD_GObj* parent2_gobj) {
    spawnitem->kind = It_Kind_Ness_PKFire_Flame;
    spawnitem->prev_pos = *offset;
    spawnitem->prev_pos.z = 0.0F;
    spawnitem->pos = spawnitem->prev_pos;
    spawnitem->vel.x = spawnitem->vel.y = spawnitem->vel.z = 0.0F;
    spawnitem->facing_dir = facing_dir;
    spawnitem->x3C_damage = 0;
    spawnitem->x0_parent_gobj = parent2_gobj;
    spawnitem->x4_parent_gobj2 = parent1_gobj;
    spawnitem->x44_flag.b0 = true;
    spawnitem->x40 = 0;
}

void itNesspkfirepillar_802AA494(HSD_GObj* parent1_gobj, HSD_GObj* parent2_gobj, Vec3* offset, f32 facing_dir) {
    Item_GObj* item_gobj;
    SpawnItem spawnitem;
    PAD_STACK(0x10);
    itNesspkfirepillar_INLINE_SpawnItem_Init(&spawnitem, offset, facing_dir, parent1_gobj, parent2_gobj);
    item_gobj = Item_80268B18(&spawnitem);
    if (item_gobj != NULL) {
        db_80225DD8(item_gobj, parent2_gobj);
        itNesspkfirepillar_802AA55C(item_gobj);
    }
}

void itNesspkfirepillar_802AA55C(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    itNessPKFirepillarAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(item_gobj, attrs->x0);
}

bool inline itNesspkfirepillar_INLINE_Anim_SetScale(Item_GObj* item_gobj, f32 scale) {
    Vec3 scaling;
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    Item* item = GET_ITEM(item_gobj);
    scaling.z = scale;
    scaling.y = scale;
    scaling.x = scale;
    HSD_JObjSetScale(jobj, &scaling);
    if (item->xD44_lifeTimer <= 0.0F) {
        return true;
    }
    item->xD44_lifeTimer--;
        return false;
}

bool itNesspkfirepillar_UnkMotion0_Anim(Item_GObj* item_gobj) {
    Item* item;
    f32 scale;
    itNessPKFirepillarAttributes* attrs;
    item = GET_ITEM(item_gobj);
    attrs = item->xC4_article_data->x4_specialAttributes;
    scale = attrs->scale + (item->xD44_lifeTimer * (1.0F - attrs->scale)) / attrs->x0;
    scale *= item->xCC_item_attr->x60_scale;
    return itNesspkfirepillar_INLINE_Anim_SetScale(item_gobj, scale);
}

//! @bug Unintentionally sets the item to be in the air (see itNokonoko_UnkMotion5_Phys)
void itNesspkfirepillar_UnkMotion0_Phys(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    if ((item->ground_or_air = GA_Air)) {
        ItemAttr* attr = item->xCC_item_attr;
        it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    }
}

//! @bug Unintentionally sets the item to be in the air (see itNokonoko_UnkMotion5_Coll)
bool itNesspkfirepillar_UnkMotion0_Coll(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    if ((item->ground_or_air = GA_Air)) {
        it_8026E414(item_gobj, it_80273454);
    }
    else {
        it_8026D82C(item_gobj);
    }
    return 0;
}

bool itNesspkfirepillar_Logic24_DmgReceived(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    itNessPKFirepillarAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    item->xD44_lifeTimer = -((item->xC9C * attrs->x4) - item->xD44_lifeTimer);
    if (item->xD44_lifeTimer <= 0.0F) {
        item->xD44_lifeTimer = get_min_life();
    }
    return 0;
}

void itNesspkfirepillar_802AA7C4(Item_GObj* item_gobj, HSD_GObj* parent_gobj) {
    it_8026B894(item_gobj, parent_gobj);
}
