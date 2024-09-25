#include "itlgun.h"

#include "itlgunray.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

/* 28E7D8 */ static void it_8028E7D8(Item_GObj*);
/* 28E828 */ static bool motion0_Anim(Item_GObj*);
/* 28E830 */ static void motion0_Phys(Item_GObj*);
/* 28E834 */ static bool motion0_Coll(Item_GObj*);
/* 28E860 */ static void it_8028E860(Item_GObj*);
/* 28E888 */ static bool motion1_Anim(Item_GObj*);
/* 28E890 */ static void motion1_Phys(Item_GObj*);
/* 28E8C0 */ static bool motion1_Coll(Item_GObj*);
/* 28E92C */ static bool motion2_Anim(Item_GObj*);
/* 28E934 */ static void motion2_Phys(Item_GObj*);
/* 28E96C */ static bool motion3_Anim(Item_GObj*);
/* 28E9B4 */ static void motion3_Phys(Item_GObj*);
/* 28EA08 */ static void motion4_Phys(Item_GObj*);
/* 28EB28 */ static bool motion5_Anim(Item_GObj*);
/* 28EB30 */ static void motion5_Phys(Item_GObj*);
/* 28EB34 */ static bool motion5_Coll(Item_GObj*);

ItemStateTable it_803F5CC8[] = {
    { -1, motion0_Anim, motion0_Phys, motion0_Coll },
    { -1, motion1_Anim, motion1_Phys, motion1_Coll },
    { -1, motion2_Anim, motion2_Phys, NULL },
    { 0, motion3_Anim, motion3_Phys, NULL },
    { +1, motion1_Anim, motion4_Phys, motion1_Coll },
    { -1, motion5_Anim, motion5_Phys, motion5_Coll },
};

void it_8028E738(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItLGunAttr* item_spec_attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xD4C = item_spec_attr->max_ammo;
    ip->xDD4_itemVar.lgun.timer = 0;
    it_8028E860(gobj);
}

void it_8028E774(Item_GObj* gobj, Vec3* arg1)
{
    ItLGunAttr* da = GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    arg1->x = da->pos.x;
    arg1->y = da->pos.y;
    arg1->z = da->pos.z;
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

bool motion0_Anim(Item_GObj* gobj)
{
    return false;
}

void motion0_Phys(Item_GObj* gobj) {}

bool motion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028E860);
    return false;
}

void it_8028E860(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool motion1_Anim(HSD_GObj* gobj)
{
    return false;
}

void motion1_Phys(Item_GObj* gobj)
{
    ItemAttr* item_comm_attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
}

bool motion1_Coll(HSD_GObj* gobj)
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

bool motion2_Anim(HSD_GObj* gobj)
{
    return false;
}

void motion2_Phys(HSD_GObj* gobj) {}

void it_8028E938(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.lgun.timer = 40;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool motion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    --ip->xDD4_itemVar.lgun.timer;
    if (ip->xDD4_itemVar.lgun.timer <= 0) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    }
    return false;
}

void motion3_Phys(Item_GObj* gobj) {}

void it_8028E9B8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void it_8028E9E0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void motion4_Phys(Item_GObj* gobj)
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

bool motion5_Anim(Item_GObj* gobj)
{
    return false;
}

void motion5_Phys(Item_GObj* gobj) {}

bool motion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8028E7D8, it_8028E860);
    return false;
}

void it_8028EB68(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
