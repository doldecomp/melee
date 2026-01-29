#include "itkireihana.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/random.h"
#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F7E28[] = {
    { 0, itKireihana_UnkMotion0_Anim, itKireihana_UnkMotion0_Phys,
      itKireihana_UnkMotion0_Coll },
    { 1, itKireihana_UnkMotion1_Anim, itKireihana_UnkMotion1_Phys,
      itKireihana_UnkMotion1_Coll },
    { 2, itKireihana_UnkMotion2_Anim, itKireihana_UnkMotion2_Phys,
      itKireihana_UnkMotion2_Coll },
    { 3, itKireihana_UnkMotion3_Anim, itKireihana_UnkMotion3_Phys,
      itKireihana_UnkMotion3_Coll },
    { 4, itKireihana_UnkMotion4_Anim, itKireihana_UnkMotion4_Phys,
      itKireihana_UnkMotion4_Coll }
};

void it_2725_Logic15_Spawned(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itkireihanaAttributes* attrs =
        item->xC4_article_data->x4_specialAttributes;
    item->facing_dir = 0.0f;
    item->xDAC_itcmd_var0 = 0;
    item->xDD4_itemVar.kireihana.timer_unk0 = attrs->x4;
    it_802D08F0(gobj);
    it_80279CDC(gobj, attrs->x0);
    Item_8026AE84(item, 0x2725, 0x7f, 0x40);
    item->xDD4_itemVar.kireihana.timer_unk1 = attrs->x8;
    item->xDD4_itemVar.kireihana.timer_unk2 = attrs->xC;
    item->xDD4_itemVar.kireihana.fall_speed = 0.0f;
    item->xDD4_itemVar.kireihana.x70 = 0.0f;
}

void it_2725_Logic15_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D0138(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_80273454(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.kireihana.fall_speed = 0.0f;
}

void it_802D01A0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    item->xDD4_itemVar.kireihana.fall_speed = 0.0f;
}

static void itKireihana_UnkMotion1_Anim_inline(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_80273454(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.kireihana.fall_speed = 0.0f;
}

bool itKireihana_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->xDD4_itemVar.kireihana.x70 = item->xDD4_itemVar.kireihana.x8;
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    if (!it_80272C6C(gobj)) {
        if (--item->xDD4_itemVar.kireihana.timer_unk0 <= 0) {
            it_802D05D8(gobj);
        } else {
            itKireihana_UnkMotion1_Anim_inline(gobj);
        }
    }
    return false;
}

void itKireihana_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    PAD_STACK(8);
    if (--item->xDD4_itemVar.kireihana.timer_unk1 == 0) {
        itkireihanaAttributes* attrs =
            item->xC4_article_data->x4_specialAttributes;
        it_8027ADEC(0x470, gobj, item->xBBC_dynamicBoneTable->bones[2], 2.6f);
        if (--item->xDD4_itemVar.kireihana.timer_unk2 == 0) {
            if (HSD_Randi(2)) {
                Item_8026AE84(item, 0x2726, 0x7FU, 0x40U);
            } else {
                Item_8026AE84(item, 0x2727, 0x7FU, 0x40U);
            }
            item->xDD4_itemVar.kireihana.timer_unk2 = attrs->xC;
        }
        item->xDD4_itemVar.kireihana.timer_unk1 = attrs->x8;
    }
    it_8027A344(gobj);
}

bool itKireihana_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    if (!it_8026DA08(gobj) && item->xDD4_itemVar.kireihana.x70 < 0.0f &&
        item->xDD4_itemVar.kireihana.x8 > 0.0f)
    {
        it_802D03F8(gobj);
    }
    return false;
}

void it_802D03F8(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
}

static void itKireihana_UnkMotion2_Anim_inline(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

bool itKireihana_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    if (!it_80272C6C(gobj)) {
        if (item->xDD4_itemVar.kireihana.timer_unk0-- <= 0) {
            it_802D0774(gobj);
        } else {
            itKireihana_UnkMotion2_Anim_inline(gobj);
        }
    }
    return false;
}

void itKireihana_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    PAD_STACK(8);
    if (--item->xDD4_itemVar.kireihana.timer_unk1 == 0) {
        itkireihanaAttributes* attrs =
            item->xC4_article_data->x4_specialAttributes;
        it_8027ADEC(0x470, gobj, item->xBBC_dynamicBoneTable->bones[2], 2.6f);
        item->xDD4_itemVar.kireihana.timer_unk1 = attrs->x8;
    }
    it_8027A344(gobj);
    item->xDD4_itemVar.kireihana.fall_speed +=
        item->xCC_item_attr->x10_fall_speed;
    if (item->xDD4_itemVar.kireihana.fall_speed >
        item->xCC_item_attr->x14_fall_speed_max)
    {
        item->xDD4_itemVar.kireihana.fall_speed =
            item->xCC_item_attr->x14_fall_speed_max;
    }
    item->x40_vel.y = -item->xDD4_itemVar.kireihana.fall_speed;
}

bool itKireihana_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E248(gobj, it_802D01A0);
    return false;
}

void it_802D05D8(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    item->xDD4_itemVar.kireihana.fall_speed = 0.0f;
}

void it_802D062C(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    item->xDD4_itemVar.kireihana.fall_speed = 0.0f;
}

bool itKireihana_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->xDD4_itemVar.kireihana.x70 = item->xDD4_itemVar.kireihana.x8;
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    if (!it_80272C6C(gobj)) {
        return true;
    }
    return false;
}

void itKireihana_UnkMotion3_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itKireihana_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    if (!it_8026DA08(gobj) && item->xDD4_itemVar.kireihana.x70 < 0.0f &&
        item->xDD4_itemVar.kireihana.x8 > 0.0f)
    {
        it_802D07C0(gobj);
    }
    return false;
}

void it_802D0774(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void it_802D07C0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 4, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itKireihana_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8027A160(item->xBBC_dynamicBoneTable->bones[1], item);
    if (!it_80272C6C(gobj)) {
        return true;
    }
    return false;
}

void itKireihana_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8027A344(gobj);
    item->xDD4_itemVar.kireihana.fall_speed +=
        item->xCC_item_attr->x10_fall_speed;
    if (item->xDD4_itemVar.kireihana.fall_speed >
        item->xCC_item_attr->x14_fall_speed_max)
    {
        item->xDD4_itemVar.kireihana.fall_speed =
            item->xCC_item_attr->x14_fall_speed_max;
    }
    item->x40_vel.y = -item->xDD4_itemVar.kireihana.fall_speed;
}

bool itKireihana_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E248(gobj, it_802D062C);
    return false;
}

void it_802D08F0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool itKireihana_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itKireihana_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itKireihana_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D0138);
}
