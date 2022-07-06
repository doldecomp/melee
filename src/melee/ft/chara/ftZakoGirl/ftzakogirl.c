#include "ftzakogirl.h"

void ftZakoGirl_OnDeath(HSD_GObj* gobj)
{
    func_80074A4C(gobj, 0, 0);
}

void ftZakoGirl_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    PUSH_ATTRS(ft, s32);
}

void ftZakoGirl_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 0);
}

void ftZakoGirl_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftZakoGirl_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftZakoGirl_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 0, 0);
}

void func_8014F624(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    *(u32*) ft->x2D4_specialAttributes = *(u32*)ft->x10C_ftData->ext_attr;
}
