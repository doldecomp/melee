#include "itnesspkthundertrail.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/item.h"

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
        ((int*)ip)[0xDD4/4] = zero;
        ((int*)ip)[0x518/4] = zero;
        byte = ((u8*)ip)[0xDCA];
        asm { rlwimi byte, zero, 4, 27, 27 }
        ((u8*)ip)[0xDCA] = byte;
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

/// #itNesspkthundertrail_UnkMotion0_Anim

/// #itNesspkthundertrail_UnkMotion0_Phys

bool itNesspkthundertrail_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}
