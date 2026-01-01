#include "itdosei.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"

/// #it_3F14_Logic7_Spawned

/// #fn_80281390

/// #itDosei_UnkMotion0_Anim

void itDosei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion0_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, (HSD_GObjEvent) it_80282074);
    it_80276CB8(gobj);
    return false;
}

/// #fn_80281734

/// #it_802817A0

/// #itDosei_UnkMotion1_Anim

void itDosei_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    f32* ap = ip->xC4_article_data->x4_specialAttributes;
    f32 vel = ap[2] * ip->x5D0_animFrameSpeed;
    if (vel < 0.0f) {
        vel = -vel;
    }
    ip->x40_vel.x = ip->facing_dir * vel;
}

/// #itDosei_UnkMotion1_Coll

/// #it_80281C6C

/// #itDosei_UnkMotion2_Anim

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion2_Coll

/// #it_80282074

/// #itDosei_UnkMotion3_Anim

void itDosei_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802817A0);
    return false;
}

/// #it_3F14_Logic7_PickedUp

/// #itDosei_UnkMotion4_Anim

void itDosei_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic7_Dropped

/// #it_3F14_Logic7_Thrown

bool itDosei_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itDosei_UnkMotion5_Phys

/// #it_3F14_Logic7_EnteredAir

bool itDosei_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion6_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion6_Coll

/// #it_80282BFC

bool itDosei_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80282CD4);
    return false;
}

/// #fn_80282CD4

/// #itDosei_UnkMotion7_Anim

void itDosei_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80282BFC);
    it_80276CB8(gobj);
    return false;
}

/// #it_80282DE4

/// #itDosei_UnkMotion9_Anim

void itDosei_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion9_Coll

/// #itDosei_UnkMotion10_Anim

void itDosei_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80282CD4, it_80282BFC);
    return false;
}

/// #it_3F14_Logic7_DmgReceived

/// #itDosei_UnkMotion11_Anim

void itDosei_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion11_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80281390);
    return false;
}

/// #it_3F14_Logic7_DmgDealt

bool it_3F14_Logic7_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic7_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic7_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
