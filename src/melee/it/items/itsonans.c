#include "itsonans.h"

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F7C70[] = {
    { 0, itSonans_UnkMotion0_Anim, itSonans_UnkMotion0_Phys,
      itSonans_UnkMotion0_Coll },
    { 1, itSonans_UnkMotion1_Anim, itSonans_UnkMotion1_Phys,
      itSonans_UnkMotion1_Coll },
    { 2, itSonans_UnkMotion2_Anim, itSonans_UnkMotion2_Phys,
      itSonans_UnkMotion2_Coll }
};

void it_802CD44C(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itsonansAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    item->facing_dir = 0.0f;
    item->xDAC_itcmd_var0 = 0;
    item->xD44_lifeTimer = attrs->x24;
    item->xDD4_itemVar.sonans.x60 = 0.0f;
    item->xDD4_itemVar.sonans.x64 = 0.0f;
    item->xDD4_itemVar.sonans.x68 = 0.0f;
    it_80279CDC(gobj, attrs->x0);
    it_80275444(gobj);
    it_802CDAA8(gobj);
}

void it_802CD4D8(Item_GObj* gobj) {}

void it_802CD4DC(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

//99.63%
void it_802CD4FC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSonans_DatAttrs* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 angle;
    f32 max_angle;
    if (ip->ground_or_air == GA_Air)
    {
        it_80272860(gobj, ip->xCC_item_attr->x10_fall_speed,
                    ip->xCC_item_attr->x14_fall_speed_max);
    }
    if (ip->xDAC_itcmd_var0)
    {
        angle = ip->xDD4_itemVar.sonans.x64;
        if (angle > 0.0f && ip->xDD4_itemVar.sonans.x60 > 0.0f)
        {
            ip->xDD4_itemVar.sonans.x60 += attr->x14;
        } else if (angle <= 0.0f && ip->xDD4_itemVar.sonans.x60 <= 0.0f)
        {
            ip->xDD4_itemVar.sonans.x60 -= attr->x14;
        } else if (angle > 0.0f && ip->xDD4_itemVar.sonans.x60 <= 0.0f)
        {
            ip->xDD4_itemVar.sonans.x60 -= attr->x10;
        } else if (angle <= 0.0f && ip->xDD4_itemVar.sonans.x60 > 0.0f)
        {
            ip->xDD4_itemVar.sonans.x60 += attr->x10;
        }
        angle = ip->xDD4_itemVar.sonans.x64;
        if (angle < 0.0f)
        {
            angle = -angle;
        }
        if (angle < attr->x1C)
        {
            angle = ip->xDD4_itemVar.sonans.x60;
            if (angle < 0.0f)
            {
                angle = -angle;
            }
            if (angle < attr->x1C)
            {
                ip->xDD4_itemVar.sonans.x64 = 0.0f;
                ip->xDD4_itemVar.sonans.x60 = 0.0f;
                ip->xDAC_itcmd_var0 = 0;
            } else
            {
                goto accumulate;
            }
        } else
        {
        accumulate:
            ip->xDD4_itemVar.sonans.x64 += ip->xDD4_itemVar.sonans.x60;
        }
        angle = ip->xDD4_itemVar.sonans.x64;
        max_angle = attr->x18;
        if (angle > max_angle)
        {
            ip->xDD4_itemVar.sonans.x60 =
                (f32) (ip->xDD4_itemVar.sonans.x60 * it_804DD3C8);
            ip->xDD4_itemVar.sonans.x64 = attr->x18;
        } else if (angle < -max_angle)
        {
            ip->xDD4_itemVar.sonans.x60 =
                (f32) (ip->xDD4_itemVar.sonans.x60 * it_804DD3C8);
            ip->xDD4_itemVar.sonans.x64 = -attr->x18;
        }
        HSD_JObjSetRotationZ(ip->xBBC_dynamicBoneTable->bones[4],
                             it_804DD3D0 * ip->xDD4_itemVar.sonans.x64);
    }
    it_80272460(&ip->x5D4_hitboxes[0].hit, (u32) ip->xDD4_itemVar.sonans.x68,
                gobj);
    ip->xDD4_itemVar.sonans.x68 -= attr->x20;
}

bool it_2725_Logic9_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sonans.x60 *= -1.0f;
    return false;
}

//99.04%
bool it_802CD7D4(Item_GObj* gobj) {
    Item* item = GET_ITEM(gobj);
    itsonansAttributes* attrs = item->xC4_article_data->x4_specialAttributes;
    f32 var_f1;
    f32 var_f3;
    f32 temp;
    if (item->xDAC_itcmd_var0 == 0)
    {
        item->xDD4_itemVar.sonans.x60 = attrs->x8 * (item->xCA0 * item->xCCC_incDamageDirection);
        item->xDAC_itcmd_var0 = 1;
    } else
    {
        if ((attrs->x8 * (item->xCA0 * item->xCCC_incDamageDirection)) < 0.0f)
        {
            var_f1 = -(attrs->x8 * (item->xCA0 * item->xCCC_incDamageDirection));
        } else
        {
            var_f1 = (attrs->x8 * (item->xCA0 * item->xCCC_incDamageDirection));
        }
        var_f3 = item->xDD4_itemVar.sonans.x60;
        if (var_f3 < 0.0f)
        {
            var_f3 = -var_f3;
        }
        if (var_f3 < var_f1)
        {
            item->xDD4_itemVar.sonans.x60 = (attrs->x8 * (item->xCA0 * item->xCCC_incDamageDirection));
        }
    }
    temp = item->xCA0 * attrs->x4;
    if (temp > attrs->xC)
    {
        item->xDD4_itemVar.sonans.x68 = attrs->xC;
    } else
    {
        item->xDD4_itemVar.sonans.x68 = temp;
    }
    return false;
}

bool itSonans_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) {
        it_802CD9C0(gobj);
        Item_8026AE84(item, 0x272B, 0x7F, 0x40);
    }
    item->xD44_lifeTimer -= 1.0f;
    return false;
}

void itSonans_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_802CD4FC(gobj);
}

bool itSonans_UnkMotion0_Coll(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CD4D8);
    } else {
        it_8026D62C(gobj, it_802CD4D8);
    }
    return false;
}

void it_802CD9C0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

f32 it_804DD3B8 = 0.0f;

bool itSonans_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (--ip->xD44_lifeTimer == it_804DD3B8) {
        return true;
    }
    return false;
}

void itSonans_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_802CD4FC(gobj);
}

bool itSonans_UnkMotion1_Coll(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CD4D8);
    } else {
        it_8026D62C(gobj, it_802CD4D8);
    }
    return false;
}

void it_802CDAA8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itSonans_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itSonans_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip;
    HSD_GObj* unused;
    if (it_8027A09C(gobj)) {
        it_80273454(gobj);
        it_802756E0(gobj);
        it_802754D4(gobj);
        it_802754BC(gobj);
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 0, 2);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
    }
}

bool itSonans_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (HSD_GObjEvent) it_802CD4D8);
}
