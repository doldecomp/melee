#include <platform.h>
#include <dolphin/mtx/forward.h>

#include "itcapsule.h"

#include "math.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lb_00F9.h"

#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

ItemStateTable it_803F5468[] = {
    {
        -1,
        it_8027D110,
        it_8027D118,
        it_8027D11C,
    },
    {
        -1,
        it_8027D170,
        it_8027D178,
        it_8027D1A8,
    },
    {
        -1,
        it_8027D1FC,
        it_8027D204,
        NULL,
    },
    {
        0,
        it_8027D170,
        it_8027D258,
        it_8027D2A4,
    },
    {
        0,
        it_8027D170,
        it_8027D178,
        it_8027D1A8,
    },
    {
        1,
        it_8027D30C,
        it_8027D32C,
        it_8027D330,
    },
    {
        -1,
        it_8027D478,
        it_8027D480,
        it_8027D484,
    },
};

void it_8027CF00(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDD4_itemVar.capsule.x0 = 0;
    it->xDD4_itemVar.capsule.x4 = 0;
    it_8027D148(item_gobj);
}

void it_8027CF30(Item_GObj* gobj)
{
    Vec3 sp18;
    u8 _[8] = { 0 };

    Item* it = GET_ITEM(gobj);
    ItCapsuleAttr* attr = it->xC4_article_data->x4_specialAttributes;

    sp18.x = sp18.y = sp18.z = 0.0F;
    if (!it_8026F8B4(gobj, &it->pos, &sp18, 0)) {
        if (!HSD_Randi(attr->x4)) {
            it_8027D2DC(gobj);
            it->xDD4_itemVar.capsule.x0 = false;
        } else {
            it_8026F3D4(gobj, 0, attr->x0, 0);
            it->xDD4_itemVar.capsule.x0 = true;
        }
    } else {
        it->xDD4_itemVar.capsule.x0 = true;
    }
}

void it_8027CFE8(Item_GObj* item_gobj)
{
    u8 _[4] = { 0 };
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    Item* it = GET_ITEM(item_gobj);
    Vec3 sp14;

    it_8026B3A8(item_gobj);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it->x5D0_animFrameSpeed = 1.0F;
    it_80273454(item_gobj);
    it->xDD4_itemVar.capsule.x4 = true;
    it_80272C08(item_gobj);
    it_80275444(item_gobj);
    it_802756D0(item_gobj);
    it_8026BD24(item_gobj);
    it_8027518C(item_gobj);
    sp14 = it->pos;
    lb_800119DC(&sp14, 0x78, 1.0F, 0.02F, 60 * M_PI / 180);
    Item_80268E5C(item_gobj, 5, 2);
}

void it_8027D0B8(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    u8 _[4] = { 0 };
    it_8026B390(gobj);
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, 2);
}

bool it_8027D110(Item_GObj* gobj)
{
    return false;
}

void it_8027D118(Item_GObj* gobj) {}

bool it_8027D11C(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8027D148);
    return false;
}

void it_8027D148(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 2);
}

bool it_8027D170(Item_GObj* gobj)
{
    return false;
}

void it_8027D178(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                it->xCC_item_attr->x14_fall_speed_max);
}

bool it_8027D1A8(Item_GObj* gobj)
{
    it_8026E15C(gobj, &it_8027D0B8);
    return 0;
}

void it_8027D1D4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, 2);
}

bool it_8027D1FC(Item_GObj* gobj)
{
    return false;
}

void it_8027D204(Item_GObj* gobj) {}

void it_8027D208(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void it_8027D230(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void it_8027D258(Item_GObj* item_gobj)
{
    it_8027D178(item_gobj);
    it_80274658(item_gobj, it_804D6D28->x68_float);
}

bool it_8027D2A4(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    it_8026E414(item_gobj, it_8027CF30);
    return it->xDD4_itemVar.capsule.x0;
}

void it_8027D2DC(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (!it->xDD4_itemVar.capsule.x4) {
        it_8027CFE8(item_gobj);
    }
}

bool it_8027D30C(Item_GObj* item_gobj)
{
    return it_802751D8(item_gobj);
}

void it_8027D32C(Item_GObj* gobj) {}

bool it_8027D330(Item_GObj* gobj)
{
    return false;
}

// Incorrect stack offsets for inlined it_8027CF30
bool it_8027D338(HSD_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    u8 _[4] = { 0 };

    if (it->msid != 5) {
        it_8027CF30(item_gobj);
    }
    return it->xDD4_itemVar.capsule.x0;
}

static bool it_8027D338_autoinlined(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (it->msid != 5) {
        it_8027CF30(item_gobj);
    }
    return it->xDD4_itemVar.capsule.x0;
}

bool it_8027D414(Item_GObj* item_gobj)
{
    return it_8027D338_autoinlined(item_gobj);
}

void it_8027D450(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 6, ITEM_ANIM_UPDATE);
}

bool it_8027D478(Item_GObj* gobj)
{
    return false;
}

void it_8027D480(Item_GObj* gobj) {}

bool it_8027D484(Item_GObj* item_gobj)
{
    it_8026E8C4(item_gobj, it_8027D0B8, it_8027D148);
    return false;
}

bool it_8027D4B8(Item_GObj* item_gobj)
{
    return it_8027D338_autoinlined(item_gobj);
}

bool it_8027D4F4(Item_GObj* item_gobj)
{
    return it_8027D338_autoinlined(item_gobj);
}

bool it_8027D530(Item_GObj* item_gobj)
{
    NOT_IMPLEMENTED;
}

bool it_8027D614(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (it->msid == 3 || it->msid == 4) {
        itColl_BounceOffShield(item_gobj);
    }
    return false;
}

void it_8027D650(Item_GObj* item_gobj, HSD_GObj* ref)
{
    it_8026B894(item_gobj, ref);
}
