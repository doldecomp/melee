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

void ftFox_OnItemInvisible(HSD_GObj* gobj) 
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFox_OnItemVisible(HSD_GObj* gobj) 
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFox_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
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