#include "ftness.h"

extern f32 lbl_804D96B0;

void func_801147C0(HSD_GObj* gobj, s32 arg1)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x2240 = 0;
    ft->x2244 = 0;
    ft->x2248 = 0;
    ft->x222C = 0;
    ft->x224C = 0;
}

void ftNess_OnLoad(HSD_GObj* gobj)
{

}

void func_801148F8(HSD_GObj* gobj)
{

}

void func_8011493C(HSD_GObj* gobj)
{
    func_8011B0F8(gobj);
}

f32 func_8011495C(Fighter* ft)
{
    return ((ftNessAttributes*)ft->x2D4_specialAttributes)->unk94;
}

void func_80114968(HSD_GObj* gobj)
{
    
}

void func_80114A48(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == NULL) {
        func_80070CC4(gobj, 1);
    }
}

void func_80114A90(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == NULL) {
        func_80070C48(gobj, 1);
    }
}

void func_80114AD8(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80114B2C(HSD_GObj* gobj)
{
    
}

void func_80114B6C(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, lbl_804D96B0);
    func_800704F0(gobj, 0, lbl_804D96B0);
}
