#include "itmatadogas.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_0C31.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/debug.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

void it_802CAFD4(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* item;
    itMatadogasAttributes* attrs;
    item = gobj->user_data;
    jobj = gobj->hsd_obj;
    attrs = item->xC4_article_data->x4_specialAttributes;
    item->xDAC_itcmd_var0 = 0;
    item->xDD4_itemVar.matadogas.x60 = (s32) attrs->x4;
    item->xDD4_itemVar.matadogas.x64 = 0;
    it_80279CDC(gobj, attrs->x0);
    it_802CB350(gobj);
    HSD_JObjSetRotationY(jobj, 0.0f);
    Item_8026AE84(item, 0x2715, 0x7f, 0x40);
}

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
        itMatadogasAttributes* attrs =
            ip->xC4_article_data->x4_specialAttributes;
        if (--ip->xDD4_itemVar.matadogas.x60 == 0) {
            ip->xDD4_itemVar.matadogas.x60 = attrs->x4;
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

void itMatadogas_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* item;
    Item* item2;
    HSD_JObj* jobj;

    if (it_8027A09C(gobj)) {
        item = gobj->user_data;
        it_80273454(gobj);
        item2 = gobj->user_data;
        jobj = gobj->hsd_obj;
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        item2->entered_hitlag = efLib_PauseAll;
        item2->exited_hitlag = efLib_ResumeAll;
        ((jobj) ? ((void) 0) : __assert("jobj.h", 660, "jobj"));
        ((!(jobj->flags & JOBJ_USE_QUATERNION)) ? ((void) 0)
            : __assert("jobj.h", 661,
                       "!(jobj->flags & JOBJ_USE_QUATERNION)"));
        jobj->rotate.y = 0.0f;
        if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
            ftCo_800C6AFC(jobj);
        }
        item2->on_accessory = (HSD_GObjEvent) it_802CB2B0;
        item->xDD1_flag.b1 = 1;
    }
}

bool itMatadogas_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CB0F4);
}

/// #it_802CB4F0

void it_2725_Logic32_Spawned(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 scale = 1.0f;
    PAD_STACK(4);
    efSync_Spawn(0x45B, gobj, jobj, &scale);
    efSync_Spawn(0x45D, gobj, jobj, &scale);
    it_802CB798(gobj);
}

void it_2725_Logic33_Spawned(Item_GObj* gobj)
{
    UNUSED u32 _pad;
    f32 scale;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(4);
    scale = 1.0f;
    efSync_Spawn(0x45C, gobj, jobj, &scale);
    efSync_Spawn(0x45E, gobj, jobj, &scale);
    it_802CB798(gobj);
}

void itMatadogas_Logic33_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CB798(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itMatadogasAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    ip->xD44_lifeTimer = attrs->x0;
    it_80274740(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8026B3A8(gobj);
}

bool it_802CB810(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void it_802CB844(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    f32 scale = 0.0f;
    ItemKind kind = ip->kind;
    itMatadogasAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    switch (kind) {
    case 0xC1:
        scale = attrs->x4;
        break;
    case 0xC2:
        scale = attrs->x8;
        break;
    }

    ip->x40_vel.x *= scale;
    ip->x40_vel.y *= scale;
    ip->x40_vel.z *= scale;
}

bool it_802CB8A4(Item_GObj* gobj)
{
    return false;
}
