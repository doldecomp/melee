#include "ftganon.h"

void ftGanon_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, -1);
    ft->sa.captain.x2230 = 0;
    ft->sa.captain.x222C = 0;
}

void ftGanon_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftGanon_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftGanon_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftGanon_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftGanon_OnLoad(HSD_GObj* gobj)
{
    ftCaptain_OnLoadForGanon(gobj->user_data);
}

void func_8014EE40(HSD_GObj* gobj)
{
    func_800E2B40(gobj);
}

void ftGanon_OnKnockbackEnter(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftGanon_OnKnockbackExit(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}
