#include <melee/ft/chara/ftIceClimber/fticeclimber1.h>

#include <melee/ft/chara/ftIceClimber/fticeclimber.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftparts.h>
#include <melee/it/code_8027CF30.h>
#include <sysdolphin/baselib/gobj.h>

void ftIceClimber_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftIceClimber_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftIceClimber_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftIceClimber_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftIceClimber_OnLoadForNana(Fighter* fp)
{
    PUSH_ATTRS(fp, ftIceClimberAttributes);
}

void ftIceClimber_OnLoad(HSD_GObj* fighter_gobj)
{
    s32 unused;
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;
    fp->x2222_flag.bits.b5 = 1;

    PUSH_ATTRS(fp, ftIceClimberAttributes);

    {
        ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
        fp->x40 = attr->x0;
        func_8026B3F8(item_list[0], 0x6AU);
        func_8026B3F8(item_list[1], 0x6BU);
        func_8026B3F8(item_list[2], 0x71U);
    }
}

void ftIceClimber_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
    func_80074A4C(fighter_gobj, 0U, 0);
    func_80074A4C(fighter_gobj, 1U, 0);
    fp->sa.nana.x2234 = 0;
    fp->sa.nana.x222C = 0;
    fp->sa.nana.x2230.bits.b0 = 0;
    fp->sa.nana.x2238 = 0;
    fp->sa.nana.x224C = 0;
    fp->sa.nana.x2250 = 0.0f;
}

void ftIceClimber_8011F060(HSD_GObj* fighter_gobj)
{
    func_8011F190(fighter_gobj);
    func_80122898(fighter_gobj);
    func_80121164(fighter_gobj);
    func_8011F68C(fighter_gobj);
}

void ftIceClimber_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftIceClimberAttributes);
}

void ftIceClimber_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, true);
}

void ftIceClimber_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, true);
}

void func_8011F16C(HSD_GObj* fighter_gobj, uint i)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);

    if (i != fp->sa.nana.x222C)
        return;

    fp->sa.nana.x222C = 0;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

void func_8011F190(HSD_GObj* fighter_gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);

    if (fp->sa.nana.x222C == 0)
        return;

    func_802C17DC(fp->sa.nana.x222C);
    func_8011F16C(fighter_gobj, fp->sa.nana.x222C);
}

extern f32 const lbl_804D9838;
extern f32 const lbl_804D983C;

void ftIceClimber_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);
    fp->x2210_ThrowFlags.flags = FLAGS_ZERO;
    fp->x2200_ftcmd_var0 = 0;
    fp->sa.nana.x222C = 0;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 341, 0, NULL, lbl_804D9838,
                                       lbl_804D983C, lbl_804D9838);

    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &lbl_8011F500;
}

extern f32 const lbl_804D9840;

void ftIceClimber_SpecialAirN_StartAction(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);
    ftIceClimberAttributes* icattr = fp->x2D4_specialAttributes;

    fp->x2210_ThrowFlags.flags = FLAGS_ZERO;
    fp->x2200_ftcmd_var0 = 0;
    fp->sa.nana.x222C = 0;

    if ((s32) fp->sa.nana.x224C == false) {
        fp->x80_self_vel.y = icattr->x4;
        fp->sa.nana.x224C = true;
        fp->sa.nana.x2250 = lbl_804D9838;
    } else {
        fp->sa.nana.x2250 = lbl_804D9840;
    }

    Fighter_ActionStateChange_800693AC(fighter_gobj, 342, 0, NULL, lbl_804D9838,
                                       lbl_804D983C, lbl_804D9838);

    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &lbl_8011F500;
}

void lbl_8011F318(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void lbl_8011F354(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void lbl_8011F390(HSD_GObj* arg0) {}

void lbl_8011F394(HSD_GObj* arg0) {}

void lbl_8011F398(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}
