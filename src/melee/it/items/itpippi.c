#include "itpippi.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"

#include <baselib/random.h>

void it_802D3260(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    Article* ap = it->xC4_article_data;
    itPokemonAttributes* sa = ap->x4_specialAttributes;

    it->facing_dir = 0.0f;
    it->xDB4_itcmd_var2 = 0;
    it->xDB0_itcmd_var1 = 0;
    it->xDAC_itcmd_var0 = 0;
    it_80279CDC(gobj, sa->x0);
    it_802D3590(gobj);
    Item_8026AE84(it, 0x272A, 0x7F, 0x40);
}

void it_802D32D8(Item_GObj* gobj)
{
    return;
}

void it_802D32DC(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool it_802D32FC(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    int timer;

    if (it_80272C6C(gobj) == false) {
        timer = --it->xDD4_itemVar.pokemon.timer;
        if (it->xDD4_itemVar.pokemon.timer <= 0) {
            it_802D33F8(gobj);
        } else {
            Item_80268D34(gobj, it->xD0_itemStateDesc);
        }
    }
    return false;
}

void it_802D3370(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it->ground_or_air == GA_Air) {
        it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                    it->xCC_item_attr->x14_fall_speed_max);
    }
}

bool it_802D3600(Item_GObj* gobj)
{
    it_80279FF8(gobj);

    return false;
}

void it_802D3624(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* it = gobj->user_data;
        it_80273454(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        it->entered_hitlag = NULL;
        it->exited_hitlag = NULL;
    }
}

bool it_802D3688(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D32D8);
}
