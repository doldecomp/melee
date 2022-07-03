#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/id.h>

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

    func_8026B3F8(items[0], It_Kind_MarioFireball);
    func_8026B3F8(items[2], sa->x14);
}

void ftMario_func_800E0A00(HSD_GObj* gobj)
{
    ftMario_func_800E1368(gobj);
}

void ftMario_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
{
    s32 result, switched_res, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) {
            case 1:
                func_80070FB4(gobj, 1, 1);
                break;
            case 2:
                func_80070FB4(gobj, 1, 0);
                break;
            case 3:
                func_80070FB4(gobj, 1, 2);
                break;
            case 4:
                func_80070FB4(gobj, 1, 3);
                break;
        }

        if (arg1 != 0) {
            func_80070C48(gobj, 1);
        }
    }
}

void ftMario_func_800E0B00(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void ftMario_func_800E0B48(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void ftMario_func_800E0B90(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
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

void ftMario_func_800E0C24(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftMario_func_800E0C68(HSD_GObj* gobj) {
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
