#include <ftmewtwo.h>
#include <melee/it/itkind.h>

void ftMewtwo_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.mewtwo.x222C = 0;
    ft->sa.mewtwo.x2230 = 0;
    ft->sa.mewtwo.x2234_shadowBallCharge = 0;
    ft->sa.mewtwo.x2238 = 0;
    ft->sa.mewtwo.x223C = 0;
}

void ftMewtwo_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftMewtwoAttributes* attr = fighter->x10C_ftData->ext_attr;
    void** item_list = fighter->x10C_ftData->x48_items;
    PUSH_ATTRS(fighter, ftMewtwoAttributes);

    {
        fighter->x5E8_fighterBones[1].flags.bits.b4 = 1;
        fighter->x2221_flag.bits.b2 = 1;
    }
    func_8026B3F8(item_list[0], It_Kind_Mewtwo_Disable);
    func_8026B3F8(item_list[1], It_Kind_Mewtwo_ShadowBall);
}

void ftMewTwo_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {}

void ftMewTwo_80144EE4(HSD_GObj* fighterObj) {
    func_801461A8(fighterObj);
    func_80146E30(fighterObj);
}

void ftMewTwo_80144F18(HSD_GObj* fighterObj) {
    func_801461A8(fighterObj);
    func_80146ED0(fighterObj);
}

void ftMewTwo_OnItemDrop(HSD_GObj* fighterObj, BOOL bool) {}

void ftMewTwo_OnItemInvisible(HSD_GObj* fighterObj) {}

void ftMewTwo_OnItemVisible(HSD_GObj* fighterObj) {}

void ftMewTwo_80144F58(HSD_GObj* fighterObj) {

    Fighter* fighter = getFighter(fighterObj);
    ftMewtwoAttributes* attr = fighter->x2D4_specialAttributes;
    f32 attr_value = attr->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
    if (fighter->sa.mewtwo.x2234_shadowBallCharge == attr_value) {
        func_800BFFD0(fighter, 0x5C, 0);
    }
}

void ftMewTwo_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftMewtwoAttributes);
    if (ft->x34_scale.y != 1.0f) {
        sA2->x80_MEWTWO_DISABLE_OFFSET_X *= ft->x34_scale.y;
        sA2->x84_MEWTWO_DISABLE_OFFSET_Y *= ft->x34_scale.y;
    }
}

void ftMewTwo_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 2);
}

void ftMewTwo_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 2);
}
