#include "itarwinglaser.h"

#include <placeholder.h>
#include <platform.h>

void it_802E7A4C(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = *(Item**)((u8*)gobj + 0x2C);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, *(int*)((u8*)item + 0xE38), 2);
}

bool it_802E8418(Item_GObj* gobj)
{
    return true;
}

bool it_802E8784(Item_GObj* gobj)
{
    return true;
}
