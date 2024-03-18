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

#include <baselib/gobj.h>

void (*it_802D1204(Item_GObj* arg0))(Item_GObj*);
void (*it_802D1320(Item_GObj* arg0))(Item_GObj*);
void (*it_802D100C(Item_GObj* arg0))(Item_GObj*);
void it_802D1140(Item_GObj* gobj);                 /* static */
void fn_802D0F98(Item_GObj* gobj);                 /* static */
void it_802D0DBC(Item_GObj* gobj);                 /* static */
M2C_UNK it_80274250(Item_GObj*, s32*, s32, void*); /* extern */
void it_8026E71C(Item_GObj* (*) (Item_GObj*) );    /* extern */
void (*it_802D0C44(Item_GObj*))(Item_GObj*);

f32 it_804DD440 = 0.0F;
f32 it_804DD444 = 1.0F;
extern f64 it_804DD448;

extern M2C_UNK it_803B86C8; // rodata

void it_802D09D0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (!((M2C_FIELD(ip, u8*, 0xDCA) >> 4) & 1) && (ip->msid != 6)) {
        it_802D1204(gobj);
    }
}

void it_802D0A0C(Item_GObj* gobj)
{
    Item* ip;
    void* temp_r29;

    ip = GET_ITEM(gobj);
    temp_r29 = ip->xC4_article_data->x4_specialAttributes;
    ip->facing_dir = it_804DD440;
    M2C_FIELD(ip, u8*, 0xDC8) = M2C_FIELD(ip, u8*, 0xDC8) | 0x80;
    ip->xDD4_itemVar.pokemon.timer = 0xB4 - M2C_FIELD(temp_r29, s32*, 8);
    it_80279CDC(gobj, M2C_FIELD(temp_r29, f32*, 0));
    it_80273454(gobj);
    it_802D1320(gobj);
    M2C_FIELD(ip, u8*, 0xDC8) = M2C_FIELD(ip, u8*, 0xDC8) | 0x80;
    ip->xDD4_itemVar.PKThunderVars.xE38.y = M2C_FIELD(temp_r29, f32*, 0xC);
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

void (*it_802D0B04(Item_GObj* gobj))(Item_GObj*)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->x5D0_animFrameSpeed = it_804DD444;
    lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed);
    Item_80268E5C(gobj, 1, ITEM_UNK_0x1);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;

    return efLib_ResumeAll;
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
    Item* temp_r31;
    void* temp_r30;

    temp_r31 = GET_ITEM(gobj);
    temp_r30 = temp_r31->xC4_article_data->x4_specialAttributes;
    if (it_8026DA08(gobj) == 0) {
        M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if (temp_r31->x5CC_currentAnimFrame == M2C_FIELD(temp_r30, s32*, 4)) {
            it_802D0C44(gobj);
        }
    }
    return false;
}

void (*it_802D0C44(Item_GObj* gobj))(Item_GObj*)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->x5D0_animFrameSpeed = it_804DD444;
    lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed);
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;

    return efLib_ResumeAll;
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
    // it_8026E15C(gobj, it_802D0B04);
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

// Undeclared write to $cr0_eq in subic.$r0, $r4,
//     0x1 Undeclared write to $cr0_eq in subic.$r0, $r4,
//     0x1 extern f32 it_804DD444;

