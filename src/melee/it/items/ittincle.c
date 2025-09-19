#include "ittincle.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/it_266F.h"

/// #it_802EB5C8

bool it_2725_Logic13_DmgReceived(Item_GObj* gobj)
{
    it_802EC18C(gobj);
    return false;
}

/// #it_2725_Logic13_DmgDealt

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

/// #itTincle_UnkMotion1_Coll

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

/// #itTincle_UnkMotion3_Coll

/// #it_802EBE5C

bool itTincle_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion4_Phys

/// #itTincle_UnkMotion4_Coll

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

/// #it_802EC35C

bool itTincle_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTincle_UnkMotion8_Phys

/// #itTincle_UnkMotion8_Coll

/// #it_802EC3F4

/// #itTincle_UnkMotion9_Anim

void itTincle_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itTincle_UnkMotion9_Coll

/// #it_802EC4D0

/// #itTincle_UnkMotion10_Anim

void itTincle_UnkMotion10_Phys(Item_GObj* gobj) {}

/// #itTincle_UnkMotion10_Coll

void it_802EC604(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 0xB, ITEM_ANIM_UPDATE);
}

/// #itTincle_UnkMotion11_Anim

void itTincle_UnkMotion11_Phys(Item_GObj* gobj) {}

/// #itTincle_UnkMotion11_Coll

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
