#include "ftdrmario.h"

void ftDrMario_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x2234 = 0;
    ft->x2238 = 0;
    ft->x223C = 0;
    ft->x2240 = 0;
}

void ftDrMario_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft;
    void** items;
    ftDrMarioAttributes* sa;
    int unused[2];

    ft = gobj->user_data;
    items = ft->x10C_ftData->x48_items;
    func_800E0920(ft);
    sa = ft->x2D4_specialAttributes;
    func_8026B3F8(items[1], 0x31);
    func_8026B3F8(items[3], sa->x14);
}

void func_80149540(HSD_GObj* gobj)
{
    func_801497CC(gobj);
}

void func_80149560(HSD_GObj* gobj, s32 arg1)
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

void func_80149640(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80149688(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_801496D0(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80149724(HSD_GObj* gobj)
{
    func_800E0BE4(gobj);
}

void func_80149744(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_80149788(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_801497CC(HSD_GObj* gobj)
{
    Fighter* ft;
    int unused[2];

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL && ft->x2240 != 0) {
            func_802C0DBC(ft->x2240);
            ft->x2240 = 0;
        }
    }

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL) {
            ft->x21DC = 0;
            ft->x21E4 = 0;
        }
    }
}

BOOL func_80149844(HSD_GObj* gobj)
{
    s32 tmp;
    Fighter* ft;

    if (gobj == NULL) {
        return TRUE;
    }
    ft = gobj->user_data;
    if (ft == NULL) {
        return TRUE;
    }
    tmp = ft->x10;
    if (tmp != 0x155 && tmp != 0x156) {
        return TRUE;
    }
    if (ft->x2240 == 0) {
        return TRUE;
    }
    return FALSE;
}

void func_801498A0(HSD_GObj* gobj)
{
    Fighter* ft;

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL && ft->x2240 != 0) {
            ft->x2240 = 0;
        }
    }
    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL) {
            ft->x21DC = 0;
            ft->x21E4 = 0;
        }
    }
}

u32 func_801498EC(HSD_GObj* gobj)
{
    Fighter* ft;

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL) {
            return ft->x2200_ftcmd_var1;
        }
    }

    return 0;
}

void func_80149910(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    func_800DEAE8(gobj, 0x155, 0x156);
    ft->x2200_ftcmd_var0 = 1;
    ft->x2200_ftcmd_var1 = 0;
}
