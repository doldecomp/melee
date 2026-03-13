#include "itnesspkthundertrail.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/jobj.h>

/// #it_802AC43C

void it_802AC58C(Item_GObj* gobj)
{
    register Item* ip;
    register u8 byte;
    register int zero;

    if (gobj != NULL) {
        ip = gobj->user_data;
        it_802725D4(gobj);
        zero = 0;
        ((int*) ip)[0xDD4 / 4] = zero;
        ((int*) ip)[0x518 / 4] = zero;
        byte = ((u8*) ip)[0xDCA];
#ifdef MWERKS_GEKKO
        asm { rlwimi byte, zero, 4, 27, 27 }
#else
        NOT_IMPLEMENTED;
#endif
        ((u8*) ip)[0xDCA] = byte;
    }
}

void it_802AC5D8(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->owner = NULL;
            ip->xDC8_word.flags.x13 = 0;
        }
    }
}

void it_802AC604(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
}

bool itNesspkthundertrail_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);

    if (ip->xDD4_itemVar.bombhei.xDDC & 1) {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    }

    ip->xDD4_itemVar.bombhei.xDDC += 1;

    if ((u32) ip->xDD4_itemVar.bombhei.xDD4 == 0U) {
        return true;
    }
    return false;
    PAD_STACK(8);
}

/// #itNesspkthundertrail_UnkMotion0_Phys

bool itNesspkthundertrail_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}
