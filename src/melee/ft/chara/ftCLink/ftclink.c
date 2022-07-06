#include "ftclink.h"

#include <melee/it/itkind.h>

void ftCLink_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    func_80074A4C(gobj, 2, 0);
    ft->sa.clink.x222C = 0;
    ft->sa.clink.x2234 = 0;
    ft->sa.clink.x2238 = 0;
    ft->sa.clink.x223C = 0;
    ft->sa.clink.x2240 = 0;
    ft->sa.clink.x2238 = 0;
    ft->sa.clink.x2244 = 0;
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
    ftLink_OnLoadForCLink(ft);
    attrs = ft->x2D4_specialAttributes;
    func_8026B3F8(items[0], attrs->x48);
    func_8026B3F8(items[1], attrs->x2C);
    func_8026B3F8(items[2], attrs->xBC);
    func_8026B3F8(items[3], attrs->xC);
    func_8026B3F8(items[4], attrs->x10);
    func_8026B3F8(items[5], It_Kind_CLink_Milk);
    func_800753D4(ft, *lbl_804D6540[ft->x4_fighterKind], items[6]);
}

void ftCLink_OnItemPickupExt(HSD_GObj* gobj, s32 arg1)
{
    int unused;
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 1) {
        func_80074A4C(gobj, 1, 1);
    }
    func_80074A4C(gobj, 2, 1);
    ftCLink_OnItemPickup(gobj, arg1);
}

void ftCLink_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftCLink_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftCLink_OnItemDropExt(HSD_GObj* gobj, s32 arg1)
{
    int unused;
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 1) {
        func_80074A4C(gobj, 1, 0);
    }
    func_80074A4C(gobj, 2, 0);
    ftCLink_OnItemDrop(gobj, arg1);
}

void ftCLink_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftCLink_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter* link = getFighter(gobj);
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void func_8014906C(HSD_GObj* gobj)
{
    func_800EB250(gobj);
}

void ftCLink_OnKnockbackEnter(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftCLink_OnKnockbackExit(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_80149114(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    CLinkAttributes* temp_r4 = (void*) ft->x10C_ftData->ext_attr;
    f32 ftmp = func_80092ED8(ft->x19A4, temp_r4, temp_r4->xD8);
    ft->xEC_ground_vel = ftmp * p_ftCommonData->x294;
    if (ft->x19AC < 0.0f) {
        ftmp = ft->xEC_ground_vel;
    } else {
        ftmp = -ft->xEC_ground_vel;
    }
    ft->xEC_ground_vel = ftmp;
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
    temp_r0 = ft->x10_action_state_index;
    if (temp_r0 != 0x156 && temp_r0 != 0x157) {
        return TRUE;
    }
    if (ft->sa.clink.x2244 == 0) {
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
    if (ft != NULL && ft->sa.clink.x2244 != 0) {
        ft->sa.clink.x2244 = 0;
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
            return ft->x2204_ftcmd_var1;
        }
    }
    return 0;
}

void func_80149318(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_800DEAE8(gobj, 0x156, 0x157);
    ft->x2204_ftcmd_var1 = 0;
}
