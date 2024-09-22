#include "itlgun.h"

#include "itlgunray.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/types.h"

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

/* 28E7D8 */ static void it_8028E7D8(Item_GObj*);
/* 28E828 */ static bool it_8028E828(Item_GObj*);
/* 28E830 */ static void it_8028E830(Item_GObj*);
/* 28E834 */ static bool it_8028E834(Item_GObj*);
/* 28E860 */ static void it_8028E860(Item_GObj*);
/* 28E888 */ static bool it_8028E888(Item_GObj*);
/* 28E890 */ static void it_8028E890(Item_GObj*);
/* 28E8C0 */ static bool it_8028E8C0(Item_GObj*);
/* 28E92C */ static bool it_8028E92C(Item_GObj*);
/* 28E934 */ static void it_8028E934(Item_GObj*);
/* 28E96C */ static bool it_8028E96C(Item_GObj*);
/* 28E9B4 */ static void it_8028E9B4(Item_GObj*);
/* 28EA08 */ static void it_8028EA08(Item_GObj*);
/* 28EB28 */ static bool it_8028EB28(Item_GObj*);
/* 28EB30 */ static void it_8028EB30(Item_GObj*);
/* 28EB34 */ static bool it_8028EB34(Item_GObj*);

ItemStateTable it_803F5CC8[] = {
    { -1, it_8028E828, it_8028E830, it_8028E834 },
    { -1, it_8028E888, it_8028E890, it_8028E8C0 },
    { -1, it_8028E92C, it_8028E934, NULL },
    { 0, it_8028E96C, it_8028E9B4, NULL },
    { +1, it_8028E888, it_8028EA08, it_8028E8C0 },
    { -1, it_8028EB28, it_8028EB30, it_8028EB34 },
};

void it_8028E738(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItLGunAttr* item_spec_attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xD4C = item_spec_attr->x0;
    ip->xDD4_itemVar.capsule.x0 = false;
    it_8028E860(gobj);
}

void it_8028E774(Item_GObj* gobj, Vec3* arg1)
{
    ItLGunAttr* da = GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    arg1->x = da->x4;
    arg1->y = da->x8;
    arg1->z = da->xC;
}

void it_8028E79C(Item_GObj* gobj, Vec3* pos, f32 facing_dir)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD4C > 0) {
        --ip->xD4C;
    }
    it_80298168(ip->owner, pos, facing_dir);
}

void it_8028E7D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_8028E828(Item_GObj* gobj)
{
    return false;
}

void it_8028E830(Item_GObj* gobj) {}

bool it_8028E834(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028E860);
    return false;
}

void it_8028E860(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_8028E888(HSD_GObj* gobj)
{
    return false;
}

void it_8028E890(Item_GObj* gobj)
{
    ItemAttr* item_comm_attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
}

bool it_8028E8C0(HSD_GObj* gobj)
{
    if (GET_ITEM(gobj)->xD4C != 0) {
        it_8026E15C(gobj, it_8028E7D8);
        return false;
    }
    return it_8026DF34(gobj);
}

void it_8028E904(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_8028E92C(HSD_GObj* gobj)
{
    return false;
}

void it_8028E934(HSD_GObj* gobj) {}

void it_8028E938(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.lgun.x0 = 40;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool it_8028E96C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    --ip->xDD4_itemVar.lgun.x0;
    if (ip->xDD4_itemVar.lgun.x0 <= 0) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    }
    return false;
}

void it_8028E9B4(Item_GObj* gobj) {}

void it_8028E9B8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void it_8028E9E0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void it_8028EA08(Item_GObj* gobj)
{
    ItemAttr* item_comm_attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool it_8028EA54(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_8028EA78(Item_GObj* gobj)
{
    itColl_BounceOffVictim((Item_GObj*) gobj);
    return false;
}

bool it_8028EA9C(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_8028EAC0(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_8028EAE0(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_8028EB00(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool it_8028EB28(Item_GObj* gobj)
{
    return false;
}

void it_8028EB30(Item_GObj* gobj) {}

bool it_8028EB34(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8028E7D8, it_8028E860);
    return false;
}

void it_8028EB68(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
