#include "itmarumine.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

static Vec3 const it_803B86C8 = { 0 };

/* 2D0AAC */ static void it_802D0AAC(Item_GObj* gobj);
/* 2D0B04 */ static void it_802D0B04(Item_GObj* gobj);
/* 2D0B74 */ static bool it_802D0B74(Item_GObj* gobj);
/* 2D0BB4 */ static void it_802D0BB4(Item_GObj* gobj);
/* 2D0BB8 */ static bool it_802D0BB8(Item_GObj* gobj);
/* 2D0C44 */ static void it_802D0C44(Item_GObj* gobj);
/* 2D0CB4 */ static bool it_802D0CB4(Item_GObj* gobj);
/* 2D0CBC */ static void it_802D0CBC(Item_GObj* gobj);
/* 2D0CEC */ static bool it_802D0CEC(Item_GObj* gobj);
/* 2D0D70 */ static bool it_802D0D70(Item_GObj* gobj);
/* 2D0DB0 */ static void it_802D0DB0(Item_GObj* gobj);
/* 2D0DB4 */ static bool it_802D0DB4(Item_GObj* gobj);
/* 2D0DBC */ static void it_802D0DBC(Item_GObj* gobj);
/* 2D0EFC */ static bool it_802D0EFC(Item_GObj* gobj);
/* 2D0F3C */ static void it_802D0F3C(Item_GObj* gobj);
/* 2D0F6C */ static bool it_802D0F6C(Item_GObj* gobj);
/* 2D0F98 */ static void fn_802D0F98(Item_GObj* gobj);
/* 2D100C */ static void it_802D100C(Item_GObj* gobj);
/* 2D1078 */ static bool it_802D1078(Item_GObj* gobj);
/* 2D10B8 */ static void it_802D10B8(Item_GObj* gobj);
/* 2D10F4 */ static bool it_802D10F4(Item_GObj* gobj);
/* 2D1140 */ static void it_802D1140(Item_GObj* gobj);
/* 2D1204 */ static void it_802D1204(Item_GObj* gobj);
/* 2D12F4 */ static bool it_802D12F4(Item_GObj* gobj);
/* 2D1314 */ static void it_802D1314(Item_GObj* gobj);
/* 2D1318 */ static bool it_802D1318(Item_GObj* gobj);
/* 2D1320 */ static void it_802D1320(Item_GObj* gobj);
/* 2D1384 */ static bool it_802D1384(Item_GObj* gobj);
/* 2D13A8 */ static void it_802D13A8(Item_GObj* gobj);
/* 2D1410 */ static bool it_802D1410(Item_GObj* gobj);

ItemStateTable it_803F7E78[] = {
    { 0, it_802D1384, it_802D13A8, it_802D1410 },
    { 1, it_802D0B74, it_802D0BB4, it_802D0BB8 },
    { 2, it_802D0CB4, it_802D0CBC, it_802D0CEC },
    { 3, it_802D0D70, it_802D0DB0, it_802D0DB4 },
    { 4, it_802D0EFC, it_802D0F3C, it_802D0F6C },
    { 5, it_802D1078, it_802D10B8, it_802D10F4 },
    { 6, it_802D12F4, it_802D1314, it_802D1318 },
};

void it_802D09D0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if ((ip->xDC8_word.flags.x13 == false) && (ip->msid != 6)) {
        it_802D1204(gobj);
    }
}

void it_802D0A0C(Item_GObj* gobj)
{
    Item* ip;
    itPokemonAttributes* attr;

    ip = GET_ITEM(gobj);
    attr = ip->xC4_article_data->x4_specialAttributes;
    ip->facing_dir = 0.0F;
    ip->xDC8_word.flags.x0 = true;
    ip->xDD4_itemVar.pokemon.timer = 0xB4 - attr->max;
    it_80279CDC(gobj, attr->x0);
    it_80273454(gobj);
    it_802D1320(gobj);
    ip->xDC8_word.flags.x0 = true;
    ip->xDD4_itemVar.pokemon.x64 = attr->xC;
    ip->xDAC_itcmd_var0 = 1;
}

void it_802D0AAC(Item_GObj* gobj) {}

void it_802D0AB0(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}

bool it_802D0AD0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->msid == 4) {
        it_802D1204(gobj);
    }
    return false;
}

void it_802D0B04(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->x5D0_animFrameSpeed = 1.0F;
    lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed);
    Item_80268E5C(gobj, 1, ITEM_UNK_0x1);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D0B74(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802D100C(gobj);
    }
    return false;
}

