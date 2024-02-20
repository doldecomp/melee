#include "itmetalb.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

void it_802953C8(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    it->xDCE_flag.bits.b7 = 0;
    it_80295498(gobj, it);
}

void it_802953FC(Item_GObj* gobj, f32 val)
{
    Item* it = gobj->user_data;
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0f;

    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}
