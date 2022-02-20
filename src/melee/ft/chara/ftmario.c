#include "ftmario.h"

extern void func_800E1368(void);
extern const f32 lbl_804D9190;
extern const f32 lbl_804D9194;
extern s32 lbl_803C5A20[];

void ftMario_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x222C = 9;
    ft->x2230 = 9;
    ft->x2234 = 0;
    ft->x2238 = 0;
    ft->x223C = 0;
    ft->x2240 = 0;
}

void func_800E0920(Fighter* ft) {
    ftMarioAttributes* sA2 = (ftMarioAttributes*)ft->x2D8_specialAttributes2;
    ftMarioAttributes* ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    ft->x2D4_specialAttributes = sA2;
}

void ftMario_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes *sA, *sA2, *ext_attr;
    Fighter* ft;
    
    ft = (Fighter*)gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    items = ftDataInfo->x48_items;

    ft->x2224_flag.bits.b7 = 1;
   
    sA2 = (ftMarioAttributes*)ft->x2D8_specialAttributes2;
    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;

    *sA2 = *ext_attr;

    (ftMarioAttributes*)ft->x2D4_specialAttributes = sA2;

    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;    

    func_8026B3F8(items[0], 0x30);
    func_8026B3F8(items[2], sA->x14);
}

void func_800E0A00(void)
{
    func_800E1368();
}

void func_800E0A20(HSD_GObj* gobj, s32 arg1) {
    s32 switched_res, result, unused;

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

void func_800E0B00(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E0B48(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_800E0B90(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E0BE4(HSD_GObj* gobj) {
    Fighter* ft;
    ftData* ftDataInfo;
    ftMarioAttributes *sA, *ext_attr;

    ft = gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    
    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    *sA = *ext_attr;
    
}

void func_800E0C24(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, lbl_804D9190);
    func_800704F0(gobj, 0, lbl_804D9190);
}

void func_800E0C68(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, lbl_804D9194);
    func_800704F0(gobj, 0, lbl_804D9194);
}

void func_800E0CAC(s32 arg0, u32* arg1, u32* arg2) {
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

s32 func_800E0CE0(s32 arg0) {
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
