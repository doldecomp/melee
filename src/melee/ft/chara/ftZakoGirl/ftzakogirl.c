#include <melee/ft/chara/ftZakoGirl/ftzakogirl.h>

void ftZakoGirl_OnDeath(HSD_GObj* gobj)
{
    func_80074A4C(gobj, 0, 0);
}

void ftZakoGirl_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, s32);
}

void ftZakoGirl_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 0);
}

void ftZakoGirl_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftZakoGirl_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftZakoGirl_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftZakoGirl_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, s32);
}
