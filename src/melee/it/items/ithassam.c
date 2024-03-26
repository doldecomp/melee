#include "it/forward.h"

#include "ithassam.h"

#include "ef/eflib.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"

#include <placeholder.h>
#include <baselib/gobj.h>

extern s8 it_803F7D38;
extern f32 it_804DD3E0;
extern f32 it_804DD3E4;
extern f64 it_804DD3E8;
extern s8 it_804D5600;
extern s8 it_804D5608;
extern f32 it_804DD3F0;
extern f32 it_804DD3F4;

bool it_802CE0C4(Item_GObj*); /* static */
void it_802CE400(Item_GObj*); /* static */
void it_802CE640(Item_GObj*); /* static */
void it_802CDCB4(Item_GObj*); /* static */
bool it_802CDD24(Item_GObj*); /* static */
void it_802CE008(Item_GObj*); /* static */

M2C_UNK it_8027A13C(Item_GObj*); /* extern */
M2C_UNK it_80272980(void*, f32); /* extern */
M2C_UNK Camera_80030788(Vec3*);  /* extern */

void it_802CDBE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Article* ap = ip->xC4_article_data;
    HassamVars* attr = ap->x4_specialAttributes;

    PAD_STACK(12);

    it_80279C48(gobj, ap);
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    it_80279CDC(gobj, attr->x0);
    it_802CE640(gobj);
    Item_8026AE84(ip, 0x2721, 0x7F, 0x40);
}

void it_802CDC5C(Item_GObj* gobj) {}

void it_802CDC60(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}

void it_802CDC80(Item_GObj* arg0)
{
    it_80273454(arg0);
    it_802CDCB4(arg0);
}

void it_802CDCB4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8027A13C(gobj);
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
}

bool it_802CDD24(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    if (it_80272C6C(gobj) == false) {
        it_802CE008(gobj);
    }
    return false;
}

void it_802CDD78(Item_GObj* gobj)
{
    ItemAttr* temp_r4;
    Item* ip = GET_ITEM(gobj);

    it_8027A344(gobj);
    if (ip->ground_or_air == GA_Air) {
        temp_r4 = ip->xCC_item_attr;
        it_80272860(gobj, temp_r4->x10_fall_speed,
                    temp_r4->x14_fall_speed_max);
    }
}

bool it_802CDDD0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CDC5C);
    } else {
        it_8026D62C(gobj, it_802CDC5C);
    }
    return false;
}

Item_GObj* it_802CDE1C(Vec3* arg0, Item_GObj* arg1)
{
    Vec3 sp20;
    Item_GObj* var_r28;
    Item_GObj* var_r29;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f31;
    void* temp_r31;
    void* var_r30;

    var_f31 = it_804DD3E0;
    if (arg1 != NULL) {
        var_r30 = arg1->user_data;
    } else {
        var_r30 = NULL;
    }
    var_r28 = NULL;
    var_r29 = HSD_GObj_Entities->fighters;
loop_13:
    if (var_r29 != NULL) {
        if (ftLib_80086FD4(arg1, var_r29) == 0) {
            temp_r31 = var_r29->user_data;
            if (!((M2C_FIELD(temp_r31, u8*, 0x221F) >> 4) & 1) &&
                ((gm_8016B168() == 0) || (var_r30 == NULL) ||
                 (M2C_FIELD(temp_r31, u8*, 0x61B) !=
                  M2C_FIELD(var_r30, u8*, 0x61B))))
            {
                ftLib_800866DC(var_r29, &sp20);
                temp_f2 = arg0->y;
                temp_f4 = temp_f2 - sp20.y;
                temp_f1 = arg0->x - sp20.x;
                temp_f0 = (temp_f1 * temp_f1) + (temp_f4 * temp_f4);
                if ((temp_f0 < var_f31) && (sp20.y > temp_f2)) {
                    var_f31 = temp_f0;
                    var_r28 = var_r29;
                }
            }
        }
        var_r29 = var_r29->next;
        goto loop_13;
    }
    if (var_r28 == NULL) {
        var_r28 = ftLib_8008627C(arg0, arg1);
    }
    return var_r28;
}

