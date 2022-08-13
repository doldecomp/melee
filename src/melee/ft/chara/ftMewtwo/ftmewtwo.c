#include <ftmewtwo.h>
#include <melee/it/itkind.h>

void ftMewtwo_OnDeath(HSD_GObj* gobj) {
    Fighter* fp = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    fp->sa.mewtwo.x222C_disableGObj = NULL;
    fp->sa.mewtwo.x2230 = 0;
    fp->sa.mewtwo.x2234_shadowBallCharge = 0;
    fp->sa.mewtwo.x2238_shadowBallGObj = NULL;
    fp->sa.mewtwo.x223C_isConfusionBoost = FALSE;
}

void ftMewtwo_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
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

void ftMewTwo_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {}

void ftMewtwo_OnDeath2(HSD_GObj* fighterObj) {
    ftMewtwo_SpecialLw_RemoveDisable(fighterObj);
    func_80146E30(fighterObj);
}

void ftMewtwo_OnTakeDamage(HSD_GObj* fighterObj) {
    ftMewtwo_SpecialLw_RemoveDisable(fighterObj);
    func_80146ED0(fighterObj);
}

void ftMewTwo_OnItemDrop(HSD_GObj* fighterObj, BOOL bool) {}

void ftMewTwo_OnItemInvisible(HSD_GObj* fighterObj) {}

void ftMewTwo_OnItemVisible(HSD_GObj* fighterObj) {}

void ftMewTwo_80144F58(HSD_GObj* fighterObj) {

    Fighter* fp = getFighter(fighterObj);
    ftMewtwoAttributes* attr = fp->x2D4_specialAttributes;
    f32 attr_value = attr->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
    if (fp->sa.mewtwo.x2234_shadowBallCharge == attr_value) {
        func_800BFFD0(fp, 0x5C, 0);
    }
}

void ftMewTwo_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftMewtwoAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x80_MEWTWO_DISABLE_OFFSET_X *= fp->x34_scale.y;
        sA2->x84_MEWTWO_DISABLE_OFFSET_Y *= fp->x34_scale.y;
    }
}

void ftMewTwo_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 2);
}

void ftMewTwo_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 2);
}
