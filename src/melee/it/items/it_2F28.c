#include "it_2F28.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/types.h"
#include "it/types.h"

#include <math.h>
#include <math_ppc.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>
#include <MetroTRK/intrinsics.h>

extern float it_802758D4(Item_GObj*);            /* extern */
static void it_802F2A58(Item_GObj*);             /* static */
static bool it_2F28_UnkMotion0_Anim(Item_GObj*); /* static */
static void it_2F28_UnkMotion0_Phys(HSD_GObj*);  /* static */
// static bool it_2F28_UnkMotion0_Coll(HSD_GObj*); /* static */
static bool it_2F28_UnkMotion0_Coll(Item_GObj*); /* static */

ItemStateTable it_803F9470[] = {
    { 0, it_2F28_UnkMotion0_Anim, it_2F28_UnkMotion0_Phys,
      it_2F28_UnkMotion0_Coll },
};

void it_802F28C8(Item_GObj* item_gobj, int arg1, float arg2)
{
    Item* item;

    item = item_gobj->user_data;
    it_8027B4A4((Fighter_GObj*) item->grab_victim, item_gobj);
    it_8027B378((Fighter_GObj*) item->grab_victim, item_gobj, arg2);
    if (arg1 != 0) {
        item->destroy_type = 0;
    }
    item->atk_victim = NULL;
    item->grab_victim = NULL;
    it_8027CE44(item_gobj);
    Item_8026A8EC(item_gobj);
}

float it_802F295C(HSD_GObj* owner_gobj, it_2F28_DatAttrs* attr)
{
    SpawnItem spawn;

    Item_GObj* item_gobj;
    Item* item;
    float var_f31;
    PAD_STACK(4);

    var_f31 = 0.0f;
    spawn.kind = It_Kind_Unk2;
    spawn.prev_pos = attr->pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.vel = attr->vel;
    spawn.x0_parent_gobj = owner_gobj;
    spawn.x4_parent_gobj2 = owner_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);

    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        item->xDD4_itemVar.it_2F28.x0 = attr->float2;
        it_80275158((HSD_GObj*) item_gobj, attr->float1);
        it_802F2A58(item_gobj);
        var_f31 = it_802758D4(item_gobj);
    }
    return var_f31;
}

void it_802F2A58(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    it_8026B3A8(item_gobj);
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
    item->xDCE_flag.b7 = 0;
}

bool it_2F28_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer = (item->xD44_lifeTimer - 1.0f);
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_2F28_UnkMotion0_Phys(HSD_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    f32 var_f4 = sqrtf(SQ(item->x40_vel.x) + SQ(item->x40_vel.y));
    if (var_f4 > item->xDD4_itemVar.it_2F28.x0) {
        item->x40_vel.x =
            (item->x40_vel.x * (var_f4 - item->xDD4_itemVar.it_2F28.x0)) /
            var_f4;
        item->x40_vel.y =
            (item->x40_vel.y * (var_f4 - item->xDD4_itemVar.it_2F28.x0)) /
            var_f4;
    } else {
        item->x40_vel.x = 0.0f;
    }
    return;
}

bool it_2F28_UnkMotion0_Coll(Item_GObj* item_gobj)
// bool it_2F28_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    if (it_8026DFB0(item_gobj) != 0) {
        // if (it_8026DFB0((Item_GObj*) item_gobj) != 0) {
        return true;
    }
    return false;
}

void it_802F2BDC(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
