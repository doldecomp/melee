#include "it/forward.h"

#include "itrabbitc.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/items/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

/* 295138 */ static void it_80295138(Item_GObj*);
/* 295188 */ static bool itRabbitc_UnkMotion0_Anim(Item_GObj*);
/* 295190 */ static void itRabbitc_UnkMotion0_Phys(Item_GObj*);
/* 295194 */ static bool itRabbitc_UnkMotion0_Coll(Item_GObj*);
/* 2951C0 */ static void it_802951C0(Item_GObj*);
/* 2951E8 */ static bool itRabbitc_UnkMotion3_Anim(Item_GObj*);
/* 2951F0 */ static void itRabbitc_UnkMotion1_Phys(Item_GObj*);
/* 295220 */ static bool itRabbitc_UnkMotion1_Coll(Item_GObj*);
/* 295290 */ static bool itRabbitc_UnkMotion2_Anim(Item_GObj*);
/* 2952DC */ static void itRabbitc_UnkMotion3_Phys(Item_GObj*);
/* 29530C */ static bool itRabbitc_UnkMotion3_Coll(Item_GObj*);
/* 295368 */ static bool itRabbitc_UnkMotion4_Anim(Item_GObj*);
/* 295370 */ static void itRabbitc_UnkMotion4_Phys(Item_GObj*);
/* 295374 */ static bool itRabbitc_UnkMotion4_Coll(Item_GObj*);

ItemStateTable it_803F6270[] = {
    { -1, itRabbitc_UnkMotion0_Anim, itRabbitc_UnkMotion0_Phys, itRabbitc_UnkMotion0_Coll },
    { -1, itRabbitc_UnkMotion3_Anim, itRabbitc_UnkMotion1_Phys, itRabbitc_UnkMotion1_Coll },
    { -1, itRabbitc_UnkMotion2_Anim, NULL, NULL },
    { -1, itRabbitc_UnkMotion3_Anim, itRabbitc_UnkMotion3_Phys, itRabbitc_UnkMotion3_Coll },
    { -1, itRabbitc_UnkMotion4_Anim, itRabbitc_UnkMotion4_Phys, itRabbitc_UnkMotion4_Coll },
};

bool it_80294DA0(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

HSD_GObj* it_80294DC0(Vec3* pos)
{
    Item_GObj* item_gobj;
    SpawnItem spawn;

    spawn.kind = It_Kind_RabbitC;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = 0;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B5C(&spawn);
    if (item_gobj != NULL) {
        it_80295138(item_gobj);
    }
    return item_gobj;
}

void it_80294E78(Item_GObj* item_gobj, f32 arg1)
{
    PAD_STACK(4);

    it_80272F7C(it_80272CC0(item_gobj, 1), arg1);
}

void it_80294EB0(Item_GObj* item_gobj, Vec3* input_pos1, Vec3* input_pos2)
{
    HSD_JObj* item_jobj_var;
    Vec3 pos_var;
    PAD_STACK(4);

    item_jobj_var = it_80272CC0(item_gobj, 8);
    HSD_JObjGetTranslation(item_jobj_var, &pos_var);
    pos_var.x += input_pos1->x;
    pos_var.y += input_pos1->y;
    pos_var.z += input_pos1->z;
    HSD_JObjSetTranslate(item_jobj_var, &pos_var);

    item_jobj_var = it_80272CC0(item_gobj, 4);
    HSD_JObjGetTranslation(item_jobj_var, &pos_var);
    pos_var.x += input_pos2->x;
    pos_var.y += input_pos2->y;
    pos_var.z += input_pos2->z;
    HSD_JObjSetTranslate(item_jobj_var, &pos_var);
}

void it_802950D4(Item_GObj* item_gobj, int arg1)
{
    HSD_JObj* item_jobj;
    PAD_STACK(4);

    item_jobj = it_80272CC0(item_gobj, 3);
    if (arg1 != 0) {
        it_80272A18(item_jobj);
        return;
    }
    it_80272A3C(item_jobj);
}

void it_80295118(Item_GObj* item_gobj)
{
    it_802951C0(item_gobj);
}

void it_80295138(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    it_8026B390(item_gobj);
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool itRabbitc_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    return false;
}

void itRabbitc_UnkMotion0_Phys(Item_GObj* item_gobj) {}

bool itRabbitc_UnkMotion0_Coll(Item_GObj* item_gobj)
{
    it_8026D62C(item_gobj, it_802951C0);
    return false;
}

void it_802951C0(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itRabbitc_UnkMotion3_Anim(Item_GObj* item_gobj)
{
    return false;
}

void itRabbitc_UnkMotion1_Phys(Item_GObj* item_gobj)
{
    ItemAttr* attr;

    attr = ((Item*) item_gobj->user_data)->xCC_item_attr;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itRabbitc_UnkMotion1_Coll(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_80295138);
    return false;
}

void it_8029524C(Item_GObj* item_gobj)
{
    PAD_STACK(8);

    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
    it_80272A3C(it_80272CC0(item_gobj, 3));
}

bool itRabbitc_UnkMotion2_Anim(Item_GObj* item_gobj)
{
    return false;
}

void it_80295298(Item_GObj* item_gobj)
{
    PAD_STACK(8);

    Item_80268E5C(item_gobj, 1, 6);
    it_80272A18(it_80272CC0(item_gobj, 3));
}

void itRabbitc_UnkMotion3_Phys(Item_GObj* item_gobj)
{
    ItemAttr* attr;

    attr = ((Item*) item_gobj->user_data)->xCC_item_attr;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itRabbitc_UnkMotion3_Coll(Item_GObj* item_gobj)
{
    if (it_8026DA08(item_gobj) != 0) {
        return true;
    }
    return false;
}

void it_80295340(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 4, ITEM_ANIM_UPDATE);
}

bool itRabbitc_UnkMotion4_Anim(Item_GObj* item_gobj)
{
    return false;
}

void itRabbitc_UnkMotion4_Phys(Item_GObj* item_gobj) {}

bool itRabbitc_UnkMotion4_Coll(Item_GObj* item_gobj)
{
    it_8026E8C4(item_gobj, it_80295138, it_802951C0);
    return false;
}

void it_802953A8(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
