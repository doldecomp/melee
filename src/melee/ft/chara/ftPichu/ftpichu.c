#include "ftpichu.h"

void ftPichu_OnLoad(HSD_GObj* gobj)
{
    ftPichuAttributes* attrs;
    u32 unused[2];

    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    void** items = ftdata->x48_items;
    ft->x2224_flag.bits.b7 = 1;
    ftPikachu_OnLoadForPichu(ft);
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
    temp_r0 = ft->x619_costume_id;

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

void ftPichu_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 0);
}

void ftPichu_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftPichu_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftPichu_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 0, 0);
}

void func_8014A1A8(HSD_GObj* gobj)
{
    ftPikachu_ScaleYAttributesArray_80124704(gobj);
}

void ftPichu_OnKnockbackEnter(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftPichu_OnKnockbackExit(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}
