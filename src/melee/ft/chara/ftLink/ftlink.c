#include <melee/ft/chara/ftLink/ftlink.h>

// extern float lbl_804D92E0; // 0.0f

s32 func_800EAD64(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (fp->sa.link.x2234) {
        return 1;
    }
    return 0;
}

void ftLink_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    func_80074A4C(fighter_gobj, 0, 0);
    func_80074A4C(fighter_gobj, 1, 0);
    func_80074A4C(fighter_gobj, 2, 0);
    fp->sa.link.x222C = 0;
    fp->sa.link.x2234 = 0;
    fp->sa.link.x2238 = 0;
    fp->sa.link.x223C = 0;
    fp->sa.link.x2240 = 0;
    fp->sa.link.x2238 = 0;
    fp->sa.link.x2244 = 0;
}

void ftLink_OnLoadForCLink(Fighter* fp) {
    PUSH_ATTRS(fp, ftLinkAttributes);
}

void ftLink_OnLoad(HSD_GObj* fighter_gobj) {

    Fighter* fp = fighter_gobj->user_data;
    ftLinkAttributes* link_attr = fp->x10C_ftData->ext_attr;
    void** item_list = fp->x10C_ftData->x48_items;
    link_attr->x54 = func_8001E8F8(func_80085E50(fp, 0x48U));
    PUSH_ATTRS(fp, ftLinkAttributes);

    link_attr = fp->x2D4_specialAttributes;
    func_8026B3F8(item_list[0], link_attr->x48);
    func_8026B3F8(item_list[1], link_attr->x2C);
    func_8026B3F8(item_list[2], link_attr->xBC);
    func_8026B3F8(item_list[3], link_attr->xC);
    func_8026B3F8(item_list[4], link_attr->x10);
    func_800753D4(fp, *lbl_804D6540[fp->x4_fighterKind], item_list[6]);
}

void func_800EAF38() {
    func_800EC06C();
}

void func_800EAF58(HSD_GObj* fighter_gobj) {
    func_800EC06C();
    func_800D94D8(fighter_gobj);
    func_800ECD04(fighter_gobj);
    func_800ECD58(fighter_gobj);
    func_80149268(fighter_gobj);
}

void ftLink_OnItemPickupExt(HSD_GObj* fighter_gobj, int arg1) {
    Fighter* fp = getFighter(fighter_gobj);
    if (func_8026B2B4(fp->x1974_heldItem) == 1) {
        func_80074A4C(fighter_gobj, 1, 1);
    }
    func_80074A4C(fighter_gobj, 2, 1);
    ftLink_OnItemPickup(fighter_gobj, arg1);
}

void ftLink_OnItemInvisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftLink_OnItemVisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftLink_OnItemDropExt(HSD_GObj* fighter_gobj, BOOL arg1) {
    Fighter* fp = getFighter(fighter_gobj);
    if (func_8026B2B4(fp->x1974_heldItem) == 1) {
        func_80074A4C(fighter_gobj, 1, 0);
    }
    func_80074A4C(fighter_gobj, 2, 0);
    ftLink_OnItemDrop(fighter_gobj, arg1);
}
 

void ftLink_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftLink_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter* fp = getFighter(gobj);
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftLink_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftLinkAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x28 *= fp->x34_scale.y;
    }
}

void ftLink_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftLink_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

void ftLink_800EB334(HSD_GObj* fighter_gobj) {
    f32 new_ground_vel;

    Fighter* fp = fighter_gobj->user_data;
    ftLinkAttributes* link_attr = fp->x10C_ftData->ext_attr;

    f32 resultf = func_80092ED8(fp->x19A4, link_attr, link_attr->xD8);
    fp->xEC_ground_vel = resultf * p_ftCommonData->x294;
    if (fp->x19AC < 0.0f) {
        new_ground_vel = fp->xEC_ground_vel;
    } else {
        new_ground_vel = -fp->xEC_ground_vel;
    }
    fp->xEC_ground_vel = new_ground_vel;
    func_80088148(fp, 0x2716AU, 0x7FU, 0x40U);
}
