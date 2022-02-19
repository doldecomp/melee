#include "ftganon.h"

extern float lbl_804D9E58;

void ftGanon_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, -1);
    ft->x2230 = 0;
    ft->x222C = 0;
}

void func_8014EC58(HSD_GObj* gobj, s32 arg1)
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

void func_8014ED38(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014ED80(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_8014EDC8(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void ftGanon_OnLoad(HSD_GObj* gobj)
{
    func_800E2AAC(gobj->user_data);
}

void func_8014EE40(HSD_GObj* gobj)
{
    func_800E2B40(gobj);
}

void func_8014EE60(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 3, lbl_804D9E58);
    ftAnim_ApplyPartAnim(gobj, 4, 3, lbl_804D9E58);
}

void func_8014EEAC(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 2, lbl_804D9E58);
    ftAnim_ApplyPartAnim(gobj, 4, 2, lbl_804D9E58);
}