void it_802CDF28(void* arg0)
{
    Vec3 sp1C;
    Vec3 sp10;
    Item_GObj* var_r3;
    f32 temp_f1;
    void* temp_r30;
    void* temp_r31;
    void* temp_r5;

    temp_r31 = M2C_FIELD(arg0, void**, 0x2C);
    temp_r5 = M2C_FIELD(temp_r31, void**, 0xC4);
    temp_r30 = M2C_FIELD(temp_r5, void**, 4);
    // var_r3 =
    //     it_802CDE1C(temp_r31 + 0x4C, M2C_FIELD(temp_r31, Item_GObj**,
    //     0x518));
    var_r3 = NULL;
    if (var_r3 == NULL) {
        var_r3 = M2C_FIELD(temp_r31, Item_GObj**, 0x518);
    }
    ftLib_800866DC(var_r3, &sp1C);
    sp1C.y += M2C_FIELD(temp_r30, f32*, 8);
    // lbVector_Diff(&sp1C, temp_r31 + 0x4C, &sp10);
    M2C_FIELD(temp_r31, f32*, 0xE34) = M2C_FIELD(temp_r30, f32*, 4);
    M2C_FIELD(temp_r31, f32*, 0xE38) = it_804DD3E4;
    M2C_FIELD(temp_r31, f32*, 0xE3C) = it_804DD3E4;
    // lbVector_Rotate(temp_r31 + 0xE34, 4, atan2f(sp10.y, (sp10.x)));
    temp_f1 = M2C_FIELD(temp_r31, f32*, 0xE38);
    M2C_FIELD(temp_r31, f32*, 0xE38) =
        temp_f1 + M2C_FIELD(temp_r30, f32*, 0xC);
    M2C_FIELD(temp_r31, f32*, 0x40) = M2C_FIELD(temp_r31, f32*, 0xE34);
    M2C_FIELD(temp_r31, f32*, 0x44) = M2C_FIELD(temp_r31, f32*, 0xE38);
    M2C_FIELD(temp_r31, f32*, 0x48) = M2C_FIELD(temp_r31, f32*, 0xE3C);
    it_80272980(arg0, temp_f1);
}

void it_802CE008(Item_GObj* arg0)
{
    Item* temp_r31;
    void* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
    temp_r31->entered_hitlag = efLib_PauseAll;
    temp_r31->exited_hitlag = efLib_ResumeAll;
    it_8027A160(temp_r31->xBBC_dynamicBoneTable->bones[2], temp_r31);
    temp_r31->xD44_lifeTimer = M2C_FIELD(temp_r30, s32*, 0x18);
    temp_r31->x40_vel.x = M2C_FIELD(temp_r30, f32*, 4) * temp_r31->facing_dir;
    temp_r31->xDD4_itemVar.pokemon.timer =
        M2C_FIELD(temp_r30, f32*, 4) * temp_r31->facing_dir;
    temp_r31->xDD4_itemVar.pokemon.x64 = it_804DD3E4;
    temp_r31->xDD4_itemVar.PKThunderVars.xE38.z = it_804DD3E4;
}

bool it_802CE0C4(Item_GObj* arg0)
{
    // too big atm lol
    return 0;
}

void it_802CE308(Item_GObj* arg0)
{
    Item* temp_r31;
    f32 temp_f0;
    void* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->xC4_article_data->x4_specialAttributes;
    it_8027A344(arg0);
    if (temp_r31->ground_or_air == GA_Air) {
        temp_r31->xDD4_itemVar.pokemon.x64 -= M2C_FIELD(temp_r30, f32*, 0x14);
        temp_f0 = -M2C_FIELD(temp_r30, f32*, 0x10);
        if (temp_r31->xDD4_itemVar.pokemon.x64 < temp_f0) {
            temp_r31->xDD4_itemVar.pokemon.x64 = temp_f0;
        }
    }
    temp_r31->x40_vel.x += temp_r31->xDD4_itemVar.pokemon.timer;
    temp_r31->x40_vel.y += temp_r31->xDD4_itemVar.pokemon.x64;
    temp_r31->x40_vel.z += temp_r31->xDD4_itemVar.PKThunderVars.xE38.z;
}

