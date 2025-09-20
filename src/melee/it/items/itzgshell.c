#include "itzgshell.h"

#include "it/forward.h"

#include "gr/grzakogenerator.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 2DFFA0 */ static void it_802DFFA0(Item_GObj* gobj);

/// #it_802DDB38

/// #it_802DDBE8

/// #fn_802DDC8C

/// #it_802DDD38

/// #it_802DDEB4

/// #it_802DE040

/// #it_802DE0F0

bool itZrshell_UnkMotion0_Anim(Item_GObj* arg0)
{
    return false;
}

/// #itZrshell_UnkMotion0_Phys

/// #itZrshell_UnkMotion0_Coll

/// #it_802DE320

/// #itZrshell_UnkMotion1_Anim

/// #itZrshell_UnkMotion1_Phys

bool itZrshell_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E32C(gobj, it_802DE0F0);
    return false;
}

/// #it_2725_Logic11_PickedUp

bool itZrshell_UnkMotion2_Anim(Item_GObj* arg0)
{
    return false;
}

/// #itZrshell_UnkMotion2_Phys

/// #it_2725_Logic11_Thrown

/// #itZrshell_UnkMotion3_Anim

/// #itZrshell_UnkMotion3_Phys

bool itZrshell_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, fn_802DDC8C);
    return false;
}

void it_2725_Logic11_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

bool itZrshell_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_802DDBE8(gobj);
    return false;
}

/// #itZrshell_UnkMotion4_Phys

bool itZrshell_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, fn_802DDC8C);
    return false;
}

/// #it_802DE6F0

/// #itZrshell_UnkMotion6_Anim

/// #itZrshell_UnkMotion6_Phys

/// #itZrshell_UnkMotion6_Coll

/// #it_802DEC80

/// #itZrshell_UnkMotion8_Anim

/// #itZrshell_UnkMotion8_Phys

bool itZrshell_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, fn_802DDC8C);
    return false;
}

/// #it_2725_Logic11_EnteredAir

bool itZrshell_UnkMotion9_Anim(Item_GObj* arg0)
{
    return false;
}

/// #itZrshell_UnkMotion9_Phys

/// #itZrshell_UnkMotion9_Coll

/// #it_802DF230

/// #itZrshell_UnkMotion11_Anim

/// #itZrshell_UnkMotion11_Phys

/// #itZrshell_UnkMotion11_Coll

/// #it_802DF9F8

/// #itZrshell_UnkMotion10_Anim

void itZrshell_UnkMotion10_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

/// #itZrshell_UnkMotion10_Coll

bool it_2725_Logic11_DmgDealt(Item_GObj* gobj)
{
    it_80272940(gobj);
    return false;
}

/// #it_2725_Logic11_DmgReceived

bool it_2725_Logic11_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_2725_Logic11_Clanked

/// #it_2725_Logic11_HitShield

/// #it_2725_Logic11_ShieldBounced

/// #fn_802DFE7C

void it_802DFED4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_2725_Logic11_Destroyed(Item_GObj* gobj)
{
    grZakoGenerator_801CACB8((Ground_GObj*) gobj);
}

/// #it_802DFF14

void it_802DFFA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.zgshell.vel.x = 0.0f;
    ip->xDD4_itemVar.zgshell.vel.y = 0.0f;
    ip->xDD4_itemVar.zgshell.vel.z = 0.0F;
}

/// #it_802DFFB8

/// #it_802E0100
