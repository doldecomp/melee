#include "ithouou.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "ef/eflib.h"
#include "it/item.h"

/// #it_2725_Logic18_Spawned

void it_802D25B8(void) {}

void it_802D25BC(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itHouou_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D2668(gobj);
    }

    return false;
}

void itHouou_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHouou_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D2668

bool itHouou_UnkMotion2_Anim(Item_GObj* gobj)
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

/// #itHouou_UnkMotion2_Phys

bool itHouou_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D27B0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

/// #itHouou_UnkMotion3_Anim

/// #itHouou_UnkMotion3_Phys

bool itHouou_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D290C

bool itHouou_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D2A58(gobj);
    }

    return false;
}

/// #itHouou_UnkMotion4_Phys

bool itHouou_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D2A58

bool itHouou_UnkMotion5_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);

    if (jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = jobj->child;
    }
    it_8027A160(jobj, ip);
    if (!it_80272C6C(gobj)) {
        return true;
    }
    return false;
}

void itHouou_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHouou_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D2B4C

void it_802D2BE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool it_802D2C54(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #it_802D2C78

bool it_802D2D04(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D25B8);
}

/// #it_802D2D2C

/// #it_2725_Logic42_Spawned

void it_802D2ED0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D2EF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D2F3C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #it_802D2F70

bool it_802D2FE8(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
