#include "itmewtwoshadowball.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_802C4D10

/// #it_802C4F50

/// #it_802C5000

/// #it_802C519C

/// #it_802C53F0

/// #it_802C56A0

/// #it_802C573C

/// #it_802C578C

/// #itMewtwoshadowball_UnkMotion0_Anim

void itMewtwoshadowball_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itMewtwoshadowball_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802C5B18

/// #itMewtwoshadowball_UnkMotion8_Anim

/// #itMewtwoshadowball_UnkMotion8_Phys

/// #itMewtwoshadowball_UnkMotion8_Coll

/// #itMewtwoshadowball_UnkMotion9_Anim

void itMewtwoshadowball_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itMewtwoshadowball_UnkMotion9_Coll

/// #fn_802C5E18

/// #it_802C5E5C

/// #itMewtwoshadowball_UnkMotion17_Anim

void itMewtwoshadowball_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itMewtwoshadowball_UnkMotion17_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_802C60B4(Item_GObj* arg0)
{
    return true;
}

bool it_802C60BC(Item_GObj* arg0)
{
    return true;
}

bool it_802C60C4(Item_GObj* arg0)
{
    return true;
}

/// #it_802C60CC

bool it_802C6138(Item_GObj* arg0)
{
    return true;
}

/// #it_802C6140

void it_802C61D4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