void it_802D0BB4(Item_GObj* gobj) {}

bool it_802D0BB8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPokemonAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    if (it_8026DA08(gobj) == false) {
        if (ip->x5CC_currentAnimFrame >= attr->timer) {
            it_802D0C44(gobj);
        }
    }
    return false;
}

void it_802D0C44(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->x5D0_animFrameSpeed = 0.0F;
    lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed);
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D0CB4(Item_GObj* gobj)
{
    return false;
}

void it_802D0CBC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_802D0CEC(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D0B04);
    return false;
}

void it_802D0D18(Item_GObj* gobj)
{
    Item* ip;

    ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_UNK_0x1);
    ip->on_accessory = it_802D0DBC;
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D0D70(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802D1204(gobj);
    }
    return false;
}

void it_802D0DB0(Item_GObj* gobj) {}

bool it_802D0DB4(Item_GObj* gobj)
{
    return false;
}

void it_802D0DBC(Item_GObj* gobj)
{
    f32 sp10;
    itPokemonAttributes* attr;
    Item* ip = GET_ITEM(gobj);

    if (--ip->xDD4_itemVar.pokemon.x64 == 0) {
        attr = ip->xC4_article_data->x4_specialAttributes;
        sp10 = 1.0F;
        efSync_Spawn(0x471, gobj, (ip->xBBC_dynamicBoneTable->bones[3]),
                     &sp10);
        ip->xDD4_itemVar.pokemon.x64 = attr->xC;
    }
}

void it_802D0E30(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    Item_80268E5C(gobj, 4, ITEM_UNK_0x1);
    it_8026B3A8(gobj);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void it_802D0E90(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    Item_80268E5C(gobj, 4, ITEM_UNK_0x1);
    it_8026B3A8(gobj);
    ip->on_accessory = fn_802D0F98;
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D0EFC(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802D1204(gobj);
    }
    return false;
}

void it_802D0F3C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_802D0F6C(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802D1204);
    return false;
}

void fn_802D0F98(Item_GObj* gobj)
{
    f32 sp10;
    Item* ip = GET_ITEM(gobj);

    if (--ip->xDD4_itemVar.pokemon.x64 == 0) {
        itPokemonAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
        sp10 = 1.0F;
        efSync_Spawn(0x471, gobj, ip->xBBC_dynamicBoneTable->bones[3], &sp10);
        ip->xDD4_itemVar.pokemon.x64 = attr->xC;
    }
}

void it_802D100C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802D1140;
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D1078(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802D1204(gobj);
    }
    return false;
}

void it_802D10B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->ground_or_air == GA_Air) {
        ItemAttr* attr = ip->xCC_item_attr;
        it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    }
}

bool it_802D10F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802D0AAC);
    } else {
        it_8026D62C(gobj, it_802D0AAC);
    }
    return false;
}

void it_802D1140(Item_GObj* gobj)
{
    f32 sp10;
    Item* ip;
    itPokemonAttributes* attr;

    ip = GET_ITEM(gobj);

    if (--ip->xDD4_itemVar.pokemon.timer < 0) {
        if (--ip->xDD4_itemVar.pokemon.x64 == 0) {
            attr = ip->xC4_article_data->x4_specialAttributes;
            sp10 = 1.0F;
            efSync_Spawn(0x471, gobj, ip->xBBC_dynamicBoneTable->bones[3],
                         &sp10);
            ip->xDD4_itemVar.pokemon.x64 = attr->xC;
        }
        it_8026B390(gobj);
        if (ip->xDAC_itcmd_var0 != 0) {
            ip->xDAC_itcmd_var0 = 0;
            Item_8026AE84(ip, 0x271F, 0x7F, 0x40);
        }
    }
}

void it_802D1204(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    PAD_STACK(8);

    Item_8026AE84(ip, 0x2720, 0x7F, 0x40);
    if (ip->xDC8_word.flags.x13 != false) {
        Vec3 vec = it_803B86C8;
        it_80274250(gobj, &vec);
    }
    it_8026B3A8(gobj);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    it_802756D0(gobj);
    it_80275444(gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D12F4(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void it_802D1314(Item_GObj* gobj) {}

bool it_802D1318(Item_GObj* gobj)
{
    return false;
}

void it_802D1320(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D1384(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D13A8(Item_GObj* gobj)
{
    Item* ip;

    if (it_8027A09C(gobj) != false) {
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, ITEM_UNK_0x1);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
    }
}

bool it_802D1410(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D0AAC);
}
