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
    Fighter_OnItemInvisible(gobj, 0);
}

void ftRoy_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftRoy_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
}

void ftRoy_OnLoad(HSD_GObj* gobj)
{
    ftMars_OnLoadForRoy(gobj->user_data);
}

void func_8014F148(HSD_GObj* gobj)
{
    func_801364E8(gobj);
}

void ftRoy_OnKnockbackEnter(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftRoy_OnKnockbackExit(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}
