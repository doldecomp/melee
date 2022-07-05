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

void func_8014ED38(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014ED80(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_8014EDC8(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void ftGanon_OnLoad(HSD_GObj* gobj)
{
    ftCFalcon_OnLoadForGanon(gobj->user_data);
}

void func_8014EE40(HSD_GObj* gobj)
{
    func_800E2B40(gobj);
}

void func_8014EE60(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void func_8014EEAC(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}
