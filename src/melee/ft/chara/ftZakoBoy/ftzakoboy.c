#include <ftzakoboy.h>


void ftZakoBoy_OnDeath(HSD_GObj* gobj)
{
    func_80074A4C(gobj, 0, 0);
}

void ftZakoBoy_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 0);
}

void ftZakoBoy_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftZakoBoy_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftZakoBoy_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 0, 0);
}

void ftZakoBoy_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PUSH_ATTRS(fp, ftZakoboyAttributes);


}

void ftZakoBoy_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftZakoboyAttributes);
}
