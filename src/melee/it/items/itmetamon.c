#include "itmetamon.h"

#include <platform.h>

#include "it/inlines.h"

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
        itMetamon_UnkMotion0_Anim,
        itMetamon_UnkMotion0_Phys,
        itMetamon_UnkMotion0_Coll,
    },
    {
        1,
        itMetamon_UnkMotion1_Anim,
        itMetamon_UnkMotion1_Phys,
        itMetamon_UnkMotion1_Coll,
    },
    {
        -1,
        itMetamon_UnkMotion2_Anim,
        itMetamon_UnkMotion2_Phys,
        itMetamon_UnkMotion2_Coll,
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

void itMetamon_Logic19_EvtUnk(Item_GObj* item_gobj, Item_GObj* gobj)
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

bool itMetamon_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    GET_ITEM(item_gobj);
    if (!it_80272C6C(item_gobj)) {
        return true;
    }
    return false;
}

void itMetamon_UnkMotion0_Phys(Item_GObj* item_gobj) {}

bool itMetamon_UnkMotion0_Coll(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_802D306C);
    return false;
}

bool itMetamon_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    if (!it_80272C6C(item_gobj)) {
        return true;
    }
    return false;
}

void itMetamon_UnkMotion1_Phys(Item_GObj* item_gobj) {}

bool itMetamon_UnkMotion1_Coll(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_802D306C);
    return false;
}

void it_802D31B4(Item_GObj* item_gobj)
{
    it_802762BC(GET_ITEM(item_gobj));
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
}

bool itMetamon_UnkMotion2_Anim(Item_GObj* item_gobj)
{
    it_80279FF8(item_gobj);
    return false;
}

void itMetamon_UnkMotion2_Phys(Item_GObj* item_gobj)
{
    it_8027A09C(item_gobj);
}

bool itMetamon_UnkMotion2_Coll(Item_GObj* item_gobj)
{
    return it_8027A118(item_gobj, it_802D3090);
}
