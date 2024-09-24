#include <baselib/forward.h>

#include "itegg.h"

#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

/* 288DC4 */ static bool it_80288DC4(Item_GObj* gobj);
/* 288E6C */ static void it_80288E6C(Item_GObj* gobj);
/* 288EC4 */ static bool it_80288EC4(Item_GObj* gobj);
/* 288ECC */ static void it_80288ECC(Item_GObj* gobj);
/* 288ED0 */ static bool it_80288ED0(Item_GObj* gobj);
/* 288EFC */ static void it_80288EFC(Item_GObj* gobj);
/* 288F24 */ static bool it_80288F24(Item_GObj* gobj);
/* 288F2C */ static void it_80288F2C(Item_GObj* gobj);
/* 288F5C */ static bool it_80288F5C(Item_GObj* gobj);
/* 288FB0 */ static bool it_80288FB0(Item_GObj* gobj);
/* 288FB8 */ static void it_80288FB8(Item_GObj* gobj);
/* 289004 */ static void it_80289004(Item_GObj* gobj);
/* 289050 */ static bool it_80289050(Item_GObj* gobj);
/* 289094 */ static void it_80289094(Item_GObj* gobj);
/* 28912C */ static bool it_8028912C(Item_GObj* gobj);
/* 28914C */ static void it_8028914C(Item_GObj* gobj);
/* 289150 */ static bool it_80289150(Item_GObj* gobj);
/* 289158 */ static void it_80289158(Item_GObj* gobj);
/* 2891E0 */ static bool it_802891E0(Item_GObj* gobj);
/* 28920C */ static void it_8028920C(Item_GObj* gobj);
/* 289210 */ static bool it_80289210(Item_GObj* gobj);
/* 28966C */ static bool it_8028966C(Item_GObj* gobj);
/* 289674 */ static void it_80289674(Item_GObj* gobj);
/* 289678 */ static bool it_80289678(Item_GObj* gobj);

ItemStateTable it_803F5988[] = {
    { -1, it_80288EC4, it_80288ECC, it_80288ED0 },
    { -1, it_80288F24, it_80288F2C, it_80288F5C },
    { -1, it_80288FB0, it_80288FB8, NULL },
    { 0, it_80288F24, it_80289004, it_80289050 },
    { -1, it_8028966C, it_80289674, it_80289678 },
    { 1, it_8028912C, it_8028914C, it_80289150 },
    { -1, it_802891E0, it_8028920C, it_80289210 },
};

Item_GObj* it_80288C88(Item_GObj* gobj, Vec3* pos, Vec3* vel, float dir)
{
    SpawnItem spawn;
    Item* ip;
    Item_GObj* item_gobj = NULL;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);

        spawn.kind = It_Kind_Egg;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = 0.0F;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = dir;
        spawn.x3C_damage = 0;
        spawn.vel = *vel;
        spawn.x0_parent_gobj = ip->owner;
        spawn.x4_parent_gobj2 = gobj;
        spawn.x44_flag.bits.b0 = true;
        spawn.x40 = 0;

        item_gobj = Item_80268B18(&spawn);
        if (item_gobj != NULL) {
            Item* ip = GET_ITEM(item_gobj);
            ip->xDD0_flag.bits.b6 = false;
            ip->xD40 = 0.0F;
            it_80279BBC(ip);
            if (!ip->xDD0_flag.bits.b7) {
                it_802756E0(item_gobj);
            }
        }
    }

    return item_gobj;
}

void it_80288D98(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.egg.x0 = false;
    it_80288EFC(gobj);
}

inline s32 attrRand(EggVars* attrs)
{
    return HSD_Randi(attrs->rand_max);
}

bool it_80288DC4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    EggVars* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (attrRand(attrs) == 0) {
        return true;
    }

    {
        Vec3 pos;
        pos.x = pos.y = pos.z = 0.0F;
        if (it_8026F8B4(gobj, &ip->pos, &pos, 0)) {
            return false;
        }
    }

    it_8026F3D4(gobj, 0, attrs->x0, 0);
    return false;
}

void it_80288E6C(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    PAD_STACK(8);

    it_8026B390(gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80288EC4(Item_GObj* gobj)
{
    return false;
}

void it_80288ECC(Item_GObj* gobj) {}

bool it_80288ED0(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80288EFC);
    return false;
}

void it_80288EFC(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    return;
}

bool it_80288F24(Item_GObj* gobj)
{
    return false;
}

void it_80288F2C(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool it_80288F5C(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80288E6C);
    return false;
}

void it_80288F88(Item_GObj* gobj)
{
    Item_80268E5C((Item_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_80288FB0(Item_GObj* gobj)
{
    return false;
}

void it_80288FB8(Item_GObj* gobj) {}

void it_80288FBC(Item_GObj* gobj)
{
    it_80288FDC(gobj);
}

void it_80288FDC(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void it_80289004(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool it_80289050(Item_GObj* gobj)
{
    if (it_8026DA08(gobj)) {
        return it_80289218(gobj);
    }
    return false;
}

void it_80289094(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    ip->x40_vel.x = 0;
    ip->x40_vel.y = 0;
    ip->xDCF_flag.bits.b2 = true;
    ip->xDD4_itemVar.egg.x0 = true;
    ip->xDD4_itemVar.egg.rand_max = 20;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool it_8028912C(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void it_8028914C(Item_GObj* gobj) {}

bool it_80289150(Item_GObj* gobj)
{
    return false;
}

void it_80289158(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);

    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    it_802756D0(gobj);
    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.bits.b2 = true;
    ip->xDD4_itemVar.egg.x0 = true;
    ip->xDD4_itemVar.egg.rand_max = 40;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool it_802891E0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    --ip->xDD4_itemVar.egg.rand_max;
    return ip->xDD4_itemVar.egg.rand_max > 0 ? false : true;
}

void it_8028920C(Item_GObj* gobj) {}

bool it_80289210(Item_GObj* gobj)
{
    return false;
}

bool it_80289218(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;

    if (ip->xDD4_itemVar.egg.x0) {
        return false;
    }
    if (it_80288DC4(gobj)) {
        it_80289094(gobj);
        return false;
    }
    efSync_Spawn(1232, gobj, &ip->pos);
    Item_8026AE84(ip, 244, 127, 64);
    it_80289158(gobj);
    return false;
}

bool it_802893D4(Item_GObj* gobj)
{
    PAD_STACK(8);
    return it_80289218(gobj);
}

bool it_80289470(Item_GObj* gobj)
{
    PAD_STACK(8);
    return it_80289218(gobj);
}

bool it_8028950C(Item_GObj* gobj)
{
    PAD_STACK(8);
    return it_80289218(gobj);
}

bool it_802895A8(Item_GObj* gobj)
{
    PAD_STACK(8);
    return it_80289218(gobj);
}

void it_80289644(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_8028966C(Item_GObj* gobj)
{
    return false;
}

void it_80289674(Item_GObj* gobj) {}

bool it_80289678(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80288E6C, it_80288EFC);
    return false;
}

void it_802896AC(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}
