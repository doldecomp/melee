#include "itseakneedlethrown.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "sysdolphin/baselib/jobj.h"

typedef struct itSeakNeedleThrownAnimVars {
    /* +00 */ f32 xDD4;
    /* +04 */ f32 xDD8;
    /* +08 */ f32 xDDC;
    /* +0C */ f32 xDE0;
    /* +10 */ Vec3 xDE4;
    /* +1C */ f32 xDF0;
} itSeakNeedleThrownAnimVars;

/// #it_802AFD8C

Item_GObj* it_802AFEA8(Item_GObj* gobj, Fighter_GObj* owner_gobj, u32 mode)
{
    if (gobj != NULL && owner_gobj != NULL) {
        if (mode == 0) {
            return it_802AFF08(gobj, owner_gobj);
        }
        if (mode == 1) {
            return it_802B00F4(gobj, owner_gobj);
        }
    }
    return gobj;
}

void itSeakNeedleThrown_Logic109_Destroyed(Item_GObj* gobj)
{
    GET_ITEM(gobj)->owner = NULL;
}

/// #it_802AFF08

/// #it_802B00F4

bool itSeakneedlethrown_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.seakneedlethrown.xDE4 = ip->pos;
    return it_80273130(gobj);
}

bool itSeakneedlethrown_UnkMotion1_Anim(Item_GObj* gobj)
{
    HSD_JObj* owner_jobj = HSD_GObjGetHSDObj(gobj);
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAnimVars* vars =
        (itSeakNeedleThrownAnimVars*) &ip->xDD4_itemVar;

    if (owner_jobj != NULL) {
        owner_jobj = owner_jobj->child;
    }
    vars->xDE4 = ip->pos;
    HSD_ASSERT(0x405, owner_jobj != NULL);
    owner_jobj->rotate.x += vars->xDD4;
    if (!(owner_jobj->flags & JOBJ_MTX_DIRTY)) {
        HSD_JObjSetMtxDirtySub(owner_jobj);
    }
    return it_80273130(gobj);
}

/// #itSeakneedlethrown_UnkMotion2_Anim

bool itSeakneedlethrown_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

/// #itSeakneedlethrown_UnkMotion4_Anim

void itSeakneedlethrown_UnkMotion0_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.seakneedlethrown.xDD8;
    ip->x40_vel.y += ip->xDD4_itemVar.seakneedlethrown.xDE0;
    if (ip->x40_vel.y < ip->xDD4_itemVar.seakneedlethrown.xDDC) {
        ip->x40_vel.y = ip->xDD4_itemVar.seakneedlethrown.xDDC;
    }
}

void itSeakneedlethrown_UnkMotion2_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

void itSeakneedlethrown_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.seakneedlethrown.xDD8;
    ip->x40_vel.y += ip->xDD4_itemVar.seakneedlethrown.xDE0;
    if (ip->x40_vel.y < ip->xDD4_itemVar.seakneedlethrown.xDDC) {
        ip->x40_vel.y = ip->xDD4_itemVar.seakneedlethrown.xDDC;
    }
}

/// #itSeakneedlethrown_UnkMotion0_Coll

/// #itSeakneedlethrown_UnkMotion1_Coll

/// #itSeakneedlethrown_UnkMotion2_Coll

bool itSeakneedlethrown_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #itSeakneedlethrown_UnkMotion4_Coll

/// #it_2725_Logic109_DmgDealt

/// #it_2725_Logic109_Clanked

/// #it_2725_Logic109_DmgReceived

/// #it_2725_Logic109_Reflected

/// #it_2725_Logic109_ShieldBounced

/// #it_2725_Logic109_HitShield

void itSeakNeedleThrown_Logic109_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
