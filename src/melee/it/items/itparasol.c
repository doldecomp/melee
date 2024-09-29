#include <dolphin/mtx/forward.h>

#include "itparasol.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <common_structs.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

/// @todo Fix these to be in a single file, not math.h
#define M_PI 3.14159265358979323846
static float const deg_to_rad = M_PI / 180;

ItemStateTable it_803F5AB0[] = {
    { -1, it_8028B144, it_8028B14C, it_8028B150 },
    { +4, it_8028B1A4, it_8028B2EC, it_8028B394 },
    { +0, it_8028B1A4, it_8028B42C, it_8028B394 },
    { -1, it_8028B5A8, it_8028B5B0, it_8028B5B4 },
    { +1, it_8028B60C, it_8028B614, NULL },
    { +2, it_8028B60C, it_8028B614, NULL },
    { +3, it_8028B60C, it_8028B614, NULL },
    { +4, it_8028B60C, it_8028B614, NULL },
    { +5, it_8028B60C, it_8028B614, NULL },
    { +6, it_8028B60C, it_8028B614, NULL },
    { +7, it_8028B60C, it_8028B614, NULL },
};

int it_8028B08C(Item_GObj* item_gobj, int statenum)
{
    static int it_803F5B60[] = {
        20, 16, 45, 2, 20, 30, 40, 16,
    };
    return it_803F5B60[it_803F5AB0[statenum].anim_id];
}

void it_8028B0B8(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->xDCE_flag.b7 = false;
    it_8028B17C(item_gobj);
}

void it_8028B0EC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    it_8026B390(item_gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_8028B144(Item_GObj* item_gobj)
{
    return false;
}

void it_8028B14C(Item_GObj* item_gobj) {}

bool it_8028B150(Item_GObj* item_gobj)
{
    it_8026D62C(item_gobj, it_8028B17C);
    return false;
}

void it_8028B17C(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
}

static inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return +x;
    }
}

static inline HSD_JObj* jobj_child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    } else {
        return jobj->child;
    }
}

bool it_8028B1A4(Item_GObj* item_gobj)
{
    f32 ry, fm;
    Item* item = item = GET_ITEM(item_gobj);
    f32* attrs = item->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(item_gobj);

    if (jobj != NULL) {
        jobj = jobj_child(jobj);
        ry = HSD_JObjGetRotationY(jobj);
        fm = attrs[2] + fabsf(item->x40_vel.y * attrs[3]);
        fm *= item->facing_dir;
        ry = deg_to_rad * fm + ry;
        HSD_JObjSetRotationY(jobj, ry);
    }
    return false;
}

inline void decelerateItemX(Item* item, f32 decel_x)
{
    if (fabsf(item->x40_vel.x) > decel_x) {
        if (item->x40_vel.x > decel_x) {
            item->x40_vel.x -= decel_x;
        }
        if (item->x40_vel.x < -decel_x) {
            item->x40_vel.x += decel_x;
        }
    } else {
        item->x40_vel.x = 0.0F;
    }
}

void it_8028B2EC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;
    f32* attrs = item->xC4_article_data->x4_specialAttributes;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    decelerateItemX(item, attrs[0]);
}

bool it_8028B394(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_8028B0EC);
    return false;
}

void it_8028B3C0(Item_GObj* item_gobj)
{
    it_8028B3E0(item_gobj);
}

void it_8028B3E0(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Item_8026AE84(item, 0xF7, 0x7F, 0x40);
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_8028B42C(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;
    f32* attrs = item->xC4_article_data->x4_specialAttributes;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    decelerateItemX(item, attrs[1]);
}

bool it_8028B4D4(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_8028B4F8(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_8028B51C(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_8028B540(Item_GObj* item_gobj)
{
    return it_80273030(item_gobj);
}

bool it_8028B560(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

void it_8028B580(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 3, ITEM_ANIM_UPDATE);
}

bool it_8028B5A8(Item_GObj* item_gobj)
{
    return false;
}

void it_8028B5B0(Item_GObj* item_gobj) {}

bool it_8028B5B4(Item_GObj* item_gobj)
{
    it_8026E8C4(item_gobj, it_8028B0EC, it_8028B17C);
    return false;
}

void it_8028B5E8(Item_GObj* item_gobj)
{
    it_8028B618(item_gobj, 1.0F);
}

bool it_8028B60C(Item_GObj* item_gobj)
{
    return false;
}

void it_8028B614(Item_GObj* item_gobj) {}

static inline void animSpeed(Item_GObj* item_gobj, f32 speed, int statenum)
{
    Item* item = GET_ITEM(item_gobj);
    if (statenum > 4) {
        Item_8026AE84(item, 0xF7, 0x7F, 0x40);
    }
    item->x5D0_animFrameSpeed = speed;
    Item_80268E5C(item_gobj, statenum, ITEM_ANIM_UPDATE);
}

void it_8028B618(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 4);
}

void it_8028B648(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 5);
}

void it_8028B6B0(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 6);
}

void it_8028B718(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 7);
}

void it_8028B780(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 8);
}

void it_8028B7E8(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 9);
}

void it_8028B850(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 10);
}

void it_8028B8B8(Item_GObj* item_gobj, HSD_GObj* arg1)
{
    it_8026B894(item_gobj, arg1);
}
