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

MACRO_ft_OnItemPickup(ftPeach, 1, 1);
