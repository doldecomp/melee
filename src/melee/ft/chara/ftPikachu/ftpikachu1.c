#include <melee/ft/chara/ftPikachu/ftpikachu.h>

void ftPikachu_OnLoadForPichu(Fighter* fp) {
    PUSH_ATTRS(fp, ftPikachuAttributes);
}


void ftPikachu_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftPikachuAttributes);

    {
        ftPikachuAttributes *pika_attr = fp->x2D4_specialAttributes;
        func_8026B3F8(item_list[0], pika_attr->xDC);
        func_8026B3F8(item_list[1], pika_attr->x14);
        func_8026B3F8(item_list[2], pika_attr->x18);
    }

}

void ftPikachu_OnDeath(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    func_80074A4C(fighter_gobj, 0, 0);
    func_80074A4C(fighter_gobj, 1, 0);
}

void ftPikachu_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 0);
}

void ftPikachu_OnItemInvisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 0);
}

void ftPikachu_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 0);
}

void ftPikachu_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftPikachu_8012467C(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    func_80074A4C(fighter_gobj, 1, -1);
    func_80074B0C(fighter_gobj, 1, 0);
}

void ftPikachu_801246C0(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    func_80074A4C(fighter_gobj, 1, 0);
    func_80074B0C(fighter_gobj, 1, 0);
}


void ftPikachu_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftPikachuAttributes);
    if (fp->x34_scale.y != 1.0f) {
        SCALE_HEIGHT_ATTRS(6); 
    }
}

void ftPikachu_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}


void ftPikachu_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}
