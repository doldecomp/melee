#include "ittools.h"

#include "math.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

#include <baselib/jobj.h>

/// #it_802EEFA8

bool itTools_Logic22_DmgDealt(Item_GObj* gobj)
{
    it_802EF320(gobj);
    return false;
}

/// #it_802EF098

/// #itTools_UnkMotion4_Anim

void itTools_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itToolsAttrEntry* entry =
        (itToolsAttrEntry*) ip->xC4_article_data->x4_specialAttributes;
    entry += ip->xDD4_itemVar.tools.x0;
    it_80272860(gobj, entry->x14, entry->x18);
}

/// #itTools_UnkMotion4_Coll

/// #it_802EF320

/// #itTools_UnkMotion9_Anim

void itTools_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itTools_UnkMotion9_Coll

/// #it_802EF548

bool itTools_Logic22_DmgReceived(Item_GObj* gobj)
{
    it_802EF548(gobj);
    return false;
}

/// #it_2725_Logic22_Clanked

/// #it_2725_Logic22_HitShield

/// #it_2725_Logic22_Absorbed

bool itTools_Logic22_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itTools_Logic22_Reflected(Item_GObj* gobj)
{
    const f32 PI_2 = M_PI / 2;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    it_80273030(gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * ip->facing_dir);
    return false;
}

void it_802EFA24(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
