#include <ftluigi.h>

void ftLuigi_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    fp->sa.luigi.x2234 = 0;
}

void ftLuigi_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    PUSH_ATTRS(fp, ftLuigiAttributes);
    
    func_8026B3F8(item_list[0], It_Kind_Luigi_Fire);
}

void ftLuigi_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftLuigi_OnItemInvisible(HSD_GObj* fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftLuigi_OnItemVisible(HSD_GObj* fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftLuigi_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}

void ftLuigi_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftLuigiAttributes);
}


void ftLuigi_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}

void ftLuigi_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
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
