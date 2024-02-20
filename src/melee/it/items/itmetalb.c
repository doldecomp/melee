#include "itmetalb.h"

#include "it/inlines.h"
#include "it/item.h"

void it_802953C8(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    it->xDCE_flag.bits.b7 = 0;
    it_80295498(gobj, it);
}
