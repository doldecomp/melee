#include <baselib/forward.h>

#include "itegg.h"

#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

/// @todo Might be #EggVars
struct ItEggAttrs {
    /* +0 */ bool x0;
    /* +4 */ int rand_max;
};

void it_80288EFC(HSD_GObj*); /* static */

Item_GObj* it_80288C88(HSD_GObj* arg_gobj, void* arg1, Vec3* arg2, f32 arg8)
{
    SpawnItem spawn;
    Item* temp_r29;
    Item_GObj* var_r30;
    u8 _[10] = { 0 };

    var_r30 = NULL;
    if (arg_gobj != NULL) {
        spawn.kind = It_Kind_Egg;
        spawn.prev_pos = *arg2;
        spawn.prev_pos.z = 0;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = arg8;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0;
        spawn.x0_parent_gobj = GET_ITEM(arg_gobj)->owner;
        spawn.x4_parent_gobj2 = arg_gobj;
        spawn.x44_flag.bits.b0 = 1;
        spawn.x40 = 0;
        var_r30 = Item_80268B18((SpawnItem*) &spawn);
        if (var_r30 != NULL) {
            temp_r29 = var_r30->user_data;
            temp_r29->xDD0_flag.u8 &= ~2;
            temp_r29->xD40 = 0.0F;
            it_80279BBC(temp_r29);
            if (!(temp_r29->xDD0_flag.u8 & 1)) {
                it_802756E0((HSD_GObj*) var_r30);
            }
        }
    }
    return var_r30;
}

void it_80288D98(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);

    item->xDD4_itemVar.capsule.x0 = 0;
    it_80288EFC((HSD_GObj*) item);
}

