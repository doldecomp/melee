#include "itpikachuthunder.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>

int it_802B1DEC(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->xDD4_itemVar.capsule.x4;
}

/// #it_802B1DF8

s32 it_802B1FC8(Item_GObj* gobj)
{
    return it_802B22B8(gobj);
}

void it_802B1FE8(Item_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    f32 scale = ip->xDD4_itemVar.pikachuthunder.x18;
    f32 offset = -attrs->x8;

    offset *= scale;
    *pos = ip->pos;
    pos->y += offset;
}

/// #it_2725_Logic39_Destroyed

void it_802B2080(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
    it_8026BB44(gobj);
}

/// #itPikachuthunder_UnkMotion0_Anim

/// #it_802B211C

bool itPikachuthunder_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xD44_lifeTimer--;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

/// #itPikachuthunder_UnkMotion1_Coll

/// #it_802B22B8

/// #itPikachuthunder_UnkMotion2_Anim

bool itPikachuThunder_Logic39_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_HitShield(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_Clanked(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_Absorbed(Item_GObj* arg0)
{
    return false;
}

void itPikachuThunder_Logic39_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x38 == ref_gobj) {
        ip->xDD4_itemVar.pikachuthunder.x38 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
