#include "ittincle.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802EB5C8

bool it_2725_Logic13_DmgReceived(Item_GObj* gobj)
{
    it_802EC18C(gobj);
    return false;
}

bool it_2725_Logic13_DmgDealt(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->msid != 7) {
        it_802EC1F4(gobj);
    }
    return false;
}

/// #it_802EB6DC

bool itTincle_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion0_Phys

bool itTincle_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

/// #it_802EB870

bool itTincle_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion1_Phys

bool itTincle_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EBA00);
    return false;
}

/// #it_802EBA00

/// #itTincle_UnkMotion2_Anim

/// #itTincle_UnkMotion2_Phys

/// #itTincle_UnkMotion2_Coll

/// #it_802EBD14

bool itTincle_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion3_Phys

bool itTincle_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EC18C);
    return false;
}

/// #it_802EBE5C

bool itTincle_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion4_Phys

bool itTincle_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EC18C);
    return false;
}

/// #it_802EBFAC

bool itTincle_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion5_Phys

bool itTincle_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026DAA8(gobj);
    return false;
}

/// #it_802EC18C

/// #it_802EC1F4

/// #itTincle_UnkMotion7_Anim

void itTincle_UnkMotion7_Phys(Item_GObj* gobj) {}

/// #itTincle_UnkMotion7_Coll

void it_802EC35C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->pos.z = -10.0f;
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

bool itTincle_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itTincle_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EC3F4);
    return false;
}

/// #it_802EC3F4

/// #itTincle_UnkMotion9_Anim

void itTincle_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion9_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802EC35C);
    return false;
}

/// #it_802EC4D0

/// #itTincle_UnkMotion10_Anim

void itTincle_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802EC35C);
    return false;
}

void it_802EC604(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 0xB, ITEM_ANIM_UPDATE);
}

/// #itTincle_UnkMotion11_Anim

void itTincle_UnkMotion11_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion11_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802EC35C);
    return false;
}

/// #it_802EC69C

bool itTincle_UnkMotion12_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion12_Phys

bool itTincle_UnkMotion12_Coll(Item_GObj* gobj)
{
    it_8026DAA8(gobj);
    return false;
}

void it_802EC830(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

void it_802EC850(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802EC870

/// #it_802EC9E8

/// #it_802ECA70

int it_802ECC8C(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->xDD4_itemVar.sword.x20;
}

void it_802ECC98(Item_GObj* arg0, f32 arg1)
{
    GET_ITEM(arg0)->xDD4_itemVar.tincle.x54 = arg1;
}

/// #it_802ECCA4
