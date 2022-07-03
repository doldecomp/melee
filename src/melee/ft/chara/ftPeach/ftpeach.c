#include "ftpeach.h"

#include <melee/it/id.h>

void ftPeach_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft;

    ft = gobj->user_data;
    ft->sa.peach.x222C = 1;
    ft->sa.peach.x2234 = -1;
    ft->sa.peach.x2240 = 0;
    ft->sa.peach.x223C = 0;
    ft->sa.peach.x2238 = 0;
    ft->sa.peach.x2244 = 0;
    ft->sa.peach.x2248 = 0;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 2, 0);
    func_80074A4C(gobj, 3, -1);
    func_80074A4C(gobj, 4, 0);

    switch (ft->x619_costume_id)
    {
        case 1:
            func_80074A4C(gobj, 1, -1);
            func_80074A4C(gobj, 5, 0);
            func_80074A4C(gobj, 6, -1);
            break;

        default:
            func_80074A4C(gobj, 1, 0);
            func_80074A4C(gobj, 5, -1);
            func_80074A4C(gobj, 6, 0);
            break;
    }
}

void ftPeach_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    ftPeachAttributes* extAtrrs = ft->x10C_ftData->ext_attr;
    void** items = ft->x10C_ftData->x48_items;

    extAtrrs->unk0 = func_8001E8F8(func_80085E50(ft, 18));
    extAtrrs->unk4 = func_8001E8F8(func_80085E50(ft, 19));

    PUSH_ATTRS(ft, ftPeachAttributes);
    
    func_8026B3F8(items[0], It_Kind_PeachUnk);
    func_8026B3F8(items[1], It_Kind_PeachTurnip);
    func_8026B3F8(items[2], It_Kind_PeachParasol);
    func_8026B3F8(items[3], It_Kind_PeachToad);
    func_8026B3F8(items[4], It_Kind_PeachToadSpore);
}

void ftPeach_8011B704(HSD_GObj* fighterObj) {
    func_8011D598(fighterObj);
    func_8011E2E8(fighterObj);
    func_8011CFA0(fighterObj);
}

void ftPeach_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
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