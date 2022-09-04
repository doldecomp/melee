#include <melee/ft/chara/ftIceClimber/fticeclimber.h>


void ftIceClimber_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftIceClimber_OnItemInvisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftIceClimber_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftIceClimber_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftIceClimber_OnLoadForNana(Fighter* fp) {
    PUSH_ATTRS(fp, ftIceClimberAttributes);
}

void ftIceClimber_OnLoad(HSD_GObj* fighter_gobj) {

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

void ftIceClimber_OnDeath(HSD_GObj* fighter_gobj) {
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

void ftIceClimber_8011F060(HSD_GObj* fighter_gobj) {
    func_8011F190(fighter_gobj);
    func_80122898(fighter_gobj);
    func_80121164(fighter_gobj);
    func_8011F68C(fighter_gobj);
}

void ftIceClimber_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftIceClimberAttributes);
}

void ftIceClimber_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftIceClimber_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}
