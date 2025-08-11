#include "baselib/forward.h"
#include "it/forward.h"

#include "itpeachtoad.h"

#include "db/db.h"
#include "ftKirby/ftKb_Init.h"
#include "ftPeach/ftPe_SpecialN.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

ItemStateTable it_803F7528[] = { {
                                     0,
                                     itPeachtoad_UnkMotion0_Anim,
                                     NULL,
                                     NULL,
                                 },
                                 {
                                     1,
                                     itPeachtoad_UnkMotion1_Anim,
                                     NULL,
                                     NULL,
                                 } };

static inline void itpeachtoad_inline_1(Item* item)
{
    HSD_GObj* hsd_gobj;

    hsd_gobj = item->owner;
    if (hsd_gobj != NULL) {
        if (item->kind == It_Kind_Peach_Toad) {
            ftPe_SpecialN_DoDeath2(hsd_gobj);
        } else {
            ftKb_SpecialNPe_8010C3C0(hsd_gobj);
        }
    }
}

static inline bool itpeachtoad_inline_2(Item* item)
{
    HSD_GObj* hsd_gobj;
    bool res;

    hsd_gobj = item->owner;
    if (hsd_gobj != NULL) {
        if (item->kind == It_Kind_Peach_Toad) {
            res = ftPe_SpecialN_IsActive(hsd_gobj);
        } else {
            res = ftKb_SpecialNPe_8010C4AC(hsd_gobj);
        }
    } else {
        res = true;
    }
    return res;
}

Item_GObj* it_802BDE18(Item_GObj* item_gobj, Vec3* pos, Fighter_Part part,
                       ItemKind kind, f32 facing_dir)
{
    Item_GObj* spawn_gobj;
    SpawnItem spawn;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = item_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;

    spawn_gobj = Item_80268B18(&spawn);
    if (spawn_gobj != NULL) {
        Item_8026AB54(spawn_gobj, item_gobj, part);
        db_80225DD8(spawn_gobj, item_gobj);
        return spawn_gobj;
    }
    return NULL;
}

void it_2725_Logic91_Destroyed(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    itpeachtoad_inline_1(item);
}

void it_802BDF40(Item_GObj* item_gobj)
{
    HSD_GObj* hsd_gobj;
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item != NULL) {
        itpeachtoad_inline_1(item);
        Item_8026A8EC(item_gobj);
    }
}

void it_802BDFA0(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802BDFC0(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void it_2725_Logic91_PickedUp(Item_GObj* item_gobj)
{
    u8 _[8];

    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    Item_802694CC(item_gobj);
    it_8026BB44(item_gobj);
    it_80274574(item_gobj);
}

bool itPeachtoad_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->x5CC_currentAnimFrame == 7.0f) {
        it_8026BB20(item_gobj);
    }
    if (item->x5CC_currentAnimFrame >= 53.0f) {
        it_8026BB44(item_gobj);
    }

    item = GET_ITEM(item_gobj);
    if (itpeachtoad_inline_2(item)) {
        item = GET_ITEM(item_gobj);
        itpeachtoad_inline_1(item);
        return true;
    }
    return false;
}

void it_802BE100(Item_GObj* item_gobj)
{
    HSD_JObj* hsd_jobj;
    u8 _[8];

    hsd_jobj = item_gobj->hsd_obj;
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    lb_8000BA0C(hsd_jobj, 10.0f);
    HSD_JObjAnimAll(hsd_jobj);
    lb_8000BA0C(hsd_jobj, 1.0f);
    it_80274574(item_gobj);
}

bool itPeachtoad_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->x5CC_currentAnimFrame >= 60.0f) {
        it_8026BB44(item_gobj);
    }

    item = GET_ITEM(item_gobj);
    if (itpeachtoad_inline_2(item)) {
        return true;
    }
    return false;
}

void it_2725_Logic91_EvtUnk(Item_GObj* item_gobj, Item_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
