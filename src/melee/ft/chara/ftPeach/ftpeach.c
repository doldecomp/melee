#include <melee/ft/chara/ftPeach/ftpeach.h>

#include <melee/it/itkind.h>

void ftPeach_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    fp->sa.peach.x222C = 1;
    fp->sa.peach.x2234 = -1;
    fp->sa.peach.x2240 = 0;
    fp->sa.peach.x223C = 0;
    fp->sa.peach.x2238 = 0;
    fp->sa.peach.x2244 = 0;
    fp->sa.peach.x2248 = 0;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 2, 0);
    func_80074A4C(gobj, 3, -1);
    func_80074A4C(gobj, 4, 0);

    switch (fp->x619_costume_id)
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
    Fighter* fp = gobj->user_data;
    ftPeachAttributes* extAtrrs = fp->x10C_ftData->ext_attr;
    void** items = fp->x10C_ftData->x48_items;

    extAtrrs->unk0 = func_8001E8F8(func_80085E50(fp, 18));
    extAtrrs->unk4 = func_8001E8F8(func_80085E50(fp, 19));

    PUSH_ATTRS(fp, ftPeachAttributes);
    
    func_8026B3F8(items[0], It_Kind_Peach_Explode);
    func_8026B3F8(items[1], It_Kind_Peach_Turnip);
    func_8026B3F8(items[2], It_Kind_Peach_Parasol);
    func_8026B3F8(items[3], It_Kind_Peach_Toad);
    func_8026B3F8(items[4], It_Kind_Peach_ToadSpore);
}

void ftPeach_8011B704(HSD_GObj* fighter_gobj) {
    ftPeach_8011D598(fighter_gobj);
    ftPeach_8011E2E8(fighter_gobj);
    ftPeach_8011CFA0(fighter_gobj);
}

void ftPeach_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftPeach_OnItemInvisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftPeach_OnItemVisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftPeach_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 1, 1);
}

void ftPeach_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftPeachAttributes);
}

void ftPeach_8011B93C(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    s32 result = func_80074A74(fighter_gobj, 2);
    if (result == -1) {
        func_80074A4C(fighter_gobj, 2, 0);
    } else {
        func_80074A4C(fighter_gobj, 2, -1);
    }
}

void ftPeach_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftPeach_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

s32 ftPeach_8011BA20(Fighter* fp) {
    s32 result = 1;

    if (!(fp->input.x624_lstick_y >= p_ftCommonData->x70_someLStickYMax) && !(fp->input.x65C_heldInputs & 0xC00))
        result = 0;

    return result;
}
