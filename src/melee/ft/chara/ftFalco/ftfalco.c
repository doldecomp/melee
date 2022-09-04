#include <melee/ft/chara/ftFalco/ftfalco.h>

#include <melee/it/itkind.h>

void ftFalco_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->sa.fox.x222C_blasterGObj = 0;
    func_80074A4C(gobj, 0, 0);
}

void ftFalco_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
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
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    s32* sa2;
    void** items = ftdata->x48_items;
    int unused;

    fp->x2224_flag.bits.b7 = 1;
    ftFox_OnLoadForFalco(fp);

    sa2 = fp->x2D4_specialAttributes;
    func_8026B3F8(items[0], sa2[7]);
    func_8026B3F8(items[1], sa2[8]);
    func_8026B3F8(items[3], 0x39);
}

void ftFalco_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftFox_LoadSpecialAttrs(gobj);
}

void ftFalco_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFalco_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}