void it_802D0DBC(Item_GObj* gobj)
{
    f32 sp10;
    void* temp_r30;
    void* temp_r31;

    // Error: Undeclared write to $cr0_eq in subic. $r0, $r4, 0x1
    // At instruction: subic. $r0, $r4, 0x1
    if (M2C_ERROR()) {
        temp_r30 = M2C_FIELD(M2C_FIELD(temp_r31, void**, 0xC4), void**, 4);
        sp10 = it_804DD444;
        efSync_Spawn(0x471, gobj,
                     M2C_FIELD(M2C_FIELD(temp_r31, void**, 0xBBC), s32*, 0xC),
                     &sp10);
        M2C_FIELD(temp_r31, s32*, 0xE38) = M2C_FIELD(temp_r30, s32*, 0xC);
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
    // it_8026E71C(it_802D1204);
    return false;
}

void (*it_802D100C(Item_GObj* arg0))(Item_GObj*)
{
    Item* temp_r31;

    temp_r31 = arg0->user_data;
    it_8026B3A8(arg0);
    Item_80268E5C(arg0, 5, ITEM_ANIM_UPDATE);
    temp_r31->on_accessory = it_802D1140;
    temp_r31->entered_hitlag = M2C_ERROR(
        /* unknown instruction: subi $r0, $r3, %l(efLib_PauseAll) */);
    temp_r31->exited_hitlag = M2C_ERROR(
        /* unknown instruction: subi $r0, $r3, %l(efLib_ResumeAll) */);
    return efLib_ResumeAll;
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

// Undeclared write to $cr0_eq in subic. $r0, $r3, 0x1
// Undeclared write to $cr0_eq in subic. $r0, $r3, 0x1
// Undeclared write to $cr0_eq in subic. $r0, $r3, 0x1
// Undeclared write to $cr0_eq in subic. $r0, $r3, 0x1

void it_802D1140(Item_GObj* gobj)
{
    f32 sp10;
    Item* temp_r4;
    void* temp_r30;

    // Error: Undeclared write to $cr0_eq in subic. $r0, $r3, 0x1
    // At instruction: subic. $r0, $r3, 0x1
    if (M2C_ERROR()) {
        // Error: Undeclared write to $cr0_eq in subic. $r0, $r3, 0x1
        // At instruction: subic. $r0, $r3, 0x1
        if (M2C_ERROR()) {
            temp_r30 = temp_r4->xC4_article_data->x4_specialAttributes;
            sp10 = it_804DD444;
            efSync_Spawn(0x471, gobj, temp_r4->xBBC_dynamicBoneTable->bones[3],
                         &sp10);
            temp_r4->xDD4_itemVar.PKThunderVars.xE38.y =
                M2C_FIELD(temp_r30, f32*, 0xC);
        }
        it_8026B390(gobj);
        if (temp_r4->xDAC_itcmd_var0 != 0) {
            temp_r4->xDAC_itcmd_var0 = 0;
            Item_8026AE84(temp_r4, 0x271F, 0x7F, 0x40);
        }
    }
}

void (*it_802D1204(Item_GObj* arg0))(Item_GObj*)
{
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    HSD_JObj* temp_r30;
    Item* temp_r31;
    s32 temp_r5;
    void* temp_r6;

    temp_r31 = arg0->user_data;
    temp_r30 = arg0->hsd_obj;
    Item_8026AE84(temp_r31, 0x2720, 0x7F, 0x40);
    if ((M2C_FIELD(temp_r31, u8*, 0xDCA) >> 4) & 1) {
        temp_r6 = M2C_ERROR(
            /* unknown instruction: subi $r6, $r3, %l(it_803B86C8) */);
        temp_r5 = M2C_FIELD(temp_r6, s32*, 0);
        sp14 = temp_r5;
        sp18 = M2C_FIELD(temp_r6, s32*, 4);
        sp1C = M2C_FIELD(temp_r6, s32*, 8);
        it_80274250(arg0, &sp14, temp_r5, temp_r6);
    }
    it_8026B3A8(arg0);
    HSD_JObjSetFlagsAll(temp_r30, 0x10);
    it_8026BD24(arg0);
    it_8027518C(arg0);
    it_80273454(arg0);
    it_802756D0(arg0);
    it_80275444(arg0);
    Item_80268E5C(arg0, 6, ITEM_ANIM_UPDATE);
    temp_r31->entered_hitlag = M2C_ERROR(
        /* unknown instruction: subi $r0, $r3, %l(efLib_PauseAll) */);
    temp_r31->exited_hitlag = M2C_ERROR(
        /* unknown instruction: subi $r0, $r3, %l(efLib_ResumeAll) */);
    return efLib_ResumeAll;
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

void (*it_802D1320(Item_GObj* gobj))(Item_GObj*)
{
    Item* ip = GET_ITEM(gobj);

    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    return efLib_ResumeAll;
}

bool it_802D1384(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D13A8(Item_GObj* gobj)
{
    Item* ip;
    void* var_r3;

    var_r3 = it_8027A09C;
    if (var_r3 != 0) {
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, ITEM_UNK_0x1);
        var_r3 = efLib_ResumeAll;
        ip->entered_hitlag = M2C_ERROR(
            /* unknown instruction: subi $r0, $r3, %l(efLib_PauseAll) */);
        ip->exited_hitlag = M2C_ERROR(
            /* unknown instruction: subi $r0, $r3, %l(efLib_ResumeAll) */);
    }
}

bool it_802D1410(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D0AAC);
}

ItemStateTable it_803F7E78[] = {
    { 0, it_802D1384, it_802D13A8, it_802D1410 },
    { 1, it_802D0B74, it_802D0BB4, it_802D0BB8 },
    { 2, it_802D0CB4, it_802D0CBC, it_802D0CEC },
    { 3, it_802D0D70, it_802D0DB0, it_802D0DB4 },
    { 4, it_802D0EFC, it_802D0F3C, it_802D0F6C },
    { 5, it_802D1078, it_802D10B8, it_802D10F4 },
    { 6, it_802D12F4, it_802D1314, it_802D1318 },
};
