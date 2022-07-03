#include "ftzakoboy.h"


void ftZakoBoy_OnDeath(HSD_GObj* gobj)
{
    func_80074A4C(gobj, 0, 0);
}

MACRO_ft_OnItemPickup(ftZakoBoy, 0, 0);

void func_8014F2F8(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 0);
    }
}

void func_8014F340(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 0);
    }
}

void func_8014F388(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 0, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 0);
    }
}

void ftZakoBoy_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    PUSH_ATTRS(ft, ftZakoboyAttributes);


}

void func_8014F3FC(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    *(u32*) ft->x2D4_specialAttributes = *(u32*)ft->x10C_ftData->ext_attr;
}
