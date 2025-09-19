#include "itkyasarin.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_2725_Logic25_Destroyed

void it_802ECD1C(Item_GObj* gobj, Vec3* v)
{
    *v = GET_ITEM(gobj)->pos;
}

/// #it_802ECD3C

void it_802ECE90(Item_GObj* gobj)
{
    it_8027B730(gobj);
}

/// #it_802ECEB0

/// #itKyasarin_UnkMotion0_Anim

/// #itKyasarin_UnkMotion0_Coll

/// #it_802ECFE0

/// #itKyasarin_UnkMotion1_Anim

/// #itKyasarin_UnkMotion3_Anim

/// #it_802ED0D0

/// #itKyasarin_UnkMotion2_Anim

/// #itKyasarin_UnkMotion2_Coll

/// #it_802ED25C

/// #itKyasarin_UnkMotion4_Anim

/// #itKyasarin_UnkMotion4_Coll

void it_802ED4F8(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

/// #itKyasarin_UnkMotion6_Anim

void it_802ED774(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

/// #itKyasarin_UnkMotion7_Anim

void it_802ED8BC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

/// #itKyasarin_UnkMotion5_Anim

/// #itKyasarin_UnkMotion8_Anim

/// #itKyasarin_UnkMotion9_Anim

void itKyasarin_UnkMotion9_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itKyasarin_UnkMotion9_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

/// #itKyasarin_UnkMotion10_Anim

void itKyasarin_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itKyasarin_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_802EDDC0

void it_802EE1E0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