bool it_802CE3A8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDAC_itcmd_var0 == 0) {
        if (ip->ground_or_air == GA_Air) {
            it_8026E15C(gobj, it_802CDC5C);
        } else {
            it_8026D62C(gobj, it_802CDC5C);
        }
    }
    return false;
}

void it_802CE400(Item_GObj* arg0)
{
    Vec3 sp1C;
    Vec3 sp10;
    HSD_JObj* temp_r31;
    Item* temp_r30;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;
    void* temp_r29;

    temp_r30 = arg0->user_data;
    temp_r31 = arg0->hsd_obj;
    temp_r29 = temp_r30->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
    temp_r30->entered_hitlag = efLib_PauseAll;
    temp_r30->exited_hitlag = efLib_ResumeAll;
    it_8027A160(temp_r30->xBBC_dynamicBoneTable->bones[2], temp_r30);
    Camera_80030788(&sp1C);
    lbVector_Diff(&sp1C, &temp_r30->pos, &sp10);
    lbVector_Normalize(&sp10);
    sp10.x = sp10.x * M2C_FIELD(temp_r29, f32*, 4);
    temp_f0 = sp10.y * M2C_FIELD(temp_r29, f32*, 4);
    sp10.y = temp_f0;
    temp_f0_2 = sp10.z * M2C_FIELD(temp_r29, f32*, 4);
    sp10.z = temp_f0_2;
    temp_r30->xDD4_itemVar.pokemon.timer = sp10.x;
    temp_r30->xDD4_itemVar.pokemon.x64 = temp_f0;
    temp_r30->xDD4_itemVar.PKThunderVars.xE38.z = temp_f0_2;
    temp_r30->x40_vel.x = it_804DD3E4;
    temp_r30->x40_vel.y = it_804DD3E4;
    temp_r30->x40_vel.z = it_804DD3E4;
    temp_r30->facing_dir = it_804DD3E4;
    if (temp_r31 == NULL) {
        //__assert(&it_804D5600, 0x294, &it_804D5608);
    }
    if (temp_r31->flags & 0x20000) {
        //__assert(&it_804D5600, 0x295, &it_803F7D38);
    }
    temp_r31->rotate.y = it_804DD3E4;
    if (!(temp_r31->flags & 0x02000000)) {
        temp_cr0_eq = temp_r31 == NULL;
        if (temp_cr0_eq == 0) {
            if (temp_cr0_eq != 0) {
                //__assert(&it_804D5600, 0x234, &it_804D5608);
            }
            temp_r4 = temp_r31->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r31);
            }
        }
    }
}

bool it_802CE588(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    if (it_80272C6C(gobj) == false) {
        return true;
    }
    return false;
}

void it_802CE5DC(Item_GObj* arg0)
{
    Item* temp_r31;

    temp_r31 = arg0->user_data;
    it_8027A344(arg0);
    temp_r31->pos.x += temp_r31->xDD4_itemVar.pokemon.timer;
    temp_r31->pos.y += temp_r31->xDD4_itemVar.pokemon.x64;
    temp_r31->pos.z += temp_r31->xDD4_itemVar.PKThunderVars.xE38.z;
}

bool it_802CE638(Item_GObj* gobj)
{
    return false;
}

void it_802CE640(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;

    it_802762BC(ip);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802CE6A4(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802CE6C8(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool it_802CE6E8(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802CDC80);
}

ItemStateTable it_803F7CF8[] = {
    { 0, it_802CDD24, it_802CDD78, it_802CDDD0 },
    { 1, it_802CE0C4, it_802CE308, it_802CE3A8 },
    { 2, it_802CE588, it_802CE5DC, it_802CE638 },
    { -1, it_802CE6A4, it_802CE6C8, it_802CE6E8 },
};
