#include <melee/ft/chara/ftEmblem/ftemblem.h>

void ftRoy_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    func_80074A4C(gobj, 2, -1);
    fp->sa.mars.x222C = 0;
}

void ftRoy_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 1);
}

void ftRoy_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftRoy_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftRoy_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
}

void ftRoy_OnLoad(HSD_GObj* gobj)
{
    ftMars_OnLoadForRoy(gobj->user_data);
}

void ftRoy_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMars_LoadSpecialAttrs(gobj);
}

void ftRoy_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftRoy_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}
