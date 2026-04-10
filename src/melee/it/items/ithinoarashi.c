#include "ithinoarashi.h"

#include "placeholder.h"

#include "baselib/gobj.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

/* 2D5D7C */ void it_802D5D7C(HSD_GObj*);
/* 2D60C8 */ static bool itHinoarashi_UnkMotion2_Anim(Item_GObj* gobj);
/* 2D64B8 */ void it_802D64B8(HSD_GObj*, Vec3*, u32, f32);

void it_802D5D7C(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;

    if (ip->xDAC_itcmd_var0 != 0) {
        if (!ip->xDD4_itemVar.hinoarashi.x60.b0) {
            ip->xDD4_itemVar.hinoarashi.x60.b0 = true;
            efSync_Spawn(0x473, gobj, ip->xBBC_dynamicBoneTable->bones[2]);
        }
        lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[2], NULL, &pos);
        it_802D64B8(gobj, &pos, Item_8026AE60(), ip->facing_dir);
        ip->xDAC_itcmd_var0 = 0;
    }
    if (ip->xDB0_itcmd_var1 != 0) {
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.hinoarashi.x60.b1 = true;
        ip->xDB0_itcmd_var1 = 0;
    }
}

void it_802D5CF8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDD4_itemVar.hinoarashi.x60.b0 = false;
    ip->xDD4_itemVar.hinoarashi.x60.b1 = false;
    ip->xDD4_itemVar.hinoarashi.x64 = 0.0f;
    it_80279CDC(gobj, ip->scl);
    Item_8026AE84(ip, 0x2734, 0x7FU, 0x40U);
    it_802D5E4C(gobj);
}

void it_802D5E4C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
    it_8026BDB4(gobj);
}

bool it_802D5EC8(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itHinoarashi_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHinoarashi_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

bool itHinoarashi_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void it_802D5EEC(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

void it_802D5F0C(Item_GObj* gobj)
{
    it_8027A118(gobj, it_802D5F34);
}

void it_802D5F34(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_802756E0((Item_GObj*) gobj);
    it_802754D4((Item_GObj*) gobj);
    it_802754BC((Item_GObj*) gobj);
    it_80273454((Item_GObj*) gobj);
    ip->on_accessory = it_802D5D7C;
    ip->xDD1_flag.b1 = true;
}

bool itHinoarashi_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHinoarashiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (!it_80272C6C(gobj)) {
        return true;
    }
    if (ip->xDD4_itemVar.hinoarashi.x60.b0 &&
        !ip->xDD4_itemVar.hinoarashi.x60.b1)
    {
        if (!ip->xDD4_itemVar.hinoarashi.x64) {
            ip->xDD4_itemVar.hinoarashi.x64 = attr->x8;
            it_802752D8(gobj, 3, 0x2735);
        }
        ip->xDD4_itemVar.hinoarashi.x64--;
    }
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[1], ip);
    return false;
}

bool it_2725_Logic27_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHinoarashiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xC9C >= attr->x4) {
        it_80279D38(gobj);
        it_802762BC(gobj->user_data);
        it_802756D0(gobj);
        efLib_DestroyAll(gobj);
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        it_80273670(gobj, 0, 0.0f);
    }
    return false;
}

void it_802D61A8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void itHinoarashi_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

void it_802D6674(Item_GObj* gobj, s32 arg1)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 scale = 1.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    efSync_Spawn(arg1 + 0x44E, gobj, jobj, &ip->facing_dir, &scale);
    it_8026B3A8(gobj);
}
