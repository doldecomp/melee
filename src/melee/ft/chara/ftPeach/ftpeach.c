#include "ftpeach.h"

#include <melee/it/itkind.h>

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
    
    func_8026B3F8(items[0], It_Kind_Peach_Explode);
    func_8026B3F8(items[1], It_Kind_Peach_Turnip);
    func_8026B3F8(items[2], It_Kind_Peach_Parasol);
    func_8026B3F8(items[3], It_Kind_Peach_Toad);
    func_8026B3F8(items[4], It_Kind_Peach_ToadSpore);
}

void ftPeach_8011B704(HSD_GObj* fighterObj) {
    ftPeach_8011D598(fighterObj);
    ftPeach_8011E2E8(fighterObj);
    ftPeach_8011CFA0(fighterObj);
}

void ftPeach_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftPeach_OnItemInvisible(HSD_GObj* fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftPeach_OnItemVisible(HSD_GObj* fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftPeach_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}

void ftPeach_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftPeachAttributes);
}

void ftPeach_8011B93C(HSD_GObj* fighterObj) {
    s32 unused[2];
    s32 result = func_80074A74(fighterObj, 2);
    if (result == -1) {
        func_80074A4C(fighterObj, 2, 0);
    } else {
        func_80074A4C(fighterObj, 2, -1);
    }
}

void ftPeach_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}

void ftPeach_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
}

s32 ftPeach_8011BA20(Fighter* fp) {
    s32 result = 1;

    if (!(fp->input.x624_lstick_y >= p_ftCommonData->x70_someLStickYMax) && !(fp->input.x65C_heldInputs & 0xC00))
        result = 0;

    return result;
}
