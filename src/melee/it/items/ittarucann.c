#include "ittarucann.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_80295ED4

/// #it_80295F38

int it_802960B8(Item_GObj* gobj)
{
    itTaruCann_DatAttrs* da =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    return da->x2C;
}

int it_802960CC(Item_GObj* gobj)
{
    itTaruCann_DatAttrs* da =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    return da->x28;
}

/// #it_3F14_Logic5_Destroyed

/// #it_3F14_Logic5_Spawned

/// #it_802961E8

/// #it_802962E0

/// #itTarucann_UnkMotion0_Anim

void itTarucann_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itTarucann_UnkMotion0_Coll

void it_80296694(Item_GObj* gobj)
{
    PAD_STACK(8);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

/// #itTarucann_UnkMotion1_Anim

void itTarucann_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itTarucann_UnkMotion1_Coll

/// #it_3F14_Logic5_PickedUp

/// #itTarucann_UnkMotion2_Anim

void itTarucann_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic5_Dropped

/// #it_3F14_Logic5_Thrown

/// #it_802969D8

/// #itTarucann_UnkMotion6_Anim

/// #itTarucann_UnkMotion6_Phys

/// #itTarucann_UnkMotion6_Coll

void it_80296E88(Item_GObj* gobj)
{
    it_80296EF0(gobj);
}

/// #it_80296EA8

/// #it_80296EF0

/// #itTarucann_UnkMotion8_Anim

/// #itTarucann_UnkMotion8_Phys

/// #itTarucann_UnkMotion8_Coll

/// #itTarucann_UnkMotion7_Anim

/// #itTarucann_UnkMotion7_Phys

bool itTarucann_UnkMotion7_Coll(Item_GObj* gobj)
{
    return itTarucann_UnkMotion8_Coll(gobj);
}

/// #it_802975F4

/// #itTarucann_UnkMotion9_Anim

void itTarucann_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itTarucann_UnkMotion9_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_80297790

bool it_3F14_Logic5_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic5_Clanked(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic5_HitShield(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic5_Reflected(Item_GObj* arg0)
{
    return false;
}

void it_3F14_Logic5_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
