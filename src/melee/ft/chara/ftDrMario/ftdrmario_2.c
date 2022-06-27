#include "ftdrmario.h"

void func_80149954(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* ft;
    u32 tmp;
    int unused2[3];

    ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 == 1 && ft->sa.mario.x2240 == 0U) {
        func_8000B1CC(ft->x5E8_fighterBones->x0_jobj, 0, &sp18);
        tmp = ftMario_func_800E0D1C(gobj);
        tmp = func_802C0850(gobj, &sp18, tmp, 0x31, ft->x2C_facing_direction);
        ft->sa.mario.x2240 = tmp;
        if (tmp != 0) {
            ft->cb.x21E4_callback_OnDeath2 = func_80149540;
            ft->cb.x21DC_callback_OnTakeDamage = func_80149540;
        }
    } else if (ft->x2200_ftcmd_var0 == 2) {
        func_801497CC(gobj);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (gobj != NULL) {
            ft = gobj->user_data;
            if (ft != NULL && ft->sa.mario.x2240 != 0) {
                func_802C0DBC(ft->sa.mario.x2240);
                ft->sa.mario.x2240 = 0;
            }
        }
        if (gobj != NULL) {
            ft = gobj->user_data;
            if (ft != NULL) {
                ft->cb.x21DC_callback_OnTakeDamage = 0;
                ft->cb.x21E4_callback_OnDeath2 = 0;
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
