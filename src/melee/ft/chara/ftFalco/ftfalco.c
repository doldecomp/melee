#include "ftfalco.h"

#include <melee/it/itkind.h>

void ftFalco_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    ft->sa.fox.x222C = 0;
    func_80074A4C(gobj, 0, 0);
}

void ftFalco_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftFalco_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFalco_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFalco_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftFalco_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    s32* sa2;
    void** items = ftdata->x48_items;
    int unused;

    ft->x2224_flag.bits.b7 = 1;
    ftFox_OnLoadForFalco(ft);

    sa2 = ft->x2D4_specialAttributes;
    func_8026B3F8(items[0], sa2[7]);
    func_8026B3F8(items[1], sa2[8]);
    func_8026B3F8(items[3], 0x39);
}

void func_80149D3C(HSD_GObj* gobj)
{
    func_800E5858(gobj);
}

void ftFalco_OnKnockbackEnter(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFalco_OnKnockbackExit(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}
