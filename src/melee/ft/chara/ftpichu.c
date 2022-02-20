#include "ftpichu.h"

void ftPichu_OnLoad(HSD_GObj* gobj)
{
    ftPichuAttributes* attrs;
    u32 unused[2];

    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    void** items = ftdata->x48_items;
    ft->x2224_flag.bits.b7 = 1;
    func_801243AC(ft);
    attrs = ft->x2D4_specialAttributes;
    func_8026B3F8(items[0], attrs->xDC);
    func_8026B3F8(items[1], attrs->x14);
    func_8026B3F8(items[2], attrs->x18);
}

void ftPichu_OnDeath(HSD_GObj* gobj)
{
    u8 temp_r0;
    Fighter* ft = gobj->user_data;

    func_80074A4C(gobj, 0, 0);
    temp_r0 = ft->x619_flag;

    switch (temp_r0) {
        case 0:
            func_80074A4C(gobj, 1, -1);
            func_80074A4C(gobj, 2, -1);
            func_80074A4C(gobj, 3, -1);
            break;
        case 1:
            func_80074A4C(gobj, 1, 0);
            func_80074A4C(gobj, 2, -1);
            func_80074A4C(gobj, 3, -1);
            break;
        case 2:
            func_80074A4C(gobj, 1, -1);
            func_80074A4C(gobj, 2, 0);
            func_80074A4C(gobj, 3, -1);
            break;
        case 3:
            func_80074A4C(gobj, 1, -1);
            func_80074A4C(gobj, 2, -1);
            func_80074A4C(gobj, 3, 0);
            break;
    }
}

void func_80149FE4(HSD_GObj* gobj, s32 arg1)
{
    s32 result, switched_result, unused;
    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);
    if (result == 0) {
        switched_result = func_8026B320(ft->x1974_heldItem);
        switch (switched_result) {
            case 1:
                func_80070FB4(gobj, 0, 1);
                break;
            case 2:
                func_80070FB4(gobj, 0, 0);
                break;
            case 3:
                func_80070FB4(gobj, 0, 2);
                break;
            case 4:
                func_80070FB4(gobj, 0, 3);
                break;
        }
        if (arg1 != 0) {
            func_80070C48(gobj, 0);
        }
    }
}

void func_8014A0C4(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 0);
    }
}

void func_8014A10C(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 0);
    }
}

void func_8014A154(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 0, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 0);
    }
}

void func_8014A1A8(HSD_GObj* gobj)
{
    func_80124704(gobj);
}

void func_8014A1C8(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_8014A20C(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}
