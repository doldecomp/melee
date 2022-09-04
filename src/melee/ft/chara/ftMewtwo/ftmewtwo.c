#include <melee/ft/chara/ftMewtwo/ftmewtwo.h>
#include <melee/it/itkind.h>

void ftMewtwo_OnDeath(HSD_GObj* gobj) {
    Fighter* fp = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    fp->sa.mewtwo.x222C_disableGObj = NULL;
    fp->sa.mewtwo.x2230_shadowHeldGObj = NULL;
    fp->sa.mewtwo.x2234_shadowBallCharge = 0;
    fp->sa.mewtwo.x2238_shadowBallGObj = NULL;
    fp->sa.mewtwo.x223C_isConfusionBoost = FALSE;
}

void ftMewtwo_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftMewtwoAttributes* attr = fp->x10C_ftData->ext_attr;
    void** item_list = fp->x10C_ftData->x48_items;
    PUSH_ATTRS(fp, ftMewtwoAttributes);

    {
        fp->x5E8_fighterBones[1].flags.bits.b4 = 1;
        fp->x2221_flag.bits.b2 = 1;
    }
    func_8026B3F8(item_list[0], It_Kind_Mewtwo_Disable);
    func_8026B3F8(item_list[1], It_Kind_Mewtwo_ShadowBall);
}

void ftMewTwo_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {}

void ftMewtwo_OnDeath2(HSD_GObj* fighter_gobj) {
    ftMewtwo_SpecialLw_RemoveDisable(fighter_gobj);
    ftMewtwo_SpecialN_OnTakeDamage(fighter_gobj);
}

void ftMewtwo_OnTakeDamage(HSD_GObj* fighter_gobj) {
    ftMewtwo_SpecialLw_RemoveDisable(fighter_gobj);
    ftMewtwo_SpecialN_OnDeath(fighter_gobj);
}

void ftMewTwo_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool) {}

void ftMewTwo_OnItemInvisible(HSD_GObj* fighter_gobj) {}

void ftMewTwo_OnItemVisible(HSD_GObj* fighter_gobj) {}

void ftMewTwo_80144F58(HSD_GObj* fighter_gobj) {

    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* attr = fp->x2D4_specialAttributes;
    f32 attr_value = attr->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
    if (fp->sa.mewtwo.x2234_shadowBallCharge == attr_value) {
        func_800BFFD0(fp, 0x5C, 0);
    }
}

void ftMewTwo_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftMewtwoAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x80_MEWTWO_DISABLE_OFFSET_X *= fp->x34_scale.y;
        sA2->x84_MEWTWO_DISABLE_OFFSET_Y *= fp->x34_scale.y;
    }
}

void ftMewTwo_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 2);
}

void ftMewTwo_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 2);
}
