#include "ftclink.h"

#include <melee/it/id.h>

void ftCLink_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    func_80074A4C(gobj, 2, 0);
    ft->x222C = 0;
    ft->x2234 = 0;
    ft->x2238 = 0;
    ft->x223C = 0;
    ft->x2240 = 0;
    ft->x2238 = 0;
    ft->x2244 = 0;
}

void ftCLink_OnLoad(HSD_GObj* gobj)
{
    int unused[2];

    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    CLinkAttributes* attrs = (void*) ftdata->ext_attr;
    void** items = ftdata->x48_items;

    ft->x2224_flag.bits.b7 = 1;
    attrs->x54 = func_8001E8F8(func_80085E50(ft, 0x48));
    func_800EAE04(ft);
    attrs = ft->x2D4_specialAttributes;
    func_8026B3F8(items[0], attrs->x48);
    func_8026B3F8(items[1], attrs->x2C);
    func_8026B3F8(items[2], attrs->xBC);
    func_8026B3F8(items[3], attrs->xC);
    func_8026B3F8(items[4], attrs->x10);
    func_8026B3F8(items[5], It_Kind_ClinkMilk);
    func_800753D4(ft, *lbl_804D6540[ft->x4_fighterKind], items[6]);
}

void func_80148DC0(HSD_GObj* gobj, s32 arg1)
{
    int unused;
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 1) {
        func_80074A4C(gobj, 1, 1);
    }
    func_80074A4C(gobj, 2, 1);
    func_80148F38(gobj, arg1);
}

void func_80148E34(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80148E7C(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_80148EC4(HSD_GObj* gobj, s32 arg1)
{
    int unused;
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 1) {
        func_80074A4C(gobj, 1, 0);
    }
    func_80074A4C(gobj, 2, 0);
    func_80149018(gobj, arg1);
}

void func_80148F38(HSD_GObj* gobj, s32 arg1)
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

void func_80149018(HSD_GObj* gobj, s32 arg1)
{
    int unused;
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014906C(HSD_GObj* gobj)
{
    func_800EB250(gobj);
}

void func_8014908C(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_801490D0(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_80149114(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    CLinkAttributes* temp_r4 = (void*) ft->x10C_ftData->ext_attr;
    f32 ftmp = func_80092ED8(ft->x19A4, temp_r4, temp_r4->xD8);
    ft->xEC_groundVel = ftmp * lbl_804D6554->x294;
    if (ft->x19AC < 0.0f) {
        ftmp = ft->xEC_groundVel;
    } else {
        ftmp = -ft->xEC_groundVel;
    }
    ft->xEC_groundVel = ftmp;
    func_80088148(ft, 0x111DA, 0x7F, 0x40);
}

void func_8014919C(HSD_GObj* gobj)
{
    CLinkAttributes* attrs;
    s32 unused[2];

    Fighter* ft = gobj->user_data;
    if (ft->x5F8 == 0) {
        attrs = (void*) ft->x2D4_specialAttributes;
        func_8007B1B8(gobj, &attrs->xC4, func_80149114);
        ft->x221B_flag.bits.b3 = 1;
        ft->x221B_flag.bits.b4 = 1;
        ft->x221B_flag.bits.b2 = 1;
    }
}

BOOL func_8014920C(HSD_GObj* gobj)
{
    s32 temp_r0;
    Fighter* ft;

    if (gobj == NULL) {
        return TRUE;
    }
    ft = gobj->user_data;
    if (ft == NULL) {
        return TRUE;
    }
    temp_r0 = ft->x10;
    if (temp_r0 != 0x156 && temp_r0 != 0x157) {
        return TRUE;
    }
    if (ft->x2244 == 0) {
        return TRUE;
    }
    return FALSE;
}

void func_80149268(HSD_GObj* gobj)
{
    int unused[2];
    checkFighter2244(gobj);
}

void func_801492C4(HSD_GObj* gobj)
{
    Fighter* ft;

    if (gobj == NULL) {
        return;
    }

    ft = gobj->user_data;
    if (ft != NULL && ft->x2244 != 0) {
        ft->x2244 = 0;
    };

    if (gobj == NULL) {
        return;
    }
}

u32 func_801492F4(HSD_GObj* gobj)
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

void func_80149318(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_800DEAE8(gobj, 0x156, 0x157);
    ft->x2200_ftcmd_var1 = 0;
}
