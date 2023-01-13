#include <melee/ft/chara/ftGanon/ftganon.h>

#include <melee/ft/chara/ftCaptain/ftCaptain.h>
#include <melee/ft/ftparts.h>

void ftGanon_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, -1);
    fp->sa.captain.x2230_isSpecialSGFX = false;
    fp->sa.captain.x222C_isSpecialSStartGFX = false;
}

void ftGanon_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, true, true);
}

void ftGanon_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGanon_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGanon_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGanon_OnLoad(HSD_GObj* gobj)
{
    ftCaptain_OnLoadForGanon(gobj->user_data);
}

void ftGanon_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftCFalcon_LoadSpecialAttrs(gobj);
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
