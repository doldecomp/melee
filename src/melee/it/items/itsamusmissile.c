#include "itsamusmissile.h"

#include "it/it_266F.h"
#include "it/it_2725.h"

bool itSamusmissile_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802B701C);
    return false;
}

bool itSamusmissile_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802B70A0);
    return false;
}

bool itSamusmissile_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

