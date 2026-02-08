#include "itgamewatchchef.h"

#include "math.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

#include <baselib/jobj.h>

/// #it_802C837C

bool itGameWatchChef_Logic112_DmgDealt(Item_GObj* gobj)
{
    it_802C875C(gobj);
    return false;
}

/// #it_802C84A0

/// #itGamewatchchef_UnkMotion0_Anim

void itGamewatchchef_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGamewatchchefAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    s32 index = ip->xDD4_itemVar.gamewatchchef.x4;
    it_80272860(gobj, attrs->entries[index].x8, attrs->entries[index].xC);
}

/// #itGamewatchchef_UnkMotion0_Coll

/// #it_802C875C

/// #itGamewatchchef_UnkMotion1_Anim

void itGamewatchchef_UnkMotion1_Phys(Item_GObj* gobj) {}

/// #itGamewatchchef_UnkMotion1_Coll

/// #it_2725_Logic112_Clanked

/// #it_2725_Logic112_HitShield

/// #it_2725_Logic112_Absorbed

bool itGameWatchChef_Logic112_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itGameWatchChef_Logic112_Reflected(Item_GObj* gobj)
{
    const f32 PI_2 = M_PI / 2;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    it_80273030(gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * ip->facing_dir);
    return false;
}

void itGameWatchChef_Logic112_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
