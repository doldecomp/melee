#include "ftdrmario.h"

void func_80149954(HSD_GObj* gobj)
{
    int unused1[3];
    f32 sp18;
    Fighter* ft;
    u32 tmp;
    int unused2[3];

    ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 == 1 && ft->x2240 == 0U) {
        func_8000B1CC(ft->x5E8_fighterBones->x0_joint, 0, &sp18);
        tmp = func_800E0D1C(gobj);
        tmp = func_802C0850(gobj, &sp18, tmp, 0x31, ft->x2C_facing_direction);
        ft->x2240 = tmp;
        if (tmp != 0) {
            ft->x21E4 = (u32) func_80149540;
            ft->x21DC = (u32) func_80149540;
        }
    } else if (ft->x2200_ftcmd_var0 == 2) {
        func_801497CC(gobj);
    }
    if (func_8006F238(gobj) == 0) {
        if (gobj != NULL) {
            ft = gobj->user_data;
            if (ft != NULL && ft->x2240 != 0) {
                func_802C0DBC(ft->x2240);
                ft->x2240 = 0;
            }
        }
        if (gobj != NULL) {
            ft = gobj->user_data;
            if (ft != NULL) {
                ft->x21DC = 0;
                ft->x21E4 = 0;
            }
        }
        func_8008A2BC(gobj);
    }
}

void func_80149A6C(HSD_GObj* gobj)
{
    func_800DED30(gobj);
}

void func_80149A8C(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void func_80149AAC(HSD_GObj* gobj)
{
    func_80084280(gobj);
}
