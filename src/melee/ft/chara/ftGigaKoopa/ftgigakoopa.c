#include "melee/ft/chara/ftKoopa/ftkoopa.h"
#include "ftgigakoopa.h"

#include <melee/it/id.h>

void ftGKoopa_OnDeath(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* ft = fighterObj->user_data;
    ftKoopaAttributes* koopaAttr = ft->x2D4_specialAttributes;

    func_80074A4C(fighterObj, 0, 0);
    ft->dmg.x18B0 = koopaAttr->x0;
    ft->sa.gkoopa.x222C = koopaAttr->x10;
    ft->sa.gkoopa.x2230 = koopaAttr->x18;
}

#pragma peephole on

void func_8014F698(HSD_GObj* gobj)
{
    func_80132A64(gobj);
}

void ftGKoopa_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    void** items = ftdata->x48_items;

    ftKoopa_OnLoadForGKoopa(ft);
    func_8026B3F8(items[0], It_Kind_KoopaFlame);

    ft->x2226_flag.bits.b1 = 1;
    ft->x222A_flag.bits.b0 = 1;
}

void ftGKoopa_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
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

void func_8014F800(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014F848(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_8014F890(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014F8E4(HSD_GObj* gobj)
{
    func_80132D00(gobj);
}

void func_8014F904(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_8014F948(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_8014F98C(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

// UB warning: this function may use offset uninitialized
s32 func_8014F9A4(s32 arg0)
{
    int offset;
    const s32* ret;

    switch (arg0) {
        case 0xf:
            offset = 0xe;
    }

    return lbl_803D3984[offset - 0xe];
}
