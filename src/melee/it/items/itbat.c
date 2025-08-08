#include "itbat.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

ItemStateTable it_803F57B0[] = {
    { -1, itBat_UnkMotion0_Anim, itBat_UnkMotion0_Phys, itBat_UnkMotion0_Coll },
    { -1, itBat_UnkMotion3_Anim, itBat_UnkMotion3_Phys, itBat_UnkMotion3_Coll },
    { -1, itBat_UnkMotion2_Anim, itBat_UnkMotion2_Phys, itBat_UnkMotion2_Coll },
    { 0, itBat_UnkMotion3_Anim, itBat_UnkMotion3_Phys, itBat_UnkMotion3_Coll },
    { -1, itBat_UnkMotion4_Anim, itBat_UnkMotion4_Phys, itBat_UnkMotion4_Coll },
};

Item_GObj* it_80284854(Vec3* pos)
{
    SpawnItem spawn;
    Item_GObj* item_gobj = NULL;

    pos->z = 0.0F;
    spawn.kind = It_Kind_Bat;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0F;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B5C(&spawn);

    if (item_gobj != NULL) {
        it_80284974(item_gobj);
    }

    return item_gobj;
}

void it_80284910(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itBatAttributes* ap = item->xC4_article_data->x4_specialAttributes;

    it_8026B390(gobj);
    item->x40_vel.x = 0.0f;
    item->x40_vel.y = ap->xC_vel;
    item->x40_vel.z = 0.0f;
    it_802849F0(gobj);
}

void it_80284974(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    item->xD50_landNum = 0;

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itBat_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itBat_UnkMotion0_Phys(Item_GObj* gobj)
{
    return;
}

bool itBat_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802849F0);
    return false;
}

void it_802849F0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->xD50_landNum = 0;
}

bool itBat_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itBat_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itBat_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80284974);
    return false;
}

void it_80284AAC(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));

    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->xD50_landNum = 0;
}

bool itBat_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itBat_UnkMotion2_Phys(Item_GObj* gobj)
{
    return;
}

bool itBat_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_80284B30(Item_GObj* gobj)
{
    Item* item = gobj->user_data;
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_80284BA0(Item_GObj* gobj)
{
    Item* item = gobj->user_data;
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_80284C10(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itBat_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itBat_UnkMotion4_Phys(Item_GObj* gobj)
{
    return;
}

bool itBat_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80284974, it_802849F0);
    return false;
}

bool it_80284C78(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);

    if (item->msid == 3) {
        itColl_BounceOffVictim(gobj);
    }

    return false;
}

bool it_80284CAC(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_80284CCC(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_80284CF0(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_80284D14(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_80284D34(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
