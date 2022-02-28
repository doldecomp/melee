#include "ftness.h"

void ftNess_OnDeath(HSD_GObj* gobj, s32 arg1)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x2240 = 0;
    ft->x2244 = 0;
    ft->x2248 = 0;
    ft->x222C = 0;
    ft->x224C = 0;
}

void ftNess_OnLoad(HSD_GObj* gobj) {
    ftNessAttributes *sA2, *sA, *ext_attr;

    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    void** items = ftdata->x48_items;
    sA2 = (ftNessAttributes*)ft->x2D8_specialAttributes2;
    ext_attr = (ftNessAttributes*)ft->x10C_ftData->ext_attr;

    *sA2 = *ext_attr;

    (ftNessAttributes*)ft->x2D4_specialAttributes = sA2;
    func_8026B3F8(items[0], 0x42);
    func_8026B3F8(items[1], 0x43);
    func_8026B3F8(items[2], 0x44);
    func_8026B3F8(items[8], 0x4E);
    func_8026B3F8(items[3], 0x45);
    func_8026B3F8(items[4], 0x46);
    func_8026B3F8(items[5], 0x47);
    func_8026B3F8(items[6], 0x48);
    func_8026B3F8(items[7], 0x49);
    func_8026B3F8(items[9], 0x65);
    func_8026B3F8(items[10], 0x66);
}

void func_801148F8(HSD_GObj* gobj)
{
    func_80115AF8(gobj);
    func_80116F38(gobj);
    func_80117E60(gobj);
    func_80114CF4(gobj);
}

void func_8011493C(HSD_GObj* gobj)
{
    func_8011B0F8(gobj);
}

f32 func_8011495C(Fighter* ft)
{
    return ((ftNessAttributes*)ft->x2D4_specialAttributes)->unk94;
}

void func_80114968(HSD_GObj* gobj, s32 arg1)
{
    s32 result, switched_res, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) {
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

        if (arg1 != 0) {
            func_80070C48(gobj, 1);
        }
    }
}

void func_80114A48(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80114A90(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
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
