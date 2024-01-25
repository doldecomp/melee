#include <platform.h>
#include "it/forward.h"

#include "itmetamon.h"

#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>

static Item_GObj* it_804D6D50;

typedef struct {
    f32 x0;
} ItMetamonVars;

ItemStateTable it_803F7FC8[] = {
    {
        0,
        it_802D30EC,
        it_802D3120,
        it_802D3124,
    },
    {
        1,
        it_802D3150,
        it_802D3184,
        it_802D3188,
    },
    {
        -1,
        it_802D31F4,
        it_802D3218,
        it_802D3238,
    },
};

void it_802D3008(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    ItMetamonVars* vars = it->xC4_article_data->x4_specialAttributes;
    it_80279CDC(item_gobj, vars->x0);
    it_802D31B4(item_gobj);
    Item_8026AE84(it, 0x2728, 0x7F, 0x40);
    it_804D6D50 = item_gobj;
}

void it_802D306C(Item_GObj* item_gobj) {}

void it_802D3070(Item_GObj* item_gobj, Item_GObj* gobj)
{
    it_8026B894(item_gobj, gobj);
}

void it_802D3090(Item_GObj* item_gobj)
{
    it_80273454(item_gobj);
    it_802D30C4(item_gobj);
}

void it_802D30C4(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802D30EC(Item_GObj* item_gobj)
{
    GET_ITEM(item_gobj);
    if (!it_80272C6C(item_gobj)) {
        return true;
    }
    return false;
}

void it_802D3120(Item_GObj* item_gobj) {}

bool it_802D3124(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_802D306C);
    return false;
}

bool it_802D3150(Item_GObj* item_gobj)
{
    if (!it_80272C6C(item_gobj)) {
        return true;
    }
    return false;
}

void it_802D3184(Item_GObj* item_gobj) {}

bool it_802D3188(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_802D306C);
    return false;
}

void it_802D31B4(Item_GObj* item_gobj)
{
    it_802762BC(GET_ITEM(item_gobj));
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_802D31F4(Item_GObj* item_gobj)
{
    it_80279FF8(item_gobj);
    return false;
}

void it_802D3218(Item_GObj* item_gobj)
{
    it_8027A09C(item_gobj);
}

bool it_802D3238(Item_GObj* item_gobj)
{
    return it_8027A118(item_gobj, it_802D3090);
}
