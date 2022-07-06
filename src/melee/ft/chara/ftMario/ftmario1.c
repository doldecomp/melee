#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

extern s32 lbl_803C5A20[];

void ftMario_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    func_80074A4C(gobj, 0, 0);
    ft->sa.mario.x222C = 9;
    ft->sa.mario.x2230 = 9;
    ft->sa.mario.x2234 = 0;
    ft->sa.mario.x2238 = 0;
    ft->sa.mario.x223C = NULL;
    ft->sa.mario.x2240 = 0;
}

void ftMario_OnLoadForDrMario(Fighter* ft) {
	PUSH_ATTRS(ft, ftMarioAttributes);
}

void ftMario_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes *sa;
    Fighter* ft = gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    items = ftDataInfo->x48_items;

    ft->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(ft, ftMarioAttributes);

    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    func_8026B3F8(items[0], It_Kind_Mario_Fire);
    func_8026B3F8(items[2], sa->x14);
}

void ftMario_func_800E0A00(HSD_GObj* gobj)
{
    ftMario_func_800E1368(gobj);
}

void ftMario_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftMario_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 1);
}

void ftMario_OnItemVisible(HSD_GObj* gobj) {
    Fighter_OnItemVisible(gobj, 1);
}

void ftMario_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftMario_func_800E0BE4(HSD_GObj* gobj) {
    Fighter* ft;
    ftData* ftDataInfo;
    ftMarioAttributes *sa, *ext_attr;

    ft = getFighter(gobj);
    ftDataInfo = ft->x10C_ftData;

    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    *sa = *ext_attr;
}

void ftMario_OnKnockbackEnter(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftMario_OnKnockbackExit(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void ftMario_func_800E0CAC(s32 arg0, u32* arg1, u32* arg2) {
    if (arg0 != 10) {
        if (arg0 >= 10)
            return;
        if (arg0 < 9)
            return;
        *arg2 = 0xe;
        *arg1 = 0xe;
    } else {
        *arg2 = 0xf;
        *arg1 = 0xf;
    }
}

s32 ftMario_func_800E0CE0(s32 arg0) {
    int offset;

    switch (arg0) {
        case 9:
            offset = 0xe;
            break;
        case 10:
            offset = 0xf;
    }

    return lbl_803C5A20[offset - 0xe];
}
