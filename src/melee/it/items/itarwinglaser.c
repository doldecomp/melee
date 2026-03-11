#include "itarwinglaser.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

void it_802E7A4C(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, item->xDD4_itemVar.arwinglaser.xE38, 2);
}

bool it_802E8418(Item_GObj* gobj)
{
    return true;
}

bool it_802E8784(Item_GObj* gobj)
{
    return true;
}
