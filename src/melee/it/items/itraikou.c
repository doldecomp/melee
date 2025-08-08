#include "itraikou.h"

#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/random.h>

ItemStateTable it_803F7DE8[] = {
    { 0, itRaikou_UnkMotion0_Anim, itRaikou_UnkMotion0_Phys, itRaikou_UnkMotion0_Coll },
    { -1, itRaikou_UnkMotion1_Anim, itRaikou_UnkMotion1_Phys, itRaikou_UnkMotion1_Coll },
};

void it_802CF814(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    Article* ap = it->xC4_article_data;
    itPokemonAttributes* sa = ap->x4_specialAttributes;
    PAD_STACK(16);

    it_80279C48(gobj, ap);
    it->xDAC_itcmd_var0 = 0;
    it->xDB0_itcmd_var1 = 0;
    it->xDB4_itcmd_var2 = 0;
    it_80279CDC(gobj, sa->x0);
    it_802CFB78(gobj);
}

void it_802CF880(Item_GObj* gobj)
{
    return;
}

void it_802CF884(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CF8A4(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    PAD_STACK(8);

    Camera_80030E44(4, NULL);
    Item_8026AE84(it, 0x9, 0x7F, 0x40);
    it_80273454(gobj);
    it_802CF908(gobj);
}

void it_802CF908(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    Article* ap = it->xC4_article_data;
    itPokemonAttributes* sa = ap->x4_specialAttributes;

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it->entered_hitlag = efLib_PauseAll;
    it->exited_hitlag = efLib_ResumeAll;
    it->on_accessory = it_802CFAFC;
    it->xDD4_itemVar.pokemon.timer = sa->timer;
}

bool itRaikou_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    itPokemonAttributes* sa;
    int timer;
    int sfx;

    if (it->xDB0_itcmd_var1) {
        it->xDB0_itcmd_var1 = 0;
        it->xDB4_itcmd_var2 = 0;
        efLib_DestroyAll(gobj);
    }
    if (it_80272C6C(gobj) == false) {
        return true;
    }
    if (it->xDB4_itcmd_var2) {
        timer = --it->xDD4_itemVar.pokemon.timer;
        if (timer == 0) {
            sa = it->xC4_article_data->x4_specialAttributes;
            switch (HSD_Randi(3)) {
            case 0:
                sfx = 0x2746;
                break;
            case 1:
                sfx = 0x2747;
                break;
            case 2:
                sfx = 0x2748;
                break;
            }
            Item_8026AE84(it, sfx, 0x7F, 0x40);
            it->xDD4_itemVar.pokemon.timer = sa->timer;
        }
    }
    return false;
}

void itRaikou_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->ground_or_air == GA_Air) {
        it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                    it->xCC_item_attr->x14_fall_speed_max);
    }
}

bool itRaikou_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->ground_or_air == GA_Air) {
        it_8026E248(gobj, it_802CF880);
    } else {
        it_8026D62C(gobj, it_802CF880);
    }
    return false;
}

void it_802CFAFC(Item_GObj* gobj)
{
    Item* it = gobj->user_data;

    if (it->xDAC_itcmd_var0) {
        HSD_JObj* jp = gobj->hsd_obj;
        f32 v = 1.0f;
        PAD_STACK(8);

        it->xDAC_itcmd_var0 = 0;
        it->xDB4_itcmd_var2 = 1;
        efSync_Spawn(0x46D, gobj, jp, &v);
        Item_8026AE84(it, 0x2745, 0x7f, 0x40);
    }
}

void it_802CFB78(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it_802762BC(it);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it->entered_hitlag = efLib_PauseAll;
    it->exited_hitlag = efLib_ResumeAll;
}

bool itRaikou_UnkMotion1_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);

    return false;
}

void itRaikou_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itRaikou_UnkMotion1_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802CF8A4);
}
