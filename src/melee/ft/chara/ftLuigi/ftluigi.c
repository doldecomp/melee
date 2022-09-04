#include <melee/ft/chara/ftLuigi/ftluigi.h>

void ftLuigi_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    func_80074A4C(fighter_gobj, 0, 0);
    fp->sa.luigi.x2234 = 0;
}

void ftLuigi_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftLuigiAttributes);
    
    func_8026B3F8(item_list[0], It_Kind_Luigi_Fire);
}

void ftLuigi_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftLuigi_OnItemInvisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftLuigi_OnItemVisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftLuigi_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 1, 1);
}

void ftLuigi_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftLuigiAttributes);
}


void ftLuigi_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftLuigi_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

void ftLuigi_8014260C(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 != 0xA) {
        if (arg0 < 0xA && arg0 >= 9) {
            *arg2 = 0xE;
            *arg1 = 0xE;
        }
    } else {
        *arg2 = 0xF;
        *arg1 = 0xF;
    }
}

extern struct DemoMotionFiles lbl_803D0AAC;

// 0x80142640 
// https://decomp.me/scratch/vH9VM // Get symbol pointers for Luigi cutscenes
void* func_80142640(s32 demoMotionArg)
{
    s32 demoFile;

    switch (demoMotionArg)
    {
    case 0x9:
        demoFile = 14;
        break;
    case 0xA:
        demoFile = 15;
        break;
    }
    return lbl_803D0AAC.x0_demoMotionPtr[demoFile - 14];
}
