#include "itmatadogas.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/random.h>

/// #it_802CAFD4

void it_802CB0F4(Item_GObj* gobj) {}

void it_802CB0F8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool it_802CB118(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        return true;
    }
    return false;
}

void it_802CB14C(Item_GObj* gobj) {}

bool it_802CB150(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802CB0F4);
    return false;
}

/// #itMatadogas_UnkMotion1_Anim

void itMatadogas_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itMatadogas_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802CB0F4);
    return false;
}

void it_802CB2B0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDAC_itcmd_var0 != 0) {
        itMatadogasAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
        s32 timer = ip->xDD4_itemVar.matadogas.x60 - 1;
        ip->xDD4_itemVar.matadogas.x60 = timer;
        if (timer == 0) {
            ip->xDD4_itemVar.matadogas.x60 = (s32) attrs->x4;
            if (HSD_Randi(2) == 0) {
                it_802CB4F0(gobj, 0xC1, attrs->x8);
            } else {
                it_802CB4F0(gobj, 0xC2, attrs->xC);
            }
        }
    }
}

void it_802CB350(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itMatadogas_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #itMatadogas_UnkMotion2_Phys

bool itMatadogas_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CB0F4);
}

/// #it_802CB4F0

/// #it_2725_Logic32_Spawned

/// #it_2725_Logic33_Spawned

void itMatadogas_Logic33_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802CB798

bool it_802CB810(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #it_802CB844

bool it_802CB8A4(Item_GObj* gobj)
{
    return false;
}
