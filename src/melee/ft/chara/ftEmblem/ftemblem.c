#include "ftemblem.h"

void ftRoy_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    func_80074A4C(gobj, 2, -1);
    ft->sa.mars.x222C = 0;
}

void ftRoy_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 1);
}

void ftRoy_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 0);
    }
}

void ftRoy_OnItemVisible(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 0);
    }
}

void ftRoy_OnItemRelease(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 0, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void ftRoy_OnLoad(HSD_GObj* gobj)
{
    ftMars_OnLoadForRoy(gobj->user_data);
}

void func_8014F148(HSD_GObj* gobj)
{
    func_801364E8(gobj);
}

void func_8014F168(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_8014F1AC(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}