bool it_80288DC4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    struct ItEggAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (HSD_Randi(attrs->rand_max) == 0) {
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
    u8 _[8] = { 0 };
    Item* item = GET_ITEM(gobj);

    it_8026B390(gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80288EC4(HSD_GObj* gobj)
{
    return false;
}

void it_80288ECC(HSD_GObj* gobj) {}

bool it_80288ED0(Item_GObj* gobj)
{
    it_8026D62C(gobj, (HSD_GObjEvent) it_80288EFC);
    return false;
}

void it_80288EFC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    return;
}

bool it_80288F24(HSD_GObj* gobj)
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
    Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_80288FB0(HSD_GObj* gobj)
{
    return false;
}

void it_80288FB8(HSD_GObj* gobj) {}

void it_80288FBC(Item_GObj* gobj)
{
    it_80288FDC(gobj);
}

void it_80288FDC(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

void it_80289004(Item_GObj* gobj)
{
    ItemAttr* temp_r4 = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658((HSD_GObj*) gobj, it_804D6D28->x68_float);
}

bool it_80289050(Item_GObj* gobj)
{
    if (it_8026DA08(gobj) != false) {
        return it_80289218(gobj);
    }
    return false;
}

void it_80289094(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0((HSD_GObj*) gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    item->x40_vel.x = 0;
    item->x40_vel.y = 0;
    item->xDCF_flag.bits.b2 = 1;
    item->xDD4_itemVar.capsule.x0 = 1;
    item->xDD4_itemVar.capsule.x4 = 0x14;
    Item_80268E5C((HSD_GObj*) gobj, 5, ITEM_ANIM_UPDATE);
}

bool it_8028912C(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void it_8028914C(HSD_GObj* gobj) {}

bool it_80289150(HSD_GObj* gobj)
{
    return false;
}

void it_80289158(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    HSD_JObjSetFlagsAll(gobj->hsd_obj, 0x10U);
    it_802756D0(gobj);
    M2C_FIELD(item, f32*, 0x40) = (f32) 0.0F;
    M2C_FIELD(item, f32*, 0x44) = (f32) 0.0F;
    M2C_FIELD(item, u8*, 0xDCF) = (u8) (M2C_FIELD(item, u8*, 0xDCF) | 0x20);
    M2C_FIELD(item, s32*, 0xDD4) = 1;
    M2C_FIELD(item, s32*, 0xDD8) = 0x28;
    it_8026B3A8((Item_GObj*) gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool it_802891E0(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);

    item->xDD4_itemVar.Egg.filler[4] -= 1;

    if (item->xDD4_itemVar.Egg.filler[4] > 0) {
        return false;
    } else {
        return true;
    }
}

void it_8028920C(HSD_GObj* gobj) {}

bool it_80289210(HSD_GObj* gobj)
{
    return false;
}

static inline void inlineA1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.bits.b2 = true;
    ip->xDD4_itemVar.capsule.x0 = 1;
    ip->xDD4_itemVar.capsule.x4 = 20;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

static inline void inlineA2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    u8 _[8] = { 0 };
    HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
    it_802756D0(gobj);
    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.bits.b2 = true;
    ip->xDD4_itemVar.capsule.x0 = true;
    ip->xDD4_itemVar.capsule.x4 = 40;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool it_80289218(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.capsule.x0) {
        return false;
    }
    if (it_80288DC4(gobj)) {
        inlineA1(gobj);
        return false;
    }
    efSync_Spawn(1232, gobj, &ip->pos);
    Item_8026AE84(ip, 244, 0x7F, 0x40);
    inlineA2(gobj);
    return false;
}

int it_802893D4(Item_GObj* arg0)
{
    Item* temp_r31;
    s32 temp_ret;

    temp_r31 = arg0->user_data;
    if ((s32) temp_r31->xDD4_itemVar.capsule.x0 != 0) {
        return 0;
    }
    temp_ret = it_80288DC4(arg0);
    if (temp_ret != 0) {
        it_80289094(arg0);
        return 0;
    }
    efSync_Spawn(0x4D0, arg0, &temp_r31->pos, M2C_BITWISE(f32, temp_ret));
    Item_8026AE84(temp_r31, 0xF4, 0x7F, 0x40);
    it_80289158(arg0);
    return 0;
}

int it_80289470(Item_GObj* arg0)
{
    Item* temp_r31;
    s32 temp_ret;

    temp_r31 = arg0->user_data;
    if ((s32) temp_r31->xDD4_itemVar.capsule.x0 != 0) {
        return 0;
    }
    temp_ret = it_80288DC4(arg0);
    if (temp_ret != 0) {
        it_80289094(arg0);
        return 0;
    }
    efSync_Spawn(0x4D0, arg0, &temp_r31->pos, M2C_BITWISE(f32, temp_ret));
    Item_8026AE84(temp_r31, 0xF4, 0x7F, 0x40);
    it_80289158(arg0);
    return 0;
}

int it_8028950C(Item_GObj* arg0)
{
    Item* temp_r31;
    s32 temp_ret;

    temp_r31 = arg0->user_data;
    if ((s32) temp_r31->xDD4_itemVar.capsule.x0 != 0) {
        return 0;
    }
    temp_ret = it_80288DC4(arg0);
    if (temp_ret != 0) {
        it_80289094(arg0);
        return 0;
    }
    efSync_Spawn(0x4D0, arg0, &temp_r31->pos, M2C_BITWISE(f32, temp_ret));
    Item_8026AE84(temp_r31, 0xF4, 0x7F, 0x40);
    it_80289158(arg0);
    return 0;
}

int it_802895A8(Item_GObj* arg0)
{
    Item* temp_r31;
    s32 temp_ret;

    temp_r31 = arg0->user_data;
    if ((s32) temp_r31->xDD4_itemVar.capsule.x0 != 0) {
        return 0;
    }
    temp_ret = it_80288DC4(arg0);
    if (temp_ret != 0) {
        it_80289094(arg0);
        return 0;
    }
    efSync_Spawn(0x4D0, arg0, &temp_r31->pos, M2C_BITWISE(f32, temp_ret));
    Item_8026AE84(temp_r31, 0xF4, 0x7F, 0x40);
    it_80289158(arg0);
    return 0;
}

void it_80289644(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_8028966C(HSD_GObj* gobj)
{
    return false;
}

void it_80289674(HSD_GObj* gobj) {}

bool it_80289678(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80288E6C, it_80288EFC);
    return false;
}

void it_802896AC(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, (HSD_GObj*) ref);
}

ItemStateTable it_803F5988[] = {
    { -1, it_80288EC4, it_80288ECC, it_80288ED0 },
    { -1, it_80288F24, it_80288F2C, it_80288F5C },
    { -1, it_80288FB0, it_80288FB8, NULL },
    { 0, it_80288F24, it_80289004, it_80289050 },
    { -1, it_8028966C, it_80289674, it_80289678 },
    { 1, it_8028912C, it_8028914C, it_80289150 },
    { -1, it_802891E0, it_8028920C, it_80289210 },
};
