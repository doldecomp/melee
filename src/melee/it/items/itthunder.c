#include "itthunder.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F7C40[] = {
    { 0, itThunder_UnkMotion0_Anim, itThunder_UnkMotion0_Phys,
      itThunder_UnkMotion0_Coll },
    { 1, itThunder_UnkMotion1_Anim, itThunder_UnkMotion1_Phys,
      itThunder_UnkMotion1_Coll },
    { 2, itThunder_UnkMotion2_Anim, itThunder_UnkMotion2_Phys,
      itThunder_UnkMotion2_Coll }
};

void it_2725_Logic7_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itThunderAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->facing_dir = 0.0f;
    ip->xDAC_itcmd_var0 = 0;
    it_802CCE28(gobj);
    it_80279CDC(gobj, attrs->x0);
}

void it_802CCB10(Item_GObj* gobj) {}

void it_802CCB14(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itThunder_UnkMotion1_Anim(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (!jobj) {
        jobj = NULL;
    } else {
        jobj = jobj->child;
    }
    if (jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = jobj->child;
    }
    it_8027A160(jobj, item);
    if (!it_80272C6C(gobj)) {
        it_802CCC68(gobj);
    }
    return false;
}

void itThunder_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itThunder_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802CCB10);
    return false;
}

void it_802CCBF8(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    f32 out = 1.0f;
    if(item->xDD4_itemVar.thunder.x64)
    {
        if(item->xDD4_itemVar.thunder.x60 <= 0){
            item->xDD4_itemVar.thunder.x64 = 0;
            efSync_Spawn(0x460, gobj, item->xBBC_dynamicBoneTable->bones[2], &out);
        }else {
            item->xDD4_itemVar.thunder.x60 = item->xDD4_itemVar.thunder.x60 - 1;
        }
    }
}

void it_802CCC68(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.thunder.x68 = it_804DD3A8;
    item->xDB0_itcmd_var1 = 0;
}

static void itThunder_UnkMotion2_Anim_inline2(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.thunder.x68 = 0.0f;
    item->xDB0_itcmd_var1 = 0;
}

static HSD_JObj *itThunder_UnkMotion2_Anim_inline(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (!jobj) {
        child = NULL;
    }else {
        child = jobj->child;
    }
    if(!child) {
        child = NULL;
    }else {
        child = child->child;
    }
    return child;
}

bool itThunder_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8027A160(itThunder_UnkMotion2_Anim_inline(gobj), item);
    if (!it_80272C6C(gobj)) {
        itThunder_UnkMotion2_Anim_inline2(gobj);
    }
    if (item->pos.y > Stage_GetBlastZoneTopOffset()) {
        return true;
    }
    return false;
}

void itThunder_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8027A344(gobj);
    if (item->xDAC_itcmd_var0 != 0) {
        itThunderAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.thunder.x68 = attrs->x4;
        item->xDAC_itcmd_var0 = 0;
        item->xDB0_itcmd_var1 = 1;
    }
    if (item->xDB0_itcmd_var1 != 0) {
        itThunderAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.thunder.x68 += attrs->x8;
    }
    item->x40_vel.y = item->xDD4_itemVar.thunder.x68;
}

bool itThunder_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CCE28(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool itThunder_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

static void itThunder_UnkMotion0_Phys_inline2(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itThunderAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    item->xDD4_itemVar.thunder.x60 = attrs->xC;
    item->xDD4_itemVar.thunder.x64 = 1;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->on_accessory = it_802CCBF8;
}

static void itThunder_UnkMotion0_Phys_inline(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_80273454(gobj);
    itThunder_UnkMotion0_Phys_inline2(gobj);
    item->xDD1_flag.b1 = 1;
}

void itThunder_UnkMotion0_Phys(Item_GObj* gobj)
{
    if (it_8027A09C(gobj) != 0) {
        itThunder_UnkMotion0_Phys_inline(gobj);
    }
}

bool itThunder_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CCB10);
}
