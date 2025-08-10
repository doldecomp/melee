#include "ittogepy.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

ItemStateTable it_803F8058[] = {
    { 0, itTogepy_UnkMotion0_Anim, itTogepy_UnkMotion0_Phys, itTogepy_UnkMotion0_Coll },
    { 1, itTogepy_UnkMotion1_Anim, itTogepy_UnkMotion1_Phys, itTogepy_UnkMotion1_Coll },
    { 2, itTogepy_UnkMotion6_Anim, itTogepy_UnkMotion6_Phys, itTogepy_UnkMotion6_Coll },
    { 3, itTogepy_UnkMotion6_Anim, itTogepy_UnkMotion6_Phys, itTogepy_UnkMotion6_Coll },
    { 4, itTogepy_UnkMotion6_Anim, itTogepy_UnkMotion6_Phys, itTogepy_UnkMotion6_Coll },
    { 5, itTogepy_UnkMotion6_Anim, itTogepy_UnkMotion6_Phys, itTogepy_UnkMotion6_Coll },
    { 6, itTogepy_UnkMotion6_Anim, itTogepy_UnkMotion6_Phys, itTogepy_UnkMotion6_Coll },
};

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
    it_802D39F8(gobj);
    Item_8026AE84(it, 0x272C, 0x7F, 0x40);
}

void it_802D3728(Item_GObj* gobj)
{
    return;
}

void it_802D372C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itTogepy_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    int timer;

    if (it_80272C6C(gobj) == false) {
        timer = --it->xDD4_itemVar.pokemon.timer;
        if (it->xDD4_itemVar.pokemon.timer <= 0) {
            it_802D3848(gobj);
        } else {
            Item_80268D34(gobj, it->xD0_itemStateDesc);
        }
    }
    return false;
}

void itTogepy_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it->ground_or_air == GA_Air) {
        it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                    it->xCC_item_attr->x14_fall_speed_max);
    }
}

bool itTogepy_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802D3728);
    } else {
        it_8026D62C(gobj, it_802D3728);
    }
    return false;
}

void it_802D3848(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    Article* ap = it->xC4_article_data;
    itPokemonAttributes* sa = ap->x4_specialAttributes;
    int rand = HSD_Randi(sa->max);
    int val = sa->xC;
    int state;
    PAD_STACK(8);

    if (rand < val) {
        state = 2;
    } else {
        val += sa->x10;
        if (rand < val) {
            state = 3;
        } else {
            val = sa->x14 + val;
            if (rand < val) {
                state = 4;
            } else if (rand < sa->x18 + val) {
                state = 5;
            } else {
                state = 6;
            }
        }
    }
    Item_80268E5C(gobj, state, ITEM_ANIM_UPDATE);
    it->entered_hitlag = NULL;
    it->exited_hitlag = NULL;
}

bool itTogepy_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it_80272C6C(gobj) == false) {
        Item_80268D34(gobj, it->xD0_itemStateDesc);
    }
    if (it->xDAC_itcmd_var0) {
        return true;
    }
    return false;
}

void itTogepy_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    if (it->ground_or_air == GA_Air) {
        it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                    it->xCC_item_attr->x14_fall_speed_max);
    }
}

bool itTogepy_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    if (it->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802D3728);
    } else {
        it_8026D62C(gobj, it_802D3728);
    }
    return false;
}

void it_802D39F8(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    Article* ap = it->xC4_article_data;
    itPokemonAttributes* sa = ap->x4_specialAttributes;

    it_802762BC(it);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it->entered_hitlag = NULL;
    it->exited_hitlag = NULL;
    it->xDD4_itemVar.pokemon.timer = sa->timer;
}

bool itTogepy_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);

    return false;
}

void itTogepy_UnkMotion0_Phys(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* it = gobj->user_data;
        it_80273454(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        it->entered_hitlag = NULL;
        it->exited_hitlag = NULL;
    }
}

bool itTogepy_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D3728);
}
