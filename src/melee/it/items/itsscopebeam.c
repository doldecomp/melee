#include "itsscopebeam.h"

#include <placeholder.h>
#include <platform.h>

#include "db/db.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

void it_80298DEC(Fighter_GObj* gobj, Vec* vec, int arg2, float arg3)
{
    HSD_GObj* n;
    SpawnItem si;
    si.kind = It_Kind_S_Scope_Beam;
    si.prev_pos = *vec;
    si.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &si.pos);
    si.facing_dir = arg3;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = 1;
    si.x40 = 0;
    n = Item_80268B18(&si);
    if (n != NULL) {
        Item* ip = GET_ITEM(n);
        ip->xDD4_itemVar.starrodstar.x0 = arg2;
        it_80298ED0(n, gobj);
        db_80225DD8(n, gobj);
    }
}

/// #it_80298ED0

/// #itSscopebeam_UnkMotion9_Anim

void itSscopebeam_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itSscopebeam_UnkMotion9_Coll

bool itSScopeBeam_Logic38_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itSScopeBeam_Logic38_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

void itSScopeBeam_Logic38_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
