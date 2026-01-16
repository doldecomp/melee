#include "itlugia.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_2725_Logic17_Spawned

void it_802D14D0(void) {}

void it_2725_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itLugia_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);       // r31
    HSD_JObj* jobj = GET_JOBJ(gobj); // r3
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D1580(gobj);
    }

    return false;
}

void itLugia_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1580

bool itLugia_UnkMotion2_Anim(Item_GObj* gobj)
{
    HSD_JObj* bone;
    Item* item = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (jobj == NULL) {
        bone = NULL;
    } else {
        bone = jobj->child;
    }

    it_8027A160(bone, item);
    return false;
}

/// #itLugia_UnkMotion2_Phys

bool itLugia_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D16D4(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

/// #itLugia_UnkMotion3_Anim

/// #itLugia_UnkMotion3_Phys

bool itLugia_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1830

/// #itLugia_UnkMotion4_Anim

/// #itLugia_UnkMotion4_Phys

bool itLugia_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1A44

/// #itLugia_UnkMotion5_Anim

void itLugia_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1BBC

/// #it_802D1D40

bool it_802D1DB4(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #it_802D1DD8

bool it_802D1E64(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D14D0);
}

/// #it_802D1E8C

/// #it_802D1F64

/// #it_802D208C

void it_2725_Logic39_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x465, gobj, HSD_GObjGetHSDObj(gobj), it_804DD490);
    it_802D23F4(gobj);
}

void it_2725_Logic40_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x466, gobj, HSD_GObjGetHSDObj(gobj), it_804DD490);
    it_802D23F4(gobj);
}

void it_2725_Logic41_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x467, gobj, HSD_GObjGetHSDObj(gobj), it_804DD490);
    it_802D23F4(gobj);
}

void it_802D23D4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802D23F4

bool it_802D246C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #it_802D24A0

bool it_802D24FC(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
