#include "ftfox.h"

BOOL func_800E5534(HSD_GObj* gobj)
{
    Fighter* ft = (Fighter*)gobj->user_data;
    
    return ft->x222C ? TRUE : FALSE;
}

void ftFox_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = (Fighter*)gobj->user_data;
    
    ft->x222C = 0;
    func_80074A4C(gobj, 0, 0);
}

void func_800E5588(HSD_GObj* gobj)
{
    func_800E5EBC(gobj);
}

void func_800E55A8(HSD_GObj* gobj, s32 arg1)
{
    s32 switched_res, result, unused;

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

void func_800E576C(Fighter* ft) 
{
    ftFoxAttributes* sA2 = (ftFoxAttributes*)ft->x2D8_specialAttributes2;
    ftFoxAttributes* ext_attr = (ftFoxAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    ft->x2D4_specialAttributes = sA2;
}
