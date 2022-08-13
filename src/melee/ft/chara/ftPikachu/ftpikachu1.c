#include <ftpikachu.h>

void ftPikachu_OnLoadForPichu(Fighter* fp) {
    PUSH_ATTRS(fp, ftPikachuAttributes);
}


void ftPikachu_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftPikachuAttributes);

    {
        ftPikachuAttributes *pika_attr = fp->x2D4_specialAttributes;
        func_8026B3F8(item_list[0], pika_attr->xDC);
        func_8026B3F8(item_list[1], pika_attr->x14);
        func_8026B3F8(item_list[2], pika_attr->x18);
    }

}

void ftPikachu_OnDeath(HSD_GObj* fighterObj) {
    s32 unused[2];
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
}

void ftPikachu_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 0);
}

void ftPikachu_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 0);
}

void ftPikachu_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 0);
}

void ftPikachu_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 0, 0);
}

void ftPikachu_8012467C(HSD_GObj* fighterObj) {
    s32 unused[2];
    func_80074A4C(fighterObj, 1, -1);
    func_80074B0C(fighterObj, 1, 0);
}

void ftPikachu_801246C0(HSD_GObj* fighterObj) {
    s32 unused[2];
    func_80074A4C(fighterObj, 1, 0);
    func_80074B0C(fighterObj, 1, 0);
}


void ftPikachu_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftPikachuAttributes);
    if (fp->x34_scale.y != 1.0f) {
        SCALE_HEIGHT_ATTRS(6); 
    }
}

void ftPikachu_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}


void ftPikachu_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
}