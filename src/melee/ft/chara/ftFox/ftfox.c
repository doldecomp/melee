#include "ftfox.h"

BOOL func_800E5534(HSD_GObj* gobj)
{
    Fighter* ft = (Fighter*)gobj->user_data;
    
    return ft->sa.fox.x222C ? TRUE : FALSE;
}

void ftFox_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = (Fighter*)gobj->user_data;
    
    ft->sa.fox.x222C = 0;
    func_80074A4C(gobj, 0, 0);
}

void func_800E5588(HSD_GObj* gobj)
{
    func_800E5EBC(gobj);
}

void ftFox_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void func_800E5688(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E56D0(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_800E5718(HSD_GObj* gobj, s32 arg1) 
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void ftFox_OnLoadForFalco(Fighter* ft) 
{
    PUSH_ATTRS(ft, ftFoxAttributes);
}

void ftFox_OnLoad(HSD_GObj* gobj) {

    Fighter* ft = gobj->user_data;
    void** item_list = ft->x10C_ftData->x48_items;

    ft->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(ft, ftFoxAttributes);
    
    {
        ftFoxAttributes *fox_attr = ft->x2D4_specialAttributes;
        func_8026B3F8(item_list[0], fox_attr->x1C);
        func_8026B3F8(item_list[1], fox_attr->x20);
        func_8026B3F8(item_list[2], 0x38U);
    }
}