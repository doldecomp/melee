#include "itseakneedleheld.h"

#include "it/it_26B1.h"
#include "it/item.h"
#include "it/inlines.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftSeak/ftSk_SpecialS.h"

#include <baselib/jobj.h>

void it_802B18B0(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* ip;
    HSD_JObj* child;
    HSD_JObj* needle;
    Fighter_GObj* holder;
    s32 count;
    s32 i;

    jobj = gobj->hsd_obj;
    ip = GET_ITEM(gobj);

    child = (jobj == NULL) ? NULL : jobj->child;
    needle = (child == NULL) ? NULL : child->child;

    holder = ip->xDD4_itemVar.seakneedleheld.xDD4_fighter;

    if (holder == NULL) {
        return;
    }
    if (ip->owner != (HSD_GObj*) holder) {
        return;
    }

    switch (ip->kind) {
    case It_Kind_Seak_NeedleHeld:
        count = ftSk_SpecialS_80111FA0((HSD_GObj*) holder);
        break;
    case It_Kind_Kirby_SeakNeedleHeld:
        count = ftKb_SpecialNSk_80106020((HSD_GObj*) holder);
        break;
    }

    for (i = 0; i < 6; i++) {
        if (i < count) {
            HSD_JObjClearFlagsAll(needle, 0x10);
        } else {
            HSD_JObjSetFlagsAll(needle, 0x10);
        }
        needle = (needle == NULL) ? NULL : needle->next;
    }
}

/// #it_802B19AC

void itSeakNeedleHeld_Logic110_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

/// #itSeakneedleheld_UnkMotion0_Anim

void itSeakneedleheld_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSeakneedleheld_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void itSeakNeedleHeld_Logic110_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
