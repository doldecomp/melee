#include "it_27CF.h"

#include "ef/efasync.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/types.h"
#include "it/types.h"

#include <math_ppc.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

ItemStateTable it_803F94A0[] = {
    { -1, it_27CF_UnkMotion0_Anim, it_27CF_UnkMotion0_Phys,
      it_27CF_UnkMotion0_Coll },
    { -1, it_27CF_UnkMotion1_Anim, it_27CF_UnkMotion1_Phys,
      it_27CF_UnkMotion1_Coll },
    { -1, it_27CF_UnkMotion2_Anim, NULL, NULL },
};

void it_802F2F34(HSD_GObj* gobj, it_27CF_DatAttrs* attr)
{
    Item* item;
    Item_GObj* item_gobj;
    SpawnItem spawn;

    spawn.kind = attr->kind;
    spawn.prev_pos = attr->pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = attr->float2;
    spawn.x3C_damage = 0;
    spawn.vel = attr->vel;
    spawn.x0_parent_gobj = 0;
    spawn.x4_parent_gobj2 = 0;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        item = GET_ITEM((HSD_GObj*) item_gobj);
        item->xDD4_itemVar.it_27CF.x0 = attr->float3;
        item->xC98 = attr->x24;
        it_80275158(item_gobj, attr->lifetime);
        // it_802F3020(item_gobj);
        it_802F3020((HSD_GObj*) item_gobj);
    }
}

// void it_802F3020(Item_GObj* item_gobj) {
void it_802F3020(HSD_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    it_8026B3A8((Item_GObj*) item_gobj);
    Item_80268E5C((HSD_GObj*) item_gobj, 1, ITEM_ANIM_UPDATE);
    item->xDCE_flag.b7 = 0;
}

#if 0
inline bool inline1(HSD_GObj* item_gobj) {
    Item* item;
    f32 sp1C;
    HSD_JObj* item_jobj;

    item = GET_ITEM(item_gobj);
    item->xD44_lifeTimer -= 1.0f;
    if (item->xD44_lifeTimer <= 0.0f) {
        item = item_gobj->user_data;
        item_jobj = item_gobj->hsd_obj;
        sp1C = 1.0f;
        Item_8026AE84(item, 280088, 127, 64);
        efAsync_Spawn(item_gobj, &item->xBC0, 4U, 1231, item_gobj->hsd_obj, &sp1C);
        it_802F3290((Item_GObj*) item_gobj);
    }
    return false;
}

bool it_27CF_UnkMotion1_Anim(HSD_GObj* item_gobj) {
    PAD_STACK(8);
    return inline1(item_gobj);
}

// void it_27CF_UnkMotion1_Phys(Item_GObj* item_gobj) {
void it_27CF_UnkMotion1_Phys(HSD_GObj* item_gobj) {
    ItemAttr* attr;

    attr = ((Item*) item_gobj->user_data)->xCC_item_attr;
    it_80272860((Item_GObj*) item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

// bool it_27CF_UnkMotion1_Coll(Item_GObj* item_gobj) {
bool it_27CF_UnkMotion1_Coll(HSD_GObj* item_gobj) {
    it_8026E15C((Item_GObj*) item_gobj, it_802F317C);
    return false;
}

// void it_802F317C(Item_GObj* gobj) {
void it_802F317C(HSD_GObj* item_gobj) {
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0f;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_27CF_UnkMotion0_Anim(HSD_GObj* item_gobj) {
    PAD_STACK(8);
    return inline1(item_gobj);
}

#else
// bool it_27CF_UnkMotion1_Anim(Item_GObj* item_gobj) {
bool it_27CF_UnkMotion1_Anim(HSD_GObj* item_gobj)
{
    Item* item;
    f32 sp1C;
    HSD_JObj* item_jobj;
    PAD_STACK(10);

    item = item_gobj->user_data;
    item->xD44_lifeTimer -= 1.0f;
    if (item->xD44_lifeTimer <= 0.0f) {
        item = item_gobj->user_data;
        item_jobj = item_gobj->hsd_obj;
        sp1C = 1.0f;
        Item_8026AE84(item, 280088, 127, 64);
        efAsync_Spawn(item_gobj, &item->xBC0, 4U, 1231, item_gobj->hsd_obj,
                      &sp1C);
        it_802F3290((Item_GObj*) item_gobj);
    }
    return false;
}

// void it_27CF_UnkMotion1_Phys(Item_GObj* item_gobj) {
void it_27CF_UnkMotion1_Phys(HSD_GObj* item_gobj)
{
    ItemAttr* attr;

    attr = ((Item*) item_gobj->user_data)->xCC_item_attr;
    it_80272860((Item_GObj*) item_gobj, attr->x10_fall_speed,
                attr->x14_fall_speed_max);
}

// bool it_27CF_UnkMotion1_Coll(Item_GObj* item_gobj) {
bool it_27CF_UnkMotion1_Coll(HSD_GObj* item_gobj)
{
    it_8026E15C((Item_GObj*) item_gobj, it_802F317C);
    return false;
}

// void it_802F317C(Item_GObj* gobj) {
void it_802F317C(HSD_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0f;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

// bool it_27CF_UnkMotion0_Anim(Item_GObj* item_gobj) {
bool it_27CF_UnkMotion0_Anim(HSD_GObj* item_gobj)
{
    Item* item;
    f32 sp1C;
    HSD_JObj* item_jobj;
    PAD_STACK(10);

    item = item_gobj->user_data;
    item->xD44_lifeTimer -= 1.0f;
    if (item->xD44_lifeTimer <= 0.0f) {
        item = item_gobj->user_data;
        item_jobj = item_gobj->hsd_obj;
        sp1C = 1.0f;
        Item_8026AE84(item, 280088, 127, 64);
        efAsync_Spawn(item_gobj, &item->xBC0, 4U, 1231, item_gobj->hsd_obj,
                      &sp1C);
        it_802F3290((Item_GObj*) item_gobj);
    }
    return false;
}
#endif

// void it_27CF_UnkMotion0_Phys(Item_GObj* item_gobj) {
void it_27CF_UnkMotion0_Phys(HSD_GObj* item_gobj)
{
    return;
}

// bool it_27CF_UnkMotion0_Coll(Item_GObj* item_gobj) {
bool it_27CF_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    it_8026D62C((Item_GObj*) item_gobj, it_802F3020);
    return false;
}

void it_802F3290(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;

    item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0f;
    item->xD44_lifeTimer = 40.0f;
    HSD_JObjSetFlagsAll(item_jobj, 0x10U);
    it_802756D0(item_gobj);
    Item_80268E5C((HSD_GObj*) item_gobj, 2, ITEM_ANIM_UPDATE);
}

// bool it_27CF_UnkMotion2_Anim(Item_GObj* item_gobj) {
bool it_27CF_UnkMotion2_Anim(HSD_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    item->xD44_lifeTimer -= 1.0f;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

bool it_27CF_Logic114_DmgReceived(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    // item->xD44_lifeTimer = -((item->xCA0 * item->xDD4_itemVar.it_27CF.x0) -
    // item->xD44_lifeTimer);
    item->xD44_lifeTimer -= item->xCA0 * item->xDD4_itemVar.it_27CF.x0;
    return false;
}

void it_27CF_Logic114_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}

void it_802B26C0(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802B26E0(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_802C6DB8(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C6DD8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_802C7AD0(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C7AF0(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}
