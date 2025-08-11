#include "ittarucann.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

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

/// #it_80296694

/// #itTarucann_UnkMotion1_Anim

/// #itTarucann_UnkMotion1_Phys

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

/// #it_80296E88

/// #it_80296EA8

/// #it_80296EF0

/// #itTarucann_UnkMotion8_Anim

/// #itTarucann_UnkMotion8_Phys

/// #itTarucann_UnkMotion8_Coll

/// #itTarucann_UnkMotion7_Anim

/// #itTarucann_UnkMotion7_Phys

/// #itTarucann_UnkMotion7_Coll

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
