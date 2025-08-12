#include "itheart.h"

#include "gm/gm_unsplit.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 283C7C */ static void it_80283C7C(Item_GObj* gobj);
/* 283CD4 */ static bool itHeart_UnkMotion0_Anim(Item_GObj* gobj);
/* 283DA4 */ static void itHeart_UnkMotion0_Phys(Item_GObj* gobj);
/* 283DA8 */ static bool itHeart_UnkMotion0_Coll(Item_GObj* gobj);
/* 283DD4 */ static void it_80283DD4(Item_GObj* gobj);
/* 283DFC */ static bool itHeart_UnkMotion3_Anim(Item_GObj* gobj);
/* 283ECC */ static void itHeart_UnkMotion3_Phys(Item_GObj* gobj);
/* 283EFC */ static bool itHeart_UnkMotion3_Coll(Item_GObj* gobj);
/* 284020 */ static bool itHeart_UnkMotion2_Anim(Item_GObj* gobj);
/* 284028 */ static void itHeart_UnkMotion2_Phys(Item_GObj* gobj);
/* 284154 */ static bool itHeart_UnkMotion4_Anim(Item_GObj* gobj);
/* 28415C */ static void itHeart_UnkMotion4_Phys(Item_GObj* gobj);
/* 284160 */ static bool itHeart_UnkMotion4_Coll(Item_GObj* gobj);

ItemStateTable it_803F56C8[] = {
    { 0xFFFFFFFF, itHeart_UnkMotion0_Anim, itHeart_UnkMotion0_Phys,
      itHeart_UnkMotion0_Coll },
    { 0xFFFFFFFF, itHeart_UnkMotion3_Anim, itHeart_UnkMotion3_Phys,
      itHeart_UnkMotion3_Coll },
    { 0xFFFFFFFF, itHeart_UnkMotion2_Anim, itHeart_UnkMotion2_Phys, NULL },
    { 0xFFFFFFFF, itHeart_UnkMotion3_Anim, itHeart_UnkMotion3_Phys,
      itHeart_UnkMotion3_Coll },
    { 0xFFFFFFFF, itHeart_UnkMotion4_Anim, itHeart_UnkMotion4_Phys,
      itHeart_UnkMotion4_Coll },
};

Item_GObj* it_80283AE4(Item_GObj* gobj, Vec3* pos, s32 arg2)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    item_gobj = NULL;
    if (gobj != NULL) {
        spawn.kind = It_Kind_Heart;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = 0.0F;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = -1;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = true;
        spawn.x40 = 0;
        item_gobj = Item_80268B18(&spawn);
    }
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDD4_itemVar.heart.xDD8.b0 = true;
        ip->xDD4_itemVar.heart.xDDC = arg2;
        Item_80267454(item_gobj);
    }
    return item_gobj;
}

void it_80283BD4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HeartContainerAttr* vars = ip->xC4_article_data->x4_specialAttributes;

    ip->xDD4_itemVar.heart.xDD4_heal = vars->x4.flags;
}

void it_3F14_Logic8_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HeartContainerAttr* vars = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = vars->x14;
    ip->x40_vel.z = 0.0F;
    ip->xDD4_itemVar.heart.xDD4_heal = vars->x0_heal;
    ip->xDD4_itemVar.heart.xDD8.b0 = false;
    ip->xDD4_itemVar.heart.xDDC = 0;
    it_80283DD4(gobj);
}

void it_3F14_Logic8_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if ((s8) ((((*(s8*) &ip->xDD4_itemVar.heart.xDD8.flags) & 0xC0) << 24) >>
              31))
    {
        ((s8*) &gm_80473A18 + ip->xDD4_itemVar.heart.xDDC)[0x90] = 0;
    }
}

void it_80283C7C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8026B390(gobj);
    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itHeart_UnkMotion0_Anim(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));
    HeartContainerAttr* attrs =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    HSD_JObjAddRotationY(child, attrs->x18);
    return false;
}

void itHeart_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itHeart_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80283DD4);
    return false;
}

void it_80283DD4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itHeart_UnkMotion3_Anim(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));
    HeartContainerAttr* attrs =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    HSD_JObjAddRotationY(child, attrs->x18);
    return false;
}

void itHeart_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itHeart_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80283C7C);
    return false;
}

void it_3F14_Logic8_PickedUp(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));

    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    HSD_JObjSetRotationY(child, 0.0F);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itHeart_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itHeart_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic8_Dropped(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    HSD_JObjSetRotationY(child, 0.0F);
    Item_80268E5C(gobj, 3, 6);
}

void it_3F14_Logic8_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itHeart_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itHeart_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itHeart_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80283C7C, it_80283DD4);
    return false;
}

void it_3F14_Logic8_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
