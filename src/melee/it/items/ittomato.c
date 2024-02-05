#include "ittomato.h"

#include <baselib/jobj.h>
#include <melee/it/inlines.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/it/items/it_27CF.h>

const f32 it_804DC8B0 = 0x00000000;
const f32 it_804DC8B4 = 0xBF800000;
extern M2C_UNK gm_80473A18;

void it_802843E4(HSD_GObj* gobj);
void it_80284458(HSD_GObj* gobj);
void it_80284358(Item_GObj* gobj);

HSD_GObj* it_802841B4(s32 arg0, Vec3* arg1, s32 arg2)
{
    u8 sp5C; // idk
    s32 sp58;
    s16 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    Item* temp_r5;
    Item_GObj* var_r3;
    f32 temp_r0;

    var_r3 = NULL;
    if (arg0 != 0) {
        sp20 = 9;
        temp_r0 = arg1->y;
        sp38 = arg1->x;
        sp3C = temp_r0;
        sp40 = arg1->z;
        sp40 = it_804DC8B0;
        sp2C = sp38;
        sp30 = temp_r0;
        sp34 = sp40;
        sp50 = it_804DC8B4;
        sp54 = 0;
        sp4C = it_804DC8B0;
        sp48 = it_804DC8B0;
        sp44 = it_804DC8B0;
        sp18 = 0;
        sp1C = sp18;
        sp5C = 0x80;
        sp58 = 0;
        var_r3 = Item_80268B18(NULL);
    }
    if (var_r3) {
        temp_r5 = var_r3->user_data;
        temp_r5->xDD4_itemVar.Egg.filler[4] |= 0x80;
        temp_r5->xDD4_itemVar.star.x8 = M2C_BITWISE(f32, arg2);
    }
    return var_r3;
}

void it_8028428C(Item_GObj* gobj)
{
    Item* ip;

    ip = gobj->user_data;
    ip->xDD4_itemVar.capsule.x0 =
        M2C_FIELD(ip->xC4_article_data->x4_specialAttributes, s32*, 4);
}

void it_802842A4(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    void* temp_r30 = item->xC4_article_data->x4_specialAttributes;

    it_8026B390(arg0);
    item->x40_vel.x = 0;
    item->x40_vel.y = it_804DC8B0;
    item->x40_vel.z = 0;

    item->xDD4_itemVar.capsule.x0 = M2C_FIELD(temp_r30, s32*, 0);
    item->xDD4_itemVar.Egg.filler[4] &= ~0x80;
    item->xDD4_itemVar.star.x8 = 0.0f;

    it_80284358(arg0);
}

void it_80284324(Item_GObj* arg0)
{
    Item* temp_r4;

    temp_r4 = arg0->user_data;
    if ((((temp_r4->xDD4_itemVar.Egg.filler[4] << 0x18) & 0xC0000000) >>
         0x1F) != 0)
    {
        M2C_FIELD(
            (&gm_80473A18 + M2C_BITWISE(s32, temp_r4->xDD4_itemVar.star.x8)),
            s8*, 0x90) = 0;
    }
}

void it_80284358(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80284380(HSD_GObj* gobj)
{
    return false;
}

void it_80284388(Item_GObj* gobj)
{
    ItemAttr* attr;

    Item* item = GET_ITEM(gobj);
    attr = item->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_802843B8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802843E4);
    return false;
}

void it_802843E4(HSD_GObj* gobj)
{
    void* ip;

    ip = gobj->user_data;
    M2C_FIELD(ip, f32*, 0x40) = it_804DC8B0;
    M2C_FIELD(ip, f32*, 0x44) = it_804DC8B0;
    M2C_FIELD(ip, f32*, 0x48) = it_804DC8B0;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_80284420(HSD_GObj* gobj)
{
    return false;
}

void it_80284428(Item_GObj* gobj) {}

bool it_8028442C(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80284458);
    return false;
}

void it_80284458(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_80284480(Item_GObj* gobj)
{
    return false;
}

void it_80284488(Item_GObj* gobj)
{
    ItemAttr* attr;

    Item* item = GET_ITEM(gobj);
    attr = item->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_802844B8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802843E4);
    return false;
}

void it_802844E4(Item_GObj* gobj) // contains branch arrows
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* jobj2 = HSD_JObjGetChild(jobj);

    HSD_JObjClearFlagsAll(jobj2, 0x10);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool it_80284540(Item_GObj* gobj)
{
    return false;
}

void it_80284548(Item_GObj* gobj) {}

void it_8028454C(Item_GObj* gobj) // contains branch arrows
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* jobj2 = HSD_JObjGetChild(jobj);

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(jobj2, 0x10);
    Item_80268E5C(gobj, 4, 6);
}

void it_802845BC(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool it_802845E4(Item_GObj* gobj)
{
    return false;
}

void it_802845EC(Item_GObj* gobj)
{
    return;
}

bool it_802845F0(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802843E4, it_80284458);
    return false;
}

void it_80284624(Item_GObj* gobj, Item_GObj* gobj_ref)
{
    it_8026B894(gobj, gobj_ref);
}

ItemStateTable it_803F5740[] = {
    { 0xFFFFFFFF, it_80284380, it_80284388, it_802843B8 },
    { 0xFFFFFFFF, it_80284420, it_80284428, it_8028442C },
    { 0xFFFFFFFF, it_80284480, it_80284488, it_802844B8 },
    { 0xFFFFFFFF, it_80284540, it_80284548, NULL },
    { 0xFFFFFFFF, it_80284480, it_80284488, it_802844B8 },
    { 0xFFFFFFFF, it_802845E4, it_802845EC, it_802845F0 },
};
