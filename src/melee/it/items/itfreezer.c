#include "itfreezer.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

void it_802CCF9C(Item_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    itfreezertAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    item->facing_dir = 0.0f;
    item->xDAC_itcmd_var0 = 0;
    item->xDB0_itcmd_var1 = 0;
    it_802CD2EC(gobj);
    it_80279CDC(gobj, attrs->x0);
}

void it_802CCFFC(Item_GObj* gobj) {}

void it_802CD000(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itFreezer_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        it_802CD12C(gobj);
    }
    return false;
}

void itFreezer_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFreezer_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802CCFFC);
    return false;
}

void it_802CD090(Item_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    if(item->xDB0_itcmd_var1 != false)
    {
        it_8027ADEC(0x462, gobj, item->xBBC_dynamicBoneTable->bones[5], 1.4f);
        item->xDB0_itcmd_var1 = false;
    }
    if(item->xDD4_itemVar.freezer.x60 <= 0)
    {
        HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
        itfreezertAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.freezer.x60 = attrs->xC;
        it_8027ADEC(0x461, gobj, jobj, 1.4f); 
        return;
    }
    item->xDD4_itemVar.freezer.x60 -= 1;
}

void it_802CD12C(HSD_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->on_accessory = it_802CD290;
    item->xDB0_itcmd_var1 = 0;
}

static void itFreezer_UnkMotion2_Anim_Inline(Item_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->on_accessory = it_802CD290;
    item->xDB0_itcmd_var1 = 0;
}

bool itFreezer_UnkMotion2_Anim(Item_GObj* gobj) 
{
    Item* item_temp = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) 
    {
        itFreezer_UnkMotion2_Anim_Inline(gobj);   
    }
    if (item_temp->pos.y > Stage_GetBlastZoneTopOffset()) {
        return 1;
    }
    return 0;
}

void itFreezer_UnkMotion2_Phys(Item_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    
    if(item->xDAC_itcmd_var0 != false)
    {
        itfreezertAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
        item->x40_vel.y = attrs->x4;
        item->xDAC_itcmd_var0 = 0;
        item->xDB0_itcmd_var1 = 1;
    }
    
    if ((u32) item->xDB0_itcmd_var1 != false) 
    {
        itfreezertAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
        item->x40_vel.y += attrs->x8;
    }
}

bool itFreezer_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CD290(Item_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    
    if (item->xDD4_itemVar.freezer.x60 <= 0) {
        HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
        itfreezertAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.freezer.x60 = attrs->xC;
        it_8027ADEC(0x461, gobj, jobj, 1.4f);
        return;
    }
    item->xDD4_itemVar.freezer.x60 -= 1;
}

void it_802CD2EC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool itFreezer_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

static void itFreezer_UnkMotion0_Phys_inline2(Item_GObj* gobj) 
{
    Item *item = GET_ITEM(gobj);

    item->xDD4_itemVar.freezer.x60 = -1;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->on_accessory = it_802CD090;
}

static void itFreezer_UnkMotion0_Phys_inline1(Item_GObj* gobj) 
{
    Item* item = GET_ITEM(gobj);
    
    it_80273454(gobj);
    itFreezer_UnkMotion0_Phys_inline2(gobj);
    item->xDD1_flag.b1 = true;
}

void itFreezer_UnkMotion0_Phys(Item_GObj* gobj) 
{
    if (it_8027A09C(gobj) != 0) {
        itFreezer_UnkMotion0_Phys_inline1(gobj);
    }
}

bool itFreezer_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CCFFC);
}
