#include "itporygon2.h"

#include "it/inlines.h"
#include "it/it_2725.h"

#include <melee/ef/eflib.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

ItemStateTable it_803F8250[] = {
    {
        0,
        it_802D5B60,
        it_802D5BBC,
        it_802D5BDC,
    },
    {
        1,
        it_802D5C60,
        it_802D5CB0,
        it_802D5CD0,
    },
};

void it_802D5ABC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    it_80279CDC(item_gobj, item->scl);
    Item_8026AE84(item, 0x273E, 0x7F, 0x40);
    it_802D5B14(item_gobj);
}

void it_802D5B14(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

bool it_802D5B60(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (!it_80272C6C(item_gobj)) {
        it_802D5C00(item_gobj);
    }
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    return false;
}

void it_802D5BBC(Item_GObj* item_gobj)
{
    it_8027A344(item_gobj);
}

bool it_802D5BDC(Item_GObj* item_gobj)
{
    it_8026DA08(item_gobj);
    return false;
}

void it_802D5C00(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    Item_8026AE84(item, 0x273F, 0x7F, 0x40);
}

bool it_802D5C60(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (!it_80272C6C(item_gobj)) {
        return true;
    }
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    return false;
}

void it_802D5CB0(Item_GObj* item_gobj)
{
    it_8027A344(item_gobj);
}

bool it_802D5CD0(Item_GObj* item_gobj)
{
    return false;
}

void it_802D5CD8(Item_GObj* item_gobj, HSD_GObj* arg1)
{
    it_8026B894(item_gobj, arg1);
}
