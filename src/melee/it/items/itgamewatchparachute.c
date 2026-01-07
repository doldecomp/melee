#include "itgamewatchparachute.h"

#include "ftGameWatch/ftGw_AttackAir.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

void it_2725_Logic74_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802C6DB8(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C6DD8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_2725_Logic74_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftGw_AttackAirN_ItemParachuteSetFlag(ip->owner);
    }
}
