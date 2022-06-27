#include "ftNess.h"

void ftNess_OnDeath(HSD_GObj* gobj, s32 arg1)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.ness.x2240_flashGObj = NULL;
    ft->sa.ness.x2244_pkThunderGObj = NULL;
    ft->sa.ness.x2248_baseballBatGObj = NULL;
    ft->sa.ness.x222C_yoyoGObj = 0;
    ft->sa.ness.x224C_thunderGFX = FALSE;
}

void ftNess_OnLoad(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;
    void** item_list = ft->x10C_ftData->x48_items;

    PUSH_ATTRS(ft, ftNessAttributes);

    func_8026B3F8(item_list[0], It_Kind_Ness_PKFire);
    func_8026B3F8(item_list[1], It_Kind_Ness_PKFire_Flame);
    func_8026B3F8(item_list[2], It_Kind_Ness_PKFlush);
    func_8026B3F8(item_list[8], It_Kind_Ness_PKFlush_Explode);
    func_8026B3F8(item_list[3], It_Kind_Ness_PKThunder);
    func_8026B3F8(item_list[4], It_Kind_Ness_PKThunder1);
    func_8026B3F8(item_list[5], It_Kind_Ness_PKThunder2);
    func_8026B3F8(item_list[6], It_Kind_Ness_PKThunder3);
    func_8026B3F8(item_list[7], It_Kind_Ness_PKThunder4);
    func_8026B3F8(item_list[9], It_Kind_Ness_Bat);
    func_8026B3F8(item_list[10], It_Kind_Ness_Yoyo);
}

void ftNess_OnDamage(HSD_GObj* gobj)
{
    ftNess_YoyoItemDespawn(gobj);
    ftNess_ItemPKFlushSetNULL(gobj);
    func_80117E60(gobj);
    ftNess_ItemNessBatRemove(gobj);
}

void func_8011493C(HSD_GObj* gobj)
{
    func_8011B0F8(gobj);
}

f32 ftNess_GetAbsorbHeal(Fighter* ft)
{
    return ((ftNessAttributes*)ft->x2D4_specialAttributes)->x94_PSI_MAGNET_HEAL_MUL;
}

void func_80114968(HSD_GObj* gobj, s32 arg1)
{
    s32 result, switched_res, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) 
        {
            case 1:
                func_80070FB4(gobj, 1, 1);
                break;
            case 2:
                func_80070FB4(gobj, 1, 0);
                break;
            case 3:
                func_80070FB4(gobj, 1, 2);
                break;
            case 4:
                func_80070FB4(gobj, 1, 3);
                break;
        }

        if (arg1 != 0) 
        {
            func_80070C48(gobj, 1);
        }
    }
}

void func_80114A48(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == FALSE) 
    {
        func_80070CC4(gobj, 1);
    }
}

void func_80114A90(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == FALSE) 
    {
        func_80070C48(gobj, 1);
    }
}

void func_80114AD8(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80114B2C(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;
    
    ftNessAttributes* sA2 = (ftNessAttributes*)ft->x2D4_specialAttributes;
    ftNessAttributes* ext_attr = (ftNessAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
}

void func_80114B6C(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_80114BB0(HSD_GObj* fighter_gobj) // Make DObjs visible? //
{
    func_800704F0(fighter_gobj, 1, 0.0f);
    func_800704F0(fighter_gobj, 0, 0.0f);
}
