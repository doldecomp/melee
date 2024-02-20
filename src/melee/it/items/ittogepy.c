#include "ittogepy.h"

#include "it/types.h"

#include <baselib/gobj.h>

void it_802D36B0(Item_GObj* gobj)
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
    Item_8026AE84(it, 0x272C, 0x7F, 0x40);
}
